#include "../game_all.h"

void BaseChest::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_chest");
	range = 2.0f;
	allowAllItems = true;
}

void BaseChest::clickAction()
{
	if (usedItem == S("ext_cord_place"))
	{
		PlayerController::pc->say(GameStrings::getWrongInteractionText());
		return;
	}
	if (usedItem == S("ac_cord"))
	{
		PlayerController::pc->say(GameStrings::getWrongInteractionText());
		return;
	}
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->trunk_open);
	if (usedItem == String::Empty)
	{
		if (!GameDataController::gd->getObjective(S("chest_tutorial")))
		{
			chestTutorial();
		}
		else
		{
			InventoryButtonController::ibc->openChest();
		}
	}
	else if (!GameDataController::gd->getObjective(S("chest_tutorial")))
	{
		chestTutorial();
	}
	else if (ItemsManager::im->getItem(usedItem)->weight >= 0.0f)
	{
		InventoryController::ic->putItemInChest(usedItem);
	}
}

void BaseChest::openTheChest()
{
	InventoryButtonController::ibc->openChest();
}

void BaseChest::chestTutorial()
{
	if (!GameDataController::gd->getObjective(S("chest_tutorial")))
	{
		ExamineSprite::es->textField->shift.x = -110.0f;
		ExamineSprite::es->textField->shift.y = 30.0f;
		ExamineSprite::es->readyText(List<String>::New({
			GameStrings::getString(GameStrings::gui, S("chest_tutorial1")),
			GameStrings::getString(GameStrings::gui, S("chest_tutorial2"))
		}), 90, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f);
		ExamineSprite::es->show(chestexamine, nullptr, nullptr, nullptr, nullptr, [this]() { openTheChest(); }, false);
		GameDataController::gd->setObjective(S("chest_tutorial"), true);
	}
}

void BaseChest::updateState()
{
	colliderManager->setCollider(0);
}

void BaseChest::clickAction2()
{
}

void BaseChest::clickAction0()
{
}

void BaseChest::whatOnClick0()
{
	if (usedItem == S("ext_cord_place") || usedItem == S("ac_cord"))
	{
		range = 300.0f;
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		characterAnimationName = S("action_n");
		animationFlip = false;
		useCurrentDirection = false;
		range = 2.0f;
	}
}

void BaseChest::whatOnClick()
{
}
