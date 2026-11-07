#include "../game_all.h"

void CarTravel::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("car");
	range = 2.0f;
	trunk = GameObject::Find(S("Trunk"));
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("canister_full"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister_empty"), GameStrings::getString(GameStrings::actions, S("canister_is_empty")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_full"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("canister2_empty"), GameStrings::getString(GameStrings::actions, S("canister_is_empty")), nullptr, String::Empty));
	updateState();
}

void CarTravel::yesFuel()
{
	InventoryController::ic->removeItem(S("canister_full"));
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("canister_empty")));
	GameDataController::gd->setObjective(S("barn_car_refueled"), true);
	GameDataController::gd->setObjectiveDetail(S("barn_car_refueled"), GameDataController::MAX_FUEL);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NE, nullptr, nullptr, true, [this]() { sayAboutCarFuel(); });
}

void CarTravel::yesFuel2()
{
	InventoryController::ic->removeItem(S("canister2_full"));
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("canister2_empty")));
	GameDataController::gd->setObjective(S("barn_car_refueled"), true);
	GameDataController::gd->setObjectiveDetail(S("barn_car_refueled"), GameDataController::MAX_FUEL);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NE, nullptr, nullptr, true, [this]() { sayAboutCarFuel(); });
}

void CarTravel::sayAboutCarFuel()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("barn_car_fueled")));
}

void CarTravel::clickAction()
{
	if (usedItem == S("canister_full"))
	{
		if (GameDataController::gd->getObjective(S("barn_car_refueled")) && GameDataController::gd->getObjectiveDetail(S("barn_car_refueled")) == GameDataController::MAX_FUEL)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("car_already_fueled")));
		}
		else
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barn_car_refuel")), QuestionController::PopupType::QUESTION, [this]() { yesFuel(); });
		}
		return;
	}
	if (usedItem == S("canister2_full"))
	{
		if (GameDataController::gd->getObjective(S("barn_car_refueled")) && GameDataController::gd->getObjectiveDetail(S("barn_car_refueled")) == GameDataController::MAX_FUEL)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("car_already_fueled")));
		}
		else
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barn_car_refuel")), QuestionController::PopupType::QUESTION, [this]() { yesFuel2(); });
		}
		return;
	}
	if (GameDataController::gd->getObjectiveDetail(S("barn_car_refueled")) == 0)
	{
		P<TimelineAction> timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("barn_car_fuel_missing"));
		Timeline::t->addAction(timelineAction);
		return;
	}
	if (SceneManager::GetActiveScene().get_name() == S("LocationBridge"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("map_restaurant_revealed")) == TravelAgency::LOCATION_STATUS_UNREACHABLE)
		{
			GameDataController::gd->setObjectiveDetail(S("map_restaurant_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
		}
		if (GameDataController::gd->getObjectiveDetail(S("map_houseb_revealed")) == TravelAgency::LOCATION_STATUS_UNREACHABLE)
		{
			GameDataController::gd->setObjectiveDetail(S("map_houseb_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
		}
	}
	if (SceneManager::GetActiveScene().get_name() == S("SiderealOutside1") && !GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_cant_leave")));
		return;
	}
	GameDataController::gd->setObjective(S("car_travel"), true);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->car_open);
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E, nullptr, SoundsManagerController::sm->car_start);
}

void CarTravel::updateState()
{
	if (trunk == nullptr)
	{
		trunk = GameObject::Find(S("Trunk"));
	}
	if ((GameDataController::gd->getObjectiveDetail(S("car_location")) == 0 && SceneManager::GetActiveScene().get_name() == S("Barn")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 1 && SceneManager::GetActiveScene().get_name() == S("LocationBridge")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 2 && SceneManager::GetActiveScene().get_name() == S("LocationGasstation1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 3 && SceneManager::GetActiveScene().get_name() == S("LocationHouseB")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 4 && SceneManager::GetActiveScene().get_name() == S("LocationCrashsite1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 5 && SceneManager::GetActiveScene().get_name() == S("LocationRestaurant1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 6 && SceneManager::GetActiveScene().get_name() == S("LocationRV")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 7 && SceneManager::GetActiveScene().get_name() == S("HuntersLodgeOutside1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 8 && SceneManager::GetActiveScene().get_name() == S("SiderealOutside1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 9 && SceneManager::GetActiveScene().get_name() == S("CS1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 10 && SceneManager::GetActiveScene().get_name() == S("LocationOutpostOutside1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 11 && SceneManager::GetActiveScene().get_name() == S("LocationBus1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 12 && SceneManager::GetActiveScene().get_name() == S("LocationAirplane1")))
	{
		colliderManager->setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		trunk->GetComponent<CarTrunk>()->setCollider(0);
		GameObject::Find(S("CarBlock"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
	}
	else
	{
		colliderManager->setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		trunk->GetComponent<CarTrunk>()->setCollider(-1);
		GameObject::Find(S("CarBlock"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
	}
	ItemsManager::im->fixGroundItems(Vector2(groundItemsFix_x, groundItemsFix_y), Vector2(groundItemsFixShiftX, groundItemsFixShiftY));
	ItemsManager::im->initGroundAndInv();
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void CarTravel::clickAction2()
{
}

void CarTravel::clickAction0()
{
}

void CarTravel::whatOnClick0()
{
}

void CarTravel::whatOnClick()
{
}
