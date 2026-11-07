#include "../game_all.h"

void LocationShipMoon1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ship_exit");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
}

void LocationShipMoon1::decompression(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->wind1);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, nullptr, SoundsManagerController::sm->slidedoor, false, [this]() { doneDecompression(); });
}

void LocationShipMoon1::doneDecompression()
{
	GameObject::Find(S("LocationManager"))->GetComponent<LocationMoonShipStart>()->updateThings();
	GameDataController::gd->setObjective(S("moon_door_open"), true);
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->textColor = Vector3(0.0f, 1.0f, 0.0f);
	timelineAction->backgroundColor = Vector3(0.0f, 0.5f, 0.0f);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("ship_exit_2"));
	timelineAction->actionWithText = true;
	Timeline::t->addAction(timelineAction);
}

void LocationShipMoon1::clickAction()
{
	if (GameDataController::gd->getObjective(S("moon_door_open")))
	{
		PlayerController::pc->spawnName = S("LocationMoon1Ship");
		CurtainController::cc->fadeOut(S("Moon1"), WalkController::Direction::S_);
	}
	else if ((!GameDataController::gd->getObjective(S("npc1_alive")) || !GameDataController::gd->getObjective(S("moon_shocked1"))) && (!GameDataController::gd->getObjective(S("npc2_alive")) || !GameDataController::gd->getObjective(S("moon_shocked2"))) && (!GameDataController::gd->getObjective(S("npc3_alive")) || !GameDataController::gd->getObjective(S("moon_shocked3"))))
	{
		if (GameDataController::gd->getObjective(S("moon_suited_up")))
		{
			GameDataController::gd->setObjective(S("moon_door_open"), true);
			P<TimelineAction> timelineAction = New<TimelineAction>();
			timelineAction = New<TimelineAction>();
			timelineAction->textfield = PlayerController::pc->textField;
			timelineAction->textColor = Vector3(0.0f, 1.0f, 0.0f);
			timelineAction->backgroundColor = Vector3(0.0f, 0.5f, 0.0f);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("ship_exit_1"));
			timelineAction->actionWithText = false;
			timelineAction->function = [this](String s) { decompression(s); };
			Timeline::t->addAction(timelineAction);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ship_exit_not_yet_suits")));
		}
	}
	else if (GameDataController::gd->getObjective(S("npc2_alive")) || GameDataController::gd->getObjective(S("npc3_alive")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ship_exit_not_yet_others")));
	}
	else if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ship_exit_not_yet_cate")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ship_exit_not_yet_suits")));
	}
}

void LocationShipMoon1::updateState()
{
	if (GameDataController::gd->getObjective(S("moon_door_open")))
	{
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
		GetComponent<SpriteRenderer>()->set_enabled(true);
		return;
	}
	characterAnimationName = S("action_stnd_");
	if (GameDataController::gd->getObjective(S("moon_suited_up")))
	{
		characterAnimationName = S("suit_action_stnd_");
	}
	animationFlip = false;
	useCurrentDirection = true;
	actionType = Type::NormalAction;
	trans_dir = WalkController::Direction::N;
	GetComponent<SpriteRenderer>()->set_enabled(false);
}

void LocationShipMoon1::clickAction2()
{
}

void LocationShipMoon1::clickAction0()
{
}
