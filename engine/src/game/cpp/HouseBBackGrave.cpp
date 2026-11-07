#include "../game_all.h"

void HouseBBackGrave::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_back_ground");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("shovel"), String::Empty, nullptr, String::Empty));
	updateState();
}

void HouseBBackGrave::Update()
{
	if (!GameDataController::gd->getObjective(S("house_b_grave_dug")))
	{
		if (CursorController::cc->selectedItemName == S("shovel") && GameDataController::gd->getCurrentDay() == 2)
		{
			setCollider(1);
		}
		else
		{
			setCollider(-1);
		}
	}
	else if (GameDataController::gd->getObjective(S("house_b_grave_dug")))
	{
		if (CursorController::cc->selectedItemName == S("shovel"))
		{
			setCollider(0);
		}
		else
		{
			setCollider(0);
		}
	}
}

void HouseBBackGrave::clickAction()
{
	if (!GameDataController::gd->getObjective(S("house_b_grave_dug")))
	{
		if (usedItem == S("shovel"))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barrys_wife_grave")), QuestionController::PopupType::QUESTION, [this]() { digGrave(); }, 90, 30);
		}
	}
	else if (GameDataController::gd->getObjective(S("house_b_grave_filled")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_grave")), true);
	}
	else
	{
		PlayerController::pc->say(S("..."));
	}
}

void HouseBBackGrave::digGrave()
{
	GameDataController::gd->setObjective(S("house_b_grave_dug"), true);
	Invoke(S("digging_end"), 3.0f);
	PlayerController::wc->forceAnimation(S("dig_start"), true);
}

void HouseBBackGrave::digging_end()
{
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::S_, S("dig_end"), nullptr, true, [this]() { digGrave2(); });
}

void HouseBBackGrave::digGrave2()
{
	Vector3 vector = ScreenControler::roundToNearestFullPixel(GameObject::Find(S("digged_grave_marker"))->transform->get_position());
	GameObject::Find(S("Location"))->transform->Find(S("plane00a (2)"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	PlayerController::wc->currentXY = Vector2(vector.x, vector.y);
	PlayerController::wc->setSimpleTarget(Vector2(vector.x, vector.y));
	Invoke(S("exitGrave"), 3.0f);
}

void HouseBBackGrave::exitGrave()
{
	PlayerController::wc->forceAnimation(S("climb_se"));
	Invoke(S("exitGrave2"), 1.3f);
}

void HouseBBackGrave::exitGrave2()
{
	Vector3 vector = ScreenControler::roundToNearestFullPixel(GameObject::Find(S("digged_grave_marker_exit"))->transform->get_position());
	PlayerController::wc->currentXY = Vector2(vector.x, vector.y);
	PlayerController::wc->setSimpleTarget(Vector2(vector.x, vector.y));
	Invoke(S("exitGrave2a"), 0.1f);
}

void HouseBBackGrave::exitGrave2a()
{
	Vector3 vector = ScreenControler::roundToNearestFullPixel(GameObject::Find(S("digged_grave_marker_exit2"))->transform->get_position());
	PlayerController::wc->currentXY = Vector2(vector.x, vector.y);
	PlayerController::wc->setSimpleTarget(Vector2(vector.x, vector.y));
	Invoke(S("exitGrave2b"), 0.2f);
}

void HouseBBackGrave::exitGrave2b()
{
	Vector3 vector = ScreenControler::roundToNearestFullPixel(GameObject::Find(S("digged_grave_marker_exit2"))->transform->get_position());
	PlayerController::wc->currentXY = Vector2(vector.x, vector.y);
	PlayerController::wc->setSimpleTarget(Vector2(vector.x, vector.y));
	Invoke(S("exitGrave2c"), 0.2f);
}

void HouseBBackGrave::exitGrave2c()
{
	Vector3 vector = ScreenControler::roundToNearestFullPixel(GameObject::Find(S("digged_grave_marker_exit3"))->transform->get_position());
	PlayerController::wc->currentXY = Vector2(vector.x, vector.y);
	PlayerController::wc->setSimpleTarget(Vector2(vector.x, vector.y));
	Invoke(S("exitGrave2d"), 0.2f);
}

void HouseBBackGrave::exitGrave2d()
{
	Vector3 vector = ScreenControler::roundToNearestFullPixel(GameObject::Find(S("digged_grave_marker_exit4"))->transform->get_position());
	PlayerController::wc->currentXY = Vector2(vector.x, vector.y);
	PlayerController::wc->setSimpleTarget(Vector2(vector.x, vector.y));
	Invoke(S("exitGrave3"), 0.2f);
}

void HouseBBackGrave::exitGrave3()
{
	Vector3 vector = ScreenControler::roundToNearestFullPixel(GameObject::Find(S("Grave"))->transform->Find(S("Action_Marker"))->transform->get_position());
	GameObject::Find(S("Location"))->transform->Find(S("plane00a (2)"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	PlayerController::wc->setSimpleTarget(Vector2(vector.x, vector.y));
}

void HouseBBackGrave::updateState()
{
	if (!GameDataController::gd->getObjective(S("house_b_grave_dug")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		objectName = S("house_b_back_ground");
	}
	else if (GameDataController::gd->getObjective(S("house_b_grave_filled")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite2);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("house_b_back_grave");
	}
	else
	{
		objectName = S("house_b_back_hole");
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void HouseBBackGrave::clickAction2()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->digger);
}

void HouseBBackGrave::clickAction0()
{
}
