#pragma once

#include <libultraship/bridge.h>

void RegisterPropHunt();

#ifdef __cplusplus
extern "C" {
#endif
void PropHunt_DrawProp(uint16_t currentProp);
#ifdef __cplusplus
}
#endif