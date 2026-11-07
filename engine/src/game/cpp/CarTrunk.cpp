#include "../game_all.h"

void CarTrunk::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("car_trunk");
	range = 2.0f;
	allowAllItems = true;
	updateState();
}

void CarTrunk::Update()
{
	if (InventoryButtonController::ibc->justClosed)
	{
		timeToOpenAgain += Time::get_deltaTime();
		if (timeToOpenAgain >= 0.25f)
		{
			InventoryButtonController::ibc->justClosed = false;
			timeToOpenAgain = 0.0f;
		}
	}
	if (actionMarker1 != nullptr && actionMarker2 != nullptr)
	{
		if (PlayerController::wc->currentXY.y < 30.0f)
		{
			actionMarker = actionMarker1;
		}
		else
		{
			actionMarker = actionMarker2;
		}
	}
}

void CarTrunk::clickAction()
{
	if (InventoryButtonController::ibc->justClosed)
	{
		return;
	}
	if (usedItem == String::Empty)
	{
		if (!InventoryButtonController::ibc->isItOpen())
		{
			InventoryButtonController::ibc->openTrunk();
		}
		else
		{
			InventoryButtonController::ibc->close();
		}
	}
	else if (ItemsManager::im->getItem(usedItem)->weight >= 0.0f)
	{
		InventoryController::ic->putItemInTrunk(usedItem);
	}
}

void CarTrunk::updateState()
{
	colliderManager->setCollider(0);
	if ((GameDataController::gd->getObjectiveDetail(S("car_location")) == 0 && SceneManager::GetActiveScene().get_name() == S("Barn")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 1 && SceneManager::GetActiveScene().get_name() == S("LocationBridge")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 2 && SceneManager::GetActiveScene().get_name() == S("LocationGasstation1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 3 && SceneManager::GetActiveScene().get_name() == S("LocationHouseB")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 4 && SceneManager::GetActiveScene().get_name() == S("LocationCrashsite1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 5 && SceneManager::GetActiveScene().get_name() == S("LocationRestaurant1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 6 && SceneManager::GetActiveScene().get_name() == S("LocationRV")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 7 && SceneManager::GetActiveScene().get_name() == S("HuntersLodgeOutside1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 8 && SceneManager::GetActiveScene().get_name() == S("SiderealOutside1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 9 && SceneManager::GetActiveScene().get_name() == S("CS1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 10 && SceneManager::GetActiveScene().get_name() == S("LocationOutpostOutside1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 11 && SceneManager::GetActiveScene().get_name() == S("LocationBus1")) || (GameDataController::gd->getObjectiveDetail(S("car_location")) == 12 && SceneManager::GetActiveScene().get_name() == S("LocationAirplane1")))
	{
		colliderManager->setCollider(0);
	}
	else
	{
		colliderManager->setCollider(-1);
	}
}

void CarTrunk::clickAction2()
{
}

void CarTrunk::clickAction0()
{
}

void CarTrunk::whatOnClick0()
{
}

void CarTrunk::whatOnClick()
{
}
