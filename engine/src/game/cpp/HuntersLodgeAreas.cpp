#include "../game_all.h"

void HuntersLodgeAreas::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::ssg->setStepType2(StepSoundGenerator::GRASS, AudioReverbPreset::Forest);
	}
	if (npcwc != nullptr)
	{
		npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType2(StepSoundGenerator::GRASS, AudioReverbPreset::Forest);
	}
}

void HuntersLodgeAreas::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::ssg->setStepType2(StepSoundGenerator::WOOD, AudioReverbPreset::Forest);
	}
	if (npcwc != nullptr)
	{
		npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType2(StepSoundGenerator::WOOD, AudioReverbPreset::Forest);
	}
}
