#include "../game_all.h"

void HuntersLodgeOutside1_Waypoint_Inside::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_to_inside");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = S("visited_hunters_lodge_inside_1");
}

void HuntersLodgeOutside1_Waypoint_Inside::clickAction()
{
	PlayerController::pc->spawnName = S("HuntersLodgeInside1_Waypoint_Outside");
	CurtainController::cc->fadeOut(S("HuntersLodgeInside1"), WalkController::Direction::E);
}

void HuntersLodgeOutside1_Waypoint_Inside::updateState()
{
}

void HuntersLodgeOutside1_Waypoint_Inside::clickAction2()
{
}

void HuntersLodgeOutside1_Waypoint_Inside::clickAction0()
{
}
