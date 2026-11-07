#include "../game_all.h"

void LocationBaseBathroomDoor::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_bathroom_exit");
	range = 5.0f;
	doubleClickCondition = S("visited_baseUpstairs");
	actionType = Type::Transition;
	trans_dir = WalkController_Direction::E;
}

void LocationBaseBathroomDoor::clickAction()
{
	PlayerController::pc->spawnName = S("BathroomDoor");
	CurtainController::cc->fadeOut(S("LocationBaseUpstairs"), WalkController_Direction::E);
}

void LocationBaseBathroomDoor::updateState()
{
}

void LocationBaseBathroomDoor::clickAction2()
{
}

void LocationBaseBathroomDoor::clickAction0()
{
}
