#include "../game_all.h"

void LocationSiderealF0C2_Waypoint_Outside::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_exit5");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void LocationSiderealF0C2_Waypoint_Outside::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_exit_unlocked")))
	{
		if (GameDataController::gd->getObjective(S("barry_warned")))
		{
			GameDataController::gd->setObjective(S("npc2_joined"), true);
		}
		if (GameDataController::gd->getObjective(S("cody_warned")))
		{
			GameDataController::gd->setObjective(S("npc3_joined"), true);
		}
		PlayerController::pc->spawnName = S("SiderealOutside3_Waypoint_Inside");
		CurtainController::cc->fadeOut(S("SiderealOutside3"), WalkController::Direction::S_, S("action_stnd_s"));
	}
	else
	{
		GameDataController::gd->setObjective(S("sidereal_exit_unlocked"), true);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("generic_unlocked")));
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->crowbar_pry_open);
		updateAll();
	}
}

void LocationSiderealF0C2_Waypoint_Outside::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_exit_unlocked")))
	{
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		doubleClickCondition = S("visited_sidereal_outside_3");
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		light1->set_enabled(false);
		light2->set_enabled(true);
		overlight->set_enabled(true);
	}
	else
	{
		characterAnimationName = S("open_n");
		animationFlip = false;
		useCurrentDirection = false;
		doubleClickCondition = String::Empty;
		actionType = Type::NormalAction;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		light1->set_enabled(true);
		light2->set_enabled(false);
		overlight->set_enabled(false);
	}
}

void LocationSiderealF0C2_Waypoint_Outside::clickAction2()
{
}

void LocationSiderealF0C2_Waypoint_Outside::clickAction0()
{
}
