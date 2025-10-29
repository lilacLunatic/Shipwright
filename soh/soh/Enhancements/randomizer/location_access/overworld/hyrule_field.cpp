#include "soh/Enhancements/randomizer/location_access.h"
#include "soh/Enhancements/randomizer/entrance.h"

using namespace Rando;

void RegionTable_Init_HyruleField() {
    // clang-format off
    areaTable[RR_HYRULE_FIELD] = Region("Hyrule Field", "Hyrule Field", {RA_HYRULE_FIELD}, DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->BigPoeKill, []{return logic->CanUse(RG_FAIRY_BOW) && logic->CanUse(RG_EPONA) && logic->HasBottle();}, true),
    }, {
        //Locations
        LOCATION_NNL(RC_HF_OCARINA_OF_TIME_ITEM,   logic->IsChild && logic->StoneCount() == 3 && logic->HasItem(RG_BRONZE_SCALE)),
        LOCATION_NNL(RC_SONG_FROM_OCARINA_OF_TIME, logic->IsChild && logic->StoneCount() == 3 && logic->HasItem(RG_BRONZE_SCALE)),
        LOCATION_NNL(RC_HF_POND_STORMS_FAIRY,      logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_1,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_2,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_3,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_4,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_5,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_6,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_7,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_8,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_9,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_10,       logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_11,       logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_CENTRAL_GRASS_12,       logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_1,          logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_2,          logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_3,          logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_4,          logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_5,          logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_6,          logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_7,          logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_8,          logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_9,          logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_10,         logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_11,         logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTH_GRASS_12,         logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_1,    logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_2,    logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_3,    logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_4,    logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_5,    logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_6,    logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_7,    logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_8,    logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_9,    logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_10,   logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_11,   logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GRASS_12,   logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_1,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_2,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_3,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_4,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_5,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_6,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_7,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_8,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_9,        logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_10,       logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_11,       logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_KF_GRASS_12,       logic->CanCutShrubs()),
        LOCATION(RC_HF_SILVER_BOULDER,         logic->CanUse(RG_SILVER_GAUNTLETS)),
        LOCATION(RC_HF_ROCK_1,                 true),
        LOCATION(RC_HF_ROCK_2,                 true),
        LOCATION(RC_HF_ROCK_3,                 true),
        LOCATION(RC_HF_ROCK_4,                 true),
        LOCATION(RC_HF_ROCK_5,                 true),
        LOCATION(RC_HF_ROCK_6,                 true),
        LOCATION(RC_HF_ROCK_7,                 true),
        LOCATION(RC_HF_ROCK_8,                 true),
        LOCATION(RC_HF_BOULDER_NORTH,          logic->BlastOrSmash()),
        LOCATION(RC_HF_BOULDER_BY_MARKET,      logic->BlastOrSmash()),
        LOCATION(RC_HF_BOULDER_SOUTH,          logic->BlastOrSmash()),
        LOCATION(RC_HF_BRONZE_BOULDER_1,       logic->IsAdult && logic->CanUse(RG_MEGATON_HAMMER)),
        LOCATION(RC_HF_BRONZE_BOULDER_2,       logic->IsAdult && logic->CanUse(RG_MEGATON_HAMMER)),
        LOCATION(RC_HF_BRONZE_BOULDER_3,       logic->IsAdult && logic->CanUse(RG_MEGATON_HAMMER)),
        LOCATION(RC_HF_BRONZE_BOULDER_4,       logic->IsAdult && logic->CanUse(RG_MEGATON_HAMMER)),
        LOCATION(RC_HF_NEAR_LLR_TREE,          logic->CanBonkTrees()),
        LOCATION(RC_HF_NEAR_LH_TREE,           logic->CanBonkTrees()),
        LOCATION(RC_HF_CHILD_NEAR_GV_TREE,     logic->IsChild && logic->CanBonkTrees()),
        LOCATION(RC_HF_ADULT_NEAR_GV_TREE,     logic->IsAdult && logic->CanBonkTrees()),
        LOCATION(RC_HF_NEAR_ZR_TREE,           logic->CanBonkTrees()),
        LOCATION(RC_HF_NEAR_KAK_TREE,          logic->CanBonkTrees()),
        LOCATION(RC_HF_NEAR_KAK_SMALL_TREE,    logic->CanBonkTrees()),
        LOCATION(RC_HF_TREE_NEAR_HC_GROTTO_1,  logic->CanBonkTrees()),
        LOCATION(RC_HF_TREE_NEAR_HC_GROTTO_2,  logic->CanBonkTrees()),
        LOCATION(RC_HF_TREE_NEAR_HC_GROTTO_3,  logic->CanBonkTrees()),
        LOCATION(RC_HF_NORTHWEST_TREE_1,       logic->CanBonkTrees()),
        LOCATION(RC_HF_NORTHWEST_TREE_2,       logic->CanBonkTrees()),
        LOCATION(RC_HF_NORTHWEST_TREE_3,       logic->CanBonkTrees()),
        LOCATION(RC_HF_NORTHWEST_TREE_4,       logic->CanBonkTrees()),
        LOCATION(RC_HF_NORTHWEST_TREE_5,       logic->CanBonkTrees()),
        LOCATION(RC_HF_NORTHWEST_TREE_6,       logic->CanBonkTrees()),
        LOCATION(RC_HF_EAST_TREE_1,            logic->CanBonkTrees()),
        LOCATION(RC_HF_EAST_TREE_2,            logic->CanBonkTrees()),
        LOCATION(RC_HF_EAST_TREE_3,            logic->CanBonkTrees()),
        LOCATION(RC_HF_EAST_TREE_4,            logic->CanBonkTrees()),
        LOCATION(RC_HF_EAST_TREE_5,            logic->CanBonkTrees()),
        LOCATION(RC_HF_EAST_TREE_6,            logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_1,       logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_2,       logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_3,       logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_4,       logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_5,       logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_6,       logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_7,       logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_8,       logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_9,       logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_10,      logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_11,      logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_12,      logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_13,      logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_14,      logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_15,      logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_16,      logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_17,      logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_18,      logic->CanBonkTrees()),
        LOCATION(RC_HF_SOUTHEAST_TREE_19,      logic->CanBonkTrees()),
        LOCATION(RC_HF_CHILD_SOUTHEAST_TREE_1, logic->IsChild && logic->CanBonkTrees()),
        LOCATION(RC_HF_CHILD_SOUTHEAST_TREE_2, logic->IsChild && logic->CanBonkTrees()),
        LOCATION(RC_HF_CHILD_SOUTHEAST_TREE_3, logic->IsChild && logic->CanBonkTrees()),
        LOCATION(RC_HF_CHILD_SOUTHEAST_TREE_4, logic->IsChild && logic->CanBonkTrees()),
        LOCATION(RC_HF_CHILD_SOUTHEAST_TREE_5, logic->IsChild && logic->CanBonkTrees()),
        LOCATION(RC_HF_CHILD_SOUTHEAST_TREE_6, logic->IsChild && logic->CanBonkTrees()),
        LOCATION(RC_HF_TEKTITE_GROTTO_TREE,    logic->CanBonkTrees()),
    }, {
        //Exits
        Entrance(RR_LW_BRIDGE,              []{return true;}),
        Entrance(RR_LAKE_HYLIA,             []{return true;}),
        Entrance(RR_GERUDO_VALLEY,          []{return true;}),
        Entrance(RR_MARKET_ENTRANCE,        []{return true;}),
        Entrance(RR_KAKARIKO_VILLAGE,       []{return true;}),
        Entrance(RR_ZR_FRONT,               []{return true;}),
        Entrance(RR_LON_LON_RANCH,          []{return true;}),
        Entrance(RR_HF_SOUTHEAST_GROTTO,    []{return Here(RR_HYRULE_FIELD, []{return logic->BlastOrSmash();});}),
        Entrance(RR_HF_OPEN_GROTTO,         []{return true;}),
        Entrance(RR_HF_INSIDE_FENCE_GROTTO, []{return logic->CanOpenBombGrotto();}, true),
        Entrance(RR_HF_COW_GROTTO,          []{return (logic->CanUse(RG_MEGATON_HAMMER) || logic->IsChild) && logic->CanOpenBombGrotto();}, true),
        Entrance(RR_HF_NEAR_MARKET_GROTTO,  []{return Here(RR_HYRULE_FIELD, []{return logic->BlastOrSmash();});}, true),
        Entrance(RR_HF_FAIRY_GROTTO,        []{return Here(RR_HYRULE_FIELD, []{return logic->BlastOrSmash();});}, true),
        Entrance(RR_HF_NEAR_KAK_GROTTO,     []{return logic->CanOpenBombGrotto();}, true),
        Entrance(RR_HF_TEKTITE_GROTTO,      []{return logic->CanOpenBombGrotto();}, true),
    });

    areaTable[RR_HF_SOUTHEAST_GROTTO] = Region("HF Southeast Grotto", "HF Southeast Grotto", {}, NO_DAY_NIGHT_CYCLE, grottoEvents, {
        //Locations
        LOCATION(RC_HF_SOUTHEAST_GROTTO_CHEST,                  true),
        LOCATION_NNL(RC_HF_SOUTHEAST_GROTTO_FISH,                   logic->HasBottle()),
        LOCATION_NNL(RC_HF_SOUTHEAST_GROTTO_GOSSIP_STONE_FAIRY,     logic->CallGossipFairy()),
        LOCATION_NNL(RC_HF_SOUTHEAST_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION(RC_HF_SOUTHEAST_GROTTO_GOSSIP_STONE,           true),
        LOCATION(RC_HF_SOUTHEAST_GROTTO_BEEHIVE_LEFT,           logic->CanBreakLowerBeehives()),
        LOCATION(RC_HF_SOUTHEAST_GROTTO_BEEHIVE_RIGHT,          logic->CanBreakLowerBeehives()),
        LOCATION_NNL(RC_HF_SOUTHEAST_GROTTO_GRASS_1,                logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTHEAST_GROTTO_GRASS_2,                logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTHEAST_GROTTO_GRASS_3,                logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_SOUTHEAST_GROTTO_GRASS_4,                logic->CanCutShrubs()),
    }, {
        //Exits
        Entrance(RR_HYRULE_FIELD, []{return true;}),
    });

    areaTable[RR_HF_OPEN_GROTTO] = Region("HF Open Grotto", "HF Open Grotto", {}, NO_DAY_NIGHT_CYCLE, grottoEvents, {
        //Locations
        LOCATION(RC_HF_OPEN_GROTTO_CHEST,                   true),
        LOCATION_NNL(RC_HF_OPEN_GROTTO_FISH,                    logic->HasBottle()),
        LOCATION_NNL(RC_HF_OPEN_GROTTO_GOSSIP_STONE_FAIRY,      logic->CallGossipFairy()),
        LOCATION_NNL(RC_HF_OPEN_GROTTO_GOSSIP_STONE_FAIRY_BIG,  logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION(RC_HF_OPEN_GROTTO_GOSSIP_STONE,            true),
        LOCATION(RC_HF_OPEN_GROTTO_BEEHIVE_LEFT,            logic->CanBreakLowerBeehives()),
        LOCATION(RC_HF_OPEN_GROTTO_BEEHIVE_RIGHT,           logic->CanBreakLowerBeehives()),
        LOCATION_NNL(RC_HF_OPEN_GROTTO_GRASS_1,                 logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_OPEN_GROTTO_GRASS_2,                 logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_OPEN_GROTTO_GRASS_3,                 logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_OPEN_GROTTO_GRASS_4,                 logic->CanCutShrubs()),
    }, {
        //Exits
        Entrance(RR_HYRULE_FIELD, []{return true;}),
    });

    areaTable[RR_HF_INSIDE_FENCE_GROTTO] = Region("HF Inside Fence Grotto", "HF Inside Fence Grotto", {}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION_NNL(RC_HF_DEKU_SCRUB_GROTTO,         logic->CanStunDeku()),
        LOCATION(RC_HF_INSIDE_FENCE_GROTTO_BEEHIVE, logic->CanBreakLowerBeehives()),
        LOCATION_NNL(RC_HF_FENCE_GROTTO_STORMS_FAIRY, logic->CanUse(RG_SONG_OF_STORMS)),
    }, {
        //Exits
        Entrance(RR_HYRULE_FIELD, []{return true;}),
    });

    areaTable[RR_HF_COW_GROTTO] = Region("HF Cow Grotto", "HF Cow Grotto", {}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        //Exits
        Entrance(RR_HYRULE_FIELD,              []{return true;}),
        Entrance(RR_HF_COW_GROTTO_BEHIND_WEBS, []{return logic->HasFireSource();}),
    });

    areaTable[RR_HF_COW_GROTTO_BEHIND_WEBS] = Region("HF Cow Grotto Behind Webs", "HF Cow Grotto", {}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->BugShrub,         []{return logic->CanCutShrubs();}, true),
        EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}, true),
    }, {
        //Locations
        LOCATION(RC_HF_GS_COW_GROTTO,                     logic->CanGetEnemyDrop(RE_GOLD_SKULLTULA, ED_BOOMERANG)),
        LOCATION_NNL(RC_HF_COW_GROTTO_COW,                    logic->CanUse(RG_EPONAS_SONG)),
        LOCATION_NNL(RC_HF_COW_GROTTO_GOSSIP_STONE_FAIRY,     logic->CallGossipFairy()),
        LOCATION_NNL(RC_HF_COW_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION(RC_HF_COW_GROTTO_GOSSIP_STONE,           true),
        LOCATION(RC_HF_COW_GROTTO_POT_1,                  logic->CanBreakPots()),
        LOCATION(RC_HF_COW_GROTTO_POT_2,                  logic->CanBreakPots()),
        LOCATION_NNL(RC_HF_COW_GROTTO_GRASS_1,                logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_COW_GROTTO_GRASS_2,                logic->CanCutShrubs()),
    }, {
        //Exits
        Entrance(RR_HF_COW_GROTTO, []{return true;}),
    });

    areaTable[RR_HF_NEAR_MARKET_GROTTO] = Region("HF Near Market Grotto", "HF Near Market Grotto", {}, NO_DAY_NIGHT_CYCLE, grottoEvents, {
        //Locations
        LOCATION(RC_HF_NEAR_MARKET_GROTTO_CHEST,                  true),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GROTTO_FISH,                   logic->HasBottle()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GROTTO_GOSSIP_STONE_FAIRY,     logic->CallGossipFairy()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION(RC_HF_NEAR_MARKET_GROTTO_GOSSIP_STONE,           true),
        LOCATION(RC_HF_NEAR_MARKET_GROTTO_BEEHIVE_LEFT,           logic->CanBreakLowerBeehives()),
        LOCATION(RC_HF_NEAR_MARKET_GROTTO_BEEHIVE_RIGHT,          logic->CanBreakLowerBeehives()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GROTTO_GRASS_1,                logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GROTTO_GRASS_2,                logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GROTTO_GRASS_3,                logic->CanCutShrubs()),
        LOCATION_NNL(RC_HF_NEAR_MARKET_GROTTO_GRASS_4,                logic->CanCutShrubs()),
    }, {
        //Exits
        Entrance(RR_HYRULE_FIELD, []{return true;}),
    });

    areaTable[RR_HF_FAIRY_GROTTO] = Region("HF Fairy Grotto", "HF Fairy Grotto", {}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->FreeFairies, []{return true;}),
    }, {
        //Locations
        LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_1, true),
        LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_2, true),
        LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_3, true),
        LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_4, true),
        LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_5, true),
        LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_6, true),
        LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_7, true),
        LOCATION(RC_HF_FAIRY_GROTTO_FAIRY_8, true),
    }, {
        //Exits
        Entrance(RR_HYRULE_FIELD, []{return true;}),
    });

    areaTable[RR_HF_NEAR_KAK_GROTTO] = Region("HF Near Kak Grotto", "HF Near Kak Grotto", {}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_HF_GS_NEAR_KAK_GROTTO, logic->HookshotOrBoomerang()),
    }, {
        //Exits
        Entrance(RR_HYRULE_FIELD, []{return true;}),
    });

    areaTable[RR_HF_TEKTITE_GROTTO] = Region("HF Tektite Grotto", "HF Tektite Grotto", {}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_HF_TEKTITE_GROTTO_FREESTANDING_POH, logic->HasItem(logic->IsNNL() ? RG_BRONZE_SCALE : RG_GOLDEN_SCALE) || logic->CanUse(RG_IRON_BOOTS)),
    }, {
        //Exits
        Entrance(RR_HYRULE_FIELD, []{return true;}),
    });

    // clang-format on
}
