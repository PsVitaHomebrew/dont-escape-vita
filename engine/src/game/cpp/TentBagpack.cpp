#include "../game_all.h"

void TentBagpack::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_s");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tent_backpack");
	range = 100.0f;
	teleport = false;
}

void TentBagpack::whatOnClick()
{
}

void TentBagpack::clickAction()
{
	colliderManager->setCollider(-1);
	GameDataController::gd->setObjective(S("tent_backpack_taken"), true);
	updateAll();
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->gameObject->GetComponent<Animator>()->set_speed(1.0f);
	Invoke(S("fixShadow"), 1.0f);
	P<TimelineAction> timelineAction = New<TimelineAction>(GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>());
	timelineAction->text = S("[") + GameStrings::getString(GameStrings::gui, S("inventory_hint")) + S("]");
	timelineAction->function = [obj = GameObject::Find(S("inventory_button"))->GetComponent<InventoryButtonController>()](String param) { obj->showInventory(param); };
	timelineAction->actionWithText = true;
	timelineAction->textWidth = 170;
	Timeline::t->addAction(timelineAction);
}

void TentBagpack::fixShadow()
{
	PlayerController::wc->shadowOffsetY = -5;
}

void TentBagpack::updateState()
{
	if (!GameDataController::gd->getObjective(S("tent_awake")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(-1);
	}
	else if (GameDataController::gd->getObjective(S("tent_backpack_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
}

void TentBagpack::clickAction2()
{
}

void TentBagpack::clickAction0()
{
}
