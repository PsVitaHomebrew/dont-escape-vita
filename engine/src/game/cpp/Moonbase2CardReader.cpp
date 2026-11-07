#include "../game_all.h"

void Moonbase2CardReader::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action1_e");
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moon_card_reader");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("outpost_card"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("sidereal_id_key"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("moon_card"), String::Empty, nullptr, String::Empty));
	updateAll();
}

void Moonbase2CardReader::pressit(String s)
{
	Invoke(S("scansound"), 0.5f);
	Invoke(S("scanfail"), 1.0f);
}

void Moonbase2CardReader::pressit2(String s)
{
	Invoke(S("scansound"), 0.5f);
	Invoke(S("scansuccess"), 1.0f);
}

void Moonbase2CardReader::scansound()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fingerscan);
}

void Moonbase2CardReader::failsound(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fail1);
}

void Moonbase2CardReader::successsound(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
	updateAll();
}

void Moonbase2CardReader::scanfail()
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("card_reader_1"));
	timelineAction->actionWithText = true;
	timelineAction->function = [this](String s) { failsound(s); };
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("card_reader_2"));
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void Moonbase2CardReader::clickAction()
{
	if (usedItem == S("sidereal_id") || usedItem == S("outpost_card"))
	{
		pressit(String::Empty);
	}
	else if (usedItem == S("moon_card"))
	{
		pressit2(String::Empty);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("card_needed")));
	}
}

void Moonbase2CardReader::scansuccess()
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
	GameDataController::gd->setObjective(S("moon_card_used"), true);
}

void Moonbase2CardReader::whatOnClick0()
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

void Moonbase2CardReader::updateState()
{
}

void Moonbase2CardReader::clickAction2()
{
}

void Moonbase2CardReader::clickAction0()
{
}
