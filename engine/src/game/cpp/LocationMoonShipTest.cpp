#include "../game_all.h"

void LocationMoonShipTest::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airplane_pilot");
	range = 1.0f;
}

void LocationMoonShipTest::clickAction()
{
	GameDataController::gd->setObjective(S("moon_shocked1"), true);
	GameDataController::gd->setObjective(S("moon_shocked2"), true);
	GameDataController::gd->setObjective(S("moon_shocked3"), true);
	PlayerController::pc->spawnName = S("WakeUp");
	CurtainController::cc->fadeOut(S("MoonShip"), WalkController::Direction::E, S("wake_up"));
}

void LocationMoonShipTest::updateState()
{
}

void LocationMoonShipTest::clickAction2()
{
}

void LocationMoonShipTest::clickAction0()
{
}

void LocationMoonShipTest::whatOnClick0()
{
}

void LocationMoonShipTest::whatOnClick()
{
}
