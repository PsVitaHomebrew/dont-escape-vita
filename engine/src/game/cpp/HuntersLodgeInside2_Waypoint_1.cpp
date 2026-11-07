#include "../game_all.h"

void HuntersLodgeInside2_Waypoint_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_to_inside1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	doubleClickCondition = S("visited_hunters_lodge_1");
}

void HuntersLodgeInside2_Waypoint_1::clickAction()
{
	PlayerController::pc->spawnName = S("HuntersLodgeInside1_Waypoint_2");
	CurtainController::cc->fadeOut(S("HuntersLodgeInside1"), WalkController::Direction::S_);
}

void HuntersLodgeInside2_Waypoint_1::updateState()
{
}

void HuntersLodgeInside2_Waypoint_1::clickAction2()
{
}

void HuntersLodgeInside2_Waypoint_1::clickAction0()
{
}
