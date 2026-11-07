#include "../game_all.h"

void MapLocationStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -5.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("none"));
	MonoBehaviour::print(S("............................. LOCATION INFO  .................................."));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	GameDataController::gd->setObjective(S("dialogue_ginger_barry_distracted"), false);
	GameDataController::gd->setObjectiveDetail(S("dialogue_ginger_barry_distracted"), 0);
	int num = 2;
	num += (int)(2.0f * (InventoryController::ic->getCurrentWeight() / 5.0f));
	if (GameDataController::gd->getObjective(S("bridge_westside")) && !GameDataController::gd->getObjective(S("bridge_planks_used_1")))
	{
		GameObject::Find(S("map_gasstation"))->GetComponent<TravelAgency>()->travelTimes[0] = 10;
		GameObject::Find(S("map_base"))->GetComponent<TravelAgency>()->travelTimes[1] = 15 + num;
	}
	else if (!GameDataController::gd->getObjective(S("bridge_planks_used_1")))
	{
		GameObject::Find(S("map_gasstation"))->GetComponent<TravelAgency>()->travelTimes[0] = 10 + num;
		GameObject::Find(S("map_base"))->GetComponent<TravelAgency>()->travelTimes[1] = 15;
	}
	else
	{
		GameObject::Find(S("map_gasstation"))->GetComponent<TravelAgency>()->travelTimes[0] = 10;
		GameObject::Find(S("map_base"))->GetComponent<TravelAgency>()->travelTimes[1] = 15;
	}
	GameObject::Find(S("Fuel"))->GetComponent<FuelController>()->updateFuelMeter();
	GameObject::Find(S("Fuel"))->GetComponent<FuelController>()->hideFuelMissingMeter();
	if (!GameDataController::gd->getObjective(S("car_travel")))
	{
		GameObject::Find(S("Fuel"))->transform->Find(S("reserves"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Fuel"))->transform->Find(S("back"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Fuel"))->transform->Find(S("fuel"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("percent"))->GetComponent<TextFieldController>()->keepAlive = false;
		GameObject::Find(S("percent"))->GetComponent<TextFieldController>()->dissmiss(true);
	}
}

void MapLocationStart::Update()
{
}
