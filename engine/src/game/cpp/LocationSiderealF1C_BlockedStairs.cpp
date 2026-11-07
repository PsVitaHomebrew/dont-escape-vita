#include "../game_all.h"

void LocationSiderealF1C_BlockedStairs::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_stairs_up_blocked");
	actionType = Type::NormalAction;
	trans_dir = WalkController::Direction::N;
	range = 200.0f;
}

void LocationSiderealF1C_BlockedStairs::clickAction()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_collapsed_stairs")));
}

void LocationSiderealF1C_BlockedStairs::updateState()
{
}

void LocationSiderealF1C_BlockedStairs::clickAction2()
{
}

void LocationSiderealF1C_BlockedStairs::clickAction0()
{
}
