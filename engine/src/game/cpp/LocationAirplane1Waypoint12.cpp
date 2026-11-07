#include "../game_all.h"

void LocationAirplane1Waypoint12::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airplane_exit");
	doubleClickCondition = S("visited_airplane2");
	actionType = Type::Transition;
	trans_dir = WalkController_Direction::N;
	range = 2.0f;
}

void LocationAirplane1Waypoint12::clickAction()
{
	if (GameDataController::gd->getObjective(S("plane_undig")))
	{
		PlayerController::pc->setBusy(true);
		PlayerController::pc->spawnName = S("LocationAirplane2Waypoint21");
		CurtainController::cc->fadeOut(S("LocationAirplane2"), WalkController_Direction::N);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("plane_covered")));
	}
}

void LocationAirplane1Waypoint12::updateState()
{
	if (GameDataController::gd->getObjective(S("plane_undig")))
	{
		colliderManager->setCollider(1);
		actionType = Type::Transition;
		characterAnimationName = S("action_stnd_");
	}
	else
	{
		colliderManager->setCollider(0);
		actionType = Type::NormalAction;
		characterAnimationName = S("stop");
	}
}

void LocationAirplane1Waypoint12::clickAction2()
{
}

void LocationAirplane1Waypoint12::clickAction0()
{
}
