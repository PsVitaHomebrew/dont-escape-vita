#include "../game_all.h"

void MapCarLocation::Start()
{
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
	if (!GameDataController::gd->getObjective(S("barn_car_wheel_repaired")) || !GameDataController::gd->getObjective(S("barn_car_coil_repaired")) || !GameDataController::gd->getObjective(S("barn_car_battery_repaired")) || !GameDataController::gd->getObjective(S("barn_car_refueled")))
	{
		hide();
	}
	else
	{
		transform->set_position(ScreenControler::roundToNearestFullPixel2(carLocation[GameDataController::gd->getObjectiveDetail(S("car_location"))]->transform->get_position()));
	}
}

void MapCarLocation::Update()
{
}

void MapCarLocation::hide()
{
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
}
