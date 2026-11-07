#include "../game_all.h"

void Waypoint_Outpost9_8::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_elev_down");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	range = 2.0f;
	doubleClickCondition = String::Empty;
}

void Waypoint_Outpost9_8::clickAction()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->elevator_away);
	PlayerController::pc->spawnName = S("Waypoint_Outpost8_9");
	CurtainController::cc->fadeOut(S("LocationOutpost8"), WalkController::Direction::S_, nullptr, nullptr, false, nullptr, 0.015f);
}

void Waypoint_Outpost9_8::rideDown()
{
}

void Waypoint_Outpost9_8::updateState()
{
}

void Waypoint_Outpost9_8::clickAction2()
{
}

void Waypoint_Outpost9_8::clickAction0()
{
}
