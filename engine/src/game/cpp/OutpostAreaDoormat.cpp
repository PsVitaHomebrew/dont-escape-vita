#include "../game_all.h"

void OutpostAreaDoormat::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::ssg->setStepType2(StepSoundGenerator::METAL, AudioReverbPreset::Mountains);
		if (GameDataController::gd->getObjective(S("outpost_door_powered")) && !GameDataController::gd->getObjective(S("outpost_door_open")) && !GameDataController::gd->getObjective(S("outpost_doormat_triggered")))
		{
			GameDataController::gd->setObjective(S("outpost_doormat_triggered"), true);
			mataEl->set_enabled(true);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->small_powerup);
			PlayerController::pc->allowDrop = false;
			loc->doormatGo(String::Empty);
		}
	}
	if (npcwc != nullptr)
	{
		npcwc->gameObject->GetComponent<StepSoundGenerator>()->setStepType2(StepSoundGenerator::METAL, AudioReverbPreset::Mountains);
	}
}

void OutpostAreaDoormat::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr && GameDataController::gd->getObjective(S("outpost_door_powered")))
	{
		if (GameDataController::gd->getObjective(S("outpost_doormat_triggered")))
		{
			GameDataController::gd->setObjective(S("outpost_doormat_triggered"), false);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 0);
			mataEl->set_enabled(false);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->small_powerdown);
			loc->letItGo();
			PlayerController::pc->allowDrop = true;
		}
		if (GameDataController::gd->getObjective(S("outpost_door_open")))
		{
			GameDataController::gd->setObjective(S("outpost_door_open"), false);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_slide);
			GameObject::Find(S("Waypoint_Outpost2_3"))->GetComponent<Waypoint_Outpost2_3>()->closedo();
		}
	}
	if (!(npcwc != nullptr))
	{
	}
}
