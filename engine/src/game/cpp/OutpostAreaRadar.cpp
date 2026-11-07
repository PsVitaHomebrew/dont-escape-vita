#include "../game_all.h"

void OutpostAreaRadar::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Mountains);
		PlayerController::pc->allowDrop = false;
	}
	if (npcwc != nullptr)
	{
		npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Mountains);
	}
}

void OutpostAreaRadar::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
