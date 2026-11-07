#include "../game_all.h"

void OutpostSomeSand::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (GameDataController::gd->getObjective(S("outpost_hatch_open")))
	{
		if (wc != nullptr)
		{
			PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Hangar);
		}
		if (npcwc != nullptr)
		{
			npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Hangar);
		}
	}
}

void OutpostSomeSand::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::ssg->setStepType2(StepSoundGenerator::METAL, AudioReverbPreset::Hangar);
	}
	if (npcwc != nullptr)
	{
		npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType2(StepSoundGenerator::METAL, AudioReverbPreset::Hangar);
	}
}
