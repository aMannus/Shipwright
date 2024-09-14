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

extern "C" {
#include <z64.h>
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
uint32_t randomCuccoStormTimer = 0;

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

void ChaosRace_HandleTriggers() {
    uint32_t randomNumber;

    // Enable harmless cucco storm (average every 5 minutes)
    randomNumber = rand();
    if (randomNumber % 6000 == 0) {
        randomCuccoStormTimer = 200;
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

void ChaosRace_HarmlessCuccoStorm() {
    if (!GameInteractor::IsSaveLoaded() || GameInteractor::IsGameplayPaused())
        return;

    if (randomCuccoStormTimer) {
        randomCuccoStormTimer--;

        uint32_t randomNumber = rand();
        if (randomNumber % 10 == 0) {
            Player* player = GET_PLAYER(gPlayState);
            std::string nameTag = "The Cock";
            Vec3f pos;
            pos.x = player->actor.world.pos.x;
            pos.y = player->actor.world.pos.y;
            pos.z = player->actor.world.pos.z;

            randomNumber = Random(0, CUCCO_NAME_TABLE_SIZE);
            nameTag = cuccoNames[randomNumber];

            Actor* actor =
                Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_ATTACK_NIW, pos.x, pos.y, pos.z, 0, 0, 0, 0, 0);
            NameTag_RegisterForActor(actor, nameTag.c_str());
            Actor_ChangeCategory(gPlayState, &gPlayState->actorCtx, actor, ACTORCAT_NPC);
        }
    }
}

void RegisterChaosRace() {
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnGameFrameUpdate>([]() {
        ChaosRace_HandleTriggers();
        ChaosRace_HarmlessCuccoStorm();
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnSceneSpawnActors>([]() { 
        ChaosRace_ChangePlayerIntoProp();
    });
    
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnActorInit>([](void* refActor) {
        
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnActorUpdate>([](void* refActor) {
        
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerDraw>([]() {
        ChaosRace_DrawLinkProp();
    });
}
