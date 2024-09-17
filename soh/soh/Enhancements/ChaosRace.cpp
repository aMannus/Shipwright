#include "ChaosRace.h"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/Enhancements/nametag.h"
#include "soh/Enhancements/randomizer/3drando/random.hpp"

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
    "Melcuck",
    "ITS GOOSIN TIME",
    "PapaCock",
    "CluckySaw",
    "CluckCloud",
    "ChickenTMH",
    "CuckiCrash",
    "SaltyCock",
    "StampedingCuckster",
    "CockySnub",
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
            posOffset.x = 0;
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

void ChaosRace_SpawnCuccoInvasion() {
    if (!GameInteractor::IsSaveLoaded() || GameInteractor::IsGameplayPaused())
        return;

    uint32_t randomNumber;
    Player* player = GET_PLAYER(gPlayState);
    std::string nameTag = "The Cock";
    Vec3f pos;
    pos.x = player->actor.world.pos.x;
    pos.y = player->actor.world.pos.y;
    pos.z = player->actor.world.pos.z;

    for (uint8_t i = 0; i < 8; i++) {
        Vec3f posOffset = ChaosRace_GetCircleAroundPlayerOffset(i);
        randomNumber = Random(0, CUCCO_NAME_TABLE_SIZE);
        nameTag = cuccoNames[randomNumber];

        Actor* actor = Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_NIW, pos.x + posOffset.x,
                                   pos.y + posOffset.y,
                                   pos.z + posOffset.z, 0, 0, 0, 0, 0);
        NameTag_RegisterForActor(actor, nameTag.c_str());
    }
}

void ChaosRace_SpawnIronKnuckleInvasion() {
    if (!GameInteractor::IsSaveLoaded() || GameInteractor::IsGameplayPaused())
        return;

    Player* player = GET_PLAYER(gPlayState);
    std::string nameTag = "FRIEND";
    Vec3f pos;
    pos.x = player->actor.world.pos.x;
    pos.y = player->actor.world.pos.y;
    pos.z = player->actor.world.pos.z;

    for (uint8_t i = 0; i < 8; i++) {
        Vec3f posOffset = ChaosRace_GetCircleAroundPlayerOffset(i);

        Actor* actor = Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_IK, pos.x + posOffset.x,
                                   pos.y + posOffset.y, pos.z + posOffset.z, 0, 0, 0, 2, 0);
        Actor_ChangeCategory(gPlayState, &gPlayState->actorCtx, actor, ACTORCAT_NPC);
        NameTag_RegisterForActor(actor, nameTag.c_str());
        EnIk* knuckleActor = (EnIk*)actor;
        knuckleActor->skelAnime.playSpeed = 1.0f;
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

void ChaosRace_HandleTriggers() {
    Player* player = GET_PLAYER(gPlayState);
    uint32_t randomNumber;

    // Spawn Cucco Invasion (average once every 10 minutes)
    randomNumber = rand();
    if (randomNumber % ChaosRace_MinutesToTicks(10) == 1) {
        ChaosRace_SpawnCuccoInvasion();
    }

    // Spawn Iron Knuckle Invasion (average once every 30 minutes)
    randomNumber = rand();
    if (randomNumber % ChaosRace_MinutesToTicks(30) == 1) {
        ChaosRace_SpawnIronKnuckleInvasion();
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
}

void RegisterChaosRace() {
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerUpdate>([]() {
        ChaosRace_HandleTriggers();
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneSpawnActors>([]() { 
        ChaosRace_ChangePlayerIntoProp();
    });
    
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnActorInit>([](void* refActor) {
        
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerDraw>([]() {
        ChaosRace_DrawLinkProp();
    });
}
