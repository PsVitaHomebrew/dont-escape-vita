#include "../game_all.h"

void LocationSiderealRoof_Waypoint_F3S::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_hole");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
}

void LocationSiderealRoof_Waypoint_F3S::clickAction()
{
	int num = 0;
	if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
	{
		num++;
	}
	if (num > 0)
	{
		if (GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
		{
			if (num == 1)
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("save_npc_first1")));
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("save_npc_first2")));
			}
		}
		else if (GameDataController::gd->getObjective(S("sidereal_roof_npc_shocked")))
		{
			if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("save_npc_shocked_barry")));
			}
			if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("save_npc_shocked_cody")));
			}
		}
		else
		{
			PlayerController::pc->spawnName = S("LocationSiderealF3S_Waypoint_Roof");
			CurtainController::cc->fadeOut(S("SiderealF3S"), WalkController::Direction::E);
		}
	}
	else
	{
		PlayerController::pc->spawnName = S("LocationSiderealF3S_Waypoint_Roof");
		CurtainController::cc->fadeOut(S("SiderealF3S"), WalkController::Direction::E);
	}
}

void LocationSiderealRoof_Waypoint_F3S::updateState()
{
}

void LocationSiderealRoof_Waypoint_F3S::clickAction2()
{
}

void LocationSiderealRoof_Waypoint_F3S::clickAction0()
{
}
