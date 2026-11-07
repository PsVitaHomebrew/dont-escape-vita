#include "../game_all.h"

#ifdef VITA
// Vita port: Options > Cursor picks the stick that moves the cursor (main_vita.cpp reads pref cursorStick: 0 right, 1 left).
static String vitaCursorStickLabel() { return PlayerPrefs::GetInt(S("cursorStick"), 0) == 1 ? S("[Cursor: Left stick]") : S("[Cursor: Right stick]"); }
static void vitaToggleCursorStick() {
	PlayerPrefs::SetInt(S("cursorStick"), PlayerPrefs::GetInt(S("cursorStick"), 0) == 1 ? 0 : 1);
	PlayerPrefs::Save();
	P<GameObject> go = GameObject::Find(S("ResolutionBtn"));
	if (go) go->GetComponent<Button>()->initButton(vitaCursorStickLabel());
}
#endif

void OptionsMenuStart::Start()
{
	Timeline::t->doNotUnlock = false;
	exampleSound = List<P<AudioClip>>::New();
	exampleSound.Add(ItemsManager::im->getItem(S("key1"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("pipe"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("sonic"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("bug"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("pest_note"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("pest1"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("crowbar"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("hammer"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("window_net1"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("canister_empty"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("board1"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("chem_glass"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("rifle_1"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("bear_trap_1"))->sound);
	exampleSound.Add(ItemsManager::im->getItem(S("revolver_0"))->sound);
	exampleMusic = SoundsManagerController::sm->chorus1;
	PlayerPrefs::Save();
	aS->set_ignoreListenerPause(true);
	aS->set_ignoreListenerVolume(true);
	aS->set_volume((float)PlayerPrefs::GetInt(S("sound")) / 100.0f);
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -5.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("none"));
	PlayerController::pc->copySettingsToNPCs();
	MonoBehaviour::print(S("............................. LOCATION INFO  .................................."));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("back")) + S("]"));
	component->buttonText->OPTIONAL_MARGIN = 6;
	component->workIfBusy = false;
	component->onClick = [this]() { continueGame(); };
	if (GameDataController::gd->previousLocation != S("MainMenu"))
	{
		P<Button> component2 = GameObject::Find(S("QuitBtn"))->GetComponent<Button>();
		component2->workIfBusy = false;
		component2->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("quit")) + S("]"));
		component2->onClick = [this]() { quit(); };
		P<Button> component3 = GameObject::Find(S("SaveBtn"))->GetComponent<Button>();
		component3->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("save")) + S("]"));
		component3->workIfBusy = false;
		component3->onClick = [this]() { saveGame(); };
		P<Button> component4 = GameObject::Find(S("LoadBtn"))->GetComponent<Button>();
		component4->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("loadGame")) + S("]"));
		component4->workIfBusy = false;
		component4->onClick = [this]() { loadGame(); };
		P<Button> component5 = GameObject::Find(S("MainBtn"))->GetComponent<Button>();
		component5->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("quitToMain")) + S("]"));
		component5->workIfBusy = false;
		component5->onClick = [this]() { mainMenu(); };
	}
	else
	{
		P<Button> component6 = GameObject::Find(S("QuitBtn"))->GetComponent<Button>();
		component6->workIfBusy = false;
		component6->initButton(S(" "));
		component6->buttonEnabled = false;
		P<Button> component7 = GameObject::Find(S("SaveBtn"))->GetComponent<Button>();
		component7->initButton(S(" "));
		component7->workIfBusy = false;
		component7->buttonEnabled = false;
		P<Button> component8 = GameObject::Find(S("LoadBtn"))->GetComponent<Button>();
		component8->initButton(S(" "));
		component8->workIfBusy = false;
		component8->buttonEnabled = false;
	}
	P<Button> component9 = GameObject::Find(S("FontBtn"))->GetComponent<Button>();
	if (PlayerPrefs::GetString(S("font"), S("pixel")) == S("pixel"))
	{
		component9->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("font")) + S(": ") + GameStrings::getString(GameStrings::gui, S("font_pixel")) + S("]"));
	}
	else
	{
		component9->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("font")) + S(": ") + GameStrings::getString(GameStrings::gui, S("font_smooth")) + S("]"));
	}
	component9->workIfBusy = false;
	component9->onClick = [this]() { pickFont(); };
	P<Button> component10 = GameObject::Find(S("LanguageBtn"))->GetComponent<Button>();
	component10->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("language")) + S(": ") + GameStrings::getString(GameStrings::languages, PlayerPrefs::GetString(S("lang"))) + S("]"));
	component10->workIfBusy = false;
	component10->onClick = [this]() { pickLanguage(); };
	P<TextFieldController> component11 = GameObject::Find(S("Caption_Speed"))->GetComponent<TextFieldController>();
	component11->viewText(GameStrings::getString(GameStrings::gui, S("text_speed")) + S(":"), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	component11->keepAlive = true;
	component11->transform->set_position(ScreenControler::roundToNearestFullPixel2(component11->transform->get_position()));
	P<TextFieldController> component12 = GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>();
	component12->viewText(GameStrings::getString(GameStrings::gui, S("static")) + S(":"), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	component12->keepAlive = true;
	component12->transform->set_position(ScreenControler::roundToNearestFullPixel2(component12->transform->get_position()));
	P<TextFieldController> component13 = GameObject::Find(S("Caption_Music"))->GetComponent<TextFieldController>();
	component13->viewText(GameStrings::getString(GameStrings::gui, S("music")) + S(":"), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	component13->keepAlive = true;
	component13->transform->set_position(ScreenControler::roundToNearestFullPixel2(component12->transform->get_position()));
	P<TextFieldController> component14 = GameObject::Find(S("Caption_Sound"))->GetComponent<TextFieldController>();
	component14->viewText(GameStrings::getString(GameStrings::gui, S("sound")) + S(":"), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	component14->keepAlive = true;
	component14->transform->set_position(ScreenControler::roundToNearestFullPixel2(component12->transform->get_position()));
	counter1 = GameObject::Find(S("Counter1"))->GetComponent<TextFieldController>();
	counter1->transform->set_position(ScreenControler::roundToNearestFullPixel2(component12->transform->get_position()));
	counter2 = GameObject::Find(S("Counter2"))->GetComponent<TextFieldController>();
	counter2->transform->set_position(ScreenControler::roundToNearestFullPixel2(component12->transform->get_position()));
	counter3 = GameObject::Find(S("Counter3"))->GetComponent<TextFieldController>();
	counter3->transform->set_position(ScreenControler::roundToNearestFullPixel2(component12->transform->get_position()));
	counter4 = GameObject::Find(S("Counter4"))->GetComponent<TextFieldController>();
	counter4->transform->set_position(ScreenControler::roundToNearestFullPixel2(component12->transform->get_position()));
	P<Button> component15 = GameObject::Find(S("SpeedBtnDown"))->GetComponent<Button>();
	component15->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("down")) + S("]"));
	component15->onClick = [this]() { speedDown(); };
	component15->workIfBusy = false;
	P<Button> component16 = GameObject::Find(S("SpeedBtnUp"))->GetComponent<Button>();
	component16->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("up")) + S("]"));
	component16->onClick = [this]() { speedUp(); };
	component16->workIfBusy = false;
	P<Button> component17 = GameObject::Find(S("StaticBtnDown"))->GetComponent<Button>();
	component17->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("down")) + S("]"));
	component17->onClick = [this]() { staticDown(); };
	component17->workIfBusy = false;
	P<Button> component18 = GameObject::Find(S("StaticBtnUp"))->GetComponent<Button>();
	component18->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("up")) + S("]"));
	component18->onClick = [this]() { staticUp(); };
	component18->workIfBusy = false;
	P<Button> component19 = GameObject::Find(S("MusicBtnDown"))->GetComponent<Button>();
	component19->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("down")) + S("]"));
	component19->onClick = [this]() { musicDown(); };
	component19->workIfBusy = false;
	P<Button> component20 = GameObject::Find(S("SoundBtnUp"))->GetComponent<Button>();
	component20->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("up")) + S("]"));
	component20->onClick = [this]() { soundsUp(); };
	component20->workIfBusy = false;
	P<Button> component21 = GameObject::Find(S("SoundBtnDown"))->GetComponent<Button>();
	component21->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("down")) + S("]"));
	component21->onClick = [this]() { soundsDown(); };
	component21->workIfBusy = false;
	P<Button> component22 = GameObject::Find(S("MusicBtnUp"))->GetComponent<Button>();
	component22->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("up")) + S("]"));
	component22->onClick = [this]() { musicUp(); };
	component22->workIfBusy = false;
	counter1->viewText(meter(PlayerPrefs::GetInt(S("sound"))), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter1->keepAlive = true;
	counter2->viewText(meter(PlayerPrefs::GetInt(S("music"))), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter2->keepAlive = true;
	counter3->viewText(meter(PlayerPrefs::GetInt(S("stati"))), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter3->keepAlive = true;
	float num = PlayerPrefs::GetFloat(S("textSpeed"), 0.05f) - 0.0125f;
	num /= 0.074999996f;
	int stat = 100 - (int)(num * 100.0f);
	counter4->viewText(meter(stat), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter4->keepAlive = true;
	int num2 = 0;
	int num3 = 0;
	P<Button> component23 = GameObject::Find(S("ResolutionBtn"))->GetComponent<Button>();
#ifdef VITA
	// Vita port: the screen size is fixed, so this button picks which stick moves the cursor.
	component23->initButton(vitaCursorStickLabel());
	component23->workIfBusy = false;
	component23->onClick = []() { vitaToggleCursorStick(); };
#else
	if (PlayerPrefs::GetInt(S("fullscreen")) == 1)
	{
		component23->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("resolution")) + S(": ") + GameStrings::getString(GameStrings::gui, S("fullscreen")) + S("]"));
	}
	else
	{
		num2 = PlayerPrefs::GetInt(S("resolution"));
		for (int i = 0; i < ScreenControler::allowedResolutions.Length(); i++)
		{
			if (ScreenControler::allowedResolutions[i].x == (float)num2)
			{
				num3 = (int)ScreenControler::allowedResolutions[i].y;
			}
		}
		component23->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("resolution")) + S(": ") + num2 + S("x") + num3 + S("]"));
	}
	component23->workIfBusy = false;
	component23->onClick = [this]() { pickResolution(); };
#endif
	if (GameDataController::persistentData->chapter1_gas || GameDataController::persistentData->chapter1_locust || GameDataController::persistentData->chapter1_spiders)
	{
		P<Button> component24 = GameObject::Find(S("ResetBtn"))->GetComponent<Button>();
		component24->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("clear_data")) + S("]"));
		component24->workIfBusy = false;
		component24->onClick = [this]() { clearData(); };
		component24->buttonText->OPTIONAL_MARGIN = 6;
	}
	else
	{
		P<Button> component25 = GameObject::Find(S("ResetBtn"))->GetComponent<Button>();
		component25->initButton(S(" "));
		component25->workIfBusy = false;
		component25->buttonEnabled = false;
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->escButton = component;
}

void OptionsMenuStart::clearData()
{
	String text = GameStrings::getString(GameStrings::warnings, S("clear_data1"));
	if (GameDataController::persistentData->disc_barry || GameDataController::persistentData->disc_cody)
	{
		text += GameStrings::getString(GameStrings::warnings, S("clear_data2"));
	}
	QuestionController::qc->showQuestion(text, QuestionController::PopupType::QUESTION, [this]() { yesClearData(); }, 0, 0, nullptr, GameStrings::getString(GameStrings::gui, S("clear_data_yes")), GameStrings::getString(GameStrings::gui, S("clear_data_no")));
}

void OptionsMenuStart::yesClearData()
{
	GameDataController::persistentData = New<PersistentData>();
	GameDataController::gd->initPersistantAchieves();
	GameDataController::gd->PersistentSave();
	P<Button> component = GameObject::Find(S("ResetBtn"))->GetComponent<Button>();
	component->initButton(S(" "));
	component->workIfBusy = false;
	component->buttonEnabled = false;
}

void OptionsMenuStart::changeResolution(String res)
{
	if (res == S("fullscreen"))
	{
		ScreenControler::setFullScreenResolution();
	}
	else
	{
		int windowedResolution = int_Parse(res);
		ScreenControler::setWindowedResolution(windowedResolution);
	}
	PlayerPrefs::Save();
	endTalk(String::Empty);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, nullptr, nullptr, false, nullptr, 1.0f);
	Start();
}

void OptionsMenuStart::pickResolution()
{
	DialogueController::dc->callback = nullptr;
	takeDoc(0);
	MonoBehaviour::print(S("PICKING RESOLUTION"));
	DialogueController::dc->reset();
	int num = 0;
	int num2 = PlayerPrefs::GetInt(S("resolution_max"));
	if (num2 == -1)
	{
		num2 = (int)ScreenControler::getHighestWindowResolution().x;
	}
	num2 = (int)ScreenControler::getHighestWindowResolution().x;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("fullscreen"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/resolutions/full")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String s) { changeResolution(s); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("fullscreen");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	for (int i = 0; i < ScreenControler::allowedResolutions.Length(); i++)
	{
		bool flag = true;
		if (ScreenControler::allowedResolutions[i].x != (float)PlayerPrefs::GetInt(S("resolution_max")) && ScreenControler::allowedResolutions[i].x <= (float)num2)
		{
			takeDoc(num);
			doc->caption = ScreenControler::allowedResolutions[i].x + S("x") + ScreenControler::allowedResolutions[i].y;
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/resolutions/") + ScreenControler::allowedResolutions[i].x));
			doc->lines = List<P<DialogueLine>>::New();
			DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
			doc->setObjective(String::Empty);
			doc->lines[doc->lines.Count() - 1]->action = [this](String s) { changeResolution(s); };
			doc->lines[doc->lines.Count() - 1]->actionParam = ScreenControler::allowedResolutions[i].x + String::Empty;
			doc->lines[doc->lines.Count() - 1]->actionWithText = true;
			num++;
		}
	}
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("cancel"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String s) { endTalk(s); };
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void OptionsMenuStart::quit()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("quit_game")), QuestionController::PopupType::QUESTION, [this]() { quit2(); });
}

void OptionsMenuStart::quit2()
{
	Application::Quit();
}

void OptionsMenuStart::takeDoc(int i)
{
	doc = DialogueController::dc->dialogueOptions[i]->GetComponent<DialogueOptionController>();
}

void OptionsMenuStart::changeLanguage(String lang)
{
	PlayerPrefs::SetString(S("lang"), lang);
	PlayerPrefs::Save();
	GameStrings::readStrings(lang);
	ItemsManager::im->reloadAfterLanguageChange();
	endTalk(String::Empty);
	Start();
}

void OptionsMenuStart::pickFont()
{
	if (PlayerPrefs::GetString(S("font")) == S("pixel"))
	{
		PlayerPrefs::SetString(S("font"), S("smooth"));
	}
	else
	{
		PlayerPrefs::SetString(S("font"), S("pixel"));
	}
	PlayerPrefs::Save();
	Array<P<TextFieldController>> array = Resources::FindObjectsOfTypeAll<TextFieldController>();
	for (int i = 0; i < array.Length(); i++)
	{
		array[i].cast<TextFieldController>()->updateFont();
	}
	Start();
}

void OptionsMenuStart::pickLanguage()
{
	DialogueController::dc->callback = nullptr;
	takeDoc(0);
	MonoBehaviour::print(S("PICKING LANGUAGE"));
	DialogueController::dc->reset();
	int num = 0;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::languages, str(GameStrings::Language::EN));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/l_eng")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String s) { changeLanguage(s); };
	doc->lines[doc->lines.Count() - 1]->actionParam = str(GameStrings::Language::EN);
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::languages, str(GameStrings::Language::PL));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/l_pl")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String s) { changeLanguage(s); };
	doc->lines[doc->lines.Count() - 1]->actionParam = str(GameStrings::Language::PL);
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::languages, str(GameStrings::Language::DE));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/l_de")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String s) { changeLanguage(s); };
	doc->lines[doc->lines.Count() - 1]->actionParam = str(GameStrings::Language::DE);
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("cancel"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String s) { endTalk(s); };
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void OptionsMenuStart::endTalk(String val)
{
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
}

void OptionsMenuStart::resetGame2()
{
	GameDataController::gd->newGame();
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationDreamBugs"), WalkController::Direction::N);
}

void OptionsMenuStart::resetGame()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("reset_game")), QuestionController::PopupType::QUESTION, [this]() { resetGame2(); });
}

void OptionsMenuStart::continueGame()
{
	PlayerController::pc->spawnName = S("previous");
	PlayerController::wc->fullStop();
	CurtainController::cc->fadeOut(GameDataController::gd->previousLocation, WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
}

void OptionsMenuStart::saveGame()
{
	GameDataController::wantSave = true;
	PlayerController::wc->fullStop();
	CurtainController::cc->fadeOut(S("SaveMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
}

void OptionsMenuStart::loadGame()
{
	GameDataController::wantSave = false;
	PlayerController::wc->fullStop();
	CurtainController::cc->fadeOut(S("SaveMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
}

void OptionsMenuStart::mainMenu()
{
	PlayerController::wc->fullStop();
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("MainMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
}

void OptionsMenuStart::staticUp()
{
	PlayerPrefs::SetInt(S("stati"), PlayerPrefs::GetInt(S("stati")) + 10);
	if (PlayerPrefs::GetInt(S("stati")) > 100)
	{
		PlayerPrefs::SetInt(S("stati"), 100);
	}
	PlayerPrefs::Save();
	counter3->viewText(meter(PlayerPrefs::GetInt(S("stati"))), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter3->keepAlive = true;
	StaticControler::static_power = PlayerPrefs::GetInt(S("stati"));
}

void OptionsMenuStart::staticDown()
{
	PlayerPrefs::SetInt(S("stati"), PlayerPrefs::GetInt(S("stati")) - 10);
	if (PlayerPrefs::GetInt(S("stati")) < 0)
	{
		PlayerPrefs::SetInt(S("stati"), 0);
	}
	PlayerPrefs::Save();
	counter3->viewText(meter(PlayerPrefs::GetInt(S("stati"))), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter3->keepAlive = true;
	StaticControler::static_power = PlayerPrefs::GetInt(S("stati"));
}

void OptionsMenuStart::speedUp()
{
	PlayerPrefs::SetFloat(S("textSpeed"), PlayerPrefs::GetFloat(S("textSpeed")) - 0.0075f);
	if (PlayerPrefs::GetFloat(S("textSpeed")) < 0.0125f)
	{
		PlayerPrefs::SetFloat(S("textSpeed"), 0.0125f);
	}
	PlayerPrefs::Save();
	float num = PlayerPrefs::GetFloat(S("textSpeed")) - 0.0125f;
	num /= 0.074999996f;
	int num2 = 100 - (int)(num * 100.0f);
	MonoBehaviour::print(num2 + S(" ") + PlayerPrefs::GetFloat(S("textSpeed")));
	counter4->viewText(meter(num2), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter4->keepAlive = true;
}

void OptionsMenuStart::speedDown()
{
	PlayerPrefs::SetFloat(S("textSpeed"), PlayerPrefs::GetFloat(S("textSpeed")) + 0.0075f);
	if (PlayerPrefs::GetFloat(S("textSpeed")) > 0.0875f)
	{
		PlayerPrefs::SetFloat(S("textSpeed"), 0.0875f);
	}
	PlayerPrefs::Save();
	float num = PlayerPrefs::GetFloat(S("textSpeed")) - 0.0125f;
	num /= 0.074999996f;
	int num2 = 100 - (int)(num * 100.0f);
	MonoBehaviour::print(num2 + S(" ") + PlayerPrefs::GetFloat(S("textSpeed")));
	counter4->viewText(meter(num2), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter4->keepAlive = true;
}

void OptionsMenuStart::musicUp()
{
	PlayerPrefs::SetInt(S("music"), PlayerPrefs::GetInt(S("music")) + 10);
	if (PlayerPrefs::GetInt(S("music")) > 100)
	{
		PlayerPrefs::SetInt(S("music"), 100);
	}
	PlayerPrefs::Save();
	counter2->viewText(meter(PlayerPrefs::GetInt(S("music"))), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter2->keepAlive = true;
}

void OptionsMenuStart::musicDown()
{
	PlayerPrefs::SetInt(S("music"), PlayerPrefs::GetInt(S("music")) - 10);
	if (PlayerPrefs::GetInt(S("music")) < 0)
	{
		PlayerPrefs::SetInt(S("music"), 0);
	}
	PlayerPrefs::Save();
	counter2->viewText(meter(PlayerPrefs::GetInt(S("music"))), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter2->keepAlive = true;
}

void OptionsMenuStart::soundsUp()
{
	PlayerPrefs::SetInt(S("sound"), PlayerPrefs::GetInt(S("sound")) + 10);
	if (PlayerPrefs::GetInt(S("sound")) > 100)
	{
		PlayerPrefs::SetInt(S("sound"), 100);
	}
	PlayerPrefs::Save();
	counter1->viewText(meter(PlayerPrefs::GetInt(S("sound"))), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter1->keepAlive = true;
}

void OptionsMenuStart::soundsDown()
{
	PlayerPrefs::SetInt(S("sound"), PlayerPrefs::GetInt(S("sound")) - 10);
	if (PlayerPrefs::GetInt(S("sound")) < 0)
	{
		PlayerPrefs::SetInt(S("sound"), 0);
	}
	PlayerPrefs::Save();
	AudioListener::set_volume((float)PlayerPrefs::GetInt(S("sound")) / 100.0f);
	counter1->viewText(meter(PlayerPrefs::GetInt(S("sound"))), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	counter1->keepAlive = true;
}

void OptionsMenuStart::Update()
{
}

String OptionsMenuStart::meter(int stat)
{
	String result = S("··········");
	if (stat >= 100)
	{
		result = S("||||||||||");
	}
	else if (stat >= 90)
	{
		result = S("|||||||||·");
	}
	else if (stat >= 80)
	{
		result = S("||||||||··");
	}
	else if (stat >= 70)
	{
		result = S("|||||||···");
	}
	else if (stat >= 60)
	{
		result = S("||||||····");
	}
	else if (stat >= 50)
	{
		result = S("|||||·····");
	}
	else if (stat >= 40)
	{
		result = S("||||······");
	}
	else if (stat >= 30)
	{
		result = S("|||·······");
	}
	else if (stat >= 20)
	{
		result = S("||········");
	}
	else if (stat >= 10)
	{
		result = S("|·········");
	}
	else if (stat >= 0)
	{
		result = S("··········");
	}
	return result;
}
