#include "../game_all.h"

void BaseFuelBasket::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_in_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_chimney_basket_empty");
	range = 1.0f;
	teleport = false;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("charcoal"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("charcoal_empty"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("planks1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("planks2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("planks3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("planks4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("planks5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("gas_note"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pest_note"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("spider_note"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("invoices"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wad_of_cash"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("bandage"), GameStrings::getString(GameStrings::actions, S("bandage_chimney")), nullptr, String::Empty));
}

void BaseFuelBasket::Update()
{
}

void BaseFuelBasket::standSay()
{
	range = 20.0f;
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
}

void BaseFuelBasket::kneel()
{
	range = 1.0f;
	characterAnimationName = S("kneel_in_n");
	animationFlip = false;
	useCurrentDirection = false;
}

void BaseFuelBasket::talk(String say)
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->blockG = true;
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = say;
	Timeline::t->addAction(timelineAction);
	if (characterAnimationName == S("kneel_in_n"))
	{
		Timeline::t->doNotUnlock = true;
	}
}

void BaseFuelBasket::whatOnClick0()
{
	if (usedItem == String::Empty)
	{
		standSay();
		return;
	}
	bool flag = false;
	bool flag2 = false;
	if (GameDataController::gd->getObjective(S("chimney_note")) || GameDataController::gd->getObjective(S("chimney_cash")) || GameDataController::gd->getObjective(S("chimney_bag")) || GameDataController::gd->getObjective(S("chimney_papers")))
	{
		flag = true;
	}
	if (GameDataController::gd->getObjective(S("chimney_charcoal")) || GameDataController::gd->getObjectiveDetail(S("chimney_wood")) > 0)
	{
		flag2 = true;
	}
	if (!flag && (usedItem == S("charcoal_empty") || usedItem == S("spider_note") || usedItem == S("pest_note") || usedItem == S("gas_note") || usedItem == S("wad_of_cash") || usedItem == S("invoices")))
	{
		standSay();
	}
	else if (!flag2)
	{
		standSay();
	}
	else
	{
		kneel();
	}
}

void BaseFuelBasket::getup(String param)
{
	PlayerController::wc->forceAnimation(S("kneel_out_n"));
}

void BaseFuelBasket::talkAndGetUp(String say)
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->blockG = true;
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->actionWithText = false;
	timelineAction->function = [this](String param) { getup(param); };
	timelineAction->text = say;
	Timeline::t->addAction(timelineAction);
	Timeline::t->doNotUnlock = true;
}

void BaseFuelBasket::clickAction()
{
	bool flag = false;
	bool flag2 = false;
	if (GameDataController::gd->getObjective(S("basket_note")) || GameDataController::gd->getObjective(S("basket_cash")) || GameDataController::gd->getObjective(S("basket_bag")) || GameDataController::gd->getObjective(S("basket_papers")))
	{
		flag = true;
	}
	if (GameDataController::gd->getObjective(S("basket_charcoal")) || GameDataController::gd->getObjectiveDetail(S("basket_wood")) > 0)
	{
		flag2 = true;
	}
	if (usedItem == String::Empty)
	{
		if (flag || flag2)
		{
			talk(GameStrings::getString(GameStrings::actions, S("chimney_basket_full")));
		}
		else
		{
			talk(GameStrings::getString(GameStrings::actions, S("chimney_basket_empty")));
		}
		if (GameDataController::gd->getObjective(S("basket_bag")))
		{
			talk(GameStrings::getPrefixedShort(GameStrings::items, S("charcoal_empty"), true) + S("..."));
		}
		if (GameDataController::gd->getObjective(S("basket_note")))
		{
			talk(GameStrings::getPrefixedShort(GameStrings::items, S("generic_note"), true) + S("..."));
		}
		if (GameDataController::gd->getObjective(S("basket_cash")))
		{
			talk(GameStrings::getPrefixedShort(GameStrings::items, S("wad_of_cash"), true) + S("..."));
		}
		if (GameDataController::gd->getObjective(S("basket_papers")))
		{
			talk(GameStrings::getPrefixedShort(GameStrings::items, S("invoices"), true) + S("..."));
		}
		if (GameDataController::gd->getObjective(S("basket_charcoal")))
		{
			talk(GameStrings::getPrefixedShort(GameStrings::items, S("charcoal"), true));
		}
		if (GameDataController::gd->getObjectiveDetail(S("basket_wood")) == 1)
		{
			talk(GameStrings::getString(GameStrings::actions, S("base_chimney_basket_plank")) + S("..."));
		}
		if (GameDataController::gd->getObjectiveDetail(S("basket_wood")) > 1)
		{
			talk(GameDataController::gd->getObjectiveDetail(S("basket_wood")) + S(" ") + GameStrings::getString(GameStrings::actions, S("base_chimney_basket_planks")) + S("..."));
		}
		return;
	}
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("chimney_basket_d1")));
		return;
	}
	if ((usedItem == S("pest_note") || usedItem == S("gas_note") || usedItem == S("spider_note")) && !GameDataController::gd->getObjective(S("day1_complete")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("this_note_might_be_usefull")));
	}
	else if (usedItem == S("charcoal_empty") || usedItem == S("pest_note") || usedItem == S("gas_note") || usedItem == S("spider_note") || usedItem == S("wad_of_cash") || usedItem == S("invoices"))
	{
		if (GameDataController::gd->getObjective(S("chimney_note")) || GameDataController::gd->getObjective(S("chimney_cash")) || GameDataController::gd->getObjective(S("chimney_bag")) || GameDataController::gd->getObjective(S("chimney_papers")))
		{
			if (usedItem == S("charcoal_empty"))
			{
				GameDataController::gd->setObjective(S("basket_bag"), true);
			}
			if (usedItem == S("pest_note") || usedItem == S("gas_note") || usedItem == S("spider_note"))
			{
				GameDataController::gd->setObjective(S("basket_note"), true);
			}
			if (usedItem == S("wad_of_cash"))
			{
				GameDataController::gd->setObjective(S("basket_cash"), true);
			}
			if (usedItem == S("invoices"))
			{
				GameDataController::gd->setObjective(S("basket_papers"), true);
			}
			InventoryController::ic->removeItem(usedItem);
			updateAll();
			talkAndGetUp(GameStrings::getString(GameStrings::actions, S("basket_kindling1")) + S(" ") + GameStrings::getPrefixedShort(GameStrings::items, usedItem) + S(" ") + GameStrings::getString(GameStrings::actions, S("basket_kindling2")));
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("chimney_basket_kindling")));
		}
	}
	if (!(usedItem == S("planks1")) && !(usedItem == S("planks2")) && !(usedItem == S("planks3")) && !(usedItem == S("planks4")) && !(usedItem == S("planks5")) && !(usedItem == S("charcoal")))
	{
		return;
	}
	if (GameDataController::gd->getObjectiveDetail(S("chimney_wood")) > 0 || GameDataController::gd->getObjective(S("chimney_charcoal")))
	{
		if (usedItem == S("planks1") || usedItem == S("planks2") || usedItem == S("planks3") || usedItem == S("planks4") || usedItem == S("planks5"))
		{
			GameDataController::gd->setObjectiveDetail(S("basket_wood"), GameDataController::gd->getObjectiveDetail(S("basket_wood")) + 1);
		}
		if (usedItem == S("charcoal"))
		{
			GameDataController::gd->setObjective(S("basket_charcoal"), true);
		}
		InventoryController::ic->removeItem(usedItem);
		talkAndGetUp(GameStrings::getString(GameStrings::actions, S("basket_kindling1")) + S(" ") + GameStrings::getPrefixedShort(GameStrings::items, usedItem) + S(" ") + GameStrings::getString(GameStrings::actions, S("basket_kindling2")));
		if (usedItem == S("charcoal"))
		{
			InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("charcoal_empty")));
		}
		updateAll();
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("chimney_basket_fuel")));
	}
}

void BaseFuelBasket::updateState()
{
	colliderManager->setCollider(0);
	objectName = S("base_chimney_basket_empty");
	if (GameDataController::gd->getObjective(S("basket_note")))
	{
		note->set_enabled(true);
		objectName = S("base_chimney_basket_filled");
	}
	else
	{
		note->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("basket_cash")))
	{
		cash->set_enabled(true);
		objectName = S("base_chimney_basket_filled");
	}
	else
	{
		cash->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("basket_papers")))
	{
		papers->set_enabled(true);
		objectName = S("base_chimney_basket_filled");
	}
	else
	{
		papers->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("basket_bag")))
	{
		objectName = S("base_chimney_basket_filled");
		charcoal_bag->set_enabled(true);
	}
	else
	{
		charcoal_bag->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("basket_charcoal")))
	{
		objectName = S("base_chimney_basket_filled");
		charcoal->set_enabled(true);
	}
	else
	{
		charcoal->set_enabled(false);
	}
	if (GameDataController::gd->getObjectiveDetail(S("basket_wood")) == 0)
	{
		wood->set_enabled(false);
	}
	else
	{
		objectName = S("base_chimney_basket_filled");
		wood->set_enabled(true);
	}
	if (GameDataController::gd->getObjectiveDetail(S("basket_wood")) == 1)
	{
		wood->set_sprite(wood1);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("basket_wood")) == 2)
	{
		wood->set_sprite(wood2);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("basket_wood")) == 3)
	{
		wood->set_sprite(wood3);
	}
	else
	{
		wood->set_sprite(wood4);
	}
}

void BaseFuelBasket::clickAction2()
{
}

void BaseFuelBasket::clickAction0()
{
}
