#include "../game_all.h"

void RestaurantSarge::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	actionType = Type::Talk;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_sarge");
	range = 30.0f;
	position = ScreenControler::roundToNearestFullPixel3(sarge->transform->get_position());
	sarge->transform->set_position(position);
	position2 = Vector2(75.0f, 92.0f);
	Vector2 vectorToChange = Vector2();
	float z = sarge->transform->get_position().z;
	vectorToChange.x = position2.x;
	vectorToChange.y = position2.y;
	vectorToChange = ScreenControler::gameToScreen(vectorToChange);
	position = Vector3(vectorToChange.x, vectorToChange.y, sarge->transform->get_position().z);
	Vector3 vector = Camera::get_main()->WorldToScreenPoint(sarge->transform->get_position());
	position.z = vector.z;
	sarge->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position));
	sarge->transform->set_position(Vector3(sarge->transform->get_position().x, sarge->transform->get_position().y, z));
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("rifle_0"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_0"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_0"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_0"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_0"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("gun_ammo"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_ammo"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("bandage"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("whiskey"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("stormcatcher3"), String::Empty, nullptr, String::Empty));
	updateState();
}

void RestaurantSarge::takeCatcher(String item)
{
	GameDataController::gd->setObjective(S("r_sarge_catcher"), true);
	InventoryController::ic->removeItem(item);
}

void RestaurantSarge::clickAction()
{
	if (usedItem == String::Empty)
	{
		initIntroDialogue();
	}
	else if (usedItem.IndexOf(S("stormcatcher")) != -1)
	{
		GameDataController::gd->setObjective(S("r_paul_mount1"), true);
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		if (!GameDataController::gd->getObjective(S("r_sarge_catchers1")))
		{
			GameDataController::gd->setObjective(S("r_sarge_catchers1"), true);
			DialogueController::dc->initDialogue(list, S("r_sarge_catchers1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
		}
		else if (!GameDataController::gd->getObjective(S("r_sarge_gun")) || !GameDataController::gd->getObjective(S("r_sarge_ammo")))
		{
			DialogueController::dc->initDialogue(list, S("r_sarge_catchers2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
		}
		else if (!GameDataController::gd->getObjective(S("r_sarge_catcher")))
		{
			DialogueController::dc->initDialogue(list, S("r_sarge_catchers4"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
			list[list.Count() - 1]->action = [this](String item) { takeCatcher(item); };
			list[list.Count() - 1]->actionParam = usedItem;
		}
		else
		{
			DialogueController::dc->initDialogue(list, S("r_sarge_catchers5"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
		}
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
	else if (usedItem.IndexOf(S("rifle")) != -1 || usedItem.IndexOf(S("revolver")) != -1 || usedItem.IndexOf(S("ammo")) != -1)
	{
		List<P<DialogueLine>> list2 = List<P<DialogueLine>>::New();
		if (GameDataController::gd->getObjective(S("r_sarge_catchers1")))
		{
			if (GameDataController::gd->getObjective(S("r_sarge_gun")) && GameDataController::gd->getObjective(S("r_sarge_ammo")))
			{
				DialogueController::dc->initDialogue(list2, S("r_sarge_catchers_gun3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
			}
			else
			{
				if (usedItem.IndexOf(S("rifle")) != -1 && usedItem.IndexOf(S("ammo")) == -1)
				{
					DialogueController::dc->initDialogue(list2, S("r_sarge_catchers_gun2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
				}
				if (usedItem.IndexOf(S("gun_ammo")) != -1)
				{
					if (GameDataController::gd->getObjective(S("r_sarge_gun")))
					{
						DialogueController::dc->initDialogue(list2, S("r_sarge_catchers_ammo1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
						InventoryController::ic->removeItem(S("gun_ammo"));
						GameDataController::gd->setObjective(S("r_sarge_ammo"), true);
					}
					else
					{
						DialogueController::dc->initDialogue(list2, S("r_sarge_catchers_ammo3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
					}
				}
				if (usedItem.IndexOf(S("revolver")) != -1)
				{
					DialogueController::dc->initDialogue(list2, S("r_sarge_catchers_gun1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
					InventoryController::ic->removeItem(usedItem);
					GameDataController::gd->setObjective(S("r_sarge_gun"), true);
				}
				if (usedItem.IndexOf(S("rifle_ammo")) != -1)
				{
					if (GameDataController::gd->getObjective(S("r_sarge_gun")))
					{
						DialogueController::dc->initDialogue(list2, S("r_sarge_catchers_ammo2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
					}
					else
					{
						DialogueController::dc->initDialogue(list2, S("r_sarge_catchers_ammo3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
					}
				}
			}
		}
		else
		{
			DialogueController::dc->initDialogue(list2, S("r_sarge_catchers_deal0"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
		}
		for (int j = 0; j < list2.Count(); j++)
		{
			Timeline::t->addDialogue(list2[j]);
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::dialogues, S("r_sarge_medical")));
	}
}

void RestaurantSarge::initIntroDialogue()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (!GameDataController::gd->getObjective(S("restaurant_sarge_encountered")))
	{
		DialogueController::dc->initDialogue(list, S("r_sarge_intro1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			DialogueController::dc->initDialogue(list, S("r_sarge_intro1_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), sarge->GetComponent<TextFieldController>(), color, GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
		}
		if (GameDataController::gd->getObjective(S("npc2_alive")))
		{
			DialogueController::dc->initDialogue(list, S("r_sarge_intro1_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), sarge->GetComponent<TextFieldController>(), color, GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
		}
		list[list.Count() - 2]->action = [this](String a) { blockanim(a); };
	}
	else
	{
		DialogueController::dc->initDialogue(list, S("sarge_intro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), sarge->GetComponent<TextFieldController>(), color);
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	DialogueController::dc->callback = [this]() { dialogues(); };
	dialogues();
}

void RestaurantSarge::takeDoc(int i)
{
	doc = DialogueController::dc->dialogueOptions[i]->GetComponent<DialogueOptionController>();
}

void RestaurantSarge::blockanim(String a)
{
	PlayerController::pc->gameObject->GetComponent<Animator>()->set_enabled(false);
}

void RestaurantSarge::dialogueintro2(String s)
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("r_sarge_intro2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
	list[list.Count() - 2]->action = [this](String v) { playerStandUp(v); };
	list[list.Count() - 2]->actionWithText = false;
	list[list.Count() - 1]->action = [this](String s) { atEase(s); };
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void RestaurantSarge::dialogueintro3()
{
	GameObject::Find(S("solider1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	GameObject::Find(S("solider2"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	GameObject::Find(S("solider4"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("r_sarge_intro3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	DialogueController::dc->talking = true;
	DialogueController::dc->callback = [this]() { dialogues(); };
	dialogues();
}

void RestaurantSarge::atEase(String s)
{
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->setBusy(true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, nullptr, nullptr, false, [this]() { dialogueintro3(); });
}

void RestaurantSarge::playerStandUp(String v)
{
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->gameObject->GetComponent<Animator>()->set_enabled(true);
	PlayerController::pc->forceAnimation(S("surr_end"));
	PlayerController::wc->forceDirection(WalkController::Direction::NW);
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("surr_end"), true);
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("surr_end"), true);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("surr_end"), true);
	}
}

void RestaurantSarge::dialogues()
{
	DialogueController::dc->reset();
	int num = 0;
	if (!GameDataController::gd->getObjective(S("restaurant_sarge_encountered")))
	{
		PlayerController::pc->gameObject->GetComponent<Animator>()->set_enabled(true);
		PlayerController::wc->forceAnimation(S("surr"), true);
		PlayerController::pc->gameObject->GetComponent<Animator>()->set_enabled(false);
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_hello1_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/us")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("restaurant_sarge_encountered"));
		DialogueController::dc->initDialogue(doc->lines, S("r_sarge_hello1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_hello1_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
		}
		if (GameDataController::gd->getObjective(S("npc2_alive")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_hello1_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
		}
		doc->lines[doc->lines.Count() - 1]->action = [this](String s) { dialogueintro2(s); };
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_hello3_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/we_family")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("restaurant_sarge_encountered"));
		DialogueController::dc->initDialogue(doc->lines, S("r_sarge_hello3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_hello3_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
		}
		if (GameDataController::gd->getObjective(S("npc2_alive")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_hello3_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
		}
		doc->lines[doc->lines.Count() - 1]->action = [this](String s) { dialogueintro2(s); };
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_hello2_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/we_noneofyour")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("restaurant_sarge_encountered"));
		DialogueController::dc->initDialogue(doc->lines, S("r_sarge_hello2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), sarge->GetComponent<TextFieldController>(), color);
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_hello1_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
		}
		if (GameDataController::gd->getObjective(S("npc2_alive")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_hello1_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
		}
		doc->lines[doc->lines.Count() - 1]->action = [this](String s) { dialogueintro2(s); };
		num++;
	}
	else
	{
		if (!GameDataController::gd->getObjective(S("r_sarge_wounded2")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_wounded1_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/wounded")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("r_sarge_wounded1"));
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_wounded1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			if (GameDataController::gd->getObjective(S("r_sarge_wounded_bandage")) && GameDataController::gd->getObjective(S("r_sarge_wounded_alcohol")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("r_sarge_wounded8"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("r_sarge_wounded_bandage")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("r_sarge_wounded4"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("r_sarge_wounded_alcohol")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("r_sarge_wounded3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else
			{
				DialogueController::dc->initDialogue(doc->lines, S("r_sarge_wounded2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			num++;
		}
		else if (!GameDataController::gd->getObjective(S("r_sarge_wounded_bandage")) && !GameDataController::gd->getObjective(S("r_sarge_wounded_alcohol")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_wounded6_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/wounded")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("r_sarge_wounded3"));
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_wounded6"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			if (GameDataController::gd->getObjective(S("r_sarge_wounded_bandage")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("r_sarge_wounded4"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("r_sarge_wounded_alcohol")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("r_sarge_wounded3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else
			{
				DialogueController::dc->initDialogue(doc->lines, S("r_sarge_wounded2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			num++;
		}
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_plans1_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/army")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("r_sarge_plans1"));
		DialogueController::dc->initDialogue(doc->lines, S("r_sarge_plans1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_places_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/map")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("r_sarge_places1"));
		DialogueController::dc->initDialogue(doc->lines, S("r_sarge_places1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { addConstruction(val); };
		num++;
		if (GameDataController::gd->getObjective(S("r_sarge_plans1")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_plans2_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/east")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("r_sarge_plans2"));
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_plans2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			num++;
		}
		if (GameDataController::gd->getObjective(S("r_sarge_plans2")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_survive1_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/storm")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("r_sarge_survive1"));
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_survive1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			num++;
		}
		if (GameDataController::gd->getObjective(S("r_sarge_plans2")) && GameDataController::gd->getObjective(S("gasstation_sarge_ship")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_plans3_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge_ship")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("r_sarge_plans3"));
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_plans3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			String text = String::Empty;
			if (GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjective(S("npc3_alive")))
			{
				text = S("r_sarge_plans3_cody_barry");
			}
			else if (GameDataController::gd->getObjective(S("npc2_alive")))
			{
				text = S("r_sarge_plans3_barry");
			}
			else if (GameDataController::gd->getObjective(S("npc3_alive")))
			{
				text = S("r_sarge_plans3_cody");
			}
			if (text != String::Empty)
			{
				doc->lines.Add(New<DialogueLine>(GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameStrings::getString(GameStrings::dialogues, text), nullptr));
				doc->lines.Add(New<DialogueLine>(GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameStrings::getString(GameStrings::dialogues, S("r_sarge_plans3_company")), nullptr));
			}
			else
			{
				doc->lines.Add(New<DialogueLine>(GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameStrings::getString(GameStrings::dialogues, S("r_sarge_plans3_single")), nullptr));
			}
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_plans4"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
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
		if (GameDataController::gd->getObjective(S("r_paul_mount1")) && !GameDataController::gd->getObjective(S("r_sarge_catcher")))
		{
			if (!GameDataController::gd->getObjective(S("r_sarge_catchers1")))
			{
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_catchers1_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pylon2")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("r_sarge_catchers1"));
				DialogueController::dc->initDialogue(doc->lines, S("r_sarge_catchers1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
				num++;
			}
			else if (!GameDataController::gd->getObjective(S("r_sarge_gun")) || !GameDataController::gd->getObjective(S("r_sarge_ammo")))
			{
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_catchers2_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pylon2")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("r_sarge_catchers2"));
				DialogueController::dc->initDialogue(doc->lines, S("r_sarge_catchers2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
				num++;
			}
			else if (!GameDataController::gd->getObjective(S("r_sarge_catcher")))
			{
				takeDoc(num);
				doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_sarge_catchers3_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pylon2")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("r_sarge_catchers3"));
				DialogueController::dc->initDialogue(doc->lines, S("r_sarge_catchers3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
				num++;
			}
		}
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("exit_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("r_sarge_first_bye"));
		if (!GameDataController::gd->getObjective(S("r_sarge_first_bye")))
		{
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_first_bye"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		else
		{
			DialogueController::dc->initDialogue(doc->lines, S("r_sarge_bye"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		}
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalk(val); };
		num++;
	}
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void RestaurantSarge::endTalk(String val)
{
	if (GameDataController::gd->getObjective(S("r_sarge_wounded1")))
	{
		GameDataController::gd->setObjective(S("r_sarge_wounded2"), true);
	}
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	updateState();
}

void RestaurantSarge::addConstruction(String val)
{
	GameDataController::gd->setObjectiveDetail(S("map_construction_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->page_turn_01);
}

void RestaurantSarge::Update()
{
}

void RestaurantSarge::updateState()
{
	if (GameDataController::gd->getCurrentDay() != 3 || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 1 || !GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		sarge->GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(-1);
	}
	else
	{
		sarge->GetComponent<SpriteRenderer>()->set_enabled(true);
		setCollider(0);
	}
}

void RestaurantSarge::clickAction2()
{
}

void RestaurantSarge::clickAction0()
{
}
