#include "../game_all.h"

void BridgeAreaAction1::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		if (mode == 1 && GameDataController::gd->getObjective(S("bridge_planks_used_1")))
		{
			PlayerController::ssg->setStepType(S("normal"));
		}
		else if (mode == 2)
		{
			PlayerController::ssg->setStepType(S("dirt"));
		}
		else
		{
			PlayerController::ssg->setStepType(S("road"));
		}
	}
	if (npcwc != nullptr)
	{
		if (mode == 1 && GameDataController::gd->getObjective(S("bridge_planks_used_1")))
		{
			npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType(S("normal"));
		}
		else if (mode == 2)
		{
			npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType(S("dirt"));
		}
		else
		{
			npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType(S("road"));
		}
	}
}

void BridgeAreaAction1::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
