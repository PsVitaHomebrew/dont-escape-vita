#include "../game_all.h"

void LocationBaseUpstairsStairs::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_stairs_down");
	doubleClickCondition = S("visited_location1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
}

void LocationBaseUpstairsStairs::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("thug_to_kill_bathroom")))
	{
		doubleClickCondition = S("none");
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else if (GameDataController::gd->getCurrentDay() == 2 && !GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
	{
		doubleClickCondition = S("none");
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		doubleClickCondition = S("visited_location1");
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void LocationBaseUpstairsStairs::clickAction()
{
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("thug_to_kill_bathroom")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("day4_start_stairs_no")));
		return;
	}
	if (GameDataController::gd->getCurrentDay() == 2 && !GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("heli_crash_check")));
		return;
	}
	PlayerController::pc->spawnName = S("Stairs_Exit");
	CurtainController::cc->fadeOut(S("Location1"), WalkController::Direction::E);
}

void LocationBaseUpstairsStairs::updateState()
{
}

void LocationBaseUpstairsStairs::clickAction2()
{
}

void LocationBaseUpstairsStairs::clickAction0()
{
}
