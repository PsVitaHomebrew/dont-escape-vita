#include "../game_all.h"

void WaypointRoof1Hatch::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("roof_hatch");
	range = 5.0f;
	doubleClickCondition = S("visited_attic1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
}

void WaypointRoof1Hatch::clickAction()
{
	PlayerController::pc->spawnName = S("Attic1Hatch2");
	CurtainController::cc->fadeOut(S("LocationAttic1"), WalkController::Direction::S_, S("window_jump"));
}

void WaypointRoof1Hatch::updateState()
{
}

void WaypointRoof1Hatch::clickAction2()
{
}

void WaypointRoof1Hatch::clickAction0()
{
}
