#include "../game_all.h"

void LocationTent2Start::music1()
{
	skipit = 1;
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_success, false, 0.0f, 0.0f);
}

void LocationTent2Start::music2()
{
	skipit = 1;
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_sorrow, false, 0.0f, 0.0f);
}

void LocationTent2Start::music3()
{
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_main, false, 0.0f, 0.0f);
}

void LocationTent2Start::Start()
{
	GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->hide();
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0015f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 8.0f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->source = 200.0f;
	PlayerController::ssg->setStepType(S("dirt"));
	PlayerController::wc->shadow->scaleFactor = 0.3f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	PlayerController::wc->speed = 0.0f;
	PlayerController::wc->dir = WalkController::Direction::SE;
	PlayerController::wc->currentXY = Vector2(-51.0f, -28.0f);
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	PlayerController::wc->busy = true;
	Invoke(S("exitTent"), 5.0f);
	Invoke(S("exitTent2"), 7.0f);
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->buttonEnabled = false;
}

void LocationTent2Start::mainMenu()
{
	PlayerController::wc->fullStop();
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("MainMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
}

void LocationTent2Start::showButton()
{
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("skip")) + S("]"));
	component->workIfBusy = true;
	component->buttonText->OPTIONAL_MARGIN = 6;
	component->onClick = [this]() { mainMenu(); };
	component->set_enabled(true);
	component->buttonEnabled = true;
}

void LocationTent2Start::exitTent()
{
	PlayerController::wc->currentXY = Vector2(51.0f, 28.0f);
	PlayerController::wc->forceAnimation(S("exit_tent"));
}

void LocationTent2Start::exitTent3(String v)
{
	Timeline::t->doNotUnlock = true;
	Invoke(S("exitTent4"), 1.0f);
}

void LocationTent2Start::exitTent4()
{
	String text = S("david_ending_bad");
	if (GameDataController::gd->getObjective(S("moon_disc1_used")) || GameDataController::gd->getObjective(S("moon_disc2_used")))
	{
		text = S("david_ending_med");
	}
	P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::dialogues, text + S("_1_a"));
	timelineAction->blockG = true;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::dialogues, text + S("_2_a"));
	timelineAction->blockG = true;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::dialogues, text + S("_3_a"));
	timelineAction->blockG = true;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::dialogues, text + S("_4_a"));
	timelineAction->blockG = true;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::dialogues, text + S("_5_a"));
	timelineAction->blockG = true;
	timelineAction->function = [this](String s) { showNapisy(s); };
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void LocationTent2Start::exitTent2()
{
	P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("story_intro_day_1_1"));
	timelineAction->blockG = true;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("story_intro_day_1_2"));
	timelineAction->blockG = true;
	timelineAction->blockG = true;
	timelineAction->function = [this](String v) { exitTent3(v); };
	timelineAction->actionWithText = false;
	Timeline::t->doNotUnlock = true;
	Timeline::t->addAction(timelineAction);
	PlayerController::wc->forceAnimation(S("stand_se"), false, false, false);
}

void LocationTent2Start::showNapisy(String s)
{
	if (GameDataController::KART)
	{
		GameDataController::persistentData->kong_game = true;
		GameDataController::gd->PersistentSave();
	}
	GameDataController::Achievement(S("ENDING_1"));
	if (!GameDataController::gd->getObjective(S("car_driven")))
	{
		GameDataController::Achievement(S("S_WALKING"));
	}
	if (!GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("npc3_alive")))
	{
		GameDataController::Achievement(S("S_WOLF"));
	}
	if (GameDataController::gd->getObjective(S("npc1_alive")) && GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjective(S("npc3_alive")))
	{
		GameDataController::Achievement(S("S_FAMILY"));
	}
	if (GameDataController::gd->getObjective(S("moon_disc1_used")) || GameDataController::gd->getObjective(S("moon_disc2_used")))
	{
		GameDataController::Achievement(S("ENDING_2"));
		Invoke(S("music1"), 3.0f);
		Invoke(S("music3"), 49.0f);
	}
	else
	{
		Invoke(S("music2"), 1.0f);
		Invoke(S("music3"), 46.0f);
	}
	gameObject->GetComponent<Napisy>()->showNapisyS(String::Empty);
}

void LocationTent2Start::Update()
{
	if (skipit == 2)
	{
		timer += Time::get_deltaTime();
		if (timer > 3.0f)
		{
			timer = 0.0f;
			skipit = 1;
			P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
			component->initButton(S(" "));
			component->workIfBusy = false;
			component->onClick = nullptr;
			component->buttonEnabled = false;
		}
	}
	if ((Input::GetMouseButtonDown(0) || Input::GetKeyDown(KeyCode::Escape)) && skipit == 1)
	{
		skipit = 2;
		showButton();
	}
}
