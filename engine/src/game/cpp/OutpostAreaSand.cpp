#include "../game_all.h"

void OutpostAreaSand::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Mountains);
	}
	if (npcwc != nullptr)
	{
		npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Mountains);
	}
}

void OutpostAreaSand::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
