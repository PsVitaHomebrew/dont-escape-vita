#include "../game_all.h"

void CS3Bars::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_bars");
	range = 1.0f;
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
}

void CS3Bars::Update()
{
}

void CS3Bars::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("window_bars1"))))
	{
		GameDataController::gd->setObjective(S("cs_bars_taken"), true);
	}
	updateState();
}

void CS3Bars::updateState()
{
	setCollider(-1);
	GetComponent<SpriteRenderer>()->set_enabled(false);
	if (!GameDataController::gd->getObjective(S("cs_bars_taken")) && GameDataController::gd->getObjective(S("gasstation_bars1_taken")) && GameDataController::gd->getObjective(S("gasstation_bars2_taken")) && GameDataController::gd->getObjective(S("gasstation_bars3_taken")))
	{
		int num = 3;
		if (ItemsManager::im->getItem(S("window_bars1"))->dataRef->droppedLocation == S("nowhere"))
		{
			num--;
		}
		if (ItemsManager::im->getItem(S("window_bars2"))->dataRef->droppedLocation == S("nowhere"))
		{
			num--;
		}
		if (ItemsManager::im->getItem(S("window_bars3"))->dataRef->droppedLocation == S("nowhere"))
		{
			num--;
		}
		if (GameDataController::gd->getObjective(S("base_window_1_bars")) && GameDataController::gd->getObjective(S("base_window1_broken")))
		{
			num--;
		}
		if (GameDataController::gd->getObjective(S("base_window_2_bars")) && GameDataController::gd->getObjective(S("base_window2_broken")))
		{
			num--;
		}
		if (GameDataController::gd->getObjective(S("base_window_3_bars")) && GameDataController::gd->getObjective(S("base_window3_broken")))
		{
			num--;
		}
		if (num <= 0)
		{
			setCollider(0);
			GetComponent<SpriteRenderer>()->set_enabled(true);
		}
	}
}

void CS3Bars::clickAction2()
{
}

void CS3Bars::clickAction0()
{
}

void CS3Bars::whatOnClick0()
{
}

void CS3Bars::whatOnClick()
{
}
