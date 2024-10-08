#ifndef PROPHUNT
#define PROPHUNT

#include <libultraship/bridge.h>

void RegisterPropHunt();

#ifdef __cplusplus
extern "C" {
#endif
void PropHunt_DrawProp(uint16_t currentProp);

#include "functions.h"
#ifdef __cplusplus
}
#endif

typedef struct PropHuntProps {
    const char* name;
    const char* dList;
    Vec3f propPos;
    Vec3f propOffset;
} PropHuntProps;

#define PROP_COUNT 7
#define LINK_PROP_DEFAULT 0

static PropHuntProps propHuntTable[PROP_COUNT] = {
    { "Link", "", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Pot", "__OTR__objects/gameplay_dangeon_keep/gPotDL", { 15.0f, 15.0f, 15.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Grass", "__OTR__objects/gameplay_field_keep/gFieldBushDL", { 45.0f, 45.0f, 45.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Rock", "__OTR__objects/gameplay_field_keep/gFieldKakeraDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Gravestone", "__OTR__objects/object_haka/gGravestoneStoneDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Royal Tomb", "__OTR__objects/object_spot02_objects/object_spot02_objects_DL_0130B0", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Crate", "__OTR__objects/object_kibako2/gLargeCrateDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
};

#endif