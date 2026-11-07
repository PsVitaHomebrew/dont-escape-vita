#include "../game_all.h"

void TentAreaAction1::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (!GameDataController::gd->getObjective(S("tent_distance_checked")) && wc != nullptr)
	{
		PlayerController::wc->fullStop(true);
		PlayerController::wc->forceAnimation(S("action_stnd_ne"), false, false, false);
		PlayerController::wc->fullStop(true);
		GameObject::Find(S("distance"))->GetComponent<TentDistanceThings>()->clickAction();
	}
}

void TentAreaAction1::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
