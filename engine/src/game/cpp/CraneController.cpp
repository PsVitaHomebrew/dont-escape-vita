#include "../game_all.h"

void CraneController::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_e");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_crane_controller");
	range = 1.0f;
	updateState();
}

void CraneController::Update()
{
}

void CraneController::clickAction()
{
	contrBack->set_enabled(true);
	lever1->showLever();
	lever2->showLever();
	lever3->showLever();
}

void CraneController::updateState()
{
}

void CraneController::clickAction2()
{
}

void CraneController::clickAction0()
{
}

void CraneController::whatOnClick0()
{
}

void CraneController::whatOnClick()
{
}
