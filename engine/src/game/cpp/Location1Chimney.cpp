#include "../game_all.h"

void Location1Chimney::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_in_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_chimney__");
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
	interactions.Add(New<ItemInteraction>(S("lighter"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flamethrower"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flamethrower_empty"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("bandage"), GameStrings::getString(GameStrings::actions, S("bandage_chimney")), nullptr, String::Empty));
}

void Location1Chimney::Update()
{
}

void Location1Chimney::standSay()
{
	range = 20.0f;
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
}

void Location1Chimney::kneel()
{
	range = 1.0f;
	characterAnimationName = S("kneel_in_n");
	animationFlip = false;
	useCurrentDirection = false;
}

void Location1Chimney::whatOnClick0()
{
	if (usedItem == String::Empty)
	{
		standSay();
		return;
	}
	if ((usedItem == S("pest_note") || usedItem == S("gas_note") || usedItem == S("spider_note")) && !GameDataController::gd->getObjective(S("day1_complete")))
	{
		standSay();
	}
	else if (usedItem == S("charcoal_empty") || usedItem == S("pest_note") || usedItem == S("gas_note") || usedItem == S("spider_note") || usedItem == S("wad_of_cash"))
	{
		if (GameDataController::gd->getObjective(S("chimney_bag")) || GameDataController::gd->getObjective(S("chimney_note")) || GameDataController::gd->getObjective(S("chimney_cash")))
		{
			standSay();
		}
		else
		{
			kneel();
		}
	}
	if (usedItem == S("planks1") || usedItem == S("planks2") || usedItem == S("planks3") || usedItem == S("planks4") || usedItem == S("planks5") || usedItem == S("charcoal"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("chimney_wood")) > 0 || GameDataController::gd->getObjective(S("chimney_charcoal")))
		{
			standSay();
		}
		else
		{
			kneel();
		}
	}
	if (!(usedItem == S("lighter")) && !(usedItem == S("flamethrower_empty")) && !(usedItem == S("flamethrower")))
	{
		return;
	}
	if (GameDataController::gd->getObjective(S("chimney_note")) || GameDataController::gd->getObjective(S("chimney_bag")) || GameDataController::gd->getObjective(S("chimney_cash")) || GameDataController::gd->getObjective(S("chimney_papers")))
	{
		if (GameDataController::gd->getObjective(S("base_fireplace_lit")))
		{
			standSay();
		}
		else if (GameDataController::gd->getObjective(S("chimney_charcoal")) || GameDataController::gd->getObjectiveDetail(S("chimney_wood")) > 0)
		{
			kneel();
		}
		else
		{
			standSay();
		}
	}
	else
	{
		standSay();
	}
}

void Location1Chimney::getup(String param)
{
	PlayerController::wc->forceAnimation(S("kneel_out_n"));
}

void Location1Chimney::talkAndGetUp(String say)
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->blockG = true;
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->actionWithText = false;
	timelineAction->function = [this](String a) { getup(a); };
	timelineAction->text = say;
	Timeline::t->addAction(timelineAction);
	Timeline::t->doNotUnlock = true;
}

void Location1Chimney::startFire()
{
	GameDataController::gd->setObjective(S("base_fireplace_lit"), true);
	updateAll();
	getup(String::Empty);
}

void Location1Chimney::stopFire()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->blockG = true;
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->actionWithText = false;
	timelineAction->function = [this](String a) { stopFire2(a); };
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("chimney_cough_cough"));
	Timeline::t->addAction(timelineAction);
	Timeline::t->doNotUnlock = true;
}

void Location1Chimney::stopFire2(String a)
{
	talkAndGetUp(GameStrings::getString(GameStrings::actions, S("chimney_cough_cough2")));
	smoke->started = false;
}

void Location1Chimney::clickAction()
{
	if (usedItem == String::Empty)
	{
		String text = GameStrings::getString(GameStrings::actions, S("base_chimney"));
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
		text = ((!flag && !flag2) ? (text + S(" ") + GameStrings::getString(GameStrings::actions, S("base_chimney_empty"))) : (text + S(" ") + GameStrings::getString(GameStrings::actions, S("base_chimney_has")) + S(" ")));
		if (GameDataController::gd->getObjective(S("chimney_bag")))
		{
			text += GameStrings::getString(GameStrings::actions, S("base_chimney_bag"));
		}
		if (GameDataController::gd->getObjective(S("chimney_note")))
		{
			text += GameStrings::getString(GameStrings::actions, S("base_chimney_note"));
		}
		if (GameDataController::gd->getObjective(S("chimney_cash")))
		{
			text += GameStrings::getString(GameStrings::actions, S("base_chimney_cash"));
		}
		if (GameDataController::gd->getObjective(S("chimney_papers")))
		{
			text += GameStrings::getString(GameStrings::actions, S("base_chimney_papers"));
		}
		if (flag && flag2)
		{
			text = text + S(" ") + GameStrings::getString(GameStrings::actions, S("base_chimney_and")) + S(" ");
		}
		if (GameDataController::gd->getObjective(S("chimney_charcoal")))
		{
			text += GameStrings::getString(GameStrings::actions, S("base_chimney_charcoal"));
		}
		if (GameDataController::gd->getObjectiveDetail(S("chimney_wood")) > 0)
		{
			text += GameStrings::getString(GameStrings::actions, S("base_chimney_wood"));
		}
		if (flag || flag2)
		{
			text = text + S(" ") + GameStrings::getString(GameStrings::actions, S("base_chimney_has_end"));
		}
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = text;
		timelineAction->blockG = true;
		Timeline::t->addAction(timelineAction);
		if (!GameDataController::gd->getObjective(S("chimney_cleaned")))
		{
			timelineAction = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("base_chimney_clogged"));
			timelineAction->blockG = true;
			Timeline::t->addAction(timelineAction);
			if (GameDataController::gd->getCurrentDay() == 1)
			{
				timelineAction = New<TimelineAction>(PlayerController::pc->textField);
				timelineAction->text = GameStrings::getString(GameStrings::actions, S("base_chimney_clogged_d1"));
				timelineAction->blockG = true;
				Timeline::t->addAction(timelineAction);
			}
		}
		return;
	}
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("base_chimney_d1")));
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
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("already_kindled")));
		}
		else
		{
			if (usedItem == S("charcoal_empty"))
			{
				GameDataController::gd->setObjective(S("chimney_bag"), true);
			}
			if (usedItem == S("pest_note") || usedItem == S("gas_note") || usedItem == S("spider_note"))
			{
				GameDataController::gd->setObjective(S("chimney_note"), true);
			}
			if (usedItem == S("wad_of_cash"))
			{
				GameDataController::gd->setObjective(S("chimney_cash"), true);
			}
			if (usedItem == S("invoices"))
			{
				GameDataController::gd->setObjective(S("chimney_papers"), true);
			}
			InventoryController::ic->removeItem(usedItem);
			updateAll();
			talkAndGetUp(GameStrings::getString(GameStrings::actions, S("chimney_kindling1")) + S(" ") + GameStrings::getPrefixedShort(GameStrings::items, usedItem) + S(" ") + GameStrings::getString(GameStrings::actions, S("chimney_kindling2")));
		}
	}
	if (usedItem == S("planks1") || usedItem == S("planks2") || usedItem == S("planks3") || usedItem == S("planks4") || usedItem == S("planks5") || usedItem == S("charcoal"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("chimney_wood")) > 0 || GameDataController::gd->getObjective(S("chimney_charcoal")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("chimney_fueled")));
		}
		else
		{
			if (usedItem == S("planks1") || usedItem == S("planks2") || usedItem == S("planks3") || usedItem == S("planks4") || usedItem == S("planks5"))
			{
				GameDataController::gd->setObjectiveDetail(S("chimney_wood"), 1);
			}
			if (usedItem == S("charcoal"))
			{
				GameDataController::gd->setObjective(S("chimney_charcoal"), true);
			}
			InventoryController::ic->removeItem(usedItem);
			talkAndGetUp(GameStrings::getString(GameStrings::actions, S("chimney_kindling1")) + S(" ") + GameStrings::getPrefixedShort(GameStrings::items, usedItem) + S(" ") + GameStrings::getString(GameStrings::actions, S("chimney_kindling2")));
			if (usedItem == S("charcoal"))
			{
				InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("charcoal_empty")));
			}
			updateAll();
		}
	}
	if (!(usedItem == S("lighter")) && !(usedItem == S("flamethrower_empty")) && !(usedItem == S("flamethrower")))
	{
		return;
	}
	if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("chimney_dont_want"), component, color, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
		if (GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
		{
			for (int i = 0; i < list.Count(); i++)
			{
				Timeline::t->addDialogue(list[i]);
			}
			Timeline::t->actions[Timeline::t->actions.Count() - 1]->function = [this](String a) { getup(a); };
			Timeline::t->actions[Timeline::t->actions.Count() - 1]->blockG = true;
			Timeline::t->actions[Timeline::t->actions.Count() - 1]->actionWithText = false;
			Timeline::t->doNotUnlock = true;
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("check_attic")));
		}
	}
	else if (GameDataController::gd->getObjective(S("chimney_note")) || GameDataController::gd->getObjective(S("chimney_cash")) || GameDataController::gd->getObjective(S("chimney_bag")) || GameDataController::gd->getObjective(S("chimney_papers")))
	{
		if (GameDataController::gd->getObjective(S("chimney_charcoal")) || GameDataController::gd->getObjectiveDetail(S("chimney_wood")) > 0)
		{
			if (GameDataController::gd->getObjective(S("base_fireplace_lit")))
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("chimney_already_lit")));
			}
			else if (GameDataController::gd->getObjective(S("chimney_cleaned")))
			{
				if (usedItem == S("flamethrower"))
				{
					PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("chimney_flamethrower_1")));
				}
				if (usedItem == S("flamethrower_empty"))
				{
					PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("chimney_flamethrower_2")));
				}
				PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fire_start, 1.0f);
				Invoke(S("startFire"), 1.0f);
			}
			else
			{
				Invoke(S("stopFire"), 3.0f);
				smoke->started = true;
			}
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("chimney_no_fuel")));
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("chimney_no_kindling")));
	}
}

void Location1Chimney::updateState()
{
	if (GameDataController::gd->getObjective(S("base_fireplace_lit")))
	{
		fireLight->set_enabled(true);
		fireLight2->set_enabled(true);
		fire1->set_enabled(true);
		fire2->set_enabled(true);
	}
	else
	{
		fireLight->set_enabled(false);
		fireLight2->set_enabled(false);
		fire1->set_enabled(false);
		fire2->set_enabled(false);
	}
	loc->decideShadows();
	colliderManager->setCollider(0);
	objectName = S("base_chimney_");
	if (GameDataController::gd->getObjective(S("base_fireplace_lit")))
	{
		objectName = S("base_chimney_lit");
		return;
	}
	smoke->started = false;
	if (GameDataController::gd->getObjective(S("chimney_note")))
	{
		note->set_enabled(true);
		objectName += S("1");
	}
	else
	{
		note->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("chimney_cash")))
	{
		cash->set_enabled(true);
		objectName += S("2");
	}
	else
	{
		cash->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("chimney_papers")))
	{
		papers->set_enabled(true);
		objectName += S("3");
	}
	else
	{
		papers->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("chimney_bag")))
	{
		objectName += S("4");
		charcoal_bag->set_enabled(true);
	}
	else
	{
		charcoal_bag->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("chimney_charcoal")))
	{
		objectName += S("A");
		charcoal->set_enabled(true);
	}
	else
	{
		charcoal->set_enabled(false);
	}
	if (GameDataController::gd->getObjectiveDetail(S("chimney_wood")) == 0)
	{
		wood->set_enabled(false);
	}
	else
	{
		objectName += S("B");
		wood->set_enabled(true);
	}
	if (GameDataController::gd->getObjectiveDetail(S("chimney_wood")) == 1)
	{
		wood->set_sprite(wood1);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("chimney_wood")) == 2)
	{
		wood->set_sprite(wood2);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("chimney_wood")) == 3)
	{
		wood->set_sprite(wood3);
	}
	else
	{
		wood->set_sprite(wood4);
	}
}

void Location1Chimney::clickAction2()
{
}

void Location1Chimney::clickAction0()
{
}
