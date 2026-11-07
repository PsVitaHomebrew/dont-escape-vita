#include "../game_all.h"

void CSFlyAwayAreaAction::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		if (!GameDataController::gd->getObjective(S("cs_crow_away")))
		{
			crow->Play(S("crow_fly_away"));
			GameDataController::gd->setObjective(S("cs_crow_away"), true);
		}
		if (GameDataController::gd->getObjective(S("cs_thug_shot")) || GameDataController::gd->getCurrentDay() != 3 || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 0)
		{
			exitcs1->doubleClickCondition = S("visited_cs_1");
			exitcs3->doubleClickCondition = S("visited_cs_3");
		}
		else if (PlayerController::wc->currentXY.x > 120.0f)
		{
			exitcs1->doubleClickCondition = String::Empty;
			exitcs3->doubleClickCondition = S("visited_cs_3");
		}
		else
		{
			exitcs1->doubleClickCondition = S("visited_cs_1");
			exitcs3->doubleClickCondition = String::Empty;
		}
	}
	if (npcwc != nullptr)
	{
	}
	if (!(gic != nullptr))
	{
	}
}

void CSFlyAwayAreaAction::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
