#include "PropHunt.h"
#include "soh/Enhancements/game-interactor/GameInteractor.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "soh/Enhancements/game-interactor/GameInteractor_Anchor.h"
#include "soh/Enhancements/debugger/dlViewer.h"

extern "C" {
#include <z64.h>
#include "variables.h"
#include "functions.h"
#include "macros.h"
extern PlayState* gPlayState;
}

void PropHunt_UpdatePropState() {
    if (gSaveContext.playerData.currentProp) {
        GameInteractor::State::InvisibleLinkActive = true;
    } else {
        GameInteractor::State::InvisibleLinkActive = false;
    }
}

std::string activeDL;
char* dlistPath;

void PropHunt_DrawProp(uint16_t currentProp) {
    Gfx* PropDL = (Gfx*)"";
    Vec3f size = { 1.0f, 1.0f, 1.0f };
    Vec3f offset = { 0.0f, 0.0f, 0.0f };

    PropDL = (Gfx*)propHuntTable[currentProp].dList;
    size = propHuntTable[currentProp].propPos;
    offset = propHuntTable[currentProp].propOffset;

    if (CVarGetInteger("gPropUseDLViewer", 0)) {
        char* dlViewerSelection = GetActiveDisplayList();

        if (dlViewerSelection != nullptr) {
            activeDL = dlViewerSelection;
            activeDL = "__OTR__" + activeDL;
            dlistPath = activeDL.data();
            PropDL = (Gfx*)dlistPath;
        }
    }

    if (CVarGetInteger("gPropCustomSizeOffsetEnabled", 0)) {
        size.x = (float)CVarGetInteger("gPropSizeX", 10) / 10.0f;
        size.y = (float)CVarGetInteger("gPropSizeY", 10) / 10.0f;
        size.z = (float)CVarGetInteger("gPropSizeZ", 10) / 10.0f;
        
        offset.x = (float)CVarGetInteger("gPropOffsetX", 10) / 10.0f;
        offset.y = (float)CVarGetInteger("gPropOffsetY", 10) / 10.0f;
        offset.z = (float)CVarGetInteger("gPropOffsetZ", 10) / 10.0f;
    }

    Matrix_Scale(size.x, size.y, size.z, MTXMODE_APPLY);
    Matrix_Translate(offset.x, offset.y, offset.z, MTXMODE_APPLY);
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
