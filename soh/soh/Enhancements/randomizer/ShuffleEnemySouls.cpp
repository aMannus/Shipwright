#include "soh/OTRGlobals.h"
#include "static_data.h"

extern "C" {
#include "functions.h"
#include "variables.h"
extern PlayState* gPlayState;
}

// clang-format off
std::unordered_map<int16_t, RandomizerInf> enemySoulMap = {
    // Flying Pot souls are excluded, as those actors are programmed to die to any collision, not just the
    // damaging type. We don't have a good answer for what behavior those should follow if the hit something.
    { ACTOR_EN_TITE,          RAND_INF_HAS_SOUL_TEKTITE },
};
// clang-format on

bool HaveEnemySoul(ActorID enemyId) {
    auto findSoulFlag = enemySoulMap.find(enemyId);
    if (findSoulFlag != enemySoulMap.end()) {
        RandomizerInf soulRandomizerInf = findSoulFlag->second;
        return Flags_GetRandomizerInf(soulRandomizerInf);
    }
    // Enemy soul does not exist, so act as if it is obtained
    return true;
}

extern "C" void ShuffleEnemySouls_DrawGrayscaledEnemy(Actor* actor) {
    OPEN_DISPS(gPlayState->state.gfxCtx);
    gDPSetGrayscaleColor(POLY_OPA_DISP++, 70, 70, 70, 255);
    gSPGrayscale(POLY_OPA_DISP++, true);
    actor->draw(actor, gPlayState);
    gSPGrayscale(POLY_OPA_DISP++, false);
    CLOSE_DISPS(gPlayState->state.gfxCtx);
}

void RegisterShuffleEnemySouls() {
    bool shouldRegister = IS_RANDO /*&& RAND_GET_OPTION(RSK_SHUFFLE_ENEMY_SOULS*/;

    COND_VB_SHOULD(VB_ACTOR_DRAW, shouldRegister, {
        Actor* actor = (Actor*)va_arg(args, void*);
        if (!HaveEnemySoul((ActorID)actor->id)) {
            *should = false;
            ShuffleEnemySouls_DrawGrayscaledEnemy(actor);
        }
    });

    COND_VB_SHOULD(VB_PERFORM_AC_COLLISION, shouldRegister, {
        Collider* ac = va_arg(args, Collider*);
        *should = HaveEnemySoul((ActorID)ac->actor->id);
    });
}

static RegisterShipInitFunc registerShuffleEnemySouls(RegisterShuffleEnemySouls, { "IS_RANDO" });
