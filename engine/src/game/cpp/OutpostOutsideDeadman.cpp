#include "../game_all.h"

void OutpostOutsideDeadman::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = true;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_dead_man");
	range = 5.0f;
}

void OutpostOutsideDeadman::clickAction()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_dead_man")));
}

void OutpostOutsideDeadman::updateState()
{
}

void OutpostOutsideDeadman::clickAction2()
{
}

void OutpostOutsideDeadman::clickAction0()
{
}

void OutpostOutsideDeadman::whatOnClick0()
{
}

void OutpostOutsideDeadman::whatOnClick()
{
}
