#include "../game_all.h"

void GasstationSargeObject::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	if (GameDataController::gd->getObjective(S("gasstation_spy_mode")))
	{
		actionMarker = am1;
		range = 3000.0f;
		teleport = true;
	}
	else
	{
		actionMarker = am2;
		range = 100.0f;
		teleport = false;
	}
	dkvs = GameStrings::objects;
	objectName = S("gasstation_sarge1");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("rifle_so_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_0"), GameStrings::getString(GameStrings::actions, S("rifle_no_ammo")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_0"), GameStrings::getString(GameStrings::actions, S("rifle_no_ammo")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_0"), GameStrings::getString(GameStrings::actions, S("rifle_no_ammo")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("whiskey"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("knife"), GameStrings::getString(GameStrings::actions, S("sarge_knife")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("sidereal_id"), GameStrings::getString(GameStrings::actions, S("sarge_sidereal_id")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_0"), GameStrings::getString(GameStrings::actions, S("rifle_no_ammo")), nullptr, String::Empty));
	updateState();
	if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		if (GameDataController::gd->getObjectiveDetail(S("gasstation_sarge_shot")) == 0)
		{
			sarge->GetComponent<Animator>()->Play(S("sarge_dead_back"));
		}
		else
		{
			sarge->GetComponent<Animator>()->Play(S("sarge_dead_front"));
		}
	}
	else if (GameDataController::gd->getObjective(S("thugs_gasstation_talk")) && !GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
	{
		sarge->GetComponent<Animator>()->Play(S("sarge_strugle"));
	}
	else
	{
		sarge->GetComponent<Animator>()->Play(S("sarge_idle"));
	}
}

void GasstationSargeObject::Update()
{
}

void GasstationSargeObject::whatOnClick0()
{
	if (GameDataController::gd->getObjective(S("gasstation_spy_mode")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 3000.0f;
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 50.0f;
	}
}

void GasstationSargeObject::stopAim(String a)
{
	sarge->GetComponent<Animator>()->Play(S("sarge_aim_down"));
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_2a);
}

void GasstationSargeObject::getToWork(String a)
{
	sarge->GetComponent<Animator>()->Play(S("sarge_kneel"));
}

void GasstationSargeObject::stopWork(String a)
{
	sarge->GetComponent<Animator>()->Play(S("sarge_stand_up"));
}

void GasstationSargeObject::shootHim()
{
	PlayerController::pc->setBusy(true);
	Invoke(S("shootHim2"), 0.5f);
}

void GasstationSargeObject::shootHim2()
{
	ItemsManager::im->rifleShot(usedItem);
	Invoke(S("shootHim3"), 0.1f);
}

void GasstationSargeObject::shootHim3()
{
	GameDataController::gd->setObjective(S("gasstation_sarge_shot"), true);
	if (GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
	{
		GameDataController::gd->setObjectiveDetail(S("gasstation_sarge_shot"), 1);
	}
	else
	{
		GameDataController::gd->setObjectiveDetail(S("gasstation_sarge_shot"), 0);
	}
	sarge->shot();
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("gasstation_sarge_shot_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		List<P<DialogueLine>> list2 = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list2, S("gasstation_sarge_shot_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
		list2[3]->actionWithText = false;
		list2[3]->action = [this](String param) { puke(param); };
		for (int j = 0; j < list2.Count(); j++)
		{
			Timeline::t->addDialogue(list2[j]);
		}
	}
	List<P<DialogueLine>> list3 = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list3, S("gasstation_sarge_shot_cate"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	for (int k = 0; k < list3.Count(); k++)
	{
		Timeline::t->addDialogue(list3[k]);
	}
	GameDataController::gd->setObjective(S("thugs_gasstation_talk"), true);
	ItemsManager::im->fixGroundItems(Vector2(175.0f, 35.0f), Vector2(5.0f, 2.0f));
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	ItemsManager::im->initGroundAndInv();
}

void GasstationSargeObject::initIntroDialogue()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (!GameDataController::gd->getObjective(S("gasstation_sarge_intro")))
	{
		DialogueController::dc->initDialogue(list, S("sarge_first_intro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("sarge"))->GetComponent<TextFieldController>(), color);
		sarge->aS->PlayOneShot(ItemsManager::im->getItem(S("rifle_5"))->sound);
		sarge->GetComponent<Animator>()->Play(S("sarge_stand_up_aim"));
	}
	else
	{
		if (!GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
		{
			sarge->GetComponent<Animator>()->Play(S("sarge_stand_up"));
		}
		else
		{
			sarge->decideRotation();
		}
		DialogueController::dc->initDialogue(list, S("sarge_intro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("sarge"))->GetComponent<TextFieldController>(), color);
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	DialogueController::dc->callback = [this]() { dialogues(); };
	dialogues();
}

void GasstationSargeObject::dialogues()
{
	DialogueController::dc->reset();
	int num = 0;
	if (!GameDataController::gd->getObjective(S("gasstation_sarge_reason")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_reason_couldkill_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/couldkill")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("gasstation_sarge_reason"));
		DialogueController::dc->initDialogue(doc->lines, S("sarge_reason_couldkill"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[3]->action = [this](String param) { stopAim(param); };
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_reason_sniper_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sniper")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("gasstation_sarge_reason"));
		DialogueController::dc->initDialogue(doc->lines, S("sarge_reason_sniper"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		doc->lines[3]->action = [this](String param) { stopAim(param); };
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_reason_surrender_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/surrender")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("gasstation_sarge_reason"));
		DialogueController::dc->initDialogue(doc->lines, S("sarge_reason_surrender"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[3]->action = [this](String param) { stopAim(param); };
		num++;
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_convincing5")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_memory_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sarge_memory"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		if (GameDataController::gd->getObjective(S("gasstation_sarge_army")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_for_your_squad_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/army")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("gasstation_sarge_convinced"));
			DialogueController::dc->initDialogue(doc->lines, S("sarge_for_your_squad"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			DialogueController::dc->initDialogue(doc->lines, S("sarge_ok"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
		}
		GameDataController::gd->setObjective(S("gasstation_sarge_convincing5"), false);
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_convincing4")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_decent_life_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("gasstation_sarge_convincing5"));
		DialogueController::dc->initDialogue(doc->lines, S("sarge_decent_life"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		if (GameDataController::gd->getObjective(S("gasstation_sarge_razor_army")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_razor_sucks_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("gasstation_sarge_convinced"));
			DialogueController::dc->initDialogue(doc->lines, S("sarge_razor_sucks"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			DialogueController::dc->initDialogue(doc->lines, S("sarge_ok"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
		}
		GameDataController::gd->setObjective(S("gasstation_sarge_convincing4"), false);
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_convincing3")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_let_us_go_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/us")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sarge_let_us_go"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_leave_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/army")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("gasstation_sarge_convincing4"));
		DialogueController::dc->initDialogue(doc->lines, S("sarge_leave"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		GameDataController::gd->setObjective(S("gasstation_sarge_convincing3"), false);
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_convincing2")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_no_threat_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/surrender")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sarge_no_threat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		if (GameDataController::gd->getObjective(S("gasstation_sarge_moon")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_end_of_days_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/moon")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("gasstation_sarge_convincing3"));
			DialogueController::dc->initDialogue(doc->lines, S("sarge_end_of_days"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
		}
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_honor2_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/rank")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sarge_honor2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		GameDataController::gd->setObjective(S("gasstation_sarge_convincing2"), false);
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_convincing1")))
	{
		GameDataController::gd->setObjectiveDetail(S("gasstation_sarge_canister_filled"), 1);
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_cody_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cody")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(String::Empty);
			DialogueController::dc->initDialogue(doc->lines, S("sarge_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
		}
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_just_let_go_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/surrender")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sarge_just_let_go"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		if (GameDataController::gd->getObjective(S("gasstation_sarge_rank")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_honor_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/rank")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("gasstation_sarge_convincing2"));
			DialogueController::dc->initDialogue(doc->lines, S("sarge_honor"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
		}
		GameDataController::gd->setObjective(S("gasstation_sarge_convincing1"), false);
	}
	else
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_rank_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/rank")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("gasstation_sarge_rank"));
		DialogueController::dc->initDialogue(doc->lines, S("sarge_rank"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		if (GameDataController::gd->getObjective(S("gasstation_sarge_rank")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_troops_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/army")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("gasstation_sarge_army"));
			DialogueController::dc->initDialogue(doc->lines, S("sarge_troops"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
		}
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_razor_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("gasstation_sarge_razor"));
		DialogueController::dc->initDialogue(doc->lines, S("sarge_razor"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
		if (GameDataController::gd->getObjective(S("gasstation_sarge_razor")) && GameDataController::gd->getObjective(S("gasstation_sarge_army")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_razor_army_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor_army")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("gasstation_sarge_razor_army"));
			DialogueController::dc->initDialogue(doc->lines, S("sarge_razor_army"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
		}
		if (GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
		{
			if (!GameDataController::gd->getObjective(S("gasstation_sarge_convinced")))
			{
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_bargain_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/wrench")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("gasstation_sarge_convincing1"));
				if (GameDataController::gd->getObjectiveDetail(S("gasstation_sarge_canister_filled")) == 0)
				{
					DialogueController::dc->initDialogue(doc->lines, S("sarge_bargain"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				}
				else
				{
					DialogueController::dc->initDialogue(doc->lines, S("sarge_bargain2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
				}
				num++;
			}
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_moon_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/moon")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("gasstation_sarge_moon"));
			DialogueController::dc->initDialogue(doc->lines, S("sarge_moon"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("sarge_spaceship_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/ship")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("gasstation_sarge_ship"));
			DialogueController::dc->initDialogue(doc->lines, S("sarge_spaceship"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			num++;
		}
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("exit_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		if (GameDataController::gd->getObjective(S("gasstation_sarge_convinced")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("sarge_last_bye"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { farewell(param); };
			Timeline::t->doNotUnlock = true;
		}
		else if (!GameDataController::gd->getObjective(S("gasstation_sarge_first_bye")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("sarge_first_bye"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { endTalk1(param); };
		}
		else
		{
			DialogueController::dc->initDialogue(doc->lines, S("sarge_bye"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { endTalk1(param); };
		}
	}
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void GasstationSargeObject::endTalk1(String val)
{
	GameDataController::gd->setObjective(S("gasstation_sarge_intro"), true);
	GameDataController::gd->setObjective(S("gasstation_sarge_first_bye"), true);
	if (!GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
	{
		getToWork(String::Empty);
	}
	endTalk(String::Empty);
}

void GasstationSargeObject::clickAction()
{
	if (GameDataController::gd->getObjective(S("gasstation_spy_mode")))
	{
		if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("gasstation_sarge_dead")));
		}
		else if (usedItem.IndexOf(S("rifle")) != -1)
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("shoot_sarge")), QuestionController::PopupType::QUESTION, [this]() { shootHim(); });
		}
		else if (usedItem == S("wrench"))
		{
			if (GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("gasstation_sarge_wrench_done")));
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("gasstation_sarge_wrench_far")));
			}
		}
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("gasstation_sarge_dead")));
	}
	else if (usedItem.IndexOf(S("rifle")) != -1)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("gasstation_sarge_shoot_not_here")));
	}
	else if (usedItem == S("wrench"))
	{
		if (!GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
		{
			sarge->GetComponent<Animator>()->Play(S("sarge_stand_up"));
			List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
			DialogueController::dc->initDialogue(list, S("sarge_wrench"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("sarge"))->GetComponent<TextFieldController>(), color);
			list[list.Count() - 1]->action = [this](String param) { endWrench(param); };
			for (int i = 0; i < list.Count(); i++)
			{
				Timeline::t->addDialogue(list[i]);
			}
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("gasstation_sarge_wrench_done")));
		}
	}
	else if (usedItem == S("whiskey"))
	{
		if (!GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
		{
			sarge->GetComponent<Animator>()->Play(S("sarge_stand_up"));
		}
		else
		{
			sarge->decideRotation();
		}
		List<P<DialogueLine>> list2 = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list2, S("sarge_whiskey"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("sarge"))->GetComponent<TextFieldController>(), color);
		list2[list2.Count() - 1]->action = [this](String param) { endTalk1(param); };
		for (int j = 0; j < list2.Count(); j++)
		{
			Timeline::t->addDialogue(list2[j]);
		}
	}
	else
	{
		initIntroDialogue();
	}
}

void GasstationSargeObject::endWrench(String a)
{
	endTalk(String::Empty);
	PlayerController::pc->setBusy(true);
	sarge->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour);
	GameDataController::gd->setObjective(S("gasstation_sarge_canister_filled"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::E, nullptr, nullptr, false, [this]() { doneFuel(); }, 0.02f);
}

void GasstationSargeObject::farewell(String a)
{
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	PlayerController::pc->setBusy(true);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->motorbikes);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::E, nullptr, nullptr, false, [this]() { hideBike(); });
}

void GasstationSargeObject::hideBike()
{
	GameObject::Find(S("LocationManager"))->GetComponent<Gasstation2Start>()->starter();
}

void GasstationSargeObject::doneFuel()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("sarge_thanks"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("sarge"))->GetComponent<TextFieldController>(), color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void GasstationSargeObject::puke(String aaa)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->vomit);
}

void GasstationSargeObject::updateState()
{
	if (GameDataController::gd->getCurrentDay() != 3 || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 0 || !GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		setCollider(-1);
		sarge->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		setCollider(0);
		sarge->GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjective(S("gasstation_sarge_canister_filled")))
		{
			setCollider(1);
		}
		if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
		{
			setCollider(2);
		}
	}
	if (GameDataController::gd->getObjective(S("gasstation_sarge_convinced")))
	{
		setCollider(-1);
		sarge->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getCurrentDay() > 3 && !GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		setCollider(-1);
		sarge->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("gasstation_spy_mode")) || GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		actionType = Type::NormalAction;
	}
	else
	{
		actionType = Type::Talk;
	}
}

void GasstationSargeObject::clickAction2()
{
}

void GasstationSargeObject::clickAction0()
{
}

void GasstationSargeObject::dontTouchThat()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("gasstation_sarge_dont_touch"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("sarge"))->GetComponent<TextFieldController>(), color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void GasstationSargeObject::talkWrench()
{
	usedItem = S("wrench");
	clickAction();
}
