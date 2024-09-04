#include "soh/Enhancements/game-interactor/GameInteractor_Hooks.h"
#include "fairy_shuffle.h"
#include "src/overlays/actors/ovl_En_Elf/z_en_elf.h"

void FairyOnVanillaBehaviorHandler(GIVanillaBehavior id, bool* should, void* optionalArg) {
	if (id == VB_SPAWN_FAIRY_GROUP) {
		// TODO
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