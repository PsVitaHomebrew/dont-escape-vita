#include "../game_all.h"

void CS2_Waypoint_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_waypoint_2_1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = String::Empty;
}

void CS2_Waypoint_1::clickAction()
{
	PlayerController::pc->spawnName = S("CS1_Waypoint_2");
	CurtainController::cc->fadeOut(S("CS1"), WalkController::Direction::S_);
}

void CS2_Waypoint_1::updateState()
{
}

void CS2_Waypoint_1::clickAction2()
{
}

void CS2_Waypoint_1::clickAction0()
{
}
