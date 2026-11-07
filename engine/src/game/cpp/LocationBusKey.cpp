#include "../game_all.h"

void LocationBusKey::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action1_e");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bus_key");
	range = 1.0f;
	teleport = false;
	updateState();
}

void LocationBusKey::Update()
{
}

void LocationBusKey::whatOnClick()
{
}

void LocationBusKey::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("key3"))))
	{
		GameDataController::gd->setObjective(S("bus_key_taken"), true);
	}
}

void LocationBusKey::updateState()
{
	if (GameDataController::gd->getObjective(S("bus_key_taken")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(-1);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		setCollider(0);
	}
}

void LocationBusKey::clickAction2()
{
	if (GameDataController::gd->getObjective(S("bus_key_taken")))
	{
		PlayerController::wc->forceAnimation(S("stand_se"), true);
		ExamineSprite::es->textField->shift.x = -110.0f;
		ExamineSprite::es->textField->shift.y = 20.0f;
		ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("key3_inspect")) }), 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f);
		ExamineSprite::es->show(zoom);
	}
	updateAll();
}

void LocationBusKey::clickAction0()
{
}
