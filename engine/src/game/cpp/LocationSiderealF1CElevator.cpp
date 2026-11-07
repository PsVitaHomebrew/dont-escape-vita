#include "../game_all.h"

void LocationSiderealF1CElevator::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_elevator_closed");
	range = 1.0f;
	teleport = false;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("fire_hose"), String::Empty, nullptr, String::Empty));
}

void LocationSiderealF1CElevator::Update()
{
}

void LocationSiderealF1CElevator::whatOnClick0()
{
	if (GameDataController::gd->getObjective(S("sidereal_elevator_f1_hosed")) || (usedItem == S("fire_hose") && GameDataController::gd->getObjective(S("sidereal_elevator_f1_open"))))
	{
		if (GameDataController::gd->getObjective(S("sidereal_elevator_f1_hosed")))
		{
			characterAnimationName = S("kneel_in_n");
			animationFlip = false;
			useCurrentDirection = false;
		}
		else
		{
			characterAnimationName = S("kneel_");
			animationFlip = false;
			useCurrentDirection = true;
		}
		range = 1.0f;
	}
	else if (GameDataController::gd->getObjective(S("sidereal_elevator_f1_open")) || usedItem == S("fire_hose"))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 100.0f;
	}
	else
	{
		characterAnimationName = S("action1_e");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
	}
}

void LocationSiderealF1CElevator::climb()
{
	PlayerController::pc->spawnName = S("LocationSiderealF0C_Waypoint_F1");
	CurtainController::cc->fadeOut(S("SiderealF0C"), WalkController::Direction::E);
}

void LocationSiderealF1CElevator::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_elevator_f1_open")))
	{
		if (usedItem == S("fire_hose"))
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rope);
			GameDataController::gd->setObjective(S("sidereal_elevator_f1_hosed"), true);
			updateAll();
		}
		else if (GameDataController::gd->getObjective(S("sidereal_elevator_f1_hosed")))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("sidereal_elevator_down")), QuestionController::PopupType::QUESTION, [this]() { climb(); }, 5);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_elevator1")), true, false, false, 150);
		}
	}
	else if (usedItem == S("fire_hose"))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_elevator_open_first")));
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_creak1);
		GameDataController::gd->setObjective(S("sidereal_elevator_f1_open"), true);
		updateState();
	}
}

void LocationSiderealF1CElevator::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_elevator_f1_hosed")))
	{
		objectName = S("sidereal_elevator_1");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::S_;
		doubleClickCondition = String::Empty;
	}
	else if (GameDataController::gd->getObjective(S("sidereal_elevator_f1_open")))
	{
		objectName = S("sidereal_elevator_2");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		actionType = Type::NormalAction;
		doubleClickCondition = String::Empty;
	}
	else
	{
		objectName = S("sidereal_elevator_closed");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		actionType = Type::NormalAction;
		doubleClickCondition = String::Empty;
	}
}

void LocationSiderealF1CElevator::clickAction2()
{
}

void LocationSiderealF1CElevator::clickAction0()
{
}
