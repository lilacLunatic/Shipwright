#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "fairy_shuffle.h"
#include "randomizer_grotto.h"
#include "draw.h"
#include "src/overlays/actors/ovl_En_Elf/z_en_elf.h"


void FairyDrawRandomizedItem(EnElf* enElf, PlayState* play) {
    GetItemEntry randoGetItem = enElf->sohFairyIdentity.itemEntry;
    if (CVarGetInteger(CVAR_RANDOMIZER_ENHANCEMENT("MysteriousShuffle"), 0)) {
        randoGetItem = GET_ITEM_MYSTERY;
    }
    func_8002ED80(&enElf->actor, play, 0);
    EnItem00_CustomItemsParticles(&enElf->actor, play, randoGetItem);
    GetItemEntry_Draw(play, randoGetItem);
}

void FairyOnVanillaBehaviorHandler(GIVanillaBehavior id, bool* should, void* optionalArg) {
    if (id == VB_SPAWN_FAIRY_GROUP) {
        EnElf* enElf = static_cast<EnElf*>(optionalArg);
        s16 grottoId = (gPlayState->sceneNum == SCENE_FAIRYS_FOUNTAIN) ? Grotto_CurrentGrotto() : 0;
        for (s16 index = 0; index < 8; index++) {
            EnElf* newFairy = (EnElf*)Actor_Spawn(&gPlayState->actorCtx, gPlayState, ACTOR_EN_ELF, enElf->actor.world.pos.x,
                        enElf->actor.world.pos.y - 30.0f, enElf->actor.world.pos.z, 0, 0, 0, FAIRY_HEAL, true);
            //EnElf* newFairy = newActor);
            Rando::Location* location = OTRGlobals::Instance->gRandomizer->GetCheckObjectFromActor(ACTOR_EN_ELF, gPlayState->sceneNum, TWO_ACTOR_PARAMS(grottoId, index));
            if (location != NULL && location->GetRandomizerCheck() != RC_UNKNOWN_CHECK) {
                GetItemEntry item = Rando::Context::GetInstance()->GetFinalGIEntry(location->GetRandomizerCheck(), true, GI_FAIRY);
                newFairy->sohFairyIdentity = { static_cast<RandomizerInf>(location->GetCollectionCheck().flag), item };
                newFairy->actor.draw = (ActorFunc)FairyDrawRandomizedItem;
            }
        }
        *should = false;
    }
}

void FairyOnActorInitHandler(void* actorRef) {
    EnElf* enElf = static_cast<EnElf*>(actorRef);
    enElf->sohFairyIdentity = { RAND_INF_MAX, GET_ITEM_NONE };
}

uint32_t onVanillaBehaviorHook = 0;
uint32_t onActorInitHook = 0;

void FairyRegisterHooks() {
    onVanillaBehaviorHook = GameInteractor::Instance->RegisterGameHook<GameInteractor::OnVanillaBehavior>(FairyOnVanillaBehaviorHandler);
    onActorInitHook = GameInteractor::Instance->RegisterGameHookForID<GameInteractor::OnActorInit>(ACTOR_EN_ELF, FairyOnActorInitHandler);
}

void FairyUnregisterHooks() {
    GameInteractor::Instance->UnregisterGameHook<GameInteractor::OnVanillaBehavior>(onVanillaBehaviorHook);
    GameInteractor::Instance->UnregisterGameHookForID<GameInteractor::OnActorInit>(onActorInitHook);

    onVanillaBehaviorHook = 0;
    onActorInitHook = 0;
}