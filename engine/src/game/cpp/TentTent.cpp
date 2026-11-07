#include "../game_all.h"

void TentTent::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tent_tent");
	range = 80.0f;
	teleport = true;
	updateState();
}

void TentTent::Update()
{
}

void TentTent::whatOnClick()
{
}

void TentTent::clickAction()
{
	if (!GameDataController::gd->getObjective(S("tent_distance_checked")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tent_tent")), true, false, false, 150);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("tent_tent_2")), true, false, false, 150);
	}
}

void TentTent::updateState()
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

void TentTent::clickAction2()
{
}

void TentTent::clickAction0()
{
}
