#include "PropHunt.h"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Anchor.h"

extern "C" {
#include <z64.h>
#include "variables.h"
#include "functions.h"
#include "macros.h"
extern PlayState* gPlayState;
}

#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"
#include "objects/gameplay_field_keep/gameplay_field_keep.h"

void PropHunt_UpdatePropState() {
    if (gSaveContext.playerData.currentProp) {
        GameInteractor::State::InvisibleLinkActive = true;
    } else {
        GameInteractor::State::InvisibleLinkActive = false;
    }
}

void PropHunt_DrawProp(uint16_t currentProp) {
    const char* PropDL = gPotDL;
    float scale = 1.0f;
    float translateY = 0.0f;

    switch (currentProp) {
        case LINK_PROP_POT:
            PropDL = gPotDL;
            scale = 15.0f;
            break;
        case LINK_PROP_GRASS:
            PropDL = gFieldBushDL;
            scale = 45.0f;
            break;
        default:
            break;
    }

    Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
    Matrix_Translate(0, translateY, 0, MTXMODE_APPLY);
    Gfx_DrawDListOpa(gPlayState, (Gfx*)PropDL);
}

void RegisterPropHunt() {
    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnGameFrameUpdate>([]() {
        PropHunt_UpdatePropState();
    });

    GameInteractor::Instance->RegisterGameHook<GameInteractor::OnPlayerDraw>([]() {
        if (gSaveContext.playerData.currentProp) {
            PropHunt_DrawProp(gSaveContext.playerData.currentProp);
        }
    });
}
