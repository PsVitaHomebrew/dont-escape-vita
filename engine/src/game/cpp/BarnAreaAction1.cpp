#include "../game_all.h"

void BarnAreaAction1::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::ssg->setStepType(StepSoundGenerator::HAY);
	}
	if (npcwc != nullptr)
	{
		npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType(StepSoundGenerator::HAY);
	}
}

void BarnAreaAction1::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::ssg->setStepType(StepSoundGenerator::DIRT);
	}
	if (npcwc != nullptr)
	{
		npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType(StepSoundGenerator::DIRT);
	}
}
