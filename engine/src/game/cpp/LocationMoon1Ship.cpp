#include "../game_all.h"

void LocationMoon1Ship::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("suit_action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ship_derlict");
	range = 200.0f;
	actionType = Type::NormalAction;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
}

void LocationMoon1Ship::clickAction()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("no_point_going_back")));
}

void LocationMoon1Ship::updateState()
{
}

void LocationMoon1Ship::clickAction2()
{
}

void LocationMoon1Ship::clickAction0()
{
}
