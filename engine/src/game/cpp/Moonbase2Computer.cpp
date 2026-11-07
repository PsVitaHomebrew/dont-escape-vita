#include "../game_all.h"

void Moonbase2Computer::updateMLF()
{
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->pc_noise, 0.75f, AudioReverbPreset::Bathroom);
	mlf->lightsFailed = false;
}

void Moonbase2Computer::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n_busy2");
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moon_computer");
	range = 2.0f;
	updateAll();
}

void Moonbase2Computer::pressit(String s)
{
	Invoke(S("scansound"), 0.1f);
	Invoke(S("scanfail"), 1.1f);
}

void Moonbase2Computer::pressit2()
{
	PlayerController::pc->setBusy(true);
	Invoke(S("scansound"), 0.1f);
	Invoke(S("scansuccess"), 1.1f);
}

void Moonbase2Computer::pressit3()
{
	PlayerController::pc->setBusy(true);
	Invoke(S("scansound"), 0.1f);
	Invoke(S("scansuccess2"), 1.1f);
}

void Moonbase2Computer::scansound()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->keyboard);
}

void Moonbase2Computer::failsound(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fail1);
}

void Moonbase2Computer::successsound(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
	updateAll();
}

void Moonbase2Computer::successsound2(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->power_up_big, 0.5f);
	updateMLF();
	updateAll();
	GameDataController::gd->setObjective(S("moon_light_restored"), true);
	GameObject::Find(S("LocationManager"))->GetComponent<LocationMoonbase2Start>()->windowMayCrack = true;
}

void Moonbase2Computer::scanfail()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("moon_computer_1"));
	timelineAction->actionWithText = true;
	timelineAction->function = [this](String s) { failsound(s); };
	Timeline::t->addAction(timelineAction);
}

void Moonbase2Computer::clickAction()
{
	if (!GameDataController::gd->getObjective(S("moon_card_used")))
	{
		pressit(String::Empty);
	}
	else if (GameDataController::gd->getObjective(S("moon_light_failed")) && !GameDataController::gd->getObjective(S("moon_light_restored")))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::world_labels, S("moon_restore_power")), QuestionController::PopupType::QUESTION, [this]() { pressit3(); }, 0, 0, nullptr, GameStrings::getString(GameStrings::world_labels, S("moon_restore_p_yes")), GameStrings::getString(GameStrings::world_labels, S("moon_restore_p_no")), screen);
	}
	else if (!GameDataController::gd->getObjective(S("moon_console_unlocked")))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::world_labels, S("moon_restore_console_unlock")), QuestionController::PopupType::QUESTION, [this]() { pressit2(); }, 0, 0, nullptr, GameStrings::getString(GameStrings::world_labels, S("moon_restore_c_yes")), GameStrings::getString(GameStrings::world_labels, S("moon_restore_c_no")), screen);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moon_computer_all")));
	}
}

void Moonbase2Computer::scansuccess()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(0.0f, 1.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.0f, 0.5f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("moon_computer_3"));
	timelineAction->actionWithText = true;
	timelineAction->function = [this](String s) { successsound(s); };
	Timeline::t->addAction(timelineAction);
	GameDataController::gd->setObjective(S("moon_console_unlocked"), true);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(0.0f, 1.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.0f, 0.5f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("moon_computer_2"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void Moonbase2Computer::scansuccess2()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(0.0f, 1.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.0f, 0.5f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("moon_computer_4"));
	timelineAction->actionWithText = true;
	timelineAction->function = [this](String s) { successsound2(s); };
	Timeline::t->addAction(timelineAction);
	GameDataController::gd->setObjective(S("moon_light_restored"), true);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(0.0f, 1.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.0f, 0.5f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("moon_computer_5"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void Moonbase2Computer::whatOnClick0()
{
	animationFlip = false;
	characterAnimationName = S("action_n_busy2");
	useCurrentDirection = false;
	if ((!GameDataController::gd->getObjective(S("moon_light_failed")) || GameDataController::gd->getObjective(S("moon_light_restored"))) && !GameDataController::gd->getObjective(S("moon_console_unlocked")))
	{
	}
}

void Moonbase2Computer::updateState()
{
	if (!GameDataController::gd->getObjective(S("moon_card_used")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void Moonbase2Computer::clickAction2()
{
}

void Moonbase2Computer::clickAction0()
{
}
