#include "../game_all.h"

void LocationEndGoodStart::Start()
{
	adoptionX = -0.156f;
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
	JukeboxAmbient::jb->changeAmbient(nullptr, 1.0f);
	PlayerController::wc->speed = 0.0f;
	PlayerController::wc->dir = WalkController::Direction::SE;
	PlayerController::wc->currentXY = Vector2(-51.0f, -28.0f);
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	PlayerController::wc->busy = true;
	GameDataController::Achievement(S("ENDING_1"));
	if (GameDataController::KART)
	{
		GameDataController::persistentData->kong_game = true;
		GameDataController::gd->PersistentSave();
	}
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
	GameDataController::Achievement(S("ENDING_3"));
	cumulInvoke(S("music"), 1.0f);
	cumulInvoke(S("slice_david00"), 2.0f);
	if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		cumulInvoke(S("slice_cate00"), 8.0f);
	}
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		cumulInvoke(S("slice_barry00"), 7.0f);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		cumulInvoke(S("slice_cody00"), 9.0f);
	}
	if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		cumulInvoke(S("slice_cate01"), 4.0f);
	}
	if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		cumulInvoke(S("slice_cate03"), 5.0f);
	}
	cumulInvoke(S("slice_david01"), 3.0f);
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		cumulInvoke(S("slice_barry01"), 2.0f);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		cumulInvoke(S("slice_cody01"), 4.0f);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		cumulInvoke(S("slice_cody02"), 0.5f);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		cumulInvoke(S("slice_cody03"), 0.5f);
	}
	if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		cumulInvoke(S("slice_cate02"), 3.0f);
	}
	cumulInvoke(S("slice_david02"), 3.0f);
	cumulInvoke(S("slice_david03"), 0.5f);
	cumulInvoke(S("slice_david04"), 0.5f);
	if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		cumulInvoke(S("slice_cate04"), 0.5f);
	}
	if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		cumulInvoke(S("slice_cate05"), 0.5f);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		cumulInvoke(S("slice_cody04"), 0.5f);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		cumulInvoke(S("slice_cody05"), 0.5f);
	}
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		cumulInvoke(S("slice_barry02"), 0.5f);
	}
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		cumulInvoke(S("slice_barry03"), 0.5f);
	}
	cumulInvoke(S("slice_end"), 3.0f);
	cumulInvoke(S("napisy"), 4.0f);
	Invoke(S("music2"), 93.0f);
	napis1->viewText(GameStrings::getString(GameStrings::world_labels, S("ending_1")), false, true, true, 100, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, true);
	napis1->setTime(100.0f);
	napis1->gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(napis1->gameObject->transform->get_position()));
	napis1->setAlpha(0.6f);
	napis2->viewText(GameStrings::getString(GameStrings::world_labels, S("ending_2")), false, true, true, 100, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, true);
	napis2->setTime(100.0f);
	napis2->gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(napis1->gameObject->transform->get_position()));
	napis2->setAlpha(0.6f);
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->buttonEnabled = false;
	if (GameDataController::persistentData == nullptr)
	{
		GameDataController::persistentData = New<PersistentData>();
		GameDataController::gd->initPersistantAchieves();
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		GameDataController::persistentData->chapter1_locust = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		GameDataController::persistentData->chapter1_gas = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		GameDataController::persistentData->chapter1_spiders = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		GameDataController::persistentData->chapter2_hot = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
	{
		GameDataController::persistentData->chapter2_cold = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		GameDataController::persistentData->chapter3_bandits = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		GameDataController::persistentData->chapter3_thunderstorm = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
	{
		GameDataController::persistentData->chapter4_air = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1)
	{
		GameDataController::persistentData->chapter4_fuel = true;
	}
	if (GameDataController::gd->getObjective(S("moon_disc1_used")))
	{
		GameDataController::persistentData->disc_barry = true;
	}
	else
	{
		GameDataController::persistentData->disc_barry = false;
	}
	if (GameDataController::gd->getObjective(S("moon_disc2_used")))
	{
		GameDataController::persistentData->disc_cody = true;
	}
	else
	{
		GameDataController::persistentData->disc_cody = false;
	}
	GameDataController::gd->PersistentSave();
}

void LocationEndGoodStart::mainMenu()
{
	PlayerController::wc->fullStop();
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("MainMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
}

void LocationEndGoodStart::napisy()
{
	gameObject->GetComponent<Napisy>()->showNapisyS(String::Empty);
}

void LocationEndGoodStart::cumulInvoke(String methodName, float time)
{
	totalTime += time;
	Invoke(methodName, totalTime);
}

void LocationEndGoodStart::fader(P<SpriteRenderer> sr)
{
	fadeOut2 = fadeOut;
	fadeIn2 = fadeIn;
	sr->set_enabled(true);
	sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	fadeIn = sr;
	fadeOut = sr;
	waiting = 8.0f;
}

void LocationEndGoodStart::music()
{
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_2a);
}

void LocationEndGoodStart::music2()
{
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_main);
}

void LocationEndGoodStart::slice_david00()
{
	fader(david00);
	if (skipit == 0)
	{
		skipit = 1;
	}
	PlayerController::wc->busy = false;
}

void LocationEndGoodStart::slice_david01()
{
	fader(david01);
}

void LocationEndGoodStart::slice_david02()
{
	fader(david02);
}

void LocationEndGoodStart::slice_david03()
{
	fader(david03);
}

void LocationEndGoodStart::slice_david04()
{
	fader(david04);
}

void LocationEndGoodStart::slice_cate00()
{
	fader(cate00);
}

void LocationEndGoodStart::slice_cate01()
{
	fader(cate01);
}

void LocationEndGoodStart::slice_cate02()
{
	fader(cate02);
}

void LocationEndGoodStart::slice_cate03()
{
	fader(cate03);
}

void LocationEndGoodStart::slice_cate04()
{
	fader(cate04);
}

void LocationEndGoodStart::slice_cate05()
{
	fader(cate05);
}

void LocationEndGoodStart::slice_barry00()
{
	fader(barry00);
}

void LocationEndGoodStart::slice_barry01()
{
	fader(barry01);
}

void LocationEndGoodStart::slice_barry02()
{
	fader(barry02);
}

void LocationEndGoodStart::slice_barry03()
{
	fader(barry03);
}

void LocationEndGoodStart::slice_cody00()
{
	fader(cody00);
}

void LocationEndGoodStart::slice_cody01()
{
	fader(cody01);
}

void LocationEndGoodStart::slice_cody02()
{
	fader(cody02);
}

void LocationEndGoodStart::slice_cody03()
{
	fader(cody03);
}

void LocationEndGoodStart::slice_cody04()
{
	fader(cody04);
}

void LocationEndGoodStart::slice_cody05()
{
	fader(cody05);
}

void LocationEndGoodStart::slice_end()
{
	fader(end);
}

void LocationEndGoodStart::Update()
{
	if (barry00->get_enabled() && adoptionX < 0.0f)
	{
		adoptionX += 0.02f * Time::get_deltaTime();
		barry00->transform->set_position(Vector3(adoptionX, barry00->transform->get_position().y, barry00->transform->get_position().z));
		barry00->transform->set_position(ScreenControler::roundToNearestFullPixel2(barry00->transform->get_position()));
		napis2->gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(adoptionX, napis1->gameObject->transform->get_position().y, napis1->gameObject->transform->get_position().z)));
	}
	if (fadeIn != nullptr)
	{
		fadeIn->set_color(Color(1.0f, 1.0f, 1.0f, fadeIn->get_color().a + 2.0f * Time::get_deltaTime()));
		if (fadeIn->get_color().a >= 1.0f)
		{
			fadeIn = nullptr;
		}
	}
	if (fadeIn2 != nullptr)
	{
		fadeIn2->set_color(Color(1.0f, 1.0f, 1.0f, fadeIn2->get_color().a + 2.0f * Time::get_deltaTime()));
		if (fadeIn2->get_color().a >= 1.0f)
		{
			fadeIn2 = nullptr;
		}
	}
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
			component->set_enabled(false);
			component->buttonEnabled = false;
		}
	}
	if ((Input::GetMouseButtonDown(0) || Input::GetKeyDown(KeyCode::Escape)) && skipit == 1)
	{
		skipit = 2;
		showButton();
	}
}

void LocationEndGoodStart::showButton()
{
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("skip")) + S("]"));
	component->workIfBusy = true;
	component->onClick = [this]() { mainMenu(); };
	component->buttonText->OPTIONAL_MARGIN = 6;
	component->set_enabled(true);
	component->buttonEnabled = true;
}
