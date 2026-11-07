#include "../game_all.h"

void HuntersLodgeOutside1_Waypoint_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_to_back");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	doubleClickCondition = S("visited_hunters_lodge_outside_2");
}

void HuntersLodgeOutside1_Waypoint_2::clickAction()
{
	PlayerController::pc->spawnName = S("HuntersLodgeOutside2_Waypoint_1");
	CurtainController::cc->fadeOut(S("HuntersLodgeOutside2"), WalkController::Direction::E);
}

void HuntersLodgeOutside1_Waypoint_2::updateState()
{
}

void HuntersLodgeOutside1_Waypoint_2::clickAction2()
{
}

void HuntersLodgeOutside1_Waypoint_2::clickAction0()
{
}
