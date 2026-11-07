#include "../game_all.h"

void TravelAgency::Start()
{
	fc = GameObject::Find(S("Fuel"))->GetComponent<FuelController>();
	topText = GameObject::Find(S("TopText"))->GetComponent<MapTextController>();
	locationName = gameObject->get_name();
	routeRenderer = gameObject->transform->Find(S("router"))->GetComponent<SpriteRenderer>();
	sr = gameObject->GetComponent<SpriteRenderer>();
	characterAnimationName = String::Empty;
	range = 1000.0f;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::map;
	objectName = locationName;
	colliderManager->setTarget(gameObject);
	colliderManager->setCollider(0);
	xMark = GameObject::Find(S("travel_target"))->GetComponent<MapXController>();
	oMark = GameObject::Find(S("travel_home"))->GetComponent<MapOController>();
}

void TravelAgency::renderRoute(P<Sprite> spr, bool red)
{
	if (spr == nullptr)
	{
		routeRenderer->set_sprite(nullptr);
		return;
	}
	if (red)
	{
		routeRenderer->set_color(Color(0.65f, 0.0f, 0.0f, 1.0f));
		xMark->GetComponent<SpriteRenderer>()->set_color(Color(0.65f, 0.0f, 0.0f, 1.0f));
		oMark->GetComponent<SpriteRenderer>()->set_color(Color(0.65f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		routeRenderer->set_color(Color(0.0f, 1.0f / 17.0f, 104.0f / 255.0f, 1.0f));
		xMark->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 1.0f / 17.0f, 104.0f / 255.0f, 1.0f));
		oMark->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 1.0f / 17.0f, 104.0f / 255.0f, 1.0f));
	}
	if (GameDataController::gd->getObjective(S("car_travel")))
	{
		xMark->GetComponent<SpriteRenderer>()->set_sprite(xMark->GetComponent<MapXController>()->targetCar);
	}
	else
	{
		xMark->GetComponent<SpriteRenderer>()->set_sprite(xMark->GetComponent<MapXController>()->target);
	}
	routeRenderer->set_sprite(spr);
}

void TravelAgency::travel(List<P<TravelAgency>> travelNodes)
{
	if (travelNodes.IndexOf(P<TravelAgency>(this)) != -1)
	{
		return;
	}
	travelNodes.Add(P<TravelAgency>(this));
	if (oMark->currentTravelAgency == P<TravelAgency>(this))
	{
		travelNodes[0]->addRoute(travelNodes);
		return;
	}
	for (int i = 0; i < nodes.Count(); i++)
	{
		List<P<TravelAgency>> list = List<P<TravelAgency>>::New();
		for (int j = 0; j < travelNodes.Count(); j++)
		{
			list.Add(travelNodes[j]);
		}
		nodes[i]->travel(list);
	}
}

void TravelAgency::addRoute(List<P<TravelAgency>> ta)
{
	if (routes == nullptr)
	{
		routes = List<List<P<TravelAgency>>>::New();
	}
	routes.Add(ta);
}

void TravelAgency::mouseOver()
{
	if (PlayerController::wc->busy)
	{
		return;
	}
	hoverThis = true;
	oMark->clearRoutes();
	xMark->updateLocation(P<TravelAgency>(this));
	routes = nullptr;
	travel(List<P<TravelAgency>>::New());
	int index = 0;
	int num = 9999999;
	for (int i = 0; i < routes.Count(); i++)
	{
		int num2 = 0;
		for (int j = 0; j < routes[i].Count() - 1; j++)
		{
			num2 += routes[i][j]->travelTimes[routes[i][j]->nodes.IndexOf(routes[i][j + 1])];
		}
		if (num2 < num)
		{
			num = num2;
			index = i;
		}
	}
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	if (routes == nullptr)
	{
		return;
	}
	fuel = num;
	if (GameDataController::gd->getObjective(S("barry_improved_car")))
	{
		fuel = (int)Mathf::Ceil((float)fuel * 0.6f);
	}
	for (int k = 0; k < routes[index].Count() - 1; k++)
	{
		bool red = false;
		if (GameDataController::gd->getObjective(S("car_travel")) && num > fc->checkFuel())
		{
			red = true;
			r = 1.0f;
			g = 0.0f;
			b = 0.0f;
		}
		routes[index][k]->renderRoute(routes[index][k]->travelDots[routes[index][k]->nodes.IndexOf(routes[index][k + 1])], red);
		fastestRoute = routes[index];
	}
	String key = S("travel_time");
	if (GameDataController::gd->getObjective(S("car_travel")))
	{
		key = S("ride_time");
		fc->updateFuelMeter();
		fc->updateFuelMissingMeter(fuel);
		if (num != 0)
		{
			num /= 5;
			num++;
		}
		else
		{
			fc->hideFuelMissingMeter();
		}
	}
	String prefixedShort = GameStrings::getPrefixedShort(dkvs, objectName, true);
	String text = prefixedShort;
	prefixedShort = text + S(". ^") + GameStrings::getString(GameStrings::gui, key) + S(" ") + num + S(" ") + GameStrings::getString(GameStrings::gui, S("minutes")) + S(".");
	if (GameDataController::gd->getObjective(S("car_travel")))
	{
		float num3 = Mathf::Round(100.0f * fc->getPercent()) - Mathf::Round(100.0f * fc->getPercent(fuel));
		text = prefixedShort;
		prefixedShort = text + S(" ^") + GameStrings::getString(GameStrings::gui, S("fuel_used")) + S(": ") + num3 + S(" %");
		if (fuel > fc->checkFuel())
		{
			prefixedShort = prefixedShort + S(" [") + GameStrings::getString(GameStrings::gui, S("not_enough_fuel")) + S("]");
		}
	}
	textfield->viewText(prefixedShort, false, true, false, ObjectActionController::BOTTOM_TEXT_WIDTH, r, g, b);
	topText->updateTime();
	calculatedTime = num;
}

void TravelAgency::mouseOut()
{
	if (!PlayerController::wc->busy || colliderManager->currentColider->get_pathCount() == 0)
	{
		hoverThis = false;
		fc->hideFuelMissingMeter();
		xMark->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 1.0f / 17.0f, 104.0f / 255.0f, 1.0f));
		oMark->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 1.0f / 17.0f, 104.0f / 255.0f, 1.0f));
		oMark->clearRoutes();
	}
}

void TravelAgency::updateState()
{
	setCollider(-1);
	if (GameDataController::gd->getObjectiveDetail(unlockingDataRefName) == LOCATION_STATUS_REACHABLE && !GameDataController::gd->getObjective(unlockingDataRefName))
	{
		changeLocationIcon(S("iconGrayed"), S("iconOn"));
		setCollider(0);
	}
	else if (GameDataController::gd->getObjectiveDetail(unlockingDataRefName) == LOCATION_STATUS_UNREACHABLE && !GameDataController::gd->getObjective(unlockingDataRefName))
	{
		changeLocationIcon(S("iconOff"), S("iconGrayed"));
		setCollider(-1);
	}
	else if (GameDataController::gd->getObjectiveDetail(unlockingDataRefName) == LOCATION_STATUS_REACHABLE)
	{
		iconOn();
		setCollider(0);
	}
	else if (GameDataController::gd->getObjectiveDetail(unlockingDataRefName) == LOCATION_STATUS_UNREACHABLE)
	{
		iconGrayed();
		setCollider(-1);
	}
	else if (GameDataController::gd->getObjectiveDetail(unlockingDataRefName) == LOCATION_STATUS_UNDISCOVERED)
	{
		iconOff();
		setCollider(-1);
	}
	if (GameDataController::gd->getObjective(S("just_visiting_map")))
	{
		setCollider(-1);
	}
}

void TravelAgency::changeLocationIcon(String a, String b)
{
	GameDataController::gd->setObjective(unlockingDataRefName, true);
	PlayerController::pc->setBusy(true);
	Invoke(b, 0.0f);
	Invoke(a, 0.55f);
	Invoke(b, 0.85f);
	Invoke(a, 1.15f);
	Invoke(b, 1.45f);
	Invoke(a, 1.75f);
	Invoke(b, 2.05f);
	Invoke(S("unlockGame"), 2.05f);
}

void TravelAgency::revealThisLocation()
{
	GameDataController::gd->setObjective(unlockingDataRefName, true);
	iconOn();
	PlayerController::pc->setBusy(true);
	Invoke(S("iconOff"), 0.3f);
	Invoke(S("iconOn"), 0.6f);
	Invoke(S("iconOff"), 0.9f);
	Invoke(S("iconOn"), 1.2f);
	Invoke(S("iconOff"), 1.5f);
	Invoke(S("iconOn"), 1.8f);
	Invoke(S("unlockGame"), 1.8f);
}

void TravelAgency::unlockGame()
{
	PlayerController::pc->setBusy(false);
	updateAll();
}

void TravelAgency::iconOn()
{
	GetComponent<SpriteRenderer>()->set_color(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
}

void TravelAgency::iconOff()
{
	GetComponent<SpriteRenderer>()->set_color(Vector4(1.0f, 1.0f, 1.0f, 0.0f));
}

void TravelAgency::iconGrayed()
{
	GetComponent<SpriteRenderer>()->set_color(Vector4(1.0f, 1.0f, 1.0f, 0.6f));
}

void TravelAgency::whatOnClick0()
{
}

bool TravelAgency::isOnRoute(String name)
{
	if (fastestRoute != nullptr)
	{
		for (int i = 0; i < fastestRoute.Count(); i++)
		{
			if (fastestRoute[i]->locationName == name)
			{
				return true;
			}
		}
	}
	return false;
}

void TravelAgency::clickAction()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = spawns[0];
	String text = locations[0];
	WalkController::Direction targetDir = facing[0];
	if (GameDataController::gd->getObjective(S("car_travel")) && fuel > fc->checkFuel())
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("travel_no_fuel")), QuestionController::PopupType::STATEMENT);
		return;
	}
	if (locationName == S("map_bridge"))
	{
		if (isOnRoute(S("map_gasstation")) || isOnRoute(S("map_houseb")))
		{
			PlayerController::pc->spawnName = spawns[0];
			GameDataController::gd->setObjective(S("bridge_westside"), true);
			targetDir = facing[0];
		}
		else if (GameDataController::gd->getObjective(S("bridge_westside")))
		{
			PlayerController::pc->spawnName = spawns[0];
			targetDir = facing[0];
		}
		else
		{
			PlayerController::pc->spawnName = spawns[1];
			targetDir = facing[1];
		}
	}
	if (locationName == S("map_base"))
	{
		if (isOnRoute(S("map_bridge")))
		{
			PlayerController::pc->spawnName = spawns[0];
			targetDir = facing[0];
		}
		else
		{
			PlayerController::pc->spawnName = spawns[1];
			targetDir = facing[1];
		}
	}
	if (locationName == S("map_base") && calculatedTime == 0 && !GameDataController::gd->getObjective(S("car_travel")))
	{
		if (GameDataController::gd->getObjective(S("crossroads_left")))
		{
			PlayerController::pc->spawnName = spawns[0];
			targetDir = facing[0];
		}
		else
		{
			PlayerController::pc->spawnName = spawns[1];
			targetDir = facing[1];
		}
	}
	P<AudioClip> sound = nullptr;
	float tSpeed = 0.025f;
	if (GameDataController::gd->getObjective(S("car_travel")) && canIGoThereByCar())
	{
		if (oMark->currentTravelAgency != P<TravelAgency>(this))
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->car_drive2);
			sound = SoundsManagerController::sm->car_close;
			tSpeed = 0.01f;
			GameDataController::gd->setObjective(S("car_driven"), true);
		}
		else
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->car_stop);
			sound = SoundsManagerController::sm->car_close;
		}
		PlayerController::pc->spawnName = S("car");
		targetDir = WalkController::Direction::SE;
		if (text == S("LocationCrossroad"))
		{
			text = S("Barn");
		}
		if (text == S("Barn"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 0);
		}
		if (text == S("LocationBridge"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 1);
		}
		if (text == S("LocationGasstation1"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 2);
		}
		if (text == S("LocationHouseB"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 3);
		}
		if (text == S("LocationCrashsite1"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 4);
		}
		if (text == S("LocationRestaurant1"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 5);
		}
		if (text == S("LocationRV"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 6);
		}
		if (text == S("HuntersLodgeOutside1"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 7);
		}
		if (text == S("SiderealOutside1"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 8);
		}
		if (text == S("CS1"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 9);
		}
		if (text == S("LocationOutpostOutside1"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 10);
		}
		if (text == S("LocationBus1"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 11);
		}
		if (text == S("LocationAirplane1"))
		{
			GameDataController::gd->setObjectiveDetail(S("car_location"), 12);
		}
	}
	if (GameDataController::gd->getObjective(S("car_travel")) && !canIGoThereByCar())
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("car_travel_bridge")), QuestionController::PopupType::QUESTION, [this]() { yesGoToBridgeInstead(); });
	}
	else if (locationName == S("map_restaurant") && GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && !GameDataController::gd->getObjective(S("gasstation_map_warned")) && GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		GameDataController::gd->setObjective(S("gasstation_map_warned"), true);
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("map_gasstation_thugs")), QuestionController::PopupType::QUESTION, [this]() { yesInvestigateGasStation(); }, 0, 0, [this]() { noDoNotInvestigateGasStation(); });
	}
	else if (locationName == S("map_gasstation") && GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && !GameDataController::gd->getObjective(S("gasstation_map_warned")) && GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		GameDataController::gd->setObjective(S("gasstation_map_warned"), true);
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("map_gasstation_soliders")), QuestionController::PopupType::STATEMENT);
	}
	else if (locationName == S("map_outpost") && GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("map_bus_revealed")) == LOCATION_STATUS_UNDISCOVERED)
	{
		GameDataController::gd->setObjectiveDetail(S("map_bus_revealed"), LOCATION_STATUS_REACHABLE);
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("map_bus_investigate")), QuestionController::PopupType::QUESTION, [this]() { yesInvestigateBus(); }, 0, 0, [this]() { noDoNotInvestigateBus(); });
	}
	else if (ClockController::advanceTime(calculatedTime, true))
	{
		if (GameDataController::gd->getObjective(S("car_travel")))
		{
			fc->useFuel(fuel);
		}
		GameDataController::gd->setObjective(S("car_travel"), false);
		CurtainController::cc->fadeOut(text, targetDir, nullptr, sound, false, nullptr, tSpeed);
	}
}

void TravelAgency::yesInvestigateGasStation()
{
	GameObject::Find(S("map_gasstation"))->GetComponent<TravelAgency>()->mouseOver();
	GameObject::Find(S("map_gasstation"))->GetComponent<TravelAgency>()->clickAction();
}

void TravelAgency::yesInvestigateBus()
{
	GameObject::Find(S("map_bus"))->GetComponent<TravelAgency>()->mouseOver();
	GameObject::Find(S("map_bus"))->GetComponent<TravelAgency>()->clickAction();
}

void TravelAgency::noDoNotInvestigateGasStation()
{
	GameObject::Find(S("map_restaurant"))->GetComponent<TravelAgency>()->mouseOver();
	GameObject::Find(S("map_restaurant"))->GetComponent<TravelAgency>()->clickAction();
}

void TravelAgency::noDoNotInvestigateBus()
{
	GameObject::Find(S("map_outpost"))->GetComponent<TravelAgency>()->mouseOver();
	GameObject::Find(S("map_outpost"))->GetComponent<TravelAgency>()->clickAction();
}

void TravelAgency::yesGoToSiderealOnFoot()
{
	if (GameDataController::gd->getObjectiveDetail(S("car_location")) == 6)
	{
		ClockController::advanceTime(60, true);
	}
	else
	{
		ClockController::advanceTime(55, true);
	}
	GameDataController::gd->setObjectiveDetail(S("car_location"), 1);
	GameDataController::gd->setObjective(S("car_travel"), false);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->car_drive2);
	CurtainController::cc->fadeOut(S("SiderealOutside1"), WalkController::Direction::N, nullptr, nullptr, false, nullptr, 0.025f);
}

void TravelAgency::yesGoToBridgeInstead()
{
	GameObject::Find(S("map_bridge"))->GetComponent<TravelAgency>()->mouseOver();
	GameObject::Find(S("map_bridge"))->GetComponent<TravelAgency>()->clickAction();
}

void TravelAgency::clickAction2()
{
}

void TravelAgency::clickAction0()
{
}

bool TravelAgency::canIGoThereByCar()
{
	if ((locationName == S("map_gasstation") || locationName == S("map_houseb") || locationName == S("map_restaurant") || locationName == S("map_sidereal") || locationName == S("map_construction")) && !GameDataController::gd->getObjective(S("bridge_planks_used_2")))
	{
		return false;
	}
	return true;
}
