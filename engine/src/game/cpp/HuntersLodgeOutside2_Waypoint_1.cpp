#include "../game_all.h"

void HuntersLodgeOutside2_Waypoint_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_to_front");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = S("visited_hunters_lodge_outside_1");
}

void HuntersLodgeOutside2_Waypoint_1::clickAction()
{
	PlayerController::pc->spawnName = S("HuntersLodgeOutside1_Waypoint_2");
	CurtainController::cc->fadeOut(S("HuntersLodgeOutside1"), WalkController::Direction::W);
}

void HuntersLodgeOutside2_Waypoint_1::updateState()
{
}

void HuntersLodgeOutside2_Waypoint_1::clickAction2()
{
}

void HuntersLodgeOutside2_Waypoint_1::clickAction0()
{
}
