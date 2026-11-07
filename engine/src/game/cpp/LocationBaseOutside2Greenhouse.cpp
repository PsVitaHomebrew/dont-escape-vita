#include "../game_all.h"

void LocationBaseOutside2Greenhouse::Start()
{
	sr = gameObject->GetComponent<SpriteRenderer>();
	colliderManager->setTarget(gameObject);
	animationFlip = true;
	characterAnimationName = S("action_stnd_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("greenhouse_nails");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("hammer"), String::Empty, nullptr, String::Empty));
}

void LocationBaseOutside2Greenhouse::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 4)
	{
		sr->set_sprite(sprite1);
		objectName = S("greenhouse_nails");
		setCollider(0);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 3)
	{
		sr->set_sprite(sprite2);
		objectName = S("greenhouse_nails");
		setCollider(1);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 2)
	{
		sr->set_sprite(sprite3);
		objectName = S("greenhouse_nails");
		setCollider(2);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 1)
	{
		sr->set_sprite(sprite4);
		objectName = S("greenhouse_nails");
		setCollider(3);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 0)
	{
		sr->set_sprite(sprite5);
		objectName = S("greenhouse_no_nails");
		setCollider(4);
	}
	characterAnimationName = S("action_stnd_");
	useCurrentDirection = true;
}

void LocationBaseOutside2Greenhouse::whatOnClick()
{
}

void LocationBaseOutside2Greenhouse::clickAction()
{
	if (usedItem == S("crowbar"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) > 0)
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("greenhouse_nails")), QuestionController_PopupType::QUESTION, [this]() { yesClicked(); }, 10, 1);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("greenhouse_no_nails")), true);
		}
	}
	else if (usedItem == S("hammer"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) > 0)
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("greenhouse_hammer")), QuestionController_PopupType::QUESTION, [this]() { yesClicked2(); }, 20, 2);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("greenhouse_no_nails")), true);
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) > 0)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("greenhouse_nails")), true);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("greenhouse_no_nails")), true);
	}
}

void LocationBaseOutside2Greenhouse::yesClicked2()
{
	nailsremove(S("action_n_long"));
}

void LocationBaseOutside2Greenhouse::yesClicked()
{
	nailsremove(S("crowbar_e"));
}

void LocationBaseOutside2Greenhouse::nailsremove(String s)
{
	P<Item> item = ItemsManager::im->getItem(S("nails") + GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")));
	P<Item> item2 = ItemsManager::im->getItem(S("planks") + GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")));
	int objectiveDetail = GameDataController::gd->getObjectiveDetail(S("greenhouse_nails"));
	if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 4)
	{
		GameDataController::gd->setObjectiveDetail(S("greenhouse_nails"), 3);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 3)
	{
		GameDataController::gd->setObjectiveDetail(S("greenhouse_nails"), 2);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 2)
	{
		GameDataController::gd->setObjectiveDetail(S("greenhouse_nails"), 1);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 1)
	{
		GameDataController::gd->setObjectiveDetail(S("greenhouse_nails"), 0);
	}
	Invoke(S("drop"), 1.0f);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->wood_crack_3);
	item->dataRef->locX = (int)PlayerController::wc->currentXY.x + (objectiveDetail - 3) * 25 + 20;
	item->dataRef->locY = (int)PlayerController::wc->currentXY.y - 2;
	item->dataRef->droppedLocation = SceneManager::GetActiveScene().get_name();
	item2->dataRef->locX = (int)PlayerController::wc->currentXY.x + (objectiveDetail - 3) * 25 - 15 + 20;
	item2->dataRef->locY = (int)PlayerController::wc->currentXY.y + 3;
	item2->dataRef->droppedLocation = SceneManager::GetActiveScene().get_name();
	PlayerController::wc->forceAnimation(s);
	CurtainController::cc->fadeOut(S("none"), WalkController_Direction::E, s);
}

void LocationBaseOutside2Greenhouse::drop()
{
	P<Item> item = ItemsManager::im->getItem(S("nails") + (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) + 1));
	Vector2 vector = ScreenControler::gameToScreen(Vector2((float)item->dataRef->locX, (float)(item->dataRef->locY + GroundItemController::yOffset)));
	Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
	vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
	P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion());
	gameObject->GetComponent<GroundItemController>()->init(item);
	P<Item> item2 = ItemsManager::im->getItem(S("planks") + (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) + 1));
	vector = ScreenControler::gameToScreen(Vector2((float)item2->dataRef->locX, (float)(item2->dataRef->locY + GroundItemController::yOffset)));
	vector2 = Vector3(vector.x, vector.y, 0.0f);
	vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
	gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion());
	gameObject->GetComponent<GroundItemController>()->init(item2);
}

void LocationBaseOutside2Greenhouse::clickAction2()
{
}

void LocationBaseOutside2Greenhouse::clickAction0()
{
}
