#include "../game_all.h"

void Outpost7_HatchControl::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_hatch_computer");
	range = 1.0f;
}

void Outpost7_HatchControl::yesOpen()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click1, 0.5f);
	if (GameDataController::gd->getObjective(S("outpost_belt_hatch")))
	{
		animator->Play(S("hatch_open"));
		pg1->started = true;
		pg2->started = true;
		pg3->started = true;
		Invoke(S("stopSand"), 3.0f);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->sand_big, 0.75f);
		GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->big_door_open);
		Invoke(S("succeed"), 3.0f);
		GameDataController::gd->setObjective(S("outpost_hatch_open"), true);
	}
	else
	{
		Invoke(S("failed"), 1.0f);
	}
}

void Outpost7_HatchControl::succeed()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(0.0f, 1.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.0f, 0.5f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("outpost_hatch_opening"));
	timelineAction->actionWithText = true;
	Timeline::t->addAction(timelineAction);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
}

void Outpost7_HatchControl::stopSand()
{
	pg1->started = false;
	pg2->started = false;
	pg3->started = false;
}

void Outpost7_HatchControl::failed()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("outpost_hatch_engine_broken"));
	timelineAction->actionWithText = true;
	Timeline::t->addAction(timelineAction);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fail1);
}

void Outpost7_HatchControl::clickAction()
{
	if (!GameDataController::gd->getObjective(S("outpost_hatch_open")))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("outpost_hatch_open")), QuestionController_PopupType::QUESTION, [this]() { yesOpen(); }, 0, 0, nullptr, nullptr, nullptr, background);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_hatch_opened")));
	}
}

void Outpost7_HatchControl::updateState()
{
	colliderManager->setCollider(0);
}

void Outpost7_HatchControl::clickAction2()
{
}

void Outpost7_HatchControl::clickAction0()
{
}

void Outpost7_HatchControl::whatOnClick0()
{
}

void Outpost7_HatchControl::whatOnClick()
{
}
