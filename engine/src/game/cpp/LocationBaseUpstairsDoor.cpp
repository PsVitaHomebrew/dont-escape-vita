#include "../game_all.h"

void LocationBaseUpstairsDoor::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_bathroom_entry");
	range = 5.0f;
	doubleClickCondition = S("visited_baseBathroom");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void LocationBaseUpstairsDoor::clickAction()
{
	PlayerController::pc->spawnName = S("BathroomDoor");
	CurtainController::cc->fadeOut(S("LocationBaseBathroom"), WalkController::Direction::W);
}

void LocationBaseUpstairsDoor::updateState()
{
}

void LocationBaseUpstairsDoor::clickAction2()
{
}

void LocationBaseUpstairsDoor::clickAction0()
{
}
