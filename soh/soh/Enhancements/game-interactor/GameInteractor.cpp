#include "GameInteractor.h"
#include <libultraship/bridge.h>

extern "C" {
#include "variables.h"
#include "macros.h"
#include "functions.h"
extern PlayState* gPlayState;
}

#include "overlays/actors/ovl_En_Niw/z_en_niw.h"

GameInteractionEffectQueryResult GameInteractor::CanApplyEffect(GameInteractionEffectBase* effect) {
    return effect->CanBeApplied();
}

void GameInteractor::ApplyEffect(GameInteractionEffectBase* effect) {
    return effect->Apply();
}

void GameInteractor::RemoveEffect(GameInteractionEffectBase* effect) {
    return effect->Remove();
}

bool GameInteractor::IsSaveLoaded() {
    Player* player = GET_PLAYER(gPlayState);
    return (gPlayState == NULL || player == NULL || gSaveContext.fileNum < 0 || gSaveContext.fileNum > 2) ? false : true;
}

bool GameInteractor::IsGameplayPaused() {
    Player* player = GET_PLAYER(gPlayState);
    return (Player_InBlockingCsMode(gPlayState, player) || gPlayState->pauseCtx.state != 0 || gPlayState->msgCtx.msgMode != 0) ? true : false;
}

void GameInteractor::AddOrRemoveHealthContainers(int32_t amount) {
    gSaveContext.healthCapacity += amount * 0x10;
}

void GameInteractor::AddOrRemoveMagic(int32_t amount) {
    // Full single magic = 48
    // Full double magic = 96
    int32_t currentMagicCapacity = (gSaveContext.isDoubleMagicAcquired + 1) * 48;

    if (gSaveContext.isMagicAcquired) {
        gSaveContext.prevMagicState = gSaveContext.magicState;
        if (amount > 0) {
            if (gSaveContext.magic + amount > currentMagicCapacity) {
                gSaveContext.magicFillTarget = currentMagicCapacity;
            } else {
                gSaveContext.magicFillTarget = gSaveContext.magic + amount;
            }
            gSaveContext.magicState = MAGIC_STATE_FILL;
        } else if (amount < 0) {
            if (gSaveContext.magic + amount < 0) {
                gSaveContext.magic = 0;
            } else {
                gSaveContext.magic += amount;
            }
        }
    }
}

void GameInteractor::HealOrDamagePlayer(int32_t hearts) {
    if (hearts > 0) {
        Health_ChangeBy(gPlayState, hearts * 0x10);
    } else if (hearts < 0) {
        Player* player = GET_PLAYER(gPlayState);
        Health_ChangeBy(gPlayState, hearts * 0x10);
        func_80837C0C(gPlayState, player, 0, 0, 0, 0, 0);
        player->invincibilityTimer = 28;
    }
}

void GameInteractor::SetPacifistMode(uint8_t effectState) {
    GameInteractor_PacifistModeActive = effectState;
    // Force interface update to update the button's transparency.
    gSaveContext.unk_13E8 = 50;
    Interface_Update(gPlayState);
}

void GameInteractor::SetWeatherStorm(uint8_t effectState) {
    if (effectState) {
        gPlayState->envCtx.unk_F2[0] = 20;    // rain intensity target
        gPlayState->envCtx.gloomySkyMode = 1; // start gloomy sky
        if ((gWeatherMode != 0) || gPlayState->envCtx.unk_17 != 0) {
            gPlayState->envCtx.unk_DE = 1;
        }
        gPlayState->envCtx.lightningMode = LIGHTNING_MODE_ON;
        Environment_PlayStormNatureAmbience(gPlayState);
    } else {
        gPlayState->envCtx.unk_F2[0] = 0;
        if (gPlayState->csCtx.state == CS_STATE_IDLE) {
            Environment_StopStormNatureAmbience(gPlayState);
        } else if (func_800FA0B4(SEQ_PLAYER_BGM_MAIN) == NA_BGM_NATURE_AMBIENCE) {
            Audio_SetNatureAmbienceChannelIO(NATURE_CHANNEL_LIGHTNING, CHANNEL_IO_PORT_1, 0);
            Audio_SetNatureAmbienceChannelIO(NATURE_CHANNEL_RAIN, CHANNEL_IO_PORT_1, 0);
        }
        osSyncPrintf("\n\n\nE_wether_flg=[%d]", gWeatherMode);
        osSyncPrintf("\nrain_evt_trg=[%d]\n\n", gPlayState->envCtx.gloomySkyMode);
        if (gWeatherMode == 0 && (gPlayState->envCtx.gloomySkyMode == 1)) {
            gPlayState->envCtx.gloomySkyMode = 2; // end gloomy sky
        } else {
            gPlayState->envCtx.gloomySkyMode = 0;
            gPlayState->envCtx.unk_DE = 0;
        }
        gPlayState->envCtx.lightningMode = LIGHTNING_MODE_LAST;
    }
}

void GameInteractor::ForceEquipBoots(uint8_t boots) {
    Player* player = GET_PLAYER(gPlayState);
    player->currentBoots = boots;
    Inventory_ChangeEquipment(EQUIP_BOOTS, boots + 1);
    Player_SetBootData(gPlayState, player);
}

void GameInteractor::FreezePlayer() {
    gSaveContext.pendingIceTrapCount++;
}

void GameInteractor::BurnPlayer() {
    Player* player = GET_PLAYER(gPlayState);
    for (int i = 0; i < 18; i++) {
        player->flameTimers[i] = Rand_S16Offset(0, 200);
    }
    player->isBurning = true;
    func_80837C0C(gPlayState, player, 0, 0, 0, 0, 0);
}

void GameInteractor::ElectrocutePlayer() {
    Player* player = GET_PLAYER(gPlayState);
    func_80837C0C(gPlayState, player, 4, 0, 0, 0, 0);
}

void GameInteractor::KnockbackPlayer(uint8_t strength) {
    Player* player = GET_PLAYER(gPlayState);
    func_8002F71C(gPlayState, &player->actor, strength * 5, player->actor.world.rot.y + 0x8000, strength * 5);
}

void GameInteractor::GiveDekuShield() {
    // Give Deku Shield to the player, and automatically equip it when they're child and have no shield currently equiped.
    Player* player = GET_PLAYER(gPlayState);
    Item_Give(gPlayState, ITEM_SHIELD_DEKU);
    if (LINK_IS_CHILD && player->currentShield == PLAYER_SHIELD_NONE) {
        player->currentShield = PLAYER_SHIELD_DEKU;
        Inventory_ChangeEquipment(EQUIP_SHIELD, PLAYER_SHIELD_DEKU);
    }
}

void GameInteractor::SpawnCuccoStorm() {
    Player* player = GET_PLAYER(gPlayState);
    EnNiw* cucco = (EnNiw*)Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_NIW, player->actor.world.pos.x,
                                       player->actor.world.pos.y + 2200, player->actor.world.pos.z, 0, 0, 0, 0, 0);
    cucco->actionFunc = func_80AB70A0_nocutscene;
}

uint8_t GameInteractor::SpawnEnemyWithOffset(uint32_t enemyId, int32_t enemyParams) {
    Player* player = GET_PLAYER(gPlayState);

    float posXOffset = 0;
    float posYOffset = 0;
    float posZOffset = 0;

    if (enemyId == ACTOR_EN_WALLMAS) {
        
    } else if (enemyId == ACTOR_EN_CLEAR_TAG) {
        // Don't allow Arwings in certain areas because they cause issues.
        // Locations: King dodongo room, Morpha room, Twinrova room, Ganondorf room, Fishing pond, Ganon's room
        // TODO: Swap this to disabling the option in CC options menu instead.
        if (gPlayState->sceneNum == SCENE_DDAN_BOSS || gPlayState->sceneNum == SCENE_MIZUSIN_BS ||
            gPlayState->sceneNum == SCENE_JYASINBOSS || gPlayState->sceneNum == SCENE_GANON_BOSS ||
            gPlayState->sceneNum == SCENE_TURIBORI || gPlayState->sceneNum == SCENE_GANON_DEMO) {
            return 0;
        }
        posYOffset = 100;
    } else if (enemyId == ACTOR_EN_TORCH2) {
        posXOffset = 75;
        posYOffset = 50;
    } else if (enemyId == ACTOR_EN_TEST) {
        posXOffset = 75;
        posYOffset = 50;
    } else if (enemyId == ACTOR_EN_WF) {
        posXOffset = 75;
        posYOffset = 50;
    } else if (enemyId == ACTOR_EN_FZ) {
        posXOffset = 75;
        posYOffset = 50;
    } else if (enemyId == ACTOR_EN_FIREFLY) {
        posXOffset = 75;
        posYOffset = 50;
    } else if (enemyId == ACTOR_EN_TITE) {
        posXOffset = 75;
        posYOffset = 50;
    } else if (enemyId == ACTOR_EN_RR) {
        posXOffset = 75;
        posYOffset = 50;
    }

    if (Actor_Spawn(&gPlayState->actorCtx, gPlayState, enemyId, player->actor.world.pos.x + posXOffset,
        player->actor.world.pos.y + posYOffset, player->actor.world.pos.z + posZOffset, 0, 0, 0,
        enemyParams, 0) != NULL) {
        return 1;
    }

    return 0;

}
