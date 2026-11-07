#include "../game_all.h"

void LocationSiderealF2B_Generator::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e_in");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_battery");
	actionType = Type::NormalAction;
}

void LocationSiderealF2B_Generator::clickAction()
{
	PlayerController::pc->spawnName = S("ElectricExit");
	CurtainController::cc->fadeOut(S("LocationElectric"), WalkController::Direction::S_);
}

void LocationSiderealF2B_Generator::updateState()
{
}

void LocationSiderealF2B_Generator::clickAction2()
{
}

void LocationSiderealF2B_Generator::clickAction0()
{
}
