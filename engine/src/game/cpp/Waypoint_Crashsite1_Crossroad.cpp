#include "../game_all.h"

void Waypoint_Crashsite1_Crossroad::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_exit");
	doubleClickCondition = S("visited_crossroad");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Waypoint_Crashsite1_Crossroad::clickAction()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
}

void Waypoint_Crashsite1_Crossroad::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_Crashsite1_Crossroad::clickAction2()
{
}

void Waypoint_Crashsite1_Crossroad::clickAction0()
{
}
