#include "../game_all.h"

void LocationDreamBugsStart::Start()
{
	plane0bla = GameObject::Find(S("plane0bla"))->GetComponent<SpriteRenderer>();
	window = GameObject::Find(S("Window"))->GetComponent<SpriteRenderer>();
	plane01 = GameObject::Find(S("plane01"))->GetComponent<SpriteRenderer>();
	plane01->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	alpha = 0.0f;
	alpha1 = 2.0f;
	GameDataController::gd->autoSave();
	PlayerController::wc->shadow->fadeRateV = 0.002f;
	PlayerController::wc->shadow->fadeRateH = 0.002f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 30.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 60.0f;
	PlayerController::ssg->setStepType2(S("wood"), AudioReverbPreset::Psychotic);
	PlayerController::pc->copySettingsToNPCs();
	MonoBehaviour::print(S("............................. LOCATION INFO  .................................."));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED / 2.0f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.75f);
	GameObject::Find(S("bugs_feast_1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	if (!GameDataController::gd->getObjective(S("dream_day_1_started")))
	{
		PlayerController::wc->currentXY.x = 280.0f;
		PlayerController::wc->currentXY.y = 20.0f;
		walkThere1();
	}
	else
	{
		alpha = 1.0f;
		alpha1 = 0.0f;
	}
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.5f);
}

void LocationDreamBugsStart::walkThere1()
{
	Invoke(S("walkThere"), 0.25f);
}

void LocationDreamBugsStart::walkThere()
{
	PlayerController::wc->currentXY.x = 290.0f;
	PlayerController::wc->currentXY.y = 25.0f;
	Vector2 simpleTarget = Vector2(120.0f, 25.0f);
	PlayerController::wc->setSimpleTarget(simpleTarget);
	PlayerController::wc->forceAnimation(S("walk_e"), true);
}

void LocationDreamBugsStart::unlock()
{
	MonoBehaviour::print(S("UNLOCK"));
	GameObject::Find(S("Window"))->GetComponent<DreamWindow>()->updateAll();
	PlayerController::wc->fullStop();
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.75f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(0.75f);
	PlayerController::pc->setBusy(false);
	PlayerController::wc->forceAnimation(S("action_stnd_e"), true);
	PlayerController::wc->forceDirection(WalkController::Direction::W);
	P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = String::Empty;
	timelineAction->blockG = false;
	timelineAction->function = [this](String p) { sayDots(p); };
	timelineAction->actionWithText = true;
	timelineAction->textWidth = 170;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>());
	timelineAction->text = S("[") + GameStrings::getString(GameStrings::gui, S("controls_hint")) + S("]");
	timelineAction->blockG = true;
	timelineAction->function = [this](String param) { unlockThings(param); };
	timelineAction->textWidth = 220;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(GameObject::Find(S("UpperText"))->GetComponent<TextFieldController>());
	timelineAction->text = S("[") + GameStrings::getString(GameStrings::gui, S("tutorial_gears")) + S("]");
	GameObject::Find(S("UpperText"))->GetComponent<TextFieldController>()->OPTIONAL_MARGIN = 20;
	timelineAction->textWidth = 100;
	timelineAction->blockG = false;
	Timeline::t->addAction(timelineAction);
}

void LocationDreamBugsStart::sayDots(String p)
{
	PlayerController::pc->textField->viewText(S("..."));
	PlayerController::pc->textField->setTime(3.0f);
}

void LocationDreamBugsStart::unlockThings(String param)
{
	GameObject::Find(S("gears"))->GetComponent<GearsController>()->showGears(false);
	PlayerController::wc->forceAnimation(S("stand_se"), true);
	PlayerController::wc->forceDirection(WalkController::Direction::SW);
	Invoke(S("unlockThings2"), 0.25f);
}

void LocationDreamBugsStart::unlockThings2()
{
	GameDataController::gd->setObjective(S("dream_day_1_started"), true);
	GameObject::Find(S("FirstEncounter"))->GetComponent<FirstEncounterHouse>()->updateAll();
}

void LocationDreamBugsStart::Update()
{
	if (PlayerController::wc->currentXY.x <= 120.0f && !GameDataController::gd->getObjective(S("dream_day_1_started")))
	{
		GameDataController::gd->setObjective(S("dream_day_1_started"), true);
		unlock();
	}
	window->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	plane01->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	float num = alpha1;
	if (num > 1.0f)
	{
		num = 1.0f;
	}
	plane0bla->set_color(Color(0.0f, 0.0f, 0.0f, num));
	if (alpha1 <= 0.0f && alpha < 1.0f)
	{
		alpha += 0.07f * Time::get_deltaTime();
	}
	if (alpha1 > 0.0f)
	{
		alpha1 -= 0.4f * Time::get_deltaTime();
	}
}
