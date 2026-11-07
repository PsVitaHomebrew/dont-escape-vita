#include "../game_all.h"

void ClockController::Start()
{
	sufix_minutes = S("0");
	sufix_hours = S("0");
	if (GameDataController::gd->getObjective(S("wall_encountered")))
	{
		show();
	}
	else
	{
		hide();
	}
}

void ClockController::showClock(String param)
{
	gameObject->GetComponent<CircleCollider2D>()->set_enabled(false);
	Invoke(S("show"), 0.25f);
	Invoke(S("hide"), 0.5f);
	Invoke(S("show"), 0.75f);
	Invoke(S("hide"), 1.0f);
	Invoke(S("show"), 1.25f);
	Invoke(S("hide"), 1.5f);
	Invoke(S("show"), 1.75f);
	Invoke(S("hide"), 2.0f);
	Invoke(S("showFinal"), 2.25f);
}

void ClockController::showFinal()
{
	show();
	gameObject->GetComponent<CircleCollider2D>()->set_enabled(true);
}

void ClockController::show()
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2(205.0f, 125.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -2.5f;
	gameObject->transform->set_position(position);
}

void ClockController::hide()
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-9999.0f, -9999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -4.0f;
	gameObject->transform->set_position(position);
}

String ClockController::getClockTimeWithRemaining()
{
	String text = GameStrings::getString(GameStrings::gui, S("left_prefix"));
	if (text.Length() > 0)
	{
		text += S(" ");
	}
	String text2 = GameStrings::getString(GameStrings::gui, S("left"));
	if (text2.Length() > 0)
	{
		text2 = S(" ") + text2;
	}
	return getClockTime() + S(" (") + text + getTimeLeft() + text2 + S(")");
}

Vector3 ClockController::getTimeColor()
{
	int num = GameDataController::gd->timeLimit - GameDataController::gd->gameTime;
	Vector3 result = Vector3(1.0f, 1.0f, 1.0f);
	if (num < 120)
	{
		result = Vector3(1.0f, 1.0f, 0.0f);
	}
	if (num < 60)
	{
		result = Vector3(1.0f, 0.0f, 0.0f);
	}
	return result;
}

bool ClockController::advanceTime(int amount, bool traveling)
{
	GameDataController::gd->gameTime += amount;
	if (traveling)
	{
		GameDataController::gd->traveledTime += amount;
	}
	else
	{
		GameDataController::gd->workedTime += amount;
	}
	if (GameDataController::gd->gameTime >= GameDataController::gd->timeLimit)
	{
		GameDataController::gd->gameTime -= amount;
		GameDataController::gd->equipped = String::Empty;
		GameDataController::gd->setObjective(S("ship_launched"), false);
		endTime(true);
		return false;
	}
	return true;
}

void ClockController::endTime(bool accident)
{
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		GameDataController::gd->saveIfOK(GameDataController::CHAPTER_1_COMPLETE_AUTOSAVE);
	}
	if (GameDataController::gd->getCurrentDay() == 2)
	{
		GameDataController::gd->saveIfOK(GameDataController::CHAPTER_2_COMPLETE_AUTOSAVE);
	}
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		GameDataController::gd->saveIfOK(GameDataController::CHAPTER_3_COMPLETE_AUTOSAVE);
	}
	if (GameDataController::gd->getCurrentDay() == 4)
	{
		GameDataController::gd->saveIfOK(GameDataController::CHAPTER_4_COMPLETE_AUTOSAVE);
	}
	GameDataController::gd->previousLocation = GameDataController::gd->location;
	PlayerController::pc->spawnName = S("LocationDefaultSpawn");
	CurtainController::cc->fadeOut(S("ChapterResults"), WalkController::Direction::W);
}

String ClockController::getClockTime(int timeToTranslate)
{
	String text = String::Empty;
	String text2 = String::Empty;
	int num = ((timeToTranslate != -1) ? timeToTranslate : GameDataController::gd->gameTime);
	int num2 = num / 60;
	int num3 = num % 60;
	if (GameStrings::getString(GameStrings::gui, S("am")) != S("-"))
	{
		if (num2 < 12)
		{
			text2 = GameStrings::getString(GameStrings::gui, S("am"));
		}
		else
		{
			text2 = GameStrings::getString(GameStrings::gui, S("pm"));
			if (text2.Length() > 0)
			{
				num2 -= 12;
			}
		}
	}
	if (num2 == 0 && text2.Length() > 0)
	{
		num2 = 12;
	}
	if (num2 < 10)
	{
		text += S("0");
	}
	text = text + num2 + S(":");
	if (num3 < 10)
	{
		text += S("0");
	}
	String text3 = text;
	return text3 + num3 + S(" ") + text2;
}

String ClockController::getTimeLeft()
{
	String text = String::Empty;
	int num = GameDataController::gd->timeLimit - GameDataController::gd->gameTime;
	int num2 = num / 60;
	int num3 = num % 60;
	if (num2 > 1)
	{
		text = text + num2 + S(" ") + GameStrings::getString(GameStrings::gui, S("hours"));
	}
	else if (num2 == 1)
	{
		text = text + num2 + S(" ") + GameStrings::getString(GameStrings::gui, S("hour"));
	}
	if (num2 > 0 && num3 > 0)
	{
		text += S(" ");
	}
	if (num3 > 1)
	{
		text = text + num3 + S(" ") + GameStrings::getString(GameStrings::gui, S("minutes"));
	}
	else if (num3 == 1)
	{
		text = text + num3 + S(" ") + GameStrings::getString(GameStrings::gui, S("minute"));
	}
	return text;
}

void ClockController::Update()
{
	for (int i = 0; i < 12; i++)
	{
		if ((GameDataController::gd->gameTime >= 60 * i && GameDataController::gd->gameTime < 60 * (i + 1)) || (GameDataController::gd->gameTime >= 60 * (i + 12) && GameDataController::gd->gameTime < 60 * (i + 13)))
		{
			sufix_hours = str(i);
		}
	}
	for (int j = 0; j < 60; j++)
	{
		int num = GameDataController::gd->gameTime % 60;
		if (num >= 5 * j && num < 5 * (j + 1))
		{
			sufix_minutes = str(j);
		}
	}
	minutesHand->GetComponent<Animator>()->Play(S("clock_hand1_") + sufix_minutes, 0);
	hoursHand->GetComponent<Animator>()->Play(S("clock_hand2_") + sufix_hours, 0);
}

void ClockController::OnMouseOver()
{
	if (!PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController::PixelCursor::ACTIVE);
		if (frame_name_sufix != S("1"))
		{
			frame_name_sufix = S("1");
			this->gameObject->GetComponent<Animator>()->Play(S("clock_") + frame_name_sufix, 0);
			P<GameObject> gameObject = GameObject::Find(S("BottomText"));
			String text = getClockTimeWithRemaining() + S(" ^") + GameStrings::getString(GameStrings::gui, S("clock"));
			Vector3 timeColor = getTimeColor();
			gameObject->GetComponent<TextFieldController>()->viewText(text, false, true, false, BottomTextController::bottomTextWidth, timeColor.x, timeColor.y, timeColor.z);
		}
	}
	else
	{
		OnMouseExit();
	}
}

void ClockController::OnMouseExit()
{
	if (!PlayerController::wc->busy || PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		hideText();
	}
}

void ClockController::hideText()
{
	GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController::PixelCursor::NORMAL);
	P<GameObject> gameObject = GameObject::Find(S("BottomText"));
	gameObject->GetComponent<TextFieldController>()->keepAlive = false;
	frame_name_sufix = S("0");
	this->gameObject->GetComponent<Animator>()->Play(S("clock_") + frame_name_sufix, 0);
}

void ClockController::takeDoc(int i)
{
	doc = DialogueController::dc->dialogueOptions[i]->GetComponent<DialogueOptionController>();
}

void ClockController::endTalk(String val)
{
	PlayerController::pc->clickedSomething = true;
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
}

void ClockController::equipItem(String item)
{
	if (GameDataController::gd->getCurrentDay() == 4)
	{
		GameDataController::gd->setObjective(S("ship_launched"), true);
	}
	GameDataController::gd->equipped = item;
	endTalk(String::Empty);
	endTime();
}

void ClockController::OnMouseDown()
{
	if (!PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		PlayerController::pc->clickedSomething = true;
		hideText();
		PlayerController::wc->fullStop(true);
		Timeline::t->stopChitChat();
		if (InventoryButtonController::ibc->gameObject->GetComponent<BoxCollider2D>()->get_enabled())
		{
			InventoryButtonController::ibc->close();
		}
		CursorController::cc->deselectItem();
		if (InventoryController::ic != nullptr)
		{
			InventoryController::ic->gameObject->SetActive(false);
		}
		if (GameDataController::gd->getCurrentDay() == 4)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("day4_no_clock")));
		}
		else if (!GameDataController::gd->getObjective(S("base_discovered")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("clock_not_yet")));
		}
		else if (GameDataController::gd->getCurrentDay() == 2 && !GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("heli_crash_check")));
		}
		else if (GameDataController::gd->getCurrentDay() == 3 && !GameDataController::gd->getObjective(S("sidereal_base_located")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_base_check")));
		}
		else
		{
			showEndDialogue();
		}
	}
}

void ClockController::showEndDialogue(String s, String s2)
{
	DialogueController::dc->callback = nullptr;
	takeDoc(0);
	DialogueController::dc->ShowText(GameStrings::getString(GameStrings::warnings, s));
	DialogueController::dc->reset();
	equip_i = 0;
	takeDoc(equip_i);
	doc->caption = GameStrings::getString(GameStrings::gui, s2);
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/hand")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String item) { equipItem(item); };
	doc->lines[doc->lines.Count() - 1]->actionParam = String::Empty;
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	equip_i++;
	addItem(S("pipe"), S("equip_arm"));
	addItem(S("crowbar"), S("equip_arm"));
	addItem(S("wrench"), S("equip_arm"));
	addItem(S("rifle_1"), S("equip_arm"));
	addItem(S("rifle_2"), S("equip_arm"));
	addItem(S("rifle_3"), S("equip_arm"));
	addItem(S("rifle_4"), S("equip_arm"));
	addItem(S("rifle_5"), S("equip_arm"));
	addItem(S("rifle_6"), S("equip_arm"));
	addItem(S("rifle_o_1"), S("equip_arm"));
	addItem(S("rifle_o_2"), S("equip_arm"));
	addItem(S("rifle_o_3"), S("equip_arm"));
	addItem(S("rifle_o_4"), S("equip_arm"));
	addItem(S("rifle_o_5"), S("equip_arm"));
	addItem(S("rifle_o_6"), S("equip_arm"));
	addItem(S("rifle_s_1"), S("equip_arm"));
	addItem(S("rifle_s_2"), S("equip_arm"));
	addItem(S("rifle_s_3"), S("equip_arm"));
	addItem(S("rifle_s_4"), S("equip_arm"));
	addItem(S("rifle_s_5"), S("equip_arm"));
	addItem(S("rifle_s_6"), S("equip_arm"));
	addItem(S("rifle_so_1"), S("equip_arm"));
	addItem(S("rifle_so_2"), S("equip_arm"));
	addItem(S("rifle_so_3"), S("equip_arm"));
	addItem(S("rifle_so_4"), S("equip_arm"));
	addItem(S("rifle_so_5"), S("equip_arm"));
	addItem(S("rifle_so_6"), S("equip_arm"));
	addItem(S("flamethrower"), S("equip_arm"));
	addItem(S("knife"), S("equip_arm"));
	addItem(S("water1"), S("equip_take"));
	addItem(S("water2"), S("equip_take"));
	addItem(S("water3"), S("equip_take"));
	addItem(S("water4"), S("equip_take"));
	addItem(S("coat1"), S("equip_wear"));
	addItem(S("coat2"), S("equip_wear"));
	addItem(S("coat3"), S("equip_wear"));
	addItem(S("coat4"), S("equip_wear"));
	addItem(S("chemsuit_dmg_dmg"), S("equip_wear"));
	addItem(S("chemsuit_dmg_rep"), S("equip_wear"));
	addItem(S("chemsuit_rep_dmg"), S("equip_wear"));
	addItem(S("chemsuit_rep_rep"), S("equip_wear"));
	addItem(S("pills"), S("equip_take"));
	takeDoc(equip_i);
	doc->caption = GameStrings::getString(GameStrings::gui, S("cancel"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), nullptr, Vector3(), nullptr, Vector3(), Resources::Load<Sprite>(S("Bitmaps/Misc/wait_bck")));
	doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalk(val); };
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	equip_i++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void ClockController::addItem(String item, String how)
{
	if (InventoryController::ic->isItemInInventory(item))
	{
		takeDoc(equip_i);
		doc->caption = GameStrings::getString(GameStrings::gui, how) + S(" ") + GameStrings::getPrefixedShort(GameStrings::items, item).ToLower();
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Items/") + item + S("_inv")));
		doc->lines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
		doc->setObjective(String::Empty);
		doc->lines[doc->lines.Count() - 1]->action = [this](String item) { equipItem(item); };
		doc->lines[doc->lines.Count() - 1]->actionParam = item;
		doc->lines[doc->lines.Count() - 1]->actionWithText = true;
		equip_i++;
	}
}
