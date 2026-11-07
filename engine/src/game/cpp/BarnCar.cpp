#include "../game_all.h"

void BarnCar::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_ne");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("car");
	range = 2.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("wheel"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("car_battery"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ignitioncoil"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister_full"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_full"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister_empty"), GameStrings::getString(GameStrings::actions, S("canister_is_empty")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_empty"), GameStrings::getString(GameStrings::actions, S("canister_is_empty")), nullptr, String::Empty));
	updateState();
}

void BarnCar::yesFuel()
{
	InventoryController::ic->removeItem(S("canister_full"));
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("canister_empty")));
	GameDataController::gd->setObjective(S("barn_car_refueled"), true);
	GameDataController::gd->setObjectiveDetail(S("barn_car_refueled"), GameDataController::MAX_FUEL);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NE, nullptr, nullptr, true, [this]() { sayAboutCarFuel(); });
}

void BarnCar::yesFuel2()
{
	InventoryController::ic->removeItem(S("canister2_full"));
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("canister2_empty")));
	GameDataController::gd->setObjective(S("barn_car_refueled"), true);
	GameDataController::gd->setObjectiveDetail(S("barn_car_refueled"), GameDataController::MAX_FUEL);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NE, nullptr, nullptr, true, [this]() { sayAboutCarFuel(); });
}

void BarnCar::yesCoil()
{
	InventoryController::ic->removeItem(S("ignitioncoil"));
	GameDataController::gd->setObjective(S("barn_car_coil_repaired"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NE, nullptr, nullptr, true, [this]() { sayAboutCarPart(); });
}

void BarnCar::yesBattery()
{
	InventoryController::ic->removeItem(S("car_battery"));
	GameDataController::gd->setObjective(S("barn_car_battery_repaired"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NE, nullptr, nullptr, true, [this]() { sayAboutCarPart(); });
}

void BarnCar::yesWheel()
{
	InventoryController::ic->removeItem(S("wheel"));
	GameDataController::gd->setObjective(S("barn_car_wheel_repaired"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NE, nullptr, nullptr, true, [this]() { sayAboutCarPart(); });
}

void BarnCar::yesExamine()
{
	GameDataController::gd->setObjective(S("barn_car_inspected"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NE, nullptr, nullptr, true, [this]() { sayAboutCarExamine(); });
}

void BarnCar::sayAboutCarFuel()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_car_fueled")));
}

void BarnCar::sayAboutCarPart()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_car_installed")));
}

void BarnCar::sayAboutCarExamine()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_car_examined")));
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->textfield = PlayerController::pc->textField;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("barn_car_examined"));
	Timeline::t->addAction(timelineAction);
	sayWhatsWrong();
}

bool BarnCar::sayWhatsWrong()
{
	P<TimelineAction> timelineAction = nullptr;
	if (!GameDataController::gd->getObjective(S("barn_car_wheel_repaired")))
	{
		timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("barn_car_missing_wheel"));
		Timeline::t->addAction(timelineAction);
	}
	if (!GameDataController::gd->getObjective(S("barn_car_coil_repaired")))
	{
		timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("barn_car_coil_missing"));
		Timeline::t->addAction(timelineAction);
	}
	if (!GameDataController::gd->getObjective(S("barn_car_battery_repaired")))
	{
		timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("barn_car_battery_missing"));
		Timeline::t->addAction(timelineAction);
	}
	if (!GameDataController::gd->getObjective(S("barn_car_refueled")))
	{
		timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("barn_car_fuel_missing"));
		Timeline::t->addAction(timelineAction);
	}
	if (timelineAction == nullptr)
	{
		return true;
	}
	return false;
}

void BarnCar::clickAction()
{
	if (!GameDataController::gd->getObjective(S("base_discovered")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_pipe_first")));
	}
	else if (usedItem == S("wheel"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barn_car_part")), QuestionController::PopupType::QUESTION, [this]() { yesWheel(); }, 15, 2);
	}
	else if (usedItem != String::Empty && !GameDataController::gd->getObjective(S("barn_car_inspected")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_car_uninspected")));
	}
	else if (usedItem == String::Empty)
	{
		if (!GameDataController::gd->getObjective(S("barn_car_inspected")))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barn_car_examine")), QuestionController::PopupType::QUESTION, [this]() { yesExamine(); }, 15);
		}
		else if (sayWhatsWrong())
		{
			GameDataController::gd->setObjective(S("car_travel"), true);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->car_open);
			PlayerController::pc->setBusy(true);
			PlayerController::pc->spawnName = S("InfoExit");
			CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E, nullptr, SoundsManagerController::sm->car_start);
		}
	}
	else if (usedItem == S("ignitioncoil"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barn_car_part")), QuestionController::PopupType::QUESTION, [this]() { yesCoil(); }, 15, 2);
	}
	else if (usedItem == S("car_battery"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barn_car_part")), QuestionController::PopupType::QUESTION, [this]() { yesBattery(); }, 15, 2);
	}
	else if (usedItem == S("canister_full"))
	{
		if (GameDataController::gd->getObjective(S("barn_car_refueled")) && GameDataController::gd->getObjectiveDetail(S("barn_car_refueled")) == GameDataController::MAX_FUEL)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("car_already_fueled")));
		}
		else
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barn_car_refuel")), QuestionController::PopupType::QUESTION, [this]() { yesFuel(); });
		}
	}
	else if (usedItem == S("canister2_full"))
	{
		if (GameDataController::gd->getObjective(S("barn_car_refueled")) && GameDataController::gd->getObjectiveDetail(S("barn_car_refueled")) == GameDataController::MAX_FUEL)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("car_already_fueled")));
		}
		else
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barn_car_refuel")), QuestionController::PopupType::QUESTION, [this]() { yesFuel2(); });
		}
	}
}

void BarnCar::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("barn_car_wheel_repaired")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(wheel_broken);
		actionMarker = action1;
	}
	else if (!GameDataController::gd->getObjective(S("barn_car_battery_repaired")) || !GameDataController::gd->getObjective(S("barn_car_coil_repaired")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(broken);
		actionMarker = action1;
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(fixedC);
		if (GameDataController::gd->getObjective(S("barn_car_refueled")))
		{
			if (GameDataController::KART)
			{
				GameDataController::persistentData->kong_car = true;
				GameDataController::gd->PersistentSave();
			}
			actionMarker = action2;
		}
		else
		{
			actionMarker = action1;
		}
	}
	if ((GameDataController::gd->getObjectiveDetail(S("car_location")) == 0 && SceneManager::GetActiveScene().get_name() == S("Barn")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 1 && SceneManager::GetActiveScene().get_name() == S("LocationBridge")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 2 && SceneManager::GetActiveScene().get_name() == S("LocationGasstation1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 3 && SceneManager::GetActiveScene().get_name() == S("LocationHouseB")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 4 && SceneManager::GetActiveScene().get_name() == S("LocationCrashsite1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 5 && SceneManager::GetActiveScene().get_name() == S("LocationRestaurant1")))
	{
		colliderManager->setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("CarBlock"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
	}
	else
	{
		colliderManager->setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("CarBlock"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
	}
	ItemsManager::im->fixGroundItems(Vector2(groundItemsFix_x, groundItemsFix_y), Vector2(groundItemsFixShiftX, groundItemsFixShiftY));
	ItemsManager::im->initGroundAndInv();
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void BarnCar::clickAction2()
{
}

void BarnCar::clickAction0()
{
}

void BarnCar::whatOnClick0()
{
}

void BarnCar::whatOnClick()
{
}
