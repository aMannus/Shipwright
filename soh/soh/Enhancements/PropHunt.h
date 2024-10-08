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

#define PROP_COUNT 48
#define LINK_PROP_DEFAULT 0

static PropHuntProps propHuntTable[] = {
    { "Link", "", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Pot", "__OTR__objects/gameplay_dangeon_keep/gPotDL", { 15.0f, 15.0f, 15.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Grass", "__OTR__objects/gameplay_field_keep/gFieldBushDL", { 45.0f, 45.0f, 45.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Rock", "__OTR__objects/gameplay_field_keep/gFieldKakeraDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 58.0f, 0.0f } },
    { "Gravestone", "__OTR__objects/object_haka/gGravestoneStoneDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Royal Tomb", "__OTR__objects/object_spot02_objects/object_spot02_objects_DL_0130B0", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Crate", "__OTR__objects/object_kibako2/gLargeCrateDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Bean Seedling", "__OTR__objects/object_mamenoki/gMagicBeanSeedlingDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Graveyard Kid Foot", "__OTR__objects/object_cs/gGraveyardKidLeftFootDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Child Link Bottle", "__OTR__objects/object_link_child/gLinkChildBottle2DL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Hookshot Post", "__OTR__objects/object_d_hsblock/gHookshotPostDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Bombwall Broken", "__OTR__objects/gameplay_field_keep/gBgBombwallBrokenDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Ganondorf Open Hand", "__OTR__objects/object_gndd/gYoungGanondorfOpenLeftHandDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Deku Stick", "__OTR__objects/object_link_child/gLinkChildLinkDekuStickDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Kak Well Arch", "__OTR__objects/object_spot01_objects/gKakarikoWellArchDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Lake Flower Patch", "__OTR__objects/gameplay_field_keep/gHanaDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Bomb", "__OTR__objects/object_gi_bomb_1/gGiBombDL", { 25.0f, 25.0f, 25.0f }, { 0.0f, 40.0f, 0.0f } },
    { "Magic Jar Large", "__OTR__objects/object_gi_magicpot/gGiMagicJarLargeDL", { 37.0f, 37.0f, 37.0f }, { 0.0f, 40.0f, 0.0f } },
    { "Water Trial Ice Block", "__OTR__objects/object_demo_kekkai/gWaterTrialIceBlockDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Zora Mask", "__OTR__objects/object_gi_zoramask/gGiZoraMaskDL", { 25.0f, 25.0f, 25.0f }, { 0.0f, 30.0f, 0.0f } },
    { "Volvagia Platform", "__OTR__objects/object_fd/gVolvagiaPlatformDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Fishing Post", "__OTR__objects/object_fish/gFishingWoodPostModelDL", { 8.0f, 8.0f, 8.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Dampe Lantern", "__OTR__objects/object_tk/gDampeLanternDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Dampe's Hut", "__OTR__scenes/shared/spot02_scene/spot02_room_1DL_003068", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Gate - Other", "__OTR__objects/object_mori_objects/gMoriHashiraGateDL", { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 30.0f } },
    { "Door - Dungeon", "__OTR__objects/gameplay_keep/gDungeonDoorDL", { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 30.0f } },
    { "Grotto", "__OTR__objects/gameplay_field_keep/gGrottoDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Great Fairy - Beta", "__OTR__objects/object_dy_obj/gGreatFairyBetaDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Flare Dancer Platform", "__OTR__objects/object_hidan_objects/gFireTempleFlareDancerPlatformDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Block - Tall", "__OTR__objects/object_pu_box/gBlockTallDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Pocket Egg", "__OTR__objects/object_gi_egg/gGiEggDL", { 25.0f, 25.0f, 25.0f }, { 0.0f, 30.0f, 0.0f } },
    { "Carpenters' Tent", "__OTR__objects/object_spot09_obj/gCarpentersTentDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Door - Dodongo", "__OTR__objects/object_ddan_objects/gDodongoDoorDL", { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 20.0f } },
    { "Door - Goron City", "__OTR__objects/object_spot18_obj/gGoronCityDoorDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 20.0f } },
    { "Ganon Castle Rubble Tall", "__OTR__objects/object_gj/gGanonsCastleRubbleTallDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Kokiri Sword Sheath", "__OTR__objects/object_link_child/gLinkChildSwordAndSheathNearDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 200.0f, 0.0f } },
    { "Flagpole", "__OTR__objects/object_hata/gFlagpolePoleDL", { 1.5f, 1.5f, 1.5f }, { 0.0f, 0.0f, 0.0f } },
    { "Volvagia Skull", "__OTR__objects/object_fd/gVolvagiaSkullDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 3500.0f, 0.0f } },
    { "GTG Fake Wall", "__OTR__objects/object_menkuri_objects/gGTGFakeWallDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, -200.0f } },
    { "Fire Temple Gate", "__OTR__objects/object_hidan_objects/gFireTempleMetalFenceDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 250.0f } },
    { "Hookshot Target", "__OTR__objects/object_d_hsblock/gHookshotTargetDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 1390.0f, -200.0f } },
    { "Ladder One Story", "__OTR__objects/object_mori_objects/gMoriHashigoLadderDL", { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, -25.0f } },
    { "Kotake Head", "__OTR__objects/object_tr/gKotakeHeadDL", { 1.0f, 1.0f, 1.0f }, { 0.0f, 1000.0f, 0.0f } },
    { "Dodongo Falling Stairs", "__OTR__objects/object_ddan_objects/gDodongoFallingStairsDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 4800.0f, 0.0f } },
    { "Spirit Temple Climbing Wall", "__OTR__objects/object_jya_obj/gZurerukabeDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, -180.0f } },
    { "Tower Collapse Bars", "__OTR__objects/object_zg/gTowerCollapseBarsDL", { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, -30.0f } },
    { "Phantom Ganon Bars", "__OTR__objects/object_gnd/gPhantomGanonBarsDL", { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 25.0f } },
    { "Jabu Blue Switch", "__OTR__objects/object_bdan_objects/gJabuBlueFloorSwitchDL", { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
};

#endif