#include "../game_all.h"

void FuseboxLight1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("fuse_door");
	range = 8000.0f;
	teleport = false;
	updateState();
}

void FuseboxLight1::Update()
{
}

void FuseboxLight1::whatOnClick()
{
}

void FuseboxLight1::clickAction()
{
	if (!GameDataController::gd->getObjective(S("outpost_door_powered")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("fuse_doormat_off")), true, false, false, 150);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("fuse_doormat_on")), true, false, false, 150);
	}
}

void FuseboxLight1::updateState()
{
	if (!GameDataController::gd->getObjective(S("outpost_door_powered")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void FuseboxLight1::clickAction2()
{
}

void FuseboxLight1::clickAction0()
{
}
