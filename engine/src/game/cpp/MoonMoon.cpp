#include "../game_all.h"

void MoonMoon::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_ne");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moon");
	range = 8000.0f;
	teleport = false;
	updateState();
}

void MoonMoon::Update()
{
}

void MoonMoon::whatOnClick()
{
}

void MoonMoon::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("moon")), true, false, false, 150);
}

void MoonMoon::updateState()
{
	if (!GameDataController::gd->getObjective(S("tent_awake")))
	{
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("tent_backpack_taken")))
	{
		colliderManager->setCollider(0);
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		characterAnimationName = S("action_stnd_ne");
		animationFlip = false;
		useCurrentDirection = false;
		colliderManager->setCollider(0);
	}
}

void MoonMoon::clickAction2()
{
}

void MoonMoon::clickAction0()
{
}
