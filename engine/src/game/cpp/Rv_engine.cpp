#include "../game_all.h"

void Rv_engine::Start()
{
	colliderManager->setTarget(gameObject);
	aS = gameObject->GetComponent<AudioSource>();
	range = 1.0f;
	characterAnimationName = S("walk2_low2");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_seats");
}

void Rv_engine::clickAction()
{
	if (!GameDataController::gd->getObjective(S("rv_inspected")))
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("rv_car_1b"));
		timelineAction->function = [this](String s) { examineCar(s); };
		timelineAction->actionWithText = false;
		Timeline::t->addAction(timelineAction);
	}
	else if (GameDataController::gd->getObjective(S("rv_fueled")) && !GameDataController::gd->getObjective(S("rv_started")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rv_engine_start);
	}
	else if (!GameDataController::gd->getObjective(S("rv_fueled")) && !GameDataController::gd->getObjective(S("rv_started")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rv_engine_fail);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_already_running")));
	}
}

void Rv_engine::updateState()
{
	if (!aS->get_isPlaying() && GameDataController::gd->getObjective(S("rv_started")))
	{
		aS->set_clip(SoundsManagerController::sm->rv_engine_loop);
		aS->set_loop(true);
		aS->set_volume(0.75f);
		aS->Play();
	}
	else if (!GameDataController::gd->getObjective(S("rv_started")) && aS->get_isPlaying())
	{
		aS->Stop();
	}
}

void Rv_engine::clickAction2()
{
	if (GameDataController::gd->getObjective(S("rv_fueled")) && !GameDataController::gd->getObjective(S("rv_started")))
	{
		GameDataController::gd->setObjective(S("rv_started"), true);
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("rv_started"));
		Timeline::t->addAction(timelineAction);
		Timeline::t->doNotUnlock = true;
	}
	else if (!GameDataController::gd->getObjective(S("rv_fueled")) && !GameDataController::gd->getObjective(S("rv_started")))
	{
		P<TimelineAction> timelineAction2 = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction2->text = GameStrings::getString(GameStrings::actions, S("rv_no_fuel"));
		Timeline::t->addAction(timelineAction2);
		Timeline::t->doNotUnlock = true;
	}
	updateState();
}

void Rv_engine::clickAction0()
{
}

void Rv_engine::whatOnClick0()
{
	if (!GameDataController::gd->getObjective(S("rv_inspected")))
	{
		range = 1.0f;
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else if (GameDataController::gd->getObjective(S("rv_fueled")) && !GameDataController::gd->getObjective(S("rv_started")))
	{
		range = 1.0f;
		characterAnimationName = S("walk2_low2");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else if (!GameDataController::gd->getObjective(S("rv_fueled")) && !GameDataController::gd->getObjective(S("rv_started")))
	{
		range = 1.0f;
		characterAnimationName = S("walk2_low2");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		range = 1111.0f;
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void Rv_engine::examineCar(String str_)
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("rv_inspect")), QuestionController::PopupType::QUESTION, [this]() { doExamineCar(); }, 5, 1);
}

void Rv_engine::doExamineCar()
{
	GameDataController::gd->setObjective(S("rv_inspected"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("stop"), nullptr, true, [this]() { sayAboutCarExplore(); });
}

void Rv_engine::sayAboutCarExplore2()
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

void Rv_engine::sayAboutCarExplore()
{
	PlayerController::pc->setBusy(true);
	Invoke(S("sayAboutCarExplore2"), 1.0f);
}
