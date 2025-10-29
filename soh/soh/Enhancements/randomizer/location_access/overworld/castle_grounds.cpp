#include "soh/Enhancements/randomizer/location_access.h"
#include "soh/Enhancements/randomizer/entrance.h"

using namespace Rando;

void RegionTable_Init_CastleGrounds() {
    // clang-format off
    //With multi-area support {RA_CASTLE_GROUNDS} is not strictly required anymore, as any interior here could inherit both
    //{RA_HYRULE_CASTLE} and {RA_OUTSIDE_GANONS_CASTLE}, but a setting to merge the latter 2 into the former may be preferred
    areaTable[RR_CASTLE_GROUNDS] = Region("Castle Grounds", "Castle Grounds", {RA_CASTLE_GROUNDS}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        //Exits
        Entrance(RR_THE_MARKET,            []{return true;}),
        Entrance(RR_HYRULE_CASTLE_GROUNDS, []{return logic->IsChild;}, true),
        Entrance(RR_GANONS_CASTLE_GROUNDS, []{return logic->IsAdult;}, true),
    });

    areaTable[RR_HYRULE_CASTLE_GROUNDS] = Region("Hyrule Castle Grounds", "Castle Grounds", {RA_HYRULE_CASTLE}, DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}, true),
        EventAccess(&logic->ButterflyFairy,   []{return logic->CanUse(RG_STICKS);}, true),
        EventAccess(&logic->BugRock,          []{return true;}),
    }, {
        //Locations
        LOCATION(RC_HC_MALON_EGG,                        true),
        LOCATION_NNL(RC_HC_GS_TREE,                          logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_CLOSE) && logic->CanBonkTrees()),
        LOCATION_NNL(RC_HC_MALON_GOSSIP_STONE_FAIRY,         logic->CallGossipFairy()),
        LOCATION_NNL(RC_HC_MALON_GOSSIP_STONE_FAIRY_BIG,     logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION_NNL(RC_HC_ROCK_WALL_GOSSIP_STONE_FAIRY,     logic->CallGossipFairy()),
        LOCATION_NNL(RC_HC_ROCK_WALL_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION(RC_HC_ROCK_1,                           true),
        LOCATION(RC_HC_ROCK_2,                           true),
        LOCATION(RC_HC_ROCK_3,                           true),
        LOCATION(RC_HC_BOULDER,                          logic->BlastOrSmash()),
        LOCATION(RC_HC_MALON_GOSSIP_STONE,               true),
        LOCATION(RC_HC_ROCK_WALL_GOSSIP_STONE,           true),
        LOCATION(RC_HC_GRASS_1,                          logic->CanCutShrubs()),
        LOCATION(RC_HC_GRASS_2,                          logic->CanCutShrubs()),
        LOCATION(RC_HC_GROTTO_TREE,                      logic->CanBonkTrees()),
        LOCATION(RC_HC_SKULLTULA_TREE,                   logic->CanBonkTrees()),
        LOCATION(RC_HC_NEAR_GUARDS_TREE_1,               logic->CanBonkTrees()),
        LOCATION(RC_HC_NEAR_GUARDS_TREE_2,               logic->CanBonkTrees()),
        LOCATION(RC_HC_NEAR_GUARDS_TREE_3,               logic->CanBonkTrees()),
        LOCATION(RC_HC_NEAR_GUARDS_TREE_4,               logic->CanBonkTrees()),
        LOCATION(RC_HC_NEAR_GUARDS_TREE_5,               logic->CanBonkTrees()),
        LOCATION(RC_HC_NEAR_GUARDS_TREE_6,               logic->CanBonkTrees()),
    }, {
        //Exits
        Entrance(RR_CASTLE_GROUNDS,          []{return true;}),
        Entrance(RR_HC_GARDEN,               []{return logic->CanUse(RG_WEIRD_EGG) || (ctx->GetTrickOption(RT_DAMAGE_BOOST_SIMPLE) && logic->HasExplosives() && logic->CanJumpslash());}, true),
        Entrance(RR_HC_GREAT_FAIRY_FOUNTAIN, []{return logic->BlastOrSmash();}, true),
        Entrance(RR_HC_STORMS_GROTTO,        []{return logic->CanOpenStormsGrotto();}, true),
    });

    areaTable[RR_HC_GARDEN] = Region("HC Garden", "Castle Grounds", {RA_HYRULE_CASTLE}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_HC_ZELDAS_LETTER, true),
        LOCATION(RC_SONG_FROM_IMPA,   true),
    }, {
        //Exits
        Entrance(RR_HYRULE_CASTLE_GROUNDS, []{return true;}),
    });

    areaTable[RR_HC_GREAT_FAIRY_FOUNTAIN] = Region("HC Great Fairy Fountain", "HC Great Fairy Fountain", {}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION_NNL(RC_HC_GREAT_FAIRY_REWARD, logic->CanUse(RG_ZELDAS_LULLABY)),
    }, {
        //Exits
        Entrance(RR_CASTLE_GROUNDS, []{return true;}),
    });

    areaTable[RR_HC_STORMS_GROTTO] = Region("HC Storms Grotto", "HC Storms Grotto", {}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION(RC_HC_GS_STORMS_GROTTO, logic->CanUse(RG_BOOMERANG) && ctx->GetTrickOption(RT_HC_STORMS_GS)),
    }, {
        //Exits
        Entrance(RR_CASTLE_GROUNDS,                []{return true;}),
        Entrance(RR_HC_STORMS_GROTTO_BEHIND_WALLS, []{return logic->CanBreakMudWalls();}),
    });

    areaTable[RR_HC_STORMS_GROTTO_BEHIND_WALLS] = Region("HC Storms Grotto Behind Walls", "HC Storms Grotto", {}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->NutPot,           []{return true;}),
        EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}, true),
        EventAccess(&logic->WanderingBugs,    []{return true;}),
    }, {
        //Locations
        LOCATION(RC_HC_GS_STORMS_GROTTO,                     logic->HookshotOrBoomerang()),
        LOCATION_NNL(RC_HC_STORMS_GROTTO_GOSSIP_STONE_FAIRY,     logic->CallGossipFairy()),
        LOCATION_NNL(RC_HC_STORMS_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION(RC_HC_STORMS_GROTTO_GOSSIP_STONE,           true),
        LOCATION(RC_HC_STORMS_GROTTO_POT_1,                  logic->CanBreakPots()),
        LOCATION(RC_HC_STORMS_GROTTO_POT_2,                  logic->CanBreakPots()),
        LOCATION(RC_HC_STORMS_GROTTO_POT_3,                  logic->CanBreakPots()),
        LOCATION(RC_HC_STORMS_GROTTO_POT_4,                  logic->CanBreakPots()),
        LOCATION(RC_HC_STORMS_GROTTO_ROCK_1,                 true),
        LOCATION(RC_HC_STORMS_GROTTO_ROCK_2,                 true),
        LOCATION(RC_HC_STORMS_GROTTO_ROCK_3,                 true),
        LOCATION(RC_HC_STORMS_GROTTO_ROCK_4,                 true),
        LOCATION(RC_HC_STORMS_GROTTO_ROCK_5,                 true),
        LOCATION(RC_HC_STORMS_GROTTO_ROCK_6,                 true),
        LOCATION(RC_HC_STORMS_GROTTO_ROCK_7,                 true),
        LOCATION(RC_HC_STORMS_GROTTO_ROCK_8,                 true),
    }, {
        //Exits
        Entrance(RR_HC_STORMS_GROTTO, []{return true;}),
    });

    areaTable[RR_GANONS_CASTLE_GROUNDS] = Region("Ganon's Castle Grounds", "Castle Grounds", {RA_OUTSIDE_GANONS_CASTLE}, NO_DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->BuiltRainbowBridge, []{return logic->CanBuildRainbowBridge();}, true),
    }, {
        //Locations
        LOCATION(RC_OGC_GS, logic->CanJumpslashExceptHammer() || logic->CanUseProjectile() || (logic->CanShield() && logic->CanUse(RG_MEGATON_HAMMER)) || logic->CanUse(RG_DINS_FIRE)),
        LOCATION(RC_OGC_BRONZE_BOULDER_1, logic->CanUse(RG_MEGATON_HAMMER)),
        LOCATION(RC_OGC_BRONZE_BOULDER_2, logic->CanUse(RG_MEGATON_HAMMER)),
        LOCATION(RC_OGC_BRONZE_BOULDER_3, logic->CanUse(RG_MEGATON_HAMMER)),
        LOCATION(RC_OGC_SILVER_BOULDER_1, logic->CanUse(RG_SILVER_GAUNTLETS)),
        LOCATION(RC_OGC_SILVER_BOULDER_2, logic->CanUse(RG_SILVER_GAUNTLETS)),
        LOCATION(RC_OGC_SILVER_BOULDER_3, logic->CanUse(RG_SILVER_GAUNTLETS)),
        LOCATION(RC_OGC_SILVER_BOULDER_4, logic->CanUse(RG_SILVER_GAUNTLETS)),
    }, {
        //Exits
        Entrance(RR_CASTLE_GROUNDS,           []{return logic->AtNight;}),
        Entrance(RR_OGC_GREAT_FAIRY_FOUNTAIN, []{return logic->CanUse(RG_GOLDEN_GAUNTLETS) && logic->AtNight;}),
        Entrance(RR_GANONS_CASTLE_LEDGE,      []{return logic->BuiltRainbowBridge;}),
    });

    areaTable[RR_OGC_GREAT_FAIRY_FOUNTAIN] = Region("OGC Great Fairy Fountain", "OGC Great Fairy Fountain", {}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION_NNL(RC_OGC_GREAT_FAIRY_REWARD, logic->CanUse(RG_ZELDAS_LULLABY)),
    }, {
        //Exits
        Entrance(RR_CASTLE_GROUNDS, []{return true;}),
    });

    areaTable[RR_CASTLE_GROUNDS_FROM_GANONS_CASTLE] = Region("Castle Grounds From Ganon's Castle", "Castle Grounds From Ganon's Castle", {RA_CASTLE_GROUNDS}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        // Exits
        Entrance(RR_HYRULE_CASTLE_GROUNDS, []{return logic->IsChild;}, true),
        Entrance(RR_GANONS_CASTLE_LEDGE,   []{return logic->IsAdult;}, true),
    });

    areaTable[RR_GANONS_CASTLE_LEDGE] = Region("Ganon's Castle Ledge", "OGC Ganon's Castle Ledge", {RA_OUTSIDE_GANONS_CASTLE}, NO_DAY_NIGHT_CYCLE, {}, {}, {
        // Exits
        Entrance(RR_GANONS_CASTLE_GROUNDS,  []{return logic->BuiltRainbowBridge;}),
        Entrance(RR_GANONS_CASTLE_ENTRYWAY, []{return logic->IsAdult;}, true),
    });

    // clang-format on
}
