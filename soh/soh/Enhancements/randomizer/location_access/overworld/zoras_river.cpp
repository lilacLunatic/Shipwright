#include "soh/Enhancements/randomizer/location_access.h"
#include "soh/Enhancements/randomizer/entrance.h"

using namespace Rando;

void RegionTable_Init_ZoraRiver() {
    // clang-format off
    areaTable[RR_ZR_FRONT] = Region("ZR Front", "Zora River", {RA_ZORAS_RIVER}, DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION_NNL(RC_ZR_GS_TREE,  logic->IsChild && logic->CanKillEnemy(RE_GOLD_SKULLTULA, ED_CLOSE) && logic->CanBonkTrees()),
        LOCATION_NNL(RC_ZR_GRASS_1,  logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_2,  logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_3,  logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_4,  logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_5,  logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_6,  logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_7,  logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_8,  logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_9,  logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_10, logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_11, logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_GRASS_12, logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_TREE, logic->IsChild && logic->CanBonkTrees()),
        LOCATION(RC_ZR_BOULDER_1, logic->IsChild && logic->BlastOrSmash()),
        LOCATION(RC_ZR_BOULDER_2, logic->IsChild && logic->BlastOrSmash()),
        LOCATION(RC_ZR_BOULDER_3, logic->IsChild && logic->BlastOrSmash()),
        LOCATION(RC_ZR_BOULDER_4, logic->IsChild && logic->BlastOrSmash()),
    }, {
        //Exits
        Entrance(RR_ZORAS_RIVER,  []{return logic->IsAdult || logic->BlastOrSmash();}),
        Entrance(RR_HYRULE_FIELD, []{return true;}),
    });

    areaTable[RR_ZORAS_RIVER] = Region("Zora River", "Zora River", {RA_ZORAS_RIVER}, DAY_NIGHT_CYCLE, {
        //Events
        EventAccess(&logic->GossipStoneFairy, []{return logic->CallGossipFairy();}, true),
        EventAccess(&logic->BeanPlantFairy,   []{return logic->IsChild && logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS);}, true),
        EventAccess(&logic->ButterflyFairy,   []{return logic->CanUse(RG_STICKS);}, true),
        EventAccess(&logic->BugShrub,         []{return logic->CanCutShrubs();}, true),
    }, {
        //Locations
        LOCATION_NNL(RC_ZR_MAGIC_BEAN_SALESMAN,              logic->HasItem(RG_CHILD_WALLET) && logic->IsChild),
        LOCATION_NNL(RC_ZR_FROGS_OCARINA_GAME,               logic->IsChild && logic->CanUse(RG_ZELDAS_LULLABY) && logic->CanUse(RG_SARIAS_SONG) && logic->CanUse(RG_SUNS_SONG) && logic->CanUse(RG_EPONAS_SONG) && logic->CanUse(RG_SONG_OF_TIME) && logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION_NNL(RC_ZR_FROGS_IN_THE_RAIN,                logic->IsChild && logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION_NNL(RC_ZR_FROGS_ZELDAS_LULLABY,             logic->IsChild && logic->CanUse(RG_ZELDAS_LULLABY)),
        LOCATION_NNL(RC_ZR_FROGS_EPONAS_SONG,                logic->IsChild && logic->CanUse(RG_EPONAS_SONG)),
        LOCATION_NNL(RC_ZR_FROGS_SARIAS_SONG,                logic->IsChild && logic->CanUse(RG_SARIAS_SONG)),
        LOCATION_NNL(RC_ZR_FROGS_SUNS_SONG,                  logic->IsChild && logic->CanUse(RG_SUNS_SONG)),
        LOCATION_NNL(RC_ZR_FROGS_SONG_OF_TIME,               logic->IsChild && logic->CanUse(RG_SONG_OF_TIME)),
        LOCATION(RC_ZR_NEAR_OPEN_GROTTO_FREESTANDING_POH,    logic->IsChild || logic->CanUse(RG_HOVER_BOOTS) || (logic->IsAdult && ctx->GetTrickOption(RT_ZR_LOWER))),
        LOCATION(RC_ZR_NEAR_DOMAIN_FREESTANDING_POH,         logic->IsChild || logic->CanUse(RG_HOVER_BOOTS) || (logic->IsAdult && ctx->GetTrickOption(RT_ZR_UPPER))),
        LOCATION_NNL(RC_ZR_GS_LADDER,                        logic->IsChild && logic->CanAttack() && logic->CanGetNightTimeGS()),
        LOCATION(RC_ZR_GS_NEAR_RAISED_GROTTOS,               logic->IsAdult && logic->HookshotOrBoomerang() && logic->CanGetNightTimeGS()),
        LOCATION(RC_ZR_GS_ABOVE_BRIDGE,                      logic->IsAdult && logic->CanUse(RG_HOOKSHOT) && logic->CanGetNightTimeGS()),
        LOCATION_NNL(RC_ZR_BEAN_SPROUT_FAIRY_1,              logic->IsChild && logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION_NNL(RC_ZR_BEAN_SPROUT_FAIRY_2,              logic->IsChild && logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION_NNL(RC_ZR_BEAN_SPROUT_FAIRY_3,              logic->IsChild && logic->CanUse(RG_MAGIC_BEAN) && logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION_NNL(RC_ZR_NEAR_GROTTOS_GOSSIP_STONE_FAIRY,      logic->CallGossipFairy()),
        LOCATION_NNL(RC_ZR_NEAR_GROTTOS_GOSSIP_STONE_FAIRY_BIG,  logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION_NNL(RC_ZR_NEAR_DOMAIN_GOSSIP_STONE_FAIRY,       logic->CallGossipFairy()),
        LOCATION_NNL(RC_ZR_NEAR_DOMAIN_GOSSIP_STONE_FAIRY_BIG,   logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION_NNL(RC_ZR_BENEATH_WATERFALL_LEFT_RUPEE,         logic->IsAdult && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG))),
        LOCATION_NNL(RC_ZR_BENEATH_WATERFALL_MIDDLE_LEFT_RUPEE,  logic->IsAdult && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG))),
        LOCATION_NNL(RC_ZR_BENEATH_WATERFALL_MIDDLE_RIGHT_RUPEE, logic->IsAdult && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG))),
        LOCATION_NNL(RC_ZR_BENEATH_WATERFALL_RIGHT_RUPEE,        logic->IsAdult && (logic->HasItem(RG_BRONZE_SCALE) || logic->CanUse(RG_IRON_BOOTS) || logic->CanUse(RG_BOOMERANG))),
        LOCATION(RC_ZR_CIRCLE_ROCK_1,                        true),
        LOCATION(RC_ZR_CIRCLE_ROCK_2,                        true),
        LOCATION(RC_ZR_CIRCLE_ROCK_3,                        true),
        LOCATION(RC_ZR_CIRCLE_ROCK_4,                        true),
        LOCATION(RC_ZR_CIRCLE_ROCK_5,                        true),
        LOCATION(RC_ZR_CIRCLE_ROCK_6,                        true),
        LOCATION(RC_ZR_CIRCLE_ROCK_7,                        true),
        LOCATION(RC_ZR_CIRCLE_ROCK_8,                        true),
        LOCATION(RC_ZR_UPPER_CIRCLE_BOULDER,            logic->BlastOrSmash()),
        LOCATION(RC_ZR_UPPER_CIRCLE_ROCK_1,                  true),
        LOCATION(RC_ZR_UPPER_CIRCLE_ROCK_2,                  true),
        LOCATION(RC_ZR_UPPER_CIRCLE_ROCK_3,                  true),
        LOCATION(RC_ZR_UPPER_CIRCLE_ROCK_4,                  true),
        LOCATION(RC_ZR_UPPER_CIRCLE_ROCK_5,                  true),
        LOCATION(RC_ZR_UPPER_CIRCLE_ROCK_6,                  true),
        LOCATION(RC_ZR_UPPER_CIRCLE_ROCK_7,                  true),
        LOCATION(RC_ZR_UPPER_CIRCLE_ROCK_8,                  true),
        LOCATION(RC_ZR_ROCK,                                 true),
        LOCATION(RC_ZR_UNDERWATER_ROCK_1,                    logic->IsAdult || logic->CanUse(RG_BOMBCHU_5)),
        LOCATION(RC_ZR_UNDERWATER_ROCK_2,                    logic->IsAdult || logic->CanUse(RG_BOMBCHU_5)),
        LOCATION(RC_ZR_UNDERWATER_ROCK_3,                    logic->IsAdult || logic->CanUse(RG_BOMBCHU_5)),
        LOCATION(RC_ZR_UNDERWATER_ROCK_4,                    logic->IsAdult || logic->CanUse(RG_BOMBCHU_5)),
        LOCATION(RC_ZR_NEAR_GROTTOS_GOSSIP_STONE,            true),
        LOCATION(RC_ZR_NEAR_DOMAIN_GOSSIP_STONE,             true),
        LOCATION(RC_ZR_NEAR_FREESTANDING_POH_GRASS,          logic->CanCutShrubs()),
    }, {
        //Exits
        Entrance(RR_ZR_FRONT,            []{return true;}),
        Entrance(RR_ZR_OPEN_GROTTO,      []{return true;}),
        Entrance(RR_ZR_FAIRY_GROTTO,     []{return Here(RR_ZORAS_RIVER, []{return logic->BlastOrSmash();});}, true),
        Entrance(RR_THE_LOST_WOODS,      []{return logic->HasItem(RG_SILVER_SCALE) || logic->CanUse(RG_IRON_BOOTS);}),
        Entrance(RR_ZR_STORMS_GROTTO,    []{return logic->CanOpenStormsGrotto();}, true),
        Entrance(RR_ZR_BEHIND_WATERFALL, []{return ctx->GetOption(RSK_SLEEPING_WATERFALL).Is(RO_WATERFALL_OPEN) || Here(RR_ZORAS_RIVER, []{return logic->CanUse(RG_ZELDAS_LULLABY);}) || (logic->IsChild && ctx->GetTrickOption(RT_ZR_CUCCO)) || (logic->IsAdult && logic->CanUse(RG_HOVER_BOOTS) && ctx->GetTrickOption(RT_ZR_HOVERS));}),
    });

    areaTable[RR_ZR_BEHIND_WATERFALL] = Region("ZR Behind Waterfall", "Zora River", {RA_ZORAS_RIVER}, DAY_NIGHT_CYCLE, {}, {}, {
        //Exits
        Entrance(RR_ZORAS_RIVER,  []{return true;}),
        Entrance(RR_ZORAS_DOMAIN, []{return true;}),
    });

    areaTable[RR_ZR_OPEN_GROTTO] = Region("ZR Open Grotto", "ZR Open Grotto", {}, NO_DAY_NIGHT_CYCLE, grottoEvents, {
        //Locations
        LOCATION(RC_ZR_OPEN_GROTTO_CHEST,                  true),
        LOCATION_NNL(RC_ZR_OPEN_GROTTO_FISH,                   logic->HasBottle()),
        LOCATION_NNL(RC_ZR_OPEN_GROTTO_GOSSIP_STONE_FAIRY,     logic->CallGossipFairy()),
        LOCATION_NNL(RC_ZR_OPEN_GROTTO_GOSSIP_STONE_FAIRY_BIG, logic->CanUse(RG_SONG_OF_STORMS)),
        LOCATION(RC_ZR_OPEN_GROTTO_GOSSIP_STONE,           true),
        LOCATION(RC_ZR_OPEN_GROTTO_BEEHIVE_LEFT,           logic->CanBreakLowerBeehives()),
        LOCATION(RC_ZR_OPEN_GROTTO_BEEHIVE_RIGHT,          logic->CanBreakLowerBeehives()),
        LOCATION_NNL(RC_ZR_OPEN_GROTTO_GRASS_1,                logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_OPEN_GROTTO_GRASS_2,                logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_OPEN_GROTTO_GRASS_3,                logic->CanCutShrubs()),
        LOCATION_NNL(RC_ZR_OPEN_GROTTO_GRASS_4,                logic->CanCutShrubs()),
    }, {
        //Exits
        Entrance(RR_ZORAS_RIVER, []{return true;}),
    });

    areaTable[RR_ZR_FAIRY_GROTTO] = Region("ZR Fairy Grotto", "ZR Fairy Grotto", {}, NO_DAY_NIGHT_CYCLE, {
        //Event
        EventAccess(&logic->FreeFairies, []{return true;}),
    }, {
        //Locations
        LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_1, true),
        LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_2, true),
        LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_3, true),
        LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_4, true),
        LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_5, true),
        LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_6, true),
        LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_7, true),
        LOCATION(RC_ZR_FAIRY_GROTTO_FAIRY_8, true),
    }, {
        //Exits
        Entrance(RR_ZORAS_RIVER, []{return true;}),
    });

    areaTable[RR_ZR_STORMS_GROTTO] = Region("ZR Storms Grotto", "ZR Storms Grotto", {}, NO_DAY_NIGHT_CYCLE, {}, {
        //Locations
        LOCATION_NNL(RC_ZR_DEKU_SCRUB_GROTTO_REAR,  logic->CanStunDeku()),
        LOCATION_NNL(RC_ZR_DEKU_SCRUB_GROTTO_FRONT, logic->CanStunDeku()),
        LOCATION(RC_ZR_STORMS_GROTTO_BEEHIVE,   logic->CanBreakUpperBeehives()),
    }, {
        //Exits
        Entrance(RR_ZORAS_RIVER, []{return true;}),
    });

    // clang-format on
}
