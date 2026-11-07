#include "../game_all.h"

void GingerActionController::_cctor()
{
	color = Vector3(215.0f / 255.0f, 58.0f / 255.0f, 46.0f / 255.0f);
}

Vector3 GingerActionController::getColor()
{
	return color;
}

bool GingerActionController::isGingerHere()
{
	if (GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
	{
		return false;
	}
	if (GameDataController::gd->getObjective(S("sidereal_roof_collapsed")) && !GameDataController::gd->getObjective(S("dialogue_ginger_reunited")))
	{
		return false;
	}
	if (!GameDataController::gd->getObjective(S("npc1_alive")))
	{
		return false;
	}
	if (GameDataController::gd->getObjective(S("moon_cate_sleeps")))
	{
		return false;
	}
	return true;
}

void GingerActionController::continueStart()
{
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("coat1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_0"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pills"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("deadbird"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("whiskey"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("oil"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("fan_broken"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rope"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ropehook"), String::Empty, nullptr, String::Empty));
	busyTalkingRandomly = false;
	actionType = Type::Talk;
}

void GingerActionController::whatOnClick()
{
}

void GingerActionController::whatOnClick0()
{
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		range = 250.0f;
		rotateToSpeaker = true;
	}
	else if (GameDataController::gd->getObjective(S("sidereal_roof_collapsed")) && SceneManager::GetActiveScene().get_name() == S("LocationSiderealRoof"))
	{
		range = 200.0f;
		rotateToSpeaker = false;
	}
	else if (GameDataController::gd->getObjective(S("moon_shocked1")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker_sit"))->gameObject;
		range = 0.0f;
		rotateToSpeaker = false;
	}
	else if (SceneManager::GetActiveScene().get_name() == S("LocationShip1"))
	{
		range = 25.0f;
		rotateToSpeaker = false;
	}
	else if (GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
	{
		range = 100.0f;
		rotateToSpeaker = false;
	}
	else
	{
		range = 25.0f;
		rotateToSpeaker = true;
	}
}

void GingerActionController::playerStandUp(String v)
{
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->forceAnimation(S("kneel_out_n"));
}

void GingerActionController::endTalkShip(String val)
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("ruda_get_up"));
	endTalk(String::Empty);
}

void GingerActionController::roofAfterFall()
{
	instantLines = List<P<DialogueLine>>::New();
	if (!GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("npc2_alive")))
	{
		DialogueController::dc->initDialogue(instantLines, S("sidereal_nofall2_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	}
	else if ((!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1) || (!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1))
	{
		DialogueController::dc->initDialogue(instantLines, S("sidereal_afterfall_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	}
	else
	{
		DialogueController::dc->initDialogue(instantLines, S("sidereal_nofall_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	}
	instantLines[instantLines.Count() - 1]->action = [this](String param) { roofWalkAway(param); };
	for (int i = 0; i < instantLines.Count(); i++)
	{
		Timeline::t->addDialogue(instantLines[i]);
	}
}

void GingerActionController::goToSleep1(String a)
{
	gameObject->GetComponent<NPCWalkController>()->setSimpleTargetV3(GameObject::Find(S("CateWalkHere"))->transform->get_position());
}

void GingerActionController::goToSleep2(String a)
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("cate_pod");
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	CurtainController::cc->fadeOut(S("LocationMoonbase3"), WalkController::Direction::NW, S("stand_ne"), nullptr, true, [this]() { goToSleep3(); });
}

void GingerActionController::goToSleep3()
{
	P<TextFieldController> component = GameObject::Find(S("Moonbase3Pad2"))->transform->Find(S("TextField"))->GetComponent<TextFieldController>();
	if (GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("moon_barry_sleeps")))
	{
		component->transform->set_position(ScreenControler::roundToNearestFullPixel3(component->transform->get_position()));
		instantLines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(instantLines, S("cate_sleep_barry"), component, color, GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
		for (int i = 0; i < instantLines.Count(); i++)
		{
			Timeline::t->addDialogue(instantLines[i]);
		}
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("moon_cody_sleeps")))
	{
		instantLines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(instantLines, S("cate_sleep_cody"), component, color, GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
		for (int j = 0; j < instantLines.Count(); j++)
		{
			Timeline::t->addDialogue(instantLines[j]);
		}
	}
	instantLines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(instantLines, S("cate_sleep_2david"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	instantLines[instantLines.Count() - 1]->action = [this](String param) { closePod(param); };
	for (int k = 0; k < instantLines.Count(); k++)
	{
		Timeline::t->addDialogue(instantLines[k]);
	}
}

void GingerActionController::closePod(String s)
{
	GameObject::Find(S("Moonbase3Pad2"))->GetComponent<Animator>()->Play(S("moon_pod2_close"));
	GameDataController::gd->setObjectiveDetail(S("moon_cate_sleeps"), 1);
	if (GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("moon_barry_sleeps")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<Npc2Controller>()->pod_rotate();
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("moon_cody_sleeps")))
	{
		GameObject::Find(S("Npc3"))->GetComponent<Npc3Controller>()->pod_rotate();
	}
}

void GingerActionController::pod_rotate()
{
	Invoke(S("pod_rotate2"), Random::Range(0.5f, 2.0f));
}

void GingerActionController::pod_rotate2()
{
	GetComponent<NPCWalkController>()->fullStop(true);
	GetComponent<NPCWalkController>()->forceAnimation(S("stand_se"));
	GetComponent<NPCWalkController>()->setBusy(false);
}

void GingerActionController::roofWalkAway(String a)
{
	gameObject->GetComponent<NPCWalkController>()->speed = gameObject->GetComponent<NPCWalkController>()->MAX_SPEED;
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("walk_e"), true);
	gameObject->GetComponent<NPCWalkController>()->setSimpleTargetV3(GameObject::Find(S("GingerWalkAway"))->transform->get_position());
	if ((!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1) || GameDataController::gd->getObjective(S("npc2_alive")) || GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
	{
	}
	Invoke(S("roofWalkAway2"), 5.0f);
}

void GingerActionController::roofWalkAway2()
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("stand_n"), true);
	gameObject->GetComponent<NPCWalkController>()->fullStop();
}

void GingerActionController::npcClickAction(String item)
{
	instantLines = List<P<DialogueLine>>::New();
	if (GameDataController::gd->getObjective(S("sidereal_roof_collapsed")) && SceneManager::GetActiveScene().get_name() == S("LocationSiderealRoof") && !GameDataController::gd->getObjective(S("dialogue_ginger_reunited")))
	{
		bool flag = true;
		if (!GameDataController::gd->getObjective(S("npc3_joined")) || !GameDataController::gd->getObjective(S("npc3_alive")))
		{
			flag = false;
		}
		bool flag2 = true;
		if (!GameDataController::gd->getObjective(S("npc2_joined")) || !GameDataController::gd->getObjective(S("npc2_alive")))
		{
			flag2 = false;
		}
		if (!GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
		{
			flag2 = false;
			flag = false;
		}
		if (flag2 && flag)
		{
			DialogueController::dc->initDialogue(instantLines, S("ginger_roof_save_them"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		else if (flag2)
		{
			DialogueController::dc->initDialogue(instantLines, S("ginger_roof_save_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		else if (flag)
		{
			DialogueController::dc->initDialogue(instantLines, S("ginger_roof_save_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		else
		{
			DialogueController::dc->initDialogue(instantLines, S("sidereal_savedfalltalk_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		for (int i = 0; i < instantLines.Count(); i++)
		{
			Timeline::t->addDialogue(instantLines[i]);
		}
		return;
	}
	if (GameDataController::gd->getObjective(S("moon_shocked1")))
	{
		PlayerController::pc->forceAnimation(S("kneel_in_n"));
		DialogueController::dc->initDialogue(instantLines, S("moon_shocked_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		GameDataController::gd->setObjective(S("moon_shocked1"), false);
		if (GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("moon_shocked1")) && (!GameDataController::gd->getObjective(S("npc2_alive")) || !GameDataController::gd->getObjective(S("moon_shocked2"))) && (!GameDataController::gd->getObjective(S("npc3_alive")) || !GameDataController::gd->getObjective(S("moon_shocked3"))))
		{
			if (GameDataController::gd->getObjective(S("npc1_alive")))
			{
				instantLines.Add(New<DialogueLine>(textField, color, GameStrings::getString(GameStrings::dialogues, S("moon_shocked_cate_ending")), nullptr));
			}
			else
			{
				instantLines.Add(New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::dialogues, S("moon_shocked_nocate_ending")), nullptr));
			}
		}
		instantLines[instantLines.Count() - 1]->action = [this](String param) { endTalkShip(param); };
		instantLines[instantLines.Count() - 2]->action = [this](String param) { playerStandUp(param); };
		for (int j = 0; j < instantLines.Count(); j++)
		{
			Timeline::t->addDialogue(instantLines[j]);
		}
		return;
	}
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("thug_to_kill_bathroom")))
	{
		GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setFlipped(true);
		textField = gameObject->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(instantLines, S("thug_kill_or_not"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("thug"))->GetComponent<TextFieldController>(), Vector3(0.588f, 0.15f, 0.43f));
		if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
		{
			Vector3 vector = getColor();
			Vector3 color_c = Npc2Controller::getColor();
			P<TextFieldController> component = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
			DialogueController::dc->initDialogue(instantLines, S("thug_kill_or_not_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, color_c);
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
		{
			Vector3 color_c2 = Npc3Controller::getColor();
			P<TextFieldController> component2 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
			DialogueController::dc->initDialogue(instantLines, S("thug_kill_or_not_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component2, color_c2);
		}
	}
	else if (!GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
	{
		if (!GameDataController::gd->getObjective(S("ginger_from_attic")))
		{
			DialogueController::dc->initDialogue(instantLines, S("ginger_intro0b"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		else
		{
			DialogueController::dc->initDialogue(instantLines, S("ginger_intro0a"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		DialogueController::dc->initDialogue(instantLines, S("ginger_intro1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		if (GameDataController::gd->getObjective(S("previous_disc_barry")) || GameDataController::gd->getObjective(S("previous_disc_cody")))
		{
			DialogueController::dc->initDialogue(instantLines, S("ginger_intro_dejavu"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		DialogueController::dc->initDialogue(instantLines, S("ginger_intro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		if (GameDataController::gd->getObjective(S("ginger_from_attic")))
		{
			instantLines[1]->action = [this](String param) { aimGun(param); };
			instantLines[1]->actionParam = S("left");
			instantLines[1]->actionWithText = true;
		}
		else
		{
			instantLines[0]->action = [this](String param) { aimGun(param); };
			instantLines[0]->actionParam = S("right");
			instantLines[0]->actionWithText = true;
		}
		instantLines[9]->action = [this](String param) { holdGunUp(param); };
		instantLines[9]->actionWithText = true;
		instantLines[9]->actionParam = S("right");
		if (GameDataController::gd->getObjective(S("ginger_from_attic")))
		{
			instantLines[9]->actionParam = S("left");
		}
		instantLines[14]->action = [this](String param) { holster(param); };
		instantLines[14]->actionParam = S("right");
		if (GameDataController::gd->getObjective(S("ginger_from_attic")))
		{
			instantLines[14]->actionParam = S("left");
		}
	}
	else
	{
		if (GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("ginger_barry_distracted")), true, false, false, 150);
			return;
		}
		if (item == S("coat1") || item == S("coat2") || item == S("coat3") || item == S("coat4"))
		{
			if (ItemsManager::im->getItem(S("coat1"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("coat2"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("coat3"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("coat4"))->dataRef->droppedLocation == S("ginger"))
			{
				DialogueController::dc->initDialogue(instantLines, S("ginger_already_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
			}
			else if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
			{
				DialogueController::dc->initDialogue(instantLines, S("ginger_give_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
				InventoryController::ic->removeItem(item);
				ItemsManager::im->getItem(item)->dataRef->droppedLocation = S("ginger");
				JournalTexts::pickTexts(GameDataController::gd->getCurrentDay());
			}
			else if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
			{
				DialogueController::dc->initDialogue(instantLines, S("ginger_bad_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
			}
			else
			{
				DialogueController::dc->initDialogue(instantLines, S("ginger_bad2_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
			}
		}
		else if (item == S("water1") || item == S("water2") || item == S("water3") || item == S("water4"))
		{
			if (ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation == S("ginger"))
			{
				DialogueController::dc->initDialogue(instantLines, S("ginger_already_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
			}
			else if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
			{
				DialogueController::dc->initDialogue(instantLines, S("ginger_give_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
				InventoryController::ic->removeItem(item);
				ItemsManager::im->getItem(item)->dataRef->droppedLocation = S("ginger");
				JournalTexts::pickTexts(GameDataController::gd->getCurrentDay());
			}
			else if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
			{
				DialogueController::dc->initDialogue(instantLines, S("ginger_bad_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
			}
			else if (ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation == S("ginger") || ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation == S("ginger"))
			{
				DialogueController::dc->initDialogue(instantLines, S("ginger_already_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
			}
			else
			{
				DialogueController::dc->initDialogue(instantLines, S("ginger_bad2_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
			}
		}
		else
		{
			if (usedItem == S("pills"))
			{
				String prefix = S("ginger_give_pills");
				if (GameDataController::gd->getObjective(S("cate_pills_taken")))
				{
					prefix = S("ginger_gave_pills");
				}
				GameDataController::gd->setObjective(S("cate_pills_taken"), true);
				DialogueController::dc->initDialogue(instantLines, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
			}
			else if (usedItem.IndexOf(S("revolver")) != -1)
			{
				DialogueController::dc->initDialogue(instantLines, S("ginger_give_gun"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
			}
			else
			{
				if (item == S("deadbird"))
				{
					DialogueController::dc->initDialogue(instantLines, S("dead_bird_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
					instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
				}
				else if (item == S("whiskey"))
				{
					DialogueController::dc->initDialogue(instantLines, S("whiskey_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
					instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
				}
				else if (item == S("oil"))
				{
					DialogueController::dc->initDialogue(instantLines, S("oil_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
					instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
				}
				else if (item == S("fan") || item == S("fan_broken"))
				{
					DialogueController::dc->initDialogue(instantLines, S("fan_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
					instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
				}
				else if (item == S("rope") || item == S("ropehook"))
				{
					DialogueController::dc->initDialogue(instantLines, S("rope_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
					instantLines[instantLines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
				}
				else
				{
					if (GameDataController::gd->getCurrentDay() == 3 && SceneManager::GetActiveScene().get_name().IndexOf(S("Sidereal")) != -1 && !GameDataController::gd->getObjective(S("sidereal_base_located")))
					{
						DialogueController::dc->initDialogue(instantLines, S("ginger_intro_sidereal"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
					}
					else if (SceneManager::GetActiveScene().get_name().IndexOf(S("Moonbase")) != -1 && !GameDataController::gd->getObjective(S("dialogue_moonbase2_intro")))
					{
						DialogueController::dc->initDialogue(instantLines, S("moonbase2_postintro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
					}
					else
					{
						DialogueController::dc->initDialogue(instantLines, S("ginger_intro2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
					}
				}
			}
		}
	}
	for (int k = 0; k < instantLines.Count(); k++)
	{
		Timeline::t->addDialogue(instantLines[k]);
	}
	DialogueController::dc->callback = [this]() { dialogues(); };
	dialogues();
}

void GingerActionController::dialogues()
{
	DialogueController::dc->reset();
	int num = 0;
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("thug_to_kill_bathroom")) && !GameDataController::gd->getObjective(S("dialogue_ginger_thug_kill_no")))
	{
		num = 0;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("thug_kill_yes_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/kill_razor")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_thug_kill_yes"));
		DialogueController::dc->initDialogue(doc->lines, S("thug_kill_yes"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("thug"))->GetComponent<TextFieldController>(), Vector3(0.588f, 0.15f, 0.43f));
		if (GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2)
		{
			doc->lines.Insert(7, New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::dialogues, S("thug_kill_yes_barry")), nullptr));
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2)
		{
			doc->lines.Insert(7, New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::dialogues, S("thug_kill_yes_cody")), nullptr));
		}
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			doc->lines[doc->lines.Count() - 1]->text = GameStrings::getString(GameStrings::dialogues, S("thug_kill_yes_11_b_cody"));
		}
		doc->lines[doc->lines.Count() - 1]->action = [this](String param) { killRazor(param); };
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("thug_kill_no_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_thug_kill_no"));
		DialogueController::dc->initDialogue(doc->lines, S("thug_kill_no"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("thug"))->GetComponent<TextFieldController>(), Vector3(0.588f, 0.15f, 0.43f));
		takeDoc(0);
		if (doc->caption != String::Empty)
		{
			DialogueController::dc->talking = true;
		}
		return;
	}
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("thug_to_kill_bathroom")))
	{
		num = 0;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("thug_kill_yes_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/kill_razor")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_thug_kill_yes"));
		DialogueController::dc->initDialogue(doc->lines, S("thug_kill_yes"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("thug"))->GetComponent<TextFieldController>(), Vector3(0.588f, 0.15f, 0.43f));
		if (GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2)
		{
			doc->lines.Insert(7, New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::dialogues, S("thug_kill_yes_barry")), nullptr));
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2)
		{
			doc->lines.Insert(7, New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::dialogues, S("thug_kill_yes_cody")), nullptr));
		}
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			doc->lines[doc->lines.Count() - 1]->text = GameStrings::getString(GameStrings::dialogues, S("thug_kill_yes_11_b_cody"));
		}
		doc->lines[doc->lines.Count() - 1]->action = [this](String param) { killRazor(param); };
		num++;
		takeDoc(num);
		if (!GameDataController::gd->getObjective(S("dialogue_ginger_thug_kill_waste")))
		{
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("thug_kill_waste_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bullet")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_ginger_thug_kill_waste"));
			DialogueController::dc->initDialogue(doc->lines, S("thug_kill_waste"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("thug"))->GetComponent<TextFieldController>(), Vector3(0.588f, 0.15f, 0.43f));
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { evaluateRazor(param); };
			num++;
			takeDoc(num);
		}
		if (!GameDataController::gd->getObjective(S("dialogue_ginger_thug_kill_lesson")))
		{
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("thug_kill_lesson_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_ginger_thug_kill_lesson"));
			DialogueController::dc->initDialogue(doc->lines, S("thug_kill_lesson"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("thug"))->GetComponent<TextFieldController>(), Vector3(0.588f, 0.15f, 0.43f));
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { evaluateRazor(param); };
			num++;
			takeDoc(num);
		}
		if (!GameDataController::gd->getObjective(S("dialogue_ginger_thug_kill_better")))
		{
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("thug_kill_better_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/ginger_saint")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_ginger_thug_kill_better"));
			DialogueController::dc->initDialogue(doc->lines, S("thug_kill_better"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("thug"))->GetComponent<TextFieldController>(), Vector3(0.588f, 0.15f, 0.43f));
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { evaluateRazor(param); };
			num++;
			takeDoc(num);
		}
		if (!GameDataController::gd->getObjective(S("dialogue_ginger_thug_kill_end_anyway")))
		{
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("thug_kill_end_anyway_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/end_of_world")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_ginger_thug_kill_end_anyway"));
			DialogueController::dc->initDialogue(doc->lines, S("thug_kill_end_anyway"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("thug"))->GetComponent<TextFieldController>(), Vector3(0.588f, 0.15f, 0.43f));
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { evaluateRazor(param); };
		}
		takeDoc(0);
		if (doc->caption != String::Empty)
		{
			DialogueController::dc->talking = true;
		}
		return;
	}
	if (SceneManager::GetActiveScene().get_name().IndexOf(S("Moonbase")) != -1 && GameDataController::gd->getObjective(S("visited_moonbase3")))
	{
		num = 0;
		num = locationDialogue(num, color, S("cate"));
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("moonbase2_sleeper_pods_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pods")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_moonbase2_sleeper_pods"));
		DialogueController::dc->initDialogue(doc->lines, S("moonbase2_sleeper_pods"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("moonbase2_body_dies_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pod_dead")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_moonbase2_body_dies"));
		DialogueController::dc->initDialogue(doc->lines, S("moonbase2_body_dies"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("moonbase2_realm_of_dreams_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/dreams")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_moonbase2_realm_of_dreams"));
		DialogueController::dc->initDialogue(doc->lines, S("moonbase2_realm_of_dreams"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_radio1_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/earth_or_moon")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_moon_radio1"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_radio1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		if (GameDataController::gd->getObjective(S("dialogue_ginger_moon_radio1")))
		{
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_radio2_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/earth_or_moon2")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_ginger_moon_radio2"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_radio2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		if (GameDataController::gd->getObjective(S("pods_cosnole_inspected")) && !GameDataController::gd->getObjective(S("moon_console_unlocked")))
		{
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_pods_lockdown_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/console_locked")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_pods_lockdown"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_pods_lockdown"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		if (GameDataController::gd->getObjective(S("dialogue_pods_intro")))
		{
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_pods_phase_controller_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/phase")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_pods_phase_controller"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_pods_phase_controller"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_pods_emergency_merge_mode_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/merge")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_pods_emergency_mode"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_pods_emergency_merge_mode"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_pods_where_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/where_go")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_pods_where"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_pods_where"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_pods_loop1_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/already")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_pods_loop1"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_pods_loop1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			if (GameDataController::gd->getObjective(S("dialogue_pods_emergency_mode")))
			{
				num++;
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_pods_loop2_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/brain")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("dialogue_pods_loop2"));
				DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_pods_loop2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			}
			if (GameDataController::gd->getObjective(S("dialogue_pods_emergency_mode")))
			{
				num++;
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_pods_paradox_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/paradox")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("dialogue_pods_paradox"));
				DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_pods_paradox"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			}
			if (GameDataController::gd->getObjective(S("moon_disc1_used")) && GameDataController::gd->getObjective(S("moon_disc2_used")))
			{
				num++;
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_disks_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/discs")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("ginger_moon_disks"));
				DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_disks"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("moon_disc1_used")))
			{
				num++;
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_disk1_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/disc1")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("ginger_moon_disk"));
				DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_disk"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("moon_disc2_used")))
			{
				num++;
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_disk2_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/disc2")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("ginger_moon_disk"));
				DialogueController::dc->initDialogue(doc->lines, S("ginger_moon_disk"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			}
			if (GameDataController::gd->getObjective(S("moon_pods_unlocked")) && SceneManager::GetActiveScene().get_name() == S("LocationMoonbase3"))
			{
				num++;
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("cate_sleep_david_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pod_cate")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("moon_cate_sleeps"));
				DialogueController::dc->initDialogue(doc->lines, S("cate_sleep_david"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				doc->lines[doc->lines.Count() - 3]->action = [this](String param) { goToSleep1(param); };
				doc->lines[doc->lines.Count() - 1]->action = [this](String param) { goToSleep2(param); };
			}
		}
		String prefix = S("moonbase2_intro_end");
		if (GameDataController::gd->getObjective(S("dialogue_moonbase2_intro")))
		{
			prefix = S("ginger_exit");
		}
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("exit_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_moonbase2_intro"));
		if (GameDataController::gd->getObjective(S("moon_console_unlocked")) && !GameDataController::gd->getObjective(S("moon_pods_unlocked")) && GameDataController::gd->getObjective(S("dialogue_pods_intro")))
		{
			doc->setObjective(S("moon_pods_unlocked"));
			prefix = S("moonbase2_pods_open_end");
		}
		DialogueController::dc->initDialogue(doc->lines, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[doc->lines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
		if (GameDataController::gd->getObjective(S("moon_console_unlocked")) && !GameDataController::gd->getObjective(S("moon_pods_unlocked")) && GameDataController::gd->getObjective(S("dialogue_pods_intro")))
		{
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { openThePodBayDoors(param); };
		}
		takeDoc(0);
		if (doc->caption != String::Empty)
		{
			DialogueController::dc->talking = true;
		}
		return;
	}
	if (GameDataController::gd->getCurrentDay() == 3 && SceneManager::GetActiveScene().get_name().IndexOf(S("Sidereal")) != -1 && !GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		num = 0;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_sidereal_arrival_outpost_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/outpost")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_sidereal_arrival_outpost"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_sidereal_arrival_outpost"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_sidereal_arrival_docs_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/docs")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_sidereal_arrival_docs"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_sidereal_arrival_docs"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_sidereal_connections1_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sidereal")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_sidereal_arrival_connections1"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_sidereal_connections1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("exit_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("ginger_sidereal_exit"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[doc->lines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
		takeDoc(0);
		if (doc->caption != String::Empty)
		{
			DialogueController::dc->talking = true;
		}
		return;
	}
	num = 0;
	if (GameDataController::gd->getObjective(S("dialogue_ginger_first_exit")))
	{
		num = locationDialogue(num, color, S("cate"));
		num = dayDialogue(num, color, S("cate"));
	}
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_about_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/ginger")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("dialogue_ginger_about"));
	DialogueController::dc->initDialogue(doc->lines, S("ginger_about"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	if (GameDataController::gd->getCurrentDay() <= 2)
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_car_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/car")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_car"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_car1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		if (!GameDataController::gd->getObjective(S("barn_car_wheel_repaired")) || !GameDataController::gd->getObjective(S("barn_car_coil_repaired")) || !GameDataController::gd->getObjective(S("barn_car_battery_repaired")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("ginger_car2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
	}
	if (GameDataController::gd->getCurrentDay() <= 3)
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_moon_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/moon")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_moon"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_moon"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_spaceship_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/ship")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_ship"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_spaceship"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_outpost_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/outpost")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_outpost"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_outpost"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		if (GameDataController::gd->getObjective(S("dialogue_ginger_outpost")))
		{
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_map_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/map")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_ginger_map"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_map"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { showMap(param); };
		}
	}
	if (GameDataController::gd->getCurrentDay() <= 2)
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_dreams_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/dream")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_dreams"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_dreams"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			doc->lines[1]->text = GameStrings::getString(GameStrings::dialogues, S("ginger_dreams_SWARM_2_a"));
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			doc->lines[1]->text = GameStrings::getString(GameStrings::dialogues, S("ginger_dreams_GAS_2_a"));
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			doc->lines[1]->text = GameStrings::getString(GameStrings::dialogues, S("ginger_dreams_SPIDERS_2_a"));
		}
		if (GameDataController::gd->getObjective(S("dialogue_ginger_dreams")))
		{
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_dreams2_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/dream2")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_ginger_dreams2"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_dreams2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
			{
				doc->lines[1]->text = GameStrings::getString(GameStrings::dialogues, S("ginger_dreams2_2_COLD"));
			}
			if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
			{
				doc->lines[1]->text = GameStrings::getString(GameStrings::dialogues, S("ginger_dreams2_2_HEAT"));
			}
		}
	}
	String empty = String::Empty;
	if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getCurrentDay() < 5)
	{
		num++;
		takeDoc(num);
		empty = S("ginger_barry");
		doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry")));
		doc->lines = List<P<DialogueLine>>::New();
		int num2 = 1;
		if (GameDataController::gd->getCurrentDay() == 2)
		{
			num2 = 1;
		}
		if (GameDataController::gd->getCurrentDay() == 3)
		{
			num2 = 2;
		}
		if (GameDataController::gd->getCurrentDay() == 4)
		{
			num2 = 3;
		}
		doc->setObjective(S("dialogue_") + empty + num2);
		DialogueController::dc->initDialogue(doc->lines, empty + num2, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	}
	else if (GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("npc2_alive")) && (GameDataController::gd->getObjective(S("sidereal_npc_found")) || GameDataController::gd->getObjectiveDetail(S("npc2_alive")) != 1))
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_barry_dead_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_barry_dead"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_barry_dead"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getCurrentDay() < 5)
	{
		num++;
		takeDoc(num);
		empty = S("ginger_cody");
		doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cody")));
		doc->lines = List<P<DialogueLine>>::New();
		int num3 = 1;
		if (GameDataController::gd->getCurrentDay() == 2)
		{
			num3 = 1;
		}
		if (GameDataController::gd->getCurrentDay() == 3)
		{
			num3 = 2;
		}
		if (GameDataController::gd->getCurrentDay() == 4)
		{
			num3 = 3;
		}
		doc->setObjective(S("dialogue_") + empty + num3);
		DialogueController::dc->initDialogue(doc->lines, empty + num3, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	}
	else if (GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")) && (GameDataController::gd->getObjective(S("sidereal_npc_found")) || GameDataController::gd->getObjectiveDetail(S("npc3_alive")) != 1))
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_cody_dead_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cody")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_cody_dead"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_cody_dead"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	}
	if (GameDataController::gd->getCurrentDay() >= 3 && GameDataController::gd->getObjective(S("sidereal_base_located")) && GameDataController::gd->getObjective(S("sidereal_read_cate_mail")))
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_sidereal_reveal_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/ginger")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("ginger_sidereal_reveal"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_sidereal_reveal"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		if (GameDataController::gd->getObjective(S("ginger_sidereal_reveal")))
		{
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_sidereal_why_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cate_hide")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("ginger_sidereal_why"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_sidereal_why"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_sidereal_else_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sidereal")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("ginger_sidereal_else"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_sidereal_else"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			if (!GameDataController::gd->getObjective(S("outpost_spaceship_discovered")))
			{
				num++;
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_sidereal_ship_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/ship")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("ginger_sidereal_ship"));
				DialogueController::dc->initDialogue(doc->lines, S("ginger_sidereal_ship"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			}
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_sidereal_dreams_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/dreams")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("ginger_sidereal_dreams"));
			DialogueController::dc->initDialogue(doc->lines, S("ginger_sidereal_dreams"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
	}
	if (GameDataController::gd->getCurrentDay() == 2 && SceneManager::GetActiveScene().get_name() == S("LocationHouseB") && GameDataController::gd->getObjectiveDetail(S("dialogue_npc2_house_blocked")) > 0 && !GameDataController::gd->getObjective(S("npc2_wife_note_given")) && GameDataController::gd->getObjective(S("dialogue_npc2_intro")))
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_barry_busy_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_ginger_barry_distracted"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_barry_busy"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[1]->action = [this](String param) { drawGun(param); };
		doc->lines[1]->actionWithText = true;
		doc->lines[3]->action = [this](String param) { holster(param); };
		doc->lines[3]->actionWithText = true;
		doc->lines[doc->lines.Count() - 1]->action = [this](String param) { goDistractBarry(param); };
	}
	if (SceneManager::GetActiveScene().get_name() == S("LocationRestaurant2") && !GameDataController::gd->getObjective(S("restaurant_trash_moved")) && GameDataController::gd->getObjective(S("restaurant_trash_tried")) && (!GameDataController::gd->getObjective(S("npc3_alive")) || GameDataController::gd->getObjective(S("dialogue_cody_intro"))))
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_push_trash_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/push_trash")));
		doc->lines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(doc->lines, S("ginger_push_trash"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[doc->lines.Count() - 1]->action = [this](String param) { pushTrashCart(param); };
	}
	if (!GameDataController::gd->getObjective(S("outpost_fingerprint_unlocked")) && GameDataController::gd->getObjectiveDetail(S("outpost_underground_light")) > 1 && SceneManager::GetActiveScene().get_name() == S("LocationOutpost4"))
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("ginger_fingerprint_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/fingerprint")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		doc->setObjective(S("dialogue_ginger_fingerprint"));
		DialogueController::dc->initDialogue(doc->lines, S("ginger_fingerprint"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[doc->lines.Count() - 1]->action = [this](String param) { fingerPress(param); };
	}
	if (GameDataController::gd->getObjective(S("gasstation_sarge_intro")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 3)
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_sarge_thugs_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge")));
		doc->lines = List<P<DialogueLine>>::New();
		if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
		{
			doc->setObjective(S("dialogue_sarge_thugs4_cate"));
			DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs4_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		else if (GameDataController::gd->getObjective(S("gasstation_sarge_convinced")))
		{
			if (GameDataController::gd->getObjective(S("previous_disc_barry")) || GameDataController::gd->getObjective(S("previous_disc_cody")))
			{
				doc->setObjective(S("dialogue_sarge_thugs3_cate"));
				DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs3_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			}
			else
			{
				doc->setObjective(S("dialogue_sarge_thugs2_cate"));
				DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs2_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			}
		}
		else
		{
			doc->setObjective(S("dialogue_sarge_thugs1_cate"));
			DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs1_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
	}
	if (GameDataController::gd->getObjective(S("restaurant_sarge_encountered")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && GameDataController::gd->getCurrentDay() == 3)
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_sarge_storm_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_sarge_storm1_cate"));
		DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_storm1_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	}
	if (!GameDataController::gd->getObjective(S("thug_to_kill_bathroom")) && GameDataController::gd->getObjective(S("thug_killed_bathroom")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() < 5)
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_razor_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("d4_kill_razor_cate"));
		DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor0_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), getColor(), textField, color);
		if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")) && GameDataController::gd->getObjective(S("cs_thug_shot")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor3_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), getColor(), textField, color);
		}
		else if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor2_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), getColor(), textField, color);
		}
		else if (GameDataController::gd->getObjective(S("cs_thug_shot")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor1_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), getColor(), textField, color);
		}
		if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")) || GameDataController::gd->getObjective(S("cs_thug_shot")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor4_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), getColor(), textField, color);
		}
		else
		{
			DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor5_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), getColor(), textField, color);
		}
	}
	if (!GameDataController::gd->getObjective(S("thug_to_kill_bathroom")) && !GameDataController::gd->getObjective(S("thug_killed_bathroom")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 4)
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_razor_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("d4_spare_razor_cate"));
		DialogueController::dc->initDialogue(doc->lines, S("d4_spare_razor0_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), getColor(), textField, color);
	}
	if (GameDataController::gd->getObjective(S("dialogue_ginger_dreams2")) && GameDataController::gd->getObjective(S("dialogue_ginger_outpost")))
	{
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("exit_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		if (GameDataController::gd->getObjective(S("dialogue_ginger_first_exit")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("ginger_exit"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { NPCActionController::endTalk(param); };
		}
		else
		{
			DialogueController::dc->initDialogue(doc->lines, S("ginger_first_exit"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { firstEndTalk(param); };
		}
	}
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void GingerActionController::fingerPress(String val)
{
	gameObject->GetComponent<NPCWalkController>()->setSimpleTargetV3(GameObject::Find(S("diode"))->transform->Find(S("Action_Marker"))->transform->get_position());
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	PlayerController::pc->setBusy(true);
	Timeline::t->doNotUnlock = true;
	GameObject::Find(S("LocationManager"))->GetComponent<LocationOutpost4Start>()->gingerShowFinger = true;
}

void GingerActionController::firstEndTalk(String val)
{
	GameDataController::gd->setObjective(S("dialogue_ginger_first_exit"), true);
	endTalk(String::Empty);
}

void GingerActionController::clickAction2()
{
}

void GingerActionController::updateState()
{
	if (!GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
	{
		objectName = S("npc_ginger");
	}
	else
	{
		objectName = S("npc_cathy");
	}
}

void GingerActionController::clickAction0()
{
}

void GingerActionController::goDistractBarry(String val)
{
	if (currentLocationManager == nullptr)
	{
		currentLocationManager = GameObject::Find(S("Location"))->GetComponent<LocationManager>();
	}
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	gameObject->GetComponent<NPCWalkController>()->setBusy(false);
	PlayerController::pc->setBusy(true);
	List<Vector2> list = currentLocationManager->Search2(currentLocationManager->findNearestClearNode(currentLocationManager->getNodeLocation(gameObject->GetComponent<NPCWalkController>()->currentXY)), currentLocationManager->findNearestClearNode(currentLocationManager->getNodeLocation(ScreenControler::roundToNearestFullPixel(GameObject::Find(S("BarryDistractPoint"))->transform->get_position()))));
	list.Insert(0, gameObject->GetComponent<NPCWalkController>()->currentXY);
	gameObject->GetComponent<NPCWalkController>()->setTarget(list);
	GameDataController::gd->setObjectiveDetail(S("dialogue_ginger_barry_distracted"), 0);
	GameDataController::gd->setObjective(S("dialogue_ginger_barry_distracted"), true);
	Invoke(S("distractBarry1"), 3.0f);
}

void GingerActionController::showMap(String val)
{
	endTalk(String::Empty);
	ExamineSprite::es->textField->shift.x = -80.0f;
	ExamineSprite::es->textField->shift.y = -40.0f;
	ExamineSprite::es->readyText(List<String>::New({
		GameStrings::getString(GameStrings::dialogues, S("ginger_map_view_1")),
		GameStrings::getString(GameStrings::dialogues, S("ginger_map_view_2")),
		GameStrings::getString(GameStrings::dialogues, S("ginger_map_view_3")),
		GameStrings::getString(GameStrings::dialogues, S("ginger_map_view_4"))
	}), 200, color.x, color.y, color.z, 0.0f, 0.0f, 0.0f, 0.75f);
	ExamineSprite::es->cycleSprites = true;
	ExamineSprite::es->show(Resources::Load<Sprite>(S("Bitmaps/Locations/base/LocationAttic2/map1")), Resources::Load<Sprite>(S("Bitmaps/Locations/base/LocationAttic2/map1")), Resources::Load<Sprite>(S("Bitmaps/Locations/base/LocationAttic2/map2")), Resources::Load<Sprite>(S("Bitmaps/Locations/base/LocationAttic2/map3")), nullptr, [this]() { resumeAfterMap(); }, false);
	if (GameDataController::gd->getObjectiveDetail(S("map_houseb_revealed")) == TravelAgency::LOCATION_STATUS_UNDISCOVERED)
	{
		GameDataController::gd->setObjectiveDetail(S("map_houseb_revealed"), TravelAgency::LOCATION_STATUS_UNREACHABLE);
	}
	if (GameDataController::gd->getObjectiveDetail(S("map_restaurant_revealed")) == TravelAgency::LOCATION_STATUS_UNDISCOVERED)
	{
		GameDataController::gd->setObjectiveDetail(S("map_restaurant_revealed"), TravelAgency::LOCATION_STATUS_UNREACHABLE);
	}
}

void GingerActionController::resumeAfterMap()
{
	DialogueController::dc->talking = true;
	DialogueController::dc->show();
}

void GingerActionController::drawGun(String val)
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("gun_draw"), gameObject->GetComponent<NPCWalkController>()->flipped());
}

void GingerActionController::aimGun(String val)
{
	bool flip = true;
	if (val == S("right"))
	{
		flip = false;
	}
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("gun_take_aim"), flip);
}

void GingerActionController::holdGunUp(String val)
{
	bool flip = true;
	if (val == S("right"))
	{
		flip = false;
	}
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("gun_aim_up"), flip);
}

void GingerActionController::aimDown(String val)
{
	bool flip = true;
	if (val == S("right"))
	{
		flip = false;
	}
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("gun_aim_down"), flip);
}

void GingerActionController::holster(String val)
{
	bool flip = gameObject->GetComponent<NPCWalkController>()->flipped();
	if (val == S("right"))
	{
		flip = false;
	}
	if (val == S("left"))
	{
		flip = true;
	}
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("gun_holster"), flip);
	GameDataController::gd->setObjective(S("dialogue_ginger_intro"), true);
}

void GingerActionController::openThePodBayDoors(String a)
{
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	PlayerController::pc->setBusy(false);
	GameDataController::gd->setObjective(S("moon_pods_unlocked"), true);
	GameObject::Find(S("Moonbase3Pad1"))->GetComponent<Moonbase3Pod>()->openIfNeeded();
	GameObject::Find(S("Moonbase3Pad2"))->GetComponent<Moonbase3Pod>()->openIfNeeded();
	GameObject::Find(S("Moonbase3Pad3"))->GetComponent<Moonbase3Pod>()->openIfNeeded();
	GameObject::Find(S("Moonbase3Pad4"))->GetComponent<Moonbase3Pod>()->openIfNeeded();
}

void GingerActionController::killRazor(String a)
{
	GameDataController::gd->setObjective(S("location01_door2_locked"), false);
	GameDataController::gd->setObjective(S("location01_door2_open"), true);
	if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1)
	{
		GameDataController::gd->setObjectiveDetail(S("towel_1_at_door"), 0);
		P<Item> item = ItemsManager::im->getItem(S("towel_1"));
		item->dataRef->locX = 35;
		item->dataRef->locY = 35;
		item->dataRef->droppedLocation = S("Location1");
	}
	if (GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
	{
		GameDataController::gd->setObjectiveDetail(S("towel_2_at_door"), 0);
		P<Item> item2 = ItemsManager::im->getItem(S("towel_2"));
		item2->dataRef->locX = 35;
		item2->dataRef->locY = 35;
		item2->dataRef->droppedLocation = S("Location1");
	}
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->setBusy(true);
	GameDataController::gd->setObjective(S("thug_to_kill_bathroom"), false);
	GameDataController::gd->setObjective(S("thug_killed_bathroom"), true);
	PlayerController::pc->spawnName = S("Day4_morning");
	CurtainController::cc->fadeOut(S("LocationBaseOutside1"), WalkController::Direction::N, S("stand_n"), SoundsManagerController::sm->rifle_shoot);
}

void GingerActionController::spareRazor(String a)
{
	GameDataController::gd->setObjective(S("location01_door2_locked"), false);
	GameDataController::gd->setObjective(S("location01_door2_open"), true);
	if (GameDataController::gd->getObjectiveDetail(S("towel_1_at_door")) == 1)
	{
		GameDataController::gd->setObjectiveDetail(S("towel_1_at_door"), 0);
		P<Item> item = ItemsManager::im->getItem(S("towel_1"));
		item->dataRef->locX = 35;
		item->dataRef->locY = 35;
		item->dataRef->droppedLocation = S("Location1");
	}
	if (GameDataController::gd->getObjectiveDetail(S("towel_2_at_door")) == 1)
	{
		GameDataController::gd->setObjectiveDetail(S("towel_2_at_door"), 0);
		P<Item> item2 = ItemsManager::im->getItem(S("towel_2"));
		item2->dataRef->locX = 35;
		item2->dataRef->locY = 35;
		item2->dataRef->droppedLocation = S("Location1");
	}
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->setBusy(true);
	GameDataController::gd->setObjective(S("thug_killed_bathroom"), false);
	GameDataController::gd->setObjective(S("thug_to_kill_bathroom"), false);
	PlayerController::pc->spawnName = S("Day4_morning");
	CurtainController::cc->fadeOut(S("LocationBaseOutside1"), WalkController::Direction::N, S("stand_n"));
}

void GingerActionController::evaluateRazor(String a)
{
	int num = 0;
	if (GameDataController::gd->getObjective(S("dialogue_ginger_thug_kill_waste")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("dialogue_ginger_thug_kill_lesson")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("dialogue_ginger_thug_kill_better")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("dialogue_ginger_thug_kill_end_anyway")))
	{
		num++;
	}
	if (num >= 2)
	{
		instantLines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(instantLines, S("thug_kill_not"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("thug"))->GetComponent<TextFieldController>(), Vector3(0.588f, 0.15f, 0.43f));
		instantLines[instantLines.Count() - 1]->action = [this](String param) { spareRazor(param); };
		for (int i = 0; i < instantLines.Count(); i++)
		{
			Timeline::t->addDialogue(instantLines[i]);
		}
	}
}

void GingerActionController::mourn()
{
	if (!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
	{
		DialogueController::dc->quickDialogue(color, P<NPCActionController>(this), S("ginger_sidereal_barry_mourn"));
		Timeline::t->actions[Timeline::t->actions.Count() - 1]->function = [this](String t) { mourned(t); };
	}
	else if (!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
	{
		DialogueController::dc->quickDialogue(color, P<NPCActionController>(this), S("ginger_sidereal_cody_mourn"));
		Timeline::t->actions[Timeline::t->actions.Count() - 1]->function = [this](String t) { mourned(t); };
	}
}

void GingerActionController::mourned(String t)
{
	GameDataController::gd->setObjective(S("dialogue_ginger_dead_mourned"), true);
}

void GingerActionController::pushTrashCart(String val)
{
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	gameObject->GetComponent<NPCWalkController>()->setBusy(false);
	PlayerController::pc->setBusy(true);
	Object::FindObjectOfType<Restaurant2Trash>()->pushLittleCart_Cate();
	Invoke(S("pushTrashCart2"), 0.75f);
	Invoke(S("pushTrashCartSound"), 0.5f);
	Invoke(S("pushTrashCartSound"), 0.75f);
	Invoke(S("pushTrashCartSound"), 1.25f);
}

void GingerActionController::pushTrashCart2()
{
	gameObject->GetComponent<NPCWalkController>()->currentXY = Vector2(55.0f, 60.0f);
	gameObject->GetComponent<NPCWalkController>()->setSimpleTarget(gameObject->GetComponent<NPCWalkController>()->currentXY);
	GameObject::Find(S("Player"))->GetComponent<WalkController>()->currentXY = Vector2(105.0f, 50.0f);
	GameObject::Find(S("Player"))->GetComponent<WalkController>()->setSimpleTarget(GameObject::Find(S("Player"))->GetComponent<WalkController>()->currentXY);
}

void GingerActionController::pushTrashCartSound()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_creak1);
}

void GingerActionController::distractBarry1()
{
	endTalk(String::Empty);
	distractBarry();
	PlayerController::pc->setBusy(false);
}

void GingerActionController::distractBarry()
{
	if (GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
	{
		if (distractBarryTextfield != nullptr)
		{
			distractBarryTextfield->dissmiss();
		}
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("npc2_mourn_look"), true);
		int num = GameDataController::gd->getObjectiveDetail(S("dialogue_ginger_barry_distracted")) + 1;
		if (num > 14)
		{
			num = 1;
		}
		GameDataController::gd->setObjectiveDetail(S("dialogue_ginger_barry_distracted"), num);
		MonoBehaviour::print(S("GINGER DISTRACTION AT ") + GameDataController::gd->getObjectiveDetail(S("dialogue_ginger_barry_distracted")));
		Vector3 vector = Vector3();
		String text = GameStrings::getString(GameStrings::dialogues, S("ginger_barry_talk_") + num + S("_a"));
		String text2 = GameStrings::getString(GameStrings::dialogues, S("ginger_barry_talk_") + num + S("_b"));
		String empty = String::Empty;
		if (text.IndexOf(S("_STRING_MISSING")) == -1)
		{
			empty = text;
			vector = getColor();
			distractBarryTextfield = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		}
		else
		{
			empty = text2;
			vector = Npc2Controller::getColor();
			distractBarryTextfield = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
		}
		distractBarryTextfield->viewText(empty, false, false, false, 100, vector.x, vector.y, vector.z);
		Invoke(S("distractBarry"), 5.0f);
	}
}

void GingerActionController::unlockDistraction(String val)
{
	gameObject->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("WaypointHouseB2"))->transform->Find(S("GingerSpawner"))->transform->Find(S("NPCTarget"))->transform->get_position());
}

void GingerActionController::setDistractFalse(String val)
{
	GameDataController::gd->setObjective(S("dialogue_ginger_barry_distracted"), false);
}

void GingerActionController::distractBarryEnd()
{
	GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("npc2_mourn_look"), true);
	GameDataController::gd->setObjectiveDetail(S("dialogue_ginger_barry_distracted"), 0);
	DialogueController::dc->reset();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("ginger_barry_talk_end"), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), getColor(), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
	list[0]->action = [this](String param) { setDistractFalse(param); };
	list[0]->actionWithText = true;
	list[1]->action = [this](String param) { unlockDistraction(param); };
	list[1]->actionWithText = false;
	Timeline::t->addDialogueLines(list);
}

void GingerActionController::initFindShipDialogue()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("ginger_barry_talk_end"), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), getColor(), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
	Timeline::t->addDialogueLines(list);
}
