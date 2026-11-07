#include "../game_all.h"

void CSEndReloadAreaAction::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr && GameDataController::gd->getObjective(S("cs_arrive_from_inside")) && !GameDataController::gd->getObjective(S("cs_safe")) && !GameDataController::gd->getObjective(S("cs_thug_shot")))
	{
		GameDataController::gd->setObjective(S("cs_arrive_from_inside"), false);
		thug->GetComponent<Animator>()->Play(S("thug_watch"));
	}
	if (npcwc != nullptr)
	{
	}
	if (!(gic != nullptr))
	{
	}
}

void CSEndReloadAreaAction::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
