#include "../game_all.h"

void Waypoint_Outside_Crossroad::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("down_hill");
	doubleClickCondition = S("visited_crossroad");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
}

void Waypoint_Outside_Crossroad::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Crossroad_Base");
	CurtainController::cc->fadeOut(S("LocationCrossroad"), WalkController::Direction::S_);
}

void Waypoint_Outside_Crossroad::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_Outside_Crossroad::clickAction2()
{
}

void Waypoint_Outside_Crossroad::clickAction0()
{
}
