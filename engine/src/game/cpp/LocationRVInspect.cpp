#include "../game_all.h"

void LocationRVInspect::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_stnd_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_car");
	aS = gameObject->GetComponent<AudioSource>();
	updateState();
	range = 50.0f;
}

void LocationRVInspect::clickAction()
{
	if (!GameDataController::gd->getObjective(S("rv_inspected")))
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("rv_car_1"));
		timelineAction->function = [this](String str_) { examineCar(str_); };
		timelineAction->actionWithText = false;
		Timeline::t->addAction(timelineAction);
	}
	else
	{
		sayAboutCarExplore2();
	}
}

void LocationRVInspect::updateState()
{
	if (!GameDataController::gd->getObjective(S("rv_inspected")))
	{
		range = 3.0f;
	}
	else
	{
		range = 100.0f;
	}
	if (!aS->get_isPlaying() && GameDataController::gd->getObjective(S("rv_started")))
	{
		aS->set_clip(SoundsManagerController::sm->rv_engine_loop);
		aS->set_loop(true);
		aS->set_volume(0.99f);
		aS->Play();
		smoke->started = true;
	}
	else if (!GameDataController::gd->getObjective(S("rv_started")))
	{
		if (aS->get_isPlaying())
		{
			aS->Stop();
		}
		smoke->started = false;
	}
}

void LocationRVInspect::clickAction2()
{
}

void LocationRVInspect::clickAction0()
{
}

void LocationRVInspect::examineCar(String str_)
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("rv_inspect")), QuestionController::PopupType::QUESTION, [this]() { doExamineCar(); }, 5, 1);
}

void LocationRVInspect::doExamineCar()
{
	GameDataController::gd->setObjective(S("rv_inspected"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("stop"), nullptr, true, [this]() { sayAboutCarExplore(); });
}

void LocationRVInspect::sayAboutCarExplore2()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("rv_car_2")), true);
	P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("rv_car_2a"));
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("rv_car_2b"));
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("rv_car_2c"));
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("rv_car_2d"));
	Timeline::t->addAction(timelineAction);
	updateAll();
}

void LocationRVInspect::sayAboutCarExplore()
{
	PlayerController::pc->setBusy(true);
	Invoke(S("sayAboutCarExplore2"), 1.0f);
}
