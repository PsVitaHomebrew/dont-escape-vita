#include "../game_all.h"

void TentBonfire::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tent_bonfire");
	range = 80.0f;
	teleport = true;
	updateState();
}

void TentBonfire::Update()
{
}

void TentBonfire::whatOnClick()
{
}

void TentBonfire::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tent_bonfire")), true, false, false, 150);
}

void TentBonfire::updateState()
{
	if (!GameDataController::gd->getObjective(S("tent_awake")))
	{
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("tent_backpack_taken")))
	{
		colliderManager->setCollider(0);
		teleport = true;
	}
	else
	{
		teleport = false;
		colliderManager->setCollider(0);
	}
}

void TentBonfire::clickAction2()
{
}

void TentBonfire::clickAction0()
{
}
