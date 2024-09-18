#include "ChaosRace.h"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/Enhancements/nametag.h"
#include "soh/Enhancements/randomizer/3drando/random.hpp"
#include "soh/Enhancements/enemyrandomizer.h"

#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"
#include "objects/object_gi_stick/object_gi_stick.h"
#include "objects/object_gi_map/object_gi_map.h"
#include "objects/object_bombiwa/object_bombiwa.h"
#include "overlays/actors/ovl_En_Ik/z_en_ik.h"

extern "C" {
#include <z64.h>
#include "variables.h"
#include "functions.h"
#include "macros.h"
PlayState* gPlayState;
}

typedef enum {
    LINK_PROP_DEFAULT,
    LINK_PROP_POT,
    LINK_PROP_GRASS,
    LINK_PROP_STICK,
    LINK_PROP_AGONY,
    LINK_PROP_BOULDER,
} GILinkProp;

uint8_t PlayerProp = LINK_PROP_DEFAULT;
uint32_t flippedWorldTimer = 0;
uint32_t ledgeGrabTimer = 0;

static std::string cuccoNames[CUCCO_NAME_TABLE_SIZE] = {
    "Cluckey_9",
    "AGreenCock",
    "alwayzcluckingirl",
    "Cockadius",
    "dblcock",
    "Obsydycluck",
    "cluckigun94",
    "CaptainCockles",
    "CardinalCluck",
    "cardinalcluck",
    "Frankie The Cock",
    "ItsCluckinPat",
    "CockingJxL",
    "Cockomato",
    "Cocklar21",
    "ITS GOOSIN TIME",
    "PapaCock",
    "CluckySaw",
    "CluckCloud",
    "ChickenTMH",
    "CuckiCrash",
    "SaltyCock",
    "StampedingCuckster",
    "CockySnub",
    "CocktunTTV",
    "ClucklitxShadows",
    "GriddyCock",
};

uint32_t ChaosRace_MinutesToTicks(uint32_t minutes) {
    return minutes * 20 * 60;
}

Vec3f ChaosRace_GetCircleAroundPlayerOffset(uint16_t index) {
    Vec3f posOffset;
    posOffset.x = 0;
    posOffset.y = 50;
    posOffset.z = 0;

    // offset in a circle around player
    switch (index) {
        case 0:
            posOffset.x = -100;
            break;
        case 1:
            posOffset.x = -75;
            posOffset.z = 75;
            break;
        case 2:
            posOffset.z = 100;
            break;
        case 3:
            posOffset.x = 75;
            posOffset.z = 75;
            break;
        case 4:
            posOffset.x = 100;
            break;
        case 5:
            posOffset.x = 75;
            posOffset.z = -75;
            break;
        case 6:
            posOffset.z = -100;
            break;
        case 7:
            posOffset.x = -75;
            posOffset.z = -75;
            break;
        default:
            break;
    }

    return posOffset;
}

Actor* ChaosRace_SpawnEnemy(int16_t actorId, int16_t params, uint8_t enemyIndex, f32 posX, f32 posY, f32 posZ) {
    Vec3f posOffset = ChaosRace_GetCircleAroundPlayerOffset(enemyIndex);

    // Raycast to place enemy on the ground
    CollisionPoly poly;
    Vec3f finalPos;
    finalPos.x = posX + posOffset.x;
    finalPos.y = posY + posOffset.y;
    finalPos.z = posZ + posOffset.z;
    f32 raycastResult = BgCheck_AnyRaycastFloor1(&gPlayState->colCtx, &poly, &finalPos);
    if (raycastResult > BGCHECK_Y_MIN) {
        finalPos.y = raycastResult;
    }

    return Actor_Spawn(&gPlayState->actorCtx, gPlayState, actorId, finalPos.x, finalPos.y, finalPos.z, 0, 0, 0, params,
                       0);
}

void ChaosRace_SpawnCuccoInvasion() {
    if (!GameInteractor::IsSaveLoaded() || GameInteractor::IsGameplayPaused())
        return;

    uint32_t randomNumber;
    Player* player = GET_PLAYER(gPlayState);
    std::string nameTag = "The Cock";

    for (uint8_t i = 0; i < 8; i++) {
        randomNumber = Random(0, CUCCO_NAME_TABLE_SIZE);
        nameTag = cuccoNames[randomNumber];
        Actor* actor = ChaosRace_SpawnEnemy(ACTOR_EN_NIW, 0, i, player->actor.world.pos.x, player->actor.world.pos.y,
                                            player->actor.world.pos.z);

        if (actor != NULL) {
            NameTag_RegisterForActor(actor, nameTag.c_str());
        }
    }
}

void ChaosRace_SpawnIronKnuckleInvasion() {
    if (!GameInteractor::IsSaveLoaded() || GameInteractor::IsGameplayPaused())
        return;

    Player* player = GET_PLAYER(gPlayState);
    std::string nameTag = "FRIEND";

    for (uint8_t i = 0; i < 8; i++) {
        Actor* actor = ChaosRace_SpawnEnemy(ACTOR_EN_IK, 2, i, player->actor.world.pos.x, player->actor.world.pos.y,
                                            player->actor.world.pos.z);
        if (actor != NULL) {
            Actor_ChangeCategory(gPlayState, &gPlayState->actorCtx, actor, ACTORCAT_NPC);
            NameTag_RegisterForActor(actor, nameTag.c_str());
            EnIk* knuckleActor = (EnIk*)actor;
            knuckleActor->skelAnime.playSpeed = 1.0f;
        }
    }
}

void ChaosRace_SpawnRandomEnemyInvasion() {
    if (!GameInteractor::IsSaveLoaded() || GameInteractor::IsGameplayPaused())
        return;

    Player* player = GET_PLAYER(gPlayState);

    for (uint8_t i = 0; i < 8; i++) {
        uint32_t seed = rand() % 20000;
        EnemyEntry enemyToSpawn = GetRandomizedEnemyEntry(seed);

        Actor* actor = ChaosRace_SpawnEnemy(enemyToSpawn.id, enemyToSpawn.params, i, player->actor.world.pos.x,
                                            player->actor.world.pos.y,
                                            player->actor.world.pos.z);
        if (actor != NULL) {
            Actor_ChangeCategory(gPlayState, &gPlayState->actorCtx, actor, ACTORCAT_NPC);
        }
    }
}

void ChaosRace_DrawLinkProp() {
    if (PlayerProp) {
        const char* PropDL = gPotDL;
        float scale = 1.0f;
        float translateY = 0.0f;

        switch (PlayerProp) {
            case LINK_PROP_POT:
                PropDL = gPotDL;
                scale = 15.0f;
                break;
            case LINK_PROP_GRASS:
                PropDL = gFieldBushDL;
                scale = 45.0f;
                break;
            case LINK_PROP_STICK:
                PropDL = gGiStickDL;
                scale = 45.0f;
                translateY = 40.0f;
                break;
            case LINK_PROP_AGONY:
                PropDL = gGiStoneOfAgonyDL;
                scale = 45.0f;
                translateY = 40.0f;
                break;
            case LINK_PROP_BOULDER:
                PropDL = object_bombiwa_DL_0009E0;
                scale = 7.0f;
                break;
            default:
                break;
        }

        Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
        Matrix_Translate(0, translateY, 0, MTXMODE_APPLY);
        Gfx_DrawDListOpa(gPlayState, (Gfx*)PropDL);
    }
}

void ChaosRace_ChangePlayerIntoProp() {
    uint32_t randomNumber = rand();
    GameInteractor::State::InvisibleLinkActive = true;

    switch (randomNumber % 20) { 
        case LINK_PROP_POT:
            PlayerProp = LINK_PROP_POT;
            break;
        case LINK_PROP_GRASS:
            PlayerProp = LINK_PROP_GRASS;
            break;
        case LINK_PROP_STICK:
            PlayerProp = LINK_PROP_STICK;
            break;
        case LINK_PROP_AGONY:
            PlayerProp = LINK_PROP_AGONY;
            break;
        case LINK_PROP_BOULDER:
            PlayerProp = LINK_PROP_BOULDER;
            break;
        default:
            GameInteractor::State::InvisibleLinkActive = false;
            PlayerProp = LINK_PROP_DEFAULT;
    }
}

void ChaosRace_DrawNothing() {
    return;
}

void ChaosRace_ChangeConsumableDraw(void* actorRef) {
    Actor* actor = static_cast<Actor*>(actorRef);

    if (actor->id == ACTOR_EN_ITEM00) {
        actor->draw = (ActorFunc)ChaosRace_DrawNothing;
    }
}

void ChaosRace_OnItemUse(int32_t item) {
    if (item == ITEM_BOMB || item == ITEM_BOMBCHU) {
        GameInteractor::RawAction::SpawnActor(ACTOR_EN_BOM, 0);
    }

    if (item == ITEM_HOOKSHOT || item == ITEM_LONGSHOT) {
        Player* player = GET_PLAYER(gPlayState);
        Actor* actor = Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_FIREFLY, player->actor.world.pos.x,
                    player->actor.world.pos.y + 100, player->actor.world.pos.z + 120, 0, 0, 0, 2, 0);
        if (actor != NULL) {
            Actor_ChangeCategory(gPlayState, &gPlayState->actorCtx, actor, ACTORCAT_NPC);
        }
    }
}

void ChaosRace_ToggleIcePhysics(int16_t scene) {
    if (scene == SCENE_FIRE_TEMPLE || scene == SCENE_FIRE_TEMPLE_BOSS || scene == SCENE_WATER_TEMPLE_BOSS) {
        GameInteractor::State::SlipperyFloorActive = 1;
    } else {
        GameInteractor::State::SlipperyFloorActive = 0;
    }
}

void ChaosRace_HandleTriggers() {
    if (!GameInteractor::IsSaveLoaded()) {
        return;
    }

    Player* player = GET_PLAYER(gPlayState);
    uint32_t randomNumber;

    // Spawn Cucco Invasion (average once every 5 minutes)
    randomNumber = rand();
    if (randomNumber % ChaosRace_MinutesToTicks(5) == 1) {
        ChaosRace_SpawnCuccoInvasion();
    }

    // Spawn Iron Knuckle Invasion (average once every 15 minutes)
    randomNumber = rand();
    if (randomNumber % ChaosRace_MinutesToTicks(15) == 1) {
        ChaosRace_SpawnIronKnuckleInvasion();
    }

    // Spawn Random Enemy Invasion (average once every 3 minutes)
    randomNumber = rand();
    if (randomNumber % ChaosRace_MinutesToTicks(3) == 1) {
        ChaosRace_SpawnRandomEnemyInvasion();
    }

    // Random age change (average once every 60 minutes)
    randomNumber = rand();
    if (randomNumber % ChaosRace_MinutesToTicks(60) == 1) {
        CVarSetInteger("gSwitchAge", 1);
    }

    // Process queued effects
    if (GameInteractor::IsSaveLoaded() && !GameInteractor::IsGameplayPaused()) {

        // Knockback after reading a gossip stone
        if (GameInteractor::State::LinkKnockbackQueued) {
            GameInteractor::State::LinkKnockbackQueued = 0;
            GameInteractor::RawAction::KnockbackPlayer(5.0f);
        }
    }

    // Rotate link on wearing bunny hood
    if (player->currentMask == PLAYER_MASK_BUNNY) {
        player->actor.shape.rot.x += 500;
        player->actor.shape.rot.y += 500;
    }

    // Enable vertically switched world randomly (average once every 30 minutes)
    randomNumber = rand();
    if (randomNumber % ChaosRace_MinutesToTicks(30) == 1) {
        flippedWorldTimer = ChaosRace_MinutesToTicks(1);
    }
    if (flippedWorldTimer) {
        flippedWorldTimer--;
        if (!CVarGetInteger("gMirroredWorld", 0)) {
            CVarSetInteger("gMirroredWorld", 1);
        }
    } else {
        if (CVarGetInteger("gMirroredWorld", 0)) {
            CVarSetInteger("gMirroredWorld", 0);
        }
    }

    // Randomly enable Disable Ledge Grabs for 10 seconds (average once every minute)
    randomNumber = rand();
    if (randomNumber % ChaosRace_MinutesToTicks(1) == 1) {
        // 20 ticks * 10 seconds
        ledgeGrabTimer = 200;
    }
    if (ledgeGrabTimer) {
        ledgeGrabTimer--;
        GameInteractor::State::DisableLedgeGrabsActive = 1;
    } else {
        GameInteractor::State::DisableLedgeGrabsActive = 0;
    }

    // If paused, chance to automatically unpause (average after a second)
    if (gPlayState->pauseCtx.state != 0) {
        randomNumber = rand();
        if (randomNumber % 20) {
            GameInteractor::State::EmulatedButtons |= BTN_START;
        }
    }
}

void RegisterChaosRace() {
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnGameFrameUpdate>([]() {
        ChaosRace_HandleTriggers();
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneSpawnActors>([]() { 
        ChaosRace_ChangePlayerIntoProp();
    });
    
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnActorInit>([](void* actorRef) { 
        ChaosRace_ChangeConsumableDraw(actorRef);
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerItemUse>([](int32_t item) { 
        ChaosRace_OnItemUse(item);
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerDraw>([]() {
        ChaosRace_DrawLinkProp();
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneInit>([](int16_t sceneNum) {
        ChaosRace_ToggleIcePhysics(sceneNum);
    });
}
