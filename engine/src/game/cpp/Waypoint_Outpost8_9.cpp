#include "../game_all.h"

void Waypoint_Outpost8_9::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_elev_up");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	doubleClickCondition = String::Empty;
}

void Waypoint_Outpost8_9::clickAction()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
	if (GameDataController::gd->getObjective(S("outpost_belt_elevator")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->elevator_away);
		PlayerController::pc->spawnName = S("Waypoint_Outpost9_8");
		CurtainController::cc->fadeOut(S("LocationOutpost9"), WalkController::Direction::S_, nullptr, nullptr, false, nullptr, 0.015f);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->engine_wrong);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("elevator_not_working")));
	}
}

void Waypoint_Outpost8_9::rideDown()
{
}

void Waypoint_Outpost8_9::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_belt_elevator")))
	{
		actionType = Type::Transition;
	}
	else
	{
		actionType = Type::NormalAction;
	}
}

void Waypoint_Outpost8_9::clickAction2()
{
}

void Waypoint_Outpost8_9::clickAction0()
{
}
