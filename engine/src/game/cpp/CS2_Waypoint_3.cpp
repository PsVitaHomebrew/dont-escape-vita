#include "../game_all.h"

void CS2_Waypoint_3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_in_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_waypoint_2_3");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
}

void CS2_Waypoint_3::clickAction()
{
	GameDataController::gd->setObjective(S("cs_rain_enter_left"), true);
	PlayerController::pc->spawnName = S("CS3_Waypoint_2");
	CurtainController::cc->fadeOut(S("CS3"), WalkController::Direction::E);
}

void CS2_Waypoint_3::updateState()
{
}

void CS2_Waypoint_3::clickAction2()
{
}

void CS2_Waypoint_3::clickAction0()
{
}
