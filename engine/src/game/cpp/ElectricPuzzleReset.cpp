#include "../game_all.h"

void ElectricPuzzleReset::Start()
{
}

void ElectricPuzzleReset::Update()
{
}

void ElectricPuzzleReset::showOrNot()
{
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_a1")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_a2")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_b1")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_b2")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_b3")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_c1")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_c2")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_d1")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_d2")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_d3")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_d4")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_e1")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_e2")) > 0 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_e3")) > 0)
	{
		MonoBehaviour::print(S("SHOWING RESET"));
		butbut->buttonEnabled = true;
		butbut->initButton(GameStrings::getString(GameStrings::world_labels, S("generic_reset")));
		butbut->gameObject->SetActive(true);
	}
	else
	{
		butbut->buttonEnabled = false;
		butbut->buttonText->dissmiss(true);
		butbut->gameObject->SetActive(false);
	}
}
