#include "../game_all.h"

void Restaurant2Trash2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_trash");
	range = 200.0f;
}

void Restaurant2Trash2::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_trash_moved")), true);
}

void Restaurant2Trash2::updateState()
{
	if (!GameDataController::gd->getObjective(S("restaurant_trash_moved")))
	{
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void Restaurant2Trash2::clickAction2()
{
}

void Restaurant2Trash2::clickAction0()
{
}
