#include "../game_all.h"

int FuelController::checkFuel()
{
	if (!GameDataController::gd->getObjective(S("barn_car_refueled")))
	{
		return 0;
	}
	return GameDataController::gd->getObjectiveDetail(S("barn_car_refueled"));
}

float FuelController::getPercent(int fuelToUse)
{
	float num = (float)checkFuel() - (float)fuelToUse;
	return num / (float)GameDataController::MAX_FUEL;
}

void FuelController::updateFuelMeter()
{
	int num = checkFuel();
	float percent = getPercent();
	int index = Mathf::CeilToInt(percent * (float)(fuelSprites.Count() - 1));
	fuelRenderer->set_sprite(fuelSprites[index]);
	int num2 = Mathf::RoundToInt(percent * 100.0f);
	tfc->viewText(num2 + S("%"), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, true);
	tfc->keepAlive = true;
	tfc->shift.y = 57.0f;
	tfc->shift.x = 93.0f;
	Vector2 vector = ScreenControler::gameToScreen(Vector2(120.0f, 67.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	tfc->transform->set_position(position);
	if (!GameDataController::gd->getObjective(S("car_travel")))
	{
		tfc->viewText(S(" "), false, true, true, 100, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		tfc->dissmiss(true);
	}
}

void FuelController::updateFuelMissingMeter(int fuelToUse)
{
	int num = checkFuel();
	if (fuelToUse > num)
	{
		reservesRenderer->set_enabled(true);
	}
	else
	{
		reservesRenderer->set_enabled(false);
	}
	num -= fuelToUse;
	if (num < 0)
	{
		num = 0;
	}
	float percent = getPercent(fuelToUse);
	int num2 = Mathf::FloorToInt(percent * (float)(missingSprites.Count() - 1));
	if (num2 < 0)
	{
		num2 = 0;
	}
	if (num2 > missingSprites.Count() - 1)
	{
		num2 = missingSprites.Count() - 1;
	}
	missingRenderer->set_sprite(missingSprites[missingSprites.Count() - 1 - num2]);
	MonoBehaviour::print(S("Frame: ") + num2 + S(" | ") + percent + S(" | ") + fuelToUse + S(" : ") + Mathf::RoundToInt(100.0f * ((float)fuelToUse / (float)GameDataController::MAX_FUEL)) + S(" | ") + (float)fuelToUse / (float)GameDataController::MAX_FUEL);
	int num3 = Mathf::RoundToInt(percent * 100.0f);
	if (num3 < 0)
	{
		num3 = 0;
	}
	tfc->viewText(num3 + S("%"), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, false, true);
	if (!GameDataController::gd->getObjective(S("car_travel")))
	{
		tfc->viewText(S(" "), false, true, true, 100, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		tfc->dissmiss(true);
	}
}

void FuelController::hideFuelMissingMeter()
{
	missingRenderer->set_sprite(missingSprites[0]);
	updateFuelMeter();
	reservesRenderer->set_enabled(false);
}

void FuelController::useFuel(int amount)
{
	int num = GameDataController::gd->getObjectiveDetail(S("barn_car_refueled")) - amount;
	if (num < 0)
	{
		num = 0;
	}
	GameDataController::gd->setObjectiveDetail(S("barn_car_refueled"), num);
}

void FuelController::Start()
{
	fuelRenderer->set_color(Color(1.0f, 1.0f, 1.0f, 0.75f));
}

void FuelController::Update()
{
}
