#include "../game_all.h"

void MainMenuStart::makeCloudsNormal()
{
	clouds->xSpread = 75;
	clouds->maxDelayBetweeenParticles = 800;
	clouds->minDelayBetweeenParticles = 6;
}

void MainMenuStart::setupButton(P<Button> button, P<Button> fake1, P<Button> fake2, P<Button> fake3, String label, Button_Delegate action)
{
	button->initButton(String::Empty + GameStrings::getString(GameStrings::gui, label) + String::Empty);
	button->workIfBusy = false;
	button->onClick = action;
	fake1->initButton(String::Empty + GameStrings::getString(GameStrings::gui, label) + String::Empty);
	fake2->initButton(String::Empty + GameStrings::getString(GameStrings::gui, label) + String::Empty);
	fake1->buttonEnabled = false;
	fake2->buttonEnabled = false;
	fake3->initButton(String::Empty + GameStrings::getString(GameStrings::gui, label) + String::Empty);
	fake3->buttonEnabled = false;
}

void MainMenuStart::Start()
{
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
	clouds->xSpread = 750;
	clouds->maxDelayBetweeenParticles = 0;
	clouds->minDelayBetweeenParticles = 0;
	Invoke(S("makeCloudsNormal"), 0.5f);
	setupButton(continueBtn, fakeContinue1, fakeContinue2, fakeContinue3, S("continueGame"), [this]() { continueGame(); });
	if (!GameDataController::gd->checkSave(GameDataController::CONTINUE))
	{
		continueBtn->initButton(S(" "));
		continueBtn->onClick = nullptr;
		continueBtn->buttonEnabled = false;
		fakeContinue1->initButton(S(" "));
		fakeContinue2->initButton(S(" "));
		fakeContinue3->initButton(S(" "));
		fakeContinue1->set_enabled(false);
		fakeContinue2->set_enabled(false);
		fakeContinue3->set_enabled(false);
		fakeContinue1->gameObject->GetComponent<BoxCollider2D>()->set_enabled(false);
		fakeContinue2->gameObject->GetComponent<BoxCollider2D>()->set_enabled(false);
		fakeContinue3->gameObject->GetComponent<BoxCollider2D>()->set_enabled(false);
	}
	if (GameDataController::persistentData->disc_barry && GameDataController::persistentData->disc_cody)
	{
		GameDataController::persistentData->custom_unlocked = true;
		GameDataController::gd->PersistentSave();
	}
	if (GameDataController::persistentData->custom_unlocked)
	{
		setupButton(newGameBtn, fakeNewGame1, fakeNewGame2, fakeNewGame3, S("custom_game_label"), [this]() { newGameCustom(); });
	}
	else
	{
		setupButton(newGameBtn, fakeNewGame1, fakeNewGame2, fakeNewGame3, S("newGame"), [this]() { newGame(); });
	}
	setupButton(loadGameBtn, fakeLoadGame1, fakeLoadGame2, fakeLoadGame3, S("loadGame"), [this]() { loadGame(); });
	setupButton(OptionsBtn, fakeOptions1, fakeOptions2, fakeOptions3, S("options"), [this]() { optionsClick(); });
	setupButton(CreditsBtn, fakeCredits1, fakeCredits2, fakeCredits3, S("credits"), [this]() { creditsClick(); });
	setupButton(QuitBtn, fakeQuit1, fakeQuit2, fakeQuit3, S("quit"), [this]() { quit(); });
	if ((bool)PlayerController::wc)
	{
		PlayerController::wc->currentXY.x = 1000.0f;
		PlayerController::wc->currentXY.y = 1000.0f;
		PlayerController::wc->clearTarget();
	}
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_main, true, 0.0f, 1.0f);
	JukeboxAmbient::jb->changeAmbient(nullptr, 0.0f);
	Vector2 vector2 = ScreenControler::gameToScreen(Vector2(120.0f, 67.0f));
	Vector3 position2 = Camera::get_main()->ScreenToWorldPoint(Vector3(vector2.x, vector2.y, 0.0f));
	position.z = -3.0f;
	GameObject::Find(S("Caption_Version"))->GetComponent<TextFieldController>()->viewText(GameDataController::VERSION, false, true, true, 200, 155.0f / 255.0f, 155.0f / 255.0f, 155.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("Caption_Version"))->GetComponent<TextFieldController>()->keepAlive = true;
	GameObject::Find(S("Caption_Version"))->transform->set_position(position2);
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->escButton = QuitBtn;
	back1->set_enabled(true);
	back2->set_enabled(true);
	background_1_3->set_enabled(true);
	background_2_1->set_enabled(false);
	background_2_2->set_enabled(false);
	background_2_3->set_enabled(false);
	d_a_1->started = true;
	d_a_2->started = true;
	d_a_3->started = true;
	d_a_4->started = true;
	d_a_5->started = true;
	d_b_1->started = false;
	d_b_2->started = false;
	d_b_3->started = false;
	d_b_4->started = false;
	d_b_5->started = false;
	if (GameDataController::persistentData->disc_barry || GameDataController::persistentData->disc_cody)
	{
		back1->set_enabled(false);
		back2->set_enabled(false);
		background_1_3->set_enabled(false);
		background_2_1->set_enabled(true);
		background_2_2->set_enabled(true);
		background_2_3->set_enabled(true);
		d_a_1->started = false;
		d_a_2->started = false;
		d_a_3->started = false;
		d_a_4->started = false;
		d_a_5->started = false;
		d_b_1->started = true;
		d_b_2->started = true;
		d_b_3->started = true;
		d_b_4->started = true;
		d_b_5->started = true;
	}
	Timeline::t->doNotUnlock = false;
}

void MainMenuStart::creditsClick()
{
	PlayerController::wc->fullStop(true);
	CurtainController::cc->fadeOut(S("Credits"), WalkController::Direction::NULL_, nullptr, nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
	AudioListener::set_pause(true);
}

void MainMenuStart::optionsClick()
{
	PlayerController::wc->fullStop(true);
	if (PlayerController::wc->speed != 0.0f)
	{
		PlayerController::wc->forceAnimation(S("stand_"), false, true);
	}
	PlayerController::pc->spawnName = S("InfoExit");
	GameDataController::gd->previousLocation = SceneManager::GetActiveScene().get_name();
	GameDataController::gd->previousX = (int)PlayerController::wc->currentXY.x;
	GameDataController::gd->previousY = (int)PlayerController::wc->currentXY.y;
	CurtainController::cc->fadeOut(S("PauseMenu"), WalkController::Direction::NULL_, nullptr, nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
	AudioListener::set_pause(true);
}

void MainMenuStart::loadGame()
{
	GameDataController::wantSave = false;
	PlayerController::wc->fullStop();
	GameDataController::gd->previousLocation = SceneManager::GetActiveScene().get_name();
	CurtainController::cc->fadeOut(S("SaveMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
}

void MainMenuStart::continueGame()
{
	GameDataController::gd->politeLoad(GameDataController::CONTINUE);
}

void MainMenuStart::quit()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("quit_game")), QuestionController::PopupType::QUESTION, [this]() { quit2(); }, 0, 0, [this]() { noQuit(); });
}

void MainMenuStart::noQuit()
{
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->escButton = GameObject::Find(S("QuitBtn"))->GetComponent<Button>();
}

void MainMenuStart::quit2()
{
	Application::Quit();
}

void MainMenuStart::newGame()
{
	if (GameDataController::gd->checkSave(GameDataController::CONTINUE))
	{
		String key = S("new_game_warning");
		if (GameDataController::persistentData->disc_barry || GameDataController::persistentData->disc_cody)
		{
			key = S("new_game_warning2");
		}
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::gui, key), QuestionController::PopupType::QUESTION, [this]() { newGame2(); });
	}
	else
	{
		newGame2();
	}
}

void MainMenuStart::newGameCustom()
{
	newGameCustom1(String::Empty);
}

void MainMenuStart::newGameCustom1(String param)
{
	if (param != String::Empty)
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click1);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->comp_beeps2);
	}
	DialogueController::dc->hide();
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss();
	DialogueController::dc->callback = nullptr;
	takeDoc(0);
	DialogueController::dc->reset();
	int num = 0;
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("custom_game_params")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_desc")) + S(" < ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d1")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d2")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d3")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d4")), false, true, true, 230, 0.015f, 0.464f, 0.79f, 0.07f, 0.14f, 0.23f, 0.75f, true, true);
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->keepAlive = true;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_disc_barry"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/disc1")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom2(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("barry");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_disc_cody"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/disc2")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom2(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("cody");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_disc_both"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/both")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom2(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("both");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_disc_none"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/nodisc")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom2(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("none");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_back"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalk(val); };
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void MainMenuStart::newGameCustom2(String param)
{
	if (param != String::Empty)
	{
		custom_disc = param;
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click1);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->comp_beeps2);
	}
	DialogueController::dc->hide();
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss();
	DialogueController::dc->callback = nullptr;
	takeDoc(0);
	DialogueController::dc->reset();
	int num = 0;
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("custom_game_params")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_desc")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_") + custom_disc) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d1")) + S(" < ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d2")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d3")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d4")), false, true, true, 230, 0.015f, 0.464f, 0.79f, 0.07f, 0.14f, 0.23f, 0.75f, true, true);
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->keepAlive = true;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_d1")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_locust"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/locust")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom3(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("locust");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_d1")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_gas"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/gas")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom3(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("gas");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_d1")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_spiders"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/spiders")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom3(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("spiders");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_back"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom1(param); };
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void MainMenuStart::newGameCustom3(String param)
{
	if (param != String::Empty)
	{
		custom_d1 = param;
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click1);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->comp_beeps2);
	}
	DialogueController::dc->hide();
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss();
	DialogueController::dc->callback = nullptr;
	takeDoc(0);
	DialogueController::dc->reset();
	int num = 0;
	String text = S("1");
	if (param != S("none"))
	{
		text = S("2");
	}
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("custom_game_params")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_desc")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_") + custom_disc) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d1")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_") + custom_d1) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d2")) + S(" < ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d3")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d4")), false, true, true, 230, 0.015f, 0.464f, 0.79f, 0.07f, 0.14f, 0.23f, 0.75f, true, true);
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->keepAlive = true;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_d2")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_hot"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/heat")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom4(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("hot");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_d2")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_cold"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/cold")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom4(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("cold");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_back"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom2(param); };
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void MainMenuStart::newGameCustom4(String param)
{
	if (param != String::Empty)
	{
		custom_d2 = param;
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click1);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->comp_beeps2);
	}
	DialogueController::dc->hide();
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss();
	DialogueController::dc->callback = nullptr;
	takeDoc(0);
	DialogueController::dc->reset();
	int num = 0;
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("custom_game_params")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_desc")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_") + custom_disc) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d1")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_") + custom_d1) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d2")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_") + custom_d2) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d3")) + S(" < ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d4")), false, true, true, 230, 0.015f, 0.464f, 0.79f, 0.07f, 0.14f, 0.23f, 0.75f, true, true);
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->keepAlive = true;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_d3")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_bandits"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/razor")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom5(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("bandits");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_d3")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_storm"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/storm")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom5(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("storm");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_back"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom3(param); };
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void MainMenuStart::newGameCustom5(String param)
{
	if (param != String::Empty)
	{
		custom_d3 = param;
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click1);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->comp_beeps2);
	}
	DialogueController::dc->hide();
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss();
	DialogueController::dc->callback = nullptr;
	takeDoc(0);
	DialogueController::dc->reset();
	int num = 0;
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("custom_game_params")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_desc")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_") + custom_disc) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d1")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_") + custom_d1) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d2")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_") + custom_d2) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d3")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_") + custom_d3) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d4")) + S(" <"), false, true, true, 230, 0.015f, 0.464f, 0.79f, 0.07f, 0.14f, 0.23f, 0.75f, true, true);
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->keepAlive = true;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_d4")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_air"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/air")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom6(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("air");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_d4")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_fuel"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/custom/fuel")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom6(param); };
	doc->lines[doc->lines.Count() - 1]->actionParam = S("fuel");
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_back"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom4(param); };
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void MainMenuStart::newGameCustom6(String param)
{
	if (param != String::Empty)
	{
		custom_d4 = param;
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click1);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->comp_beeps2);
	}
	DialogueController::dc->hide();
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss();
	DialogueController::dc->callback = nullptr;
	takeDoc(0);
	DialogueController::dc->reset();
	int num = 0;
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("custom_game_params")) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_desc")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_disc_") + custom_disc) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d1")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_") + custom_d1) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d2")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_") + custom_d2) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d3")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_") + custom_d3) + S(" ^") + GameStrings::getString(GameStrings::gui, S("custom_game_d4")) + S(" ") + GameStrings::getString(GameStrings::gui, S("custom_game_") + custom_d4), false, true, true, 230, 0.015f, 0.464f, 0.79f, 0.07f, 0.14f, 0.23f, 0.75f, true, true);
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->keepAlive = true;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_start"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/yes")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String lang) { pickDays(lang); };
	doc->lines[doc->lines.Count() - 1]->actionParam = String::Empty;
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("custom_game_back"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String param) { newGameCustom5(param); };
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void MainMenuStart::takeDoc(int i)
{
	doc = DialogueController::dc->dialogueOptions[i]->GetComponent<DialogueOptionController>();
}

void MainMenuStart::pickDays(String lang)
{
	endTalk(String::Empty);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->power_up_big);
	GameDataController::gd->newGame();
	if (custom_d1 == S("locust"))
	{
		GameDataController::gd->setObjectiveDetail(S("day_1_threat"), 0);
	}
	if (custom_d1 == S("gas"))
	{
		GameDataController::gd->setObjectiveDetail(S("day_1_threat"), 1);
	}
	if (custom_d1 == S("spiders"))
	{
		GameDataController::gd->setObjectiveDetail(S("day_1_threat"), 2);
	}
	if (custom_d2 == S("hot"))
	{
		GameDataController::gd->setObjectiveDetail(S("day_2_threat"), 0);
	}
	if (custom_d2 == S("cold"))
	{
		GameDataController::gd->setObjectiveDetail(S("day_2_threat"), 1);
	}
	if (custom_d3 == S("bandits"))
	{
		GameDataController::gd->setObjectiveDetail(S("day_3_threat"), 0);
	}
	if (custom_d3 == S("storm"))
	{
		GameDataController::gd->setObjectiveDetail(S("day_3_threat"), 1);
	}
	if (custom_d4 == S("air"))
	{
		GameDataController::gd->setObjectiveDetail(S("day_4_threat"), 0);
	}
	if (custom_d4 == S("fuel"))
	{
		GameDataController::gd->setObjectiveDetail(S("day_4_threat"), 1);
	}
	GameDataController::gd->setObjective(S("previous_disc_barry"), false);
	GameDataController::gd->setObjective(S("previous_disc_cody"), false);
	if (custom_disc == S("both"))
	{
		GameDataController::gd->setObjective(S("previous_disc_barry"), true);
		GameDataController::gd->setObjective(S("previous_disc_cody"), true);
	}
	if (custom_disc == S("cody"))
	{
		GameDataController::gd->setObjective(S("previous_disc_cody"), true);
	}
	if (custom_disc == S("barry"))
	{
		GameDataController::gd->setObjective(S("previous_disc_barry"), true);
	}
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationDreamBugs"), WalkController::Direction::N);
}

void MainMenuStart::endTalk(String val)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->viewText(S(" "), false, true, true, 230, 0.015f, 0.464f, 0.79f, 0.07f, 0.14f, 0.23f, 0.75f, true, true);
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->keepAlive = false;
	GameObject::Find(S("Caption_Static"))->GetComponent<TextFieldController>()->dissmiss(true);
}

void MainMenuStart::newGame2()
{
	GameDataController::gd->newGame();
	List<int> list = List<int>::New();
	List<int> list2 = List<int>::New();
	List<int> list3 = List<int>::New();
	List<int> list4 = List<int>::New();
	List<int> list5 = List<int>::New();
	List<int> list6 = List<int>::New();
	List<int> list7 = List<int>::New();
	List<int> list8 = List<int>::New();
	if (GameDataController::persistentData->chapter1_locust)
	{
		list2.Add(0);
	}
	else
	{
		list.Add(0);
	}
	if (GameDataController::persistentData->chapter1_gas)
	{
		list2.Add(1);
	}
	else
	{
		list.Add(1);
	}
	if (GameDataController::persistentData->chapter1_spiders)
	{
		list2.Add(2);
	}
	else
	{
		list.Add(2);
	}
	if (GameDataController::persistentData->chapter2_hot)
	{
		list4.Add(0);
	}
	else
	{
		list3.Add(0);
	}
	if (GameDataController::persistentData->chapter2_cold)
	{
		list4.Add(1);
	}
	else
	{
		list3.Add(1);
	}
	if (GameDataController::persistentData->chapter3_bandits)
	{
		list6.Add(0);
	}
	else
	{
		list5.Add(0);
	}
	if (GameDataController::persistentData->chapter3_thunderstorm)
	{
		list6.Add(1);
	}
	else
	{
		list5.Add(1);
	}
	if (GameDataController::persistentData->chapter4_air)
	{
		list8.Add(0);
	}
	else
	{
		list7.Add(0);
	}
	if (GameDataController::persistentData->chapter4_fuel)
	{
		list8.Add(1);
	}
	else
	{
		list7.Add(1);
	}
	int detail = ((list.Count() <= 0) ? list2[Random::Range(0, list2.Count())] : list[Random::Range(0, list.Count())]);
	int detail2 = ((list3.Count() <= 0) ? list4[Random::Range(0, list4.Count())] : list3[Random::Range(0, list3.Count())]);
	int detail3 = ((list5.Count() <= 0) ? list6[Random::Range(0, list6.Count())] : list5[Random::Range(0, list5.Count())]);
	int detail4 = ((list7.Count() <= 0) ? list8[Random::Range(0, list8.Count())] : list7[Random::Range(0, list7.Count())]);
	Debug::LogWarning(S("===== PERSISTENT ==================="));
	Debug::LogWarning(S("CH1_0: ") + GameDataController::persistentData->chapter1_locust);
	Debug::LogWarning(S("CH1_1: ") + GameDataController::persistentData->chapter1_gas);
	Debug::LogWarning(S("CH1_2: ") + GameDataController::persistentData->chapter1_spiders);
	Debug::LogWarning(S("CH2_0: ") + GameDataController::persistentData->chapter2_hot);
	Debug::LogWarning(S("CH2_1: ") + GameDataController::persistentData->chapter2_cold);
	Debug::LogWarning(S("CH3_0: ") + GameDataController::persistentData->chapter3_bandits);
	Debug::LogWarning(S("CH3_1: ") + GameDataController::persistentData->chapter3_thunderstorm);
	Debug::LogWarning(S("CH4_0: ") + GameDataController::persistentData->chapter4_air);
	Debug::LogWarning(S("CH4_1: ") + GameDataController::persistentData->chapter4_fuel);
	GameDataController::gd->setObjectiveDetail(S("day_1_threat"), detail);
	GameDataController::gd->setObjectiveDetail(S("day_2_threat"), detail2);
	GameDataController::gd->setObjectiveDetail(S("day_3_threat"), detail3);
	GameDataController::gd->setObjectiveDetail(S("day_4_threat"), detail4);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationDreamBugs"), WalkController::Direction::N);
}

void MainMenuStart::Update()
{
	if (!GameDataController::persistentData->custom_unlocked && (GameDataController::persistentData->disc_barry || GameDataController::persistentData->disc_cody))
	{
		blinkDelay += Time::get_deltaTime();
		if (blinkDelay > 0.1f)
		{
			blinkDelay = 0.0f;
			if (Random::Range(0.0f, 1.0f) < blinkChance && blinkChance < 0.6f)
			{
				blinkChance -= 0.01f;
				if (blinkChance < 0.3f)
				{
					blinkChance = 0.3f;
				}
				if (!old)
				{
					old = true;
					setupButton(newGameBtn, fakeNewGame1, fakeNewGame2, fakeNewGame3, S("newGamePlus"), [this]() { newGame(); });
					if (blinkChance == 0.3f)
					{
						blinkChance = -100.0f;
					}
				}
				else if (old)
				{
					old = false;
					setupButton(newGameBtn, fakeNewGame1, fakeNewGame2, fakeNewGame3, S("newGame"), [this]() { newGame(); });
				}
			}
			else if (blinkChance >= 0.6f)
			{
				blinkChance -= 0.03f;
			}
		}
	}
	if ((bool)PlayerController::wc)
	{
		PlayerController::wc->currentXY.x = 1000.0f;
		PlayerController::wc->currentXY.y = 1000.0f;
		PlayerController::wc->clearTarget();
	}
	xpos = Input::get_mousePosition().x / (float)Screen::get_width();
	xpos *= 5.0f;
	xpos -= 2.0f;
	if (xpos > 1.0f)
	{
		xpos = 1.0f;
	}
	if (xpos < 0.0f)
	{
		xpos = 0.0f;
	}
	alpha -= (alpha - xpos) / 1.0f * Time::get_deltaTime() * 3.0f;
	if (Mathf::Abs(alpha - xpos) < 0.001f)
	{
		alpha = xpos;
	}
	background_2_2->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	back2->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	fore1->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	fore2->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f - alpha));
	if ((bool)newGameBtn)
	{
		previousAlpha = alpha;
		continueBtn->buttonText->setAlpha(alpha);
		newGameBtn->buttonText->setAlpha(alpha);
		loadGameBtn->buttonText->setAlpha(alpha);
		OptionsBtn->buttonText->setAlpha(alpha);
		CreditsBtn->buttonText->setAlpha(alpha);
		QuitBtn->buttonText->setAlpha(alpha);
		float num = 0.2f - alpha / 4.0f;
		if (num < 0.0f)
		{
			num = 0.0f;
		}
		if (num > 1.0f)
		{
			num = 1.0f;
		}
		fakeContinue1->buttonText->setAlpha(num);
		fakeContinue2->buttonText->setAlpha(num);
		fakeContinue3->buttonText->setAlpha(num);
		fakeCredits1->buttonText->setAlpha(num);
		fakeCredits2->buttonText->setAlpha(num);
		fakeCredits3->buttonText->setAlpha(num);
		fakeLoadGame1->buttonText->setAlpha(num);
		fakeLoadGame2->buttonText->setAlpha(num);
		fakeLoadGame3->buttonText->setAlpha(num);
		fakeNewGame1->buttonText->setAlpha(num);
		fakeNewGame2->buttonText->setAlpha(num);
		fakeNewGame3->buttonText->setAlpha(num);
		fakeOptions1->buttonText->setAlpha(num);
		fakeOptions2->buttonText->setAlpha(num);
		fakeOptions3->buttonText->setAlpha(num);
		fakeQuit1->buttonText->setAlpha(num);
		fakeQuit2->buttonText->setAlpha(num);
		fakeQuit3->buttonText->setAlpha(num);
	}
}
