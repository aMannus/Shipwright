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
    uint16_t category;
    Vec3f propPos;
    Vec3f propOffset;
} PropHuntProps;

typedef enum {
    PROP_NONE,
    PROP_COMMON_OBJECTS,
    PROP_SCENERY,
    PROP_DUNGEON,
    PROP_ITEM,
    PROP_BODY_PARTS,
    PROP_MISC,
} PropHuntCategories;

#define PROP_COUNT 114
#define LINK_PROP_DEFAULT 0

static PropHuntProps propHuntTable[] = {
    { "Link", "", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Bean Seedling", "__OTR__objects/object_mamenoki/gMagicBeanSeedlingDL", PROP_COMMON_OBJECTS, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Beehive", "__OTR__objects/gameplay_field_keep/gFieldBeehiveDL", PROP_COMMON_OBJECTS, { 10.0f, 10.0f, 10.0f }, { 0.0f, 1400.0f, 30.0f } },
    { "Bomb Flower Base", "__OTR__objects/object_bombf/gBombFlowerBaseLeaves", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Bomb Flower Leaves", "__OTR__objects/object_bombf/gBombFlowerLeavesDL", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Boulder Silver", "__OTR__objects/gameplay_field_keep/gSilverRockDL", PROP_COMMON_OBJECTS, { 40.0f, 40.0f, 40.0f }, { 0.0f, 60.0f, 0.0f } },
    { "Crate", "__OTR__objects/object_kibako2/gLargeCrateDL", PROP_COMMON_OBJECTS, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Deku Baba Leaves", "__OTR__objects/object_dekubaba/gDekuBabaBaseLeavesDL", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Flagpole", "__OTR__objects/object_hata/gFlagpolePoleDL", PROP_COMMON_OBJECTS, { 15.0f, 15.0f, 15.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Grass", "__OTR__objects/gameplay_field_keep/gFieldBushDL", PROP_COMMON_OBJECTS, { 45.0f, 45.0f, 45.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Grave Earth", "__OTR__objects/object_haka/gGravestoneEarthDL", PROP_COMMON_OBJECTS, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 540.0f } },
    { "Gravestone", "__OTR__objects/object_haka/gGravestoneStoneDL", PROP_COMMON_OBJECTS, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Grotto", "__OTR__objects/gameplay_field_keep/gGrottoDL", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Hookshot Post", "__OTR__objects/object_d_hsblock/gHookshotPostDL", PROP_COMMON_OBJECTS, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Hookshot Target", "__OTR__objects/object_d_hsblock/gHookshotTargetDL", PROP_COMMON_OBJECTS, { 10.0f, 10.0f, 10.0f }, { 0.0f, 1390.0f, -200.0f } },
    { "Lake Flower Patch", "__OTR__objects/gameplay_field_keep/gHanaDL", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Pot", "__OTR__objects/gameplay_dangeon_keep/gPotDL", PROP_COMMON_OBJECTS, { 15.0f, 15.0f, 15.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Rock", "__OTR__objects/gameplay_field_keep/gFieldKakeraDL", PROP_COMMON_OBJECTS, { 10.0f, 10.0f, 10.0f }, { 0.0f, 58.0f, 0.0f } },
    { "Scrub Flower - G", "__OTR__objects/object_dnk/gDntStageFlowerDL", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Scrub Flower - O", "__OTR__objects/object_dekunuts/gDekuNutsFlowerDL", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Scrub Flower - OG", "__OTR__objects/object_dns/gDntJijiFlowerDL", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Sign Directional", "__OTR__objects/gameplay_keep/gSignDirectionalDL", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Sign Rectangular", "__OTR__objects/gameplay_keep/gSignRectangularDL", PROP_COMMON_OBJECTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Small Box", "__OTR__objects/gameplay_dangeon_keep/gSmallWoodenBoxDL", PROP_COMMON_OBJECTS, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Torch Golden", "__OTR__objects/object_syokudai/gGoldenTorchDL", PROP_COMMON_OBJECTS, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Torch Timed", "__OTR__objects/object_syokudai/gTimedTorchDL", PROP_COMMON_OBJECTS, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Torch Wooden", "__OTR__objects/object_syokudai/gWoodenTorchDL", PROP_SCENERY, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Block - Tall", "__OTR__objects/object_pu_box/gBlockTallDL", PROP_SCENERY, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Bombwall Broken", "__OTR__objects/gameplay_field_keep/gBgBombwallBrokenDL", PROP_SCENERY, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Bombwall Normal", "__OTR__objects/gameplay_field_keep/gBgBombwallNormalDL", PROP_SCENERY, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Carpenters' Tent", "__OTR__objects/object_spot09_obj/gCarpentersTentDL", PROP_SCENERY, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Crater Ring", "__OTR__objects/object_spot16_obj/gDeathMountainRingDL", PROP_SCENERY, { 10.0f, 10.0f, 10.0f }, { 0.0f, 10.0f, 0.0f } },
    { "Dampe's Hut", "__OTR__scenes/shared/spot02_scene/spot02_room_1DL_003068", PROP_SCENERY, { 100.0f, 100.0f, 100.0f }, { 800.0f, 0.0f, -650.0f } },
    { "Door - Goron City", "__OTR__objects/object_spot18_obj/gGoronCityDoorDL", PROP_SCENERY, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 20.0f } },
    { "Fishing Post", "__OTR__objects/object_fish/gFishingWoodPostModelDL", PROP_SCENERY, { 8.0f, 8.0f, 8.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Goron Statue", "__OTR__objects/object_spot18_obj/gGoronCityStatueDL", PROP_SCENERY, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Iceberg", "__OTR__objects/object_spot08_obj/gZorasFountainIcebergDL", PROP_SCENERY, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Kak Well Arch", "__OTR__objects/object_spot01_objects/gKakarikoWellArchDL", PROP_SCENERY, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Royal Tomb", "__OTR__objects/object_spot02_objects/object_spot02_objects_DL_0130B0", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Bongo Drum", "__OTR__objects/object_sst/gBongoDrumDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 500.0f, 0.0f } },
    { "Boss Door Lock", "__OTR__objects/object_bdoor/gBossDoorLockDL", PROP_DUNGEON, { 1.0f, 1.0f, 1.0f }, { 0.0f, 8000.0f, -1000.0f } },
    { "BOTW Blood", "__OTR__objects/object_hakach_objects/gBotwBloodSplatterDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "BOTW Bomb Spot", "__OTR__objects/object_hakach_objects/gBotwBombSpotDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "BOTW Coffin", "__OTR__objects/object_hakach_objects/gBotwCoffinLidDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "BOTW Fake", "__OTR__objects/object_hakach_objects/gBotwFakeWallsAndFloorsDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 1.0f, 0.0f } },
    { "BOTW Trap Floor 1", "__OTR__objects/object_hakach_objects/gBotwHoleTrap1DL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 1.0f, 0.0f } },
    { "BOTW Trap Floor 2", "__OTR__objects/object_hakach_objects/gBotwHoleTrap2DL", PROP_DUNGEON, { 12.0f, 12.0f, 12.0f }, { 0.0f, 1.0f, 0.0f } },
    { "Collapsing Platform", "__OTR__objects/object_d_lift/gCollapsingPlatformDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 150.0f, 0.0f } },
    { "Crystal Switch Beta", "__OTR__objects/gameplay_dangeon_keep/gBetaCrystalSwitchDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Dodongo Bars", "__OTR__objects/object_ddan_objects/gDodongoBarsDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, -15.0f } },
    { "Dodongo Falling Stairs", "__OTR__objects/object_ddan_objects/gDodongoFallingStairsDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 4800.0f, 0.0f } },
    { "Dodongo Platform", "__OTR__objects/object_ddan_objects/gDodongoRisingPlatformDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Door - Dodongo", "__OTR__objects/object_ddan_objects/gDodongoDoorDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 20.0f } },
    { "Door - Dungeon", "__OTR__objects/gameplay_keep/gDungeonDoorDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 30.0f } },
    { "Door - Gerudo Cell", "__OTR__objects/object_door_gerudo/gGerudoCellDoorDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 25.0f } },
    { "Fire Temple Gate", "__OTR__objects/object_hidan_objects/gFireTempleMetalFenceDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 250.0f } },
    { "Flare Dancer Platform", "__OTR__objects/object_hidan_objects/gFireTempleFlareDancerPlatformDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Floor Switch B", "__OTR__objects/gameplay_dangeon_keep/gFloorSwitch2DL", PROP_DUNGEON, { 10.0f, 17.0f, 10.0f }, { 0.0f, 5.0f, 0.0f } },
    { "Floor Switch R", "__OTR__objects/gameplay_dangeon_keep/gFloorSwitch3DL", PROP_DUNGEON, { 10.0f, 17.0f, 10.0f }, { 0.0f, 5.0f, 0.0f } },
    { "Floor Switch Rusty", "__OTR__objects/gameplay_dangeon_keep/gRustyFloorSwitchDL", PROP_DUNGEON, { 10.0f, 17.0f, 10.0f }, { 0.0f, 5.0f, 0.0f } },
    { "Floor Switch Y", "__OTR__objects/gameplay_dangeon_keep/gFloorSwitch1DL", PROP_DUNGEON, { 10.0f, 17.0f, 10.0f }, { 0.0f, 5.0f, 0.0f } },
    { "Floor Swtich Beta", "__OTR__objects/gameplay_dangeon_keep/gBetaFloorSwitchDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 10.0f, 0.0f } },
    { "Forest Elevator", "__OTR__objects/object_mori_objects/gMoriElevatorDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Forest Platform", "__OTR__objects/object_mori_objects/gMoriBigstDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 1.0f, 0.0f } },
    { "Ganon Fake Wall", "__OTR__objects/object_demo_kekkai/gGanonsCastleScrubsFakeWallDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Ganon Rubble", "__OTR__objects/object_geff/gGanonRubbleDL", PROP_DUNGEON, { 20.0f, 20.0f, 20.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Gate - Other", "__OTR__objects/object_mori_objects/gMoriHashiraGateDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 30.0f } },
    { "GTG Fake Wall", "__OTR__objects/object_menkuri_objects/gGTGFakeWallDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, -200.0f } },
    { "Jabu Blue Switch", "__OTR__objects/object_bdan_objects/gJabuBlueFloorSwitchDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Jabu Elevator", "__OTR__objects/object_bdan_objects/gJabuElevatorPlatformDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Jabu Falling Platform", "__OTR__objects/object_bdan_objects/gJabuFallingPlatformDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Jabu Large Platform", "__OTR__objects/object_bdan_objects/gJabuObjectsLargeRotatingSpikePlatformDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Jabu Web Door", "__OTR__objects/object_bdan_objects/gJabuWebDoorDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 800.0f, -150.0f } },
    { "Jabu Yellow Switch", "__OTR__objects/object_bdan_objects/gJabuYellowFloorSwitchDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Ladder One Story", "__OTR__objects/object_mori_objects/gMoriHashigoLadderDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, -25.0f } },
    { "Phantom Ganon Bars", "__OTR__objects/object_gnd/gPhantomGanonBarsDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 25.0f } },
    { "Rock Volvagia", "__OTR__objects/object_fd/gVolvagiaRockDL", PROP_DUNGEON, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Sliding Blade", "__OTR__objects/object_trap/gSlidingBladeTrapDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Spirit Climbing Wall", "__OTR__objects/object_jya_obj/gZurerukabeDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, -180.0f } },
    { "Tower Collapse Bars", "__OTR__objects/object_zg/gTowerCollapseBarsDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, -30.0f } },
    { "Trial Door", "__OTR__objects/object_demo_kekkai/gGanonsCastleDoorDL", PROP_DUNGEON, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 25.0f } },
    { "Volvagia Platform", "__OTR__objects/object_fd/gVolvagiaPlatformDL", PROP_DUNGEON, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Volvagia Skull", "__OTR__objects/object_fd/gVolvagiaSkullDL", PROP_DUNGEON, { 1.0f, 1.0f, 1.0f }, { 0.0f, 3500.0f, 0.0f } },
    { "Water Trial Ice Block", "__OTR__objects/object_demo_kekkai/gWaterTrialIceBlockDL", PROP_ITEM, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Beans", "__OTR__objects/object_gi_bean/gGiBeanDL", PROP_ITEM, { 25.0f, 25.0f, 25.0f }, { 0.0f, 40.0f, 0.0f } },
    { "Bomb", "__OTR__objects/object_gi_bomb_1/gGiBombDL", PROP_ITEM, { 25.0f, 25.0f, 25.0f }, { 0.0f, 40.0f, 0.0f } },
    { "Bombchu", "__OTR__objects/object_gi_bomb_2/gGiBombchuDL", PROP_ITEM, { 25.0f, 25.0f, 25.0f }, { 0.0f, 40.0f, 0.0f } },
    { "Boss Key", "__OTR__objects/object_gi_bosskey/gGiBossKeyDL", PROP_ITEM, { 25.0f, 25.0f, 25.0f }, { 0.0f, 40.0f, 0.0f } },
    { "Child Link Bottle", "__OTR__objects/object_link_child/gLinkChildBottle2DL", PROP_ITEM, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Deku Stick", "__OTR__objects/object_link_child/gLinkChildLinkDekuStickDL", PROP_ITEM, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Kokiri Sword Sheath", "__OTR__objects/object_link_child/gLinkChildSwordAndSheathNearDL", PROP_ITEM, { 1.0f, 1.0f, 1.0f }, { 0.0f, 200.0f, 0.0f } },
    { "Magic Jar Large", "__OTR__objects/object_gi_magicpot/gGiMagicJarLargeDL", PROP_ITEM, { 37.0f, 37.0f, 37.0f }, { 0.0f, 40.0f, 0.0f } },
    { "Pocket Egg", "__OTR__objects/object_gi_egg/gGiEggDL", PROP_ITEM, { 25.0f, 25.0f, 25.0f }, { 0.0f, 30.0f, 0.0f } },
    { "Zora Mask", "__OTR__objects/object_gi_zoramask/gGiZoraMaskDL", PROP_BODY_PARTS, { 25.0f, 25.0f, 25.0f }, { 0.0f, 30.0f, 0.0f } },
    { "Ganondorf Open Hand", "__OTR__objects/object_gndd/gYoungGanondorfOpenLeftHandDL", PROP_BODY_PARTS, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Kotake Head", "__OTR__objects/object_tr/gKotakeHeadDL", PROP_MISC, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1000.0f, 0.0f } },
    { "Bean Bag", "__OTR__objects/object_ms/gBeanSalesmanBeanbagDL", PROP_MISC, { 15.0f, 15.0f, 15.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Block - Medium", "__OTR__objects/object_pu_box/gBlockMediumDL", PROP_MISC, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Block - Small", "__OTR__objects/object_pu_box/gBlockSmallDL", PROP_MISC, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Block - Tallest", "__OTR__objects/object_pu_box/gBlockTallestDL", PROP_MISC, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Dampe Halo", "__OTR__objects/object_tk/gDampeHaloDL", PROP_MISC, { 1.0f, 1.0f, 1.0f }, { -500.0f, 0.0f, 0.0f } },
    { "Dampe Lantern", "__OTR__objects/object_tk/gDampeLanternDL", PROP_MISC, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Dampe Shovel", "__OTR__objects/object_tk/gDampeShovelDL", PROP_MISC, { 1.0f, 1.0f, 1.0f }, { 0.0f, 500.0f, 0.0f } },
    { "Fish - Unused", "__OTR__objects/gameplay_field_keep/gFieldUnusedFishDL", PROP_MISC, { 1.0f, 1.0f, 1.0f }, { 0.0f, 600.0f, 0.0f } },
    { "Ganon Castle Rubble Tall", "__OTR__objects/object_gj/gGanonsCastleRubbleTallDL", PROP_MISC, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Great Fairy - Beta", "__OTR__objects/object_dy_obj/gGreatFairyBetaDL", PROP_MISC, { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Nintendo Logo", "__OTR__textures/nintendo_rogo_static/gNintendo64LogoDL", PROP_MISC, { 100.0f, 100.0f, 100.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Rock Unused", "__OTR__objects/gameplay_keep/gLiftableRockDL", PROP_MISC, { 1.0f, 1.0f, 1.0f }, { 0.0f, 100.0f, 0.0f } },
    { "Ship", "__OTR__textures/nintendo_rogo_static/gShipLogoDL", PROP_MISC, { 100.0f, 100.0f, 100.0f }, { 0.0f, 10.0f, 0.0f } },
    { "Small Cube", "__OTR__objects/gameplay_keep/gSmallCubeDL", PROP_MISC, { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Stump Unused", "__OTR__objects/gameplay_keep/gTreeStumpDL", PROP_MISC, { 2.0f, 2.0f, 2.0f }, { 0.0f, 0.0f, 0.0f } },
    { "Triforce", "__OTR__objects/object_triforce_completed/gTriforcePieceCompletedDL", PROP_MISC, { 1.0f, 1.0f, 1.0f }, { 0.0f, 600.0f, 0.0f } },
    { "Water - Jabu", "__OTR__objects/object_bdan_objects/gJabuWaterDL", PROP_MISC, { 10.0f, 10.0f, 10.0f }, { 0.0f, 10.0f, 0.0f } },
    { "Wooden Platform", "__OTR__objects/gameplay_dangeon_keep/gWoodenPlatofrmDL", PROP_MISC, { 10.0f, 10.0f, 10.0f }, { 0.0f, 180.0f, 0.0f } },
};

#endif