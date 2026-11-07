#include "../game_all.h"

void Outpost7_BigComputer::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_big_computer");
	range = 5.0f;
}

void Outpost7_BigComputer::clickAction()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_big_computer")));
}

void Outpost7_BigComputer::updateState()
{
	colliderManager->setCollider(0);
}

void Outpost7_BigComputer::clickAction2()
{
}

void Outpost7_BigComputer::clickAction0()
{
}

void Outpost7_BigComputer::whatOnClick0()
{
}

void Outpost7_BigComputer::whatOnClick()
{
}
