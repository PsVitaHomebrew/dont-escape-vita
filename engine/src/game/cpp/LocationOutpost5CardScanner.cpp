#include "../game_all.h"

void LocationOutpost5CardScanner::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_cardscanner");
	actionType = Type::NormalAction;
	range = 2.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("sidereal_id"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("outpost_card"), String::Empty, nullptr, String::Empty));
}

void LocationOutpost5CardScanner::pressit(String s)
{
	Invoke(S("scansound"), 0.5f);
	Invoke(S("scanfail"), 1.0f);
}

void LocationOutpost5CardScanner::pressit2(String s)
{
	Invoke(S("scansound"), 0.5f);
	Invoke(S("scansuccess"), 1.0f);
}

void LocationOutpost5CardScanner::scansound()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fingerscan);
}

void LocationOutpost5CardScanner::failsound(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fail1);
}

void LocationOutpost5CardScanner::successsound(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->auto_unlock);
	updateAll();
}

void LocationOutpost5CardScanner::scanfail()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = GetComponent<TextFieldController>();
	timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("card_reader_1"));
	timelineAction->actionWithText = true;
	timelineAction->function = [this](String s) { failsound(s); };
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = GetComponent<TextFieldController>();
	timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("card_reader_2"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void LocationOutpost5CardScanner::clickAction()
{
	if (usedItem == S("sidereal_id"))
	{
		pressit(String::Empty);
	}
	else if (usedItem == S("outpost_card"))
	{
		pressit2(String::Empty);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("card_needed")));
	}
}

void LocationOutpost5CardScanner::scansuccess()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(0.0f, 1.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.0f, 0.5f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("card_reader_3"));
	timelineAction->actionWithText = true;
	timelineAction->function = [this](String s) { successsound(s); };
	Timeline::t->addAction(timelineAction);
	GameDataController::gd->setObjective(S("outpost_hall_unlocked"), true);
}

void LocationOutpost5CardScanner::updateState()
{
	if (!GameDataController::gd->getObjective(S("outpost_hall_unlocked")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(red);
	}
	else if (GameDataController::gd->getObjective(S("outpost_hall_unlocked")))
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_sprite(green);
	}
}

void LocationOutpost5CardScanner::whatOnClick0()
{
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	if (usedItem != String::Empty)
	{
		characterAnimationName = S("action_n_busy2");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void LocationOutpost5CardScanner::clickAction2()
{
}

void LocationOutpost5CardScanner::clickAction0()
{
}
