#include "../game_all.h"

void OutpostAreaClimb::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Mountains);
		wc->speed = wc->MAX_SPEED * 0.8f;
	}
	if (npcwc != nullptr)
	{
		npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Mountains);
	}
}

void OutpostAreaClimb::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		wc->speed = wc->MAX_SPEED;
	}
	if (!(npcwc != nullptr))
	{
	}
}
