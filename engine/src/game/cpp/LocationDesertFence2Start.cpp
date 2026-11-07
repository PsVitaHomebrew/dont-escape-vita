#include "../game_all.h"

void LocationDesertFence2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.01f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 2.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 0.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Off);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_3, 1.0f);
	ItemsManager::im->getItem(S("sledgehammer"))->groundSprite = hammerDown;
	if (!GameDataController::gd->getObjective(S("wall_encountered")))
	{
		PlayerController::wc->forceAnimation(S("stand_n"));
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("tutorial_wall_encounter1"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("tutorial_wall_encounter2"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>());
		timelineAction->textWidth = BottomTextController::bottomTextWidth;
		timelineAction->actionWithText = true;
		timelineAction->function = [this](String a) { makeItLast(a); };
		timelineAction->text = S("[") + GameStrings::getString(GameStrings::gui, S("clock_hint1")) + S("]");
		timelineAction->actionWithText = true;
		timelineAction->function = [obj = GameObject::Find(S("clock"))->GetComponent<ClockController>()](String param) { obj->showClock(param); };
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>());
		timelineAction->textWidth = BottomTextController::bottomTextWidth;
		timelineAction->actionWithText = true;
		timelineAction->function = [this](String a) { makeItLast(a); };
		timelineAction->text = S("[") + GameStrings::getString(GameStrings::gui, S("clock_hint2")) + S("]");
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>());
		timelineAction->textWidth = BottomTextController::bottomTextWidth;
		timelineAction->actionWithText = true;
		timelineAction->function = [this](String a) { makeItLast(a); };
		timelineAction->text = S("[") + GameStrings::getString(GameStrings::gui, S("clock_hint3")) + S("]");
		Timeline::t->addAction(timelineAction);
		GameDataController::gd->setObjective(S("wall_encountered"), true);
	}
}

void LocationDesertFence2Start::makeItLast(String a)
{
}

void LocationDesertFence2Start::Update()
{
	if (GameDataController::gd->getItemData(S("sledgehammer"))->droppedLocation == S("LocationDesertFence2") && !GameDataController::gd->getObjective(S("tutorial_tab")))
	{
		GameDataController::gd->setObjective(S("tutorial_tab"), true);
		P<TimelineAction> timelineAction = New<TimelineAction>(GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>());
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("tutorial_tab"));
		timelineAction->textWidth = 200;
		Timeline::t->addAction(timelineAction);
	}
}
