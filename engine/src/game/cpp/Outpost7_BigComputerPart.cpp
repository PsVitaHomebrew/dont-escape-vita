#include "../game_all.h"

void Outpost7_BigComputerPart::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_big_computer_part");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("duplexer"), String::Empty, nullptr, String::Empty));
}

void Outpost7_BigComputerPart::clickAction()
{
	if (!GameDataController::gd->getObjective(S("outpost_computer_part_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("duplexer"))))
		{
			GameDataController::gd->setObjective(S("outpost_computer_part_taken"), true);
			updateState();
		}
	}
	else if (usedItem != String::Empty)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_big_computer_nah")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_big_computer_empty")));
	}
}

void Outpost7_BigComputerPart::updateState()
{
	colliderManager->setCollider(0);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	if (!GameDataController::gd->getObjective(S("outpost_computer_part_taken")))
	{
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void Outpost7_BigComputerPart::clickAction2()
{
}

void Outpost7_BigComputerPart::clickAction0()
{
	if (!GameDataController::gd->getObjective(S("outpost_computer_part_taken")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_big_computer_part")));
	}
}

void Outpost7_BigComputerPart::whatOnClick0()
{
}

void Outpost7_BigComputerPart::whatOnClick()
{
}
