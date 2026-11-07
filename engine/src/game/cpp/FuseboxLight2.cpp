#include "../game_all.h"

void FuseboxLight2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("fuse_elevator");
	range = 8000.0f;
	teleport = false;
	updateState();
}

void FuseboxLight2::Update()
{
}

void FuseboxLight2::whatOnClick()
{
}

void FuseboxLight2::clickAction()
{
	if (!GameDataController::gd->getObjective(S("outpost_elevator_powered")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("fuse_elevator_off")), true, false, false, 150);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("fuse_elevator_on")), true, false, false, 150);
	}
}

void FuseboxLight2::updateState()
{
	if (!GameDataController::gd->getObjective(S("outpost_elevator_powered")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void FuseboxLight2::clickAction2()
{
}

void FuseboxLight2::clickAction0()
{
}
