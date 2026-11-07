#include "../game_all.h"

void HuntersLodgeInside1_Waypoint_Outside::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_to_outside");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = S("visited_hunters_lodge_outside_1");
}

void HuntersLodgeInside1_Waypoint_Outside::clickAction()
{
	PlayerController::pc->spawnName = S("HuntersLodgeOutside1_Waypoint_Inside");
	CurtainController::cc->fadeOut(S("HuntersLodgeOutside1"), WalkController::Direction::W);
}

void HuntersLodgeInside1_Waypoint_Outside::updateState()
{
}

void HuntersLodgeInside1_Waypoint_Outside::clickAction2()
{
}

void HuntersLodgeInside1_Waypoint_Outside::clickAction0()
{
}
