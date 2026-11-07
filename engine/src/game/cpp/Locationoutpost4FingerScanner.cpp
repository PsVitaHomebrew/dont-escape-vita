#include "../game_all.h"

void Locationoutpost4FingerScanner::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_fingerscanner");
	actionType = Type::NormalAction;
	range = 2.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("fingerprint"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("finger"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("sidereal_id"), GameStrings::getString(GameStrings::actions, S("fingerprint_no_card")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("outpost_card"), GameStrings::getString(GameStrings::actions, S("fingerprint_no_card")), nullptr, String::Empty));
}

void Locationoutpost4FingerScanner::pressit(String s)
{
	PlayerController::wc->forceAnimation(S("action_n_busy2"));
	Timeline::t->doNotUnlock = true;
	Invoke(S("scansound"), 0.5f);
	Invoke(S("scanfail"), 1.0f);
}

void Locationoutpost4FingerScanner::pressit2(String s)
{
	PlayerController::wc->forceAnimation(S("action_n_busy2"));
	Timeline::t->doNotUnlock = true;
	Invoke(S("scansound"), 0.5f);
	Invoke(S("scansuccess"), 1.0f);
}

void Locationoutpost4FingerScanner::pressit3(String s)
{
	PlayerController::wc->forceAnimation(S("action_n_busy2"));
	Timeline::t->doNotUnlock = true;
	Invoke(S("scansound"), 0.5f);
	Invoke(S("scanfail2"), 1.0f);
}

void Locationoutpost4FingerScanner::scansound()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fingerscan);
}

void Locationoutpost4FingerScanner::failsound(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fail1);
}

void Locationoutpost4FingerScanner::successsound(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->auto_unlock);
	updateAll();
}

void Locationoutpost4FingerScanner::scanfail()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = GetComponent<TextFieldController>();
	timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("fingerprint_reader3"));
	timelineAction->actionWithText = true;
	timelineAction->function = [this](String s) { failsound(s); };
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->backgroundColor = Vector3(0.0f, 0.0f, 0.0f);
	timelineAction->textColor = Vector3(1.0f, 1.0f, 1.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("fingerprint_reader4"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void Locationoutpost4FingerScanner::scanfail2()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = GetComponent<TextFieldController>();
	timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("fingerprint_finger2"));
	timelineAction->actionWithText = true;
	timelineAction->function = [this](String s) { failsound(s); };
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = GetComponent<TextFieldController>();
	timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("fingerprint_finger3"));
	timelineAction->actionWithText = true;
	timelineAction->function = [this](String s) { failsound(s); };
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->backgroundColor = Vector3(0.0f, 0.0f, 0.0f);
	timelineAction->textColor = Vector3(1.0f, 1.0f, 1.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("fingerprint_finger4"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void Locationoutpost4FingerScanner::clickAction()
{
	if (usedItem == String::Empty)
	{
		P<TimelineAction> timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->textColor = Vector3(1.0f, 1.0f, 1.0f);
		timelineAction->backgroundColor = Vector3(0.0f, 0.0f, 0.0f);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("fingerprint_reader1"));
		timelineAction->actionWithText = false;
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->textColor = Vector3(1.0f, 1.0f, 1.0f);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("fingerprint_reader2"));
		timelineAction->actionWithText = true;
		timelineAction->function = [this](String s) { pressit(s); };
		Timeline::t->addAction(timelineAction);
	}
	else if (usedItem == S("fingerprint"))
	{
		InventoryController::ic->removeItem(S("fingerprint"));
		GameDataController::gd->setObjective(S("outpost_fingerprint_unlocked"), true);
		P<TimelineAction> timelineAction2 = New<TimelineAction>();
		timelineAction2 = New<TimelineAction>();
		timelineAction2->textfield = PlayerController::pc->textField;
		timelineAction2->textColor = Vector3(1.0f, 1.0f, 1.0f);
		timelineAction2->text = GameStrings::getString(GameStrings::actions, S("fingerprint_reader5"));
		timelineAction2->actionWithText = true;
		timelineAction2->function = [this](String s) { pressit2(s); };
		Timeline::t->addAction(timelineAction2);
	}
	else if (usedItem == S("finger"))
	{
		InventoryController::ic->removeItem(S("finger"));
		GameDataController::gd->setObjective(S("outpost_fingerprint_unlocked"), true);
		P<TimelineAction> timelineAction3 = New<TimelineAction>();
		timelineAction3 = New<TimelineAction>();
		timelineAction3->textfield = PlayerController::pc->textField;
		timelineAction3->textColor = Vector3(1.0f, 1.0f, 1.0f);
		timelineAction3->text = GameStrings::getString(GameStrings::actions, S("fingerprint_finger1"));
		timelineAction3->actionWithText = true;
		timelineAction3->function = [this](String s) { pressit2(s); };
		Timeline::t->addAction(timelineAction3);
	}
}

void Locationoutpost4FingerScanner::scansuccess()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = GetComponent<TextFieldController>();
	timelineAction->textColor = Vector3(0.0f, 1.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.0f, 0.5f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("fingerprint_reader6"));
	timelineAction->actionWithText = true;
	timelineAction->function = [this](String s) { successsound(s); };
	Timeline::t->addAction(timelineAction);
}

void Locationoutpost4FingerScanner::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("outpost_underground_light")) < 2)
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("outpost_fingerprint_unlocked")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(red);
	}
	else if (GameDataController::gd->getObjective(S("outpost_fingerprint_unlocked")))
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(green);
	}
}

void Locationoutpost4FingerScanner::clickAction2()
{
}

void Locationoutpost4FingerScanner::clickAction0()
{
}
