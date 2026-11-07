#include "../game_all.h"

void LocationTentStart::Start()
{
	if (!GameDataController::gd->getObjective(S("tent_distance_checked")))
	{
		GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->hide();
	}
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
	if (!GameDataController::gd->getObjective(S("tent_awake")))
	{
		PlayerController::wc->speed = 0.0f;
		PlayerController::wc->dir = WalkController::Direction::SE;
		PlayerController::wc->currentXY = Vector2(-51.0f, -28.0f);
		Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
		Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
		position.z = -3.0f;
		InventoryButtonController::ibc->gameObject->transform->set_position(position);
		PlayerController::wc->busy = true;
		Invoke(S("exitTent"), 2.0f);
		Invoke(S("exitTent2"), 4.0f);
	}
	else if (!GameDataController::gd->getObjective(S("tent_backpack_taken")))
	{
		PlayerController::wc->speed = 0.0f;
		PlayerController::wc->dir = WalkController::Direction::S_;
		PlayerController::wc->forceAnimation(S("stand_s"), false, false, false);
		PlayerController::wc->busy = false;
		GameObject::Find(S("Bagpack"))->GetComponent<TentBagpack>()->updateAll();
	}
}

void LocationTentStart::exitTent()
{
	PlayerController::wc->currentXY = Vector2(51.0f, 28.0f);
	PlayerController::wc->forceAnimation(S("exit_tent"));
}

void LocationTentStart::exitTent3(String v)
{
	PlayerController::pc->setBusy(true);
	Timeline::t->doNotUnlock = true;
	Invoke(S("exitTent4"), 1.0f);
}

void LocationTentStart::exitTent4()
{
	String text = S("david_ending_med");
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
	timelineAction->function = [this](String val) { keepStraight(val); };
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void LocationTentStart::exitTent2()
{
	PlayerController::wc->dir = WalkController::Direction::S_;
	PlayerController::wc->forceAnimation(S("stand_s"), false, false, false);
	P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("story_intro_day_1_1"));
	timelineAction->blockG = true;
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("story_intro_day_1_2"));
	timelineAction->blockG = true;
	if (GameDataController::gd->getObjective(S("previous_disc_barry")) || GameDataController::gd->getObjective(S("previous_disc_cody")))
	{
		timelineAction->function = [this](String v) { exitTent3(v); };
		timelineAction->actionWithText = false;
		Timeline::t->doNotUnlock = true;
	}
	else
	{
		timelineAction->function = [this](String val) { keepStraight(val); };
	}
	Timeline::t->addAction(timelineAction);
	PlayerController::wc->forceDirection(WalkController::Direction::S_);
}

void LocationTentStart::keepStraight(String val)
{
	GameDataController::gd->setObjective(S("tent_awake"), true);
	GameObject::Find(S("Bagpack"))->GetComponent<TentBagpack>()->updateAll();
	PlayerController::wc->fullStop(true, true, true);
	PlayerController::wc->dir = WalkController::Direction::S_;
	PlayerController::wc->forceAnimation(S("stand_s"), false, false, false);
	PlayerController::wc->forceDirection(WalkController::Direction::S_);
}

void LocationTentStart::Update()
{
}
