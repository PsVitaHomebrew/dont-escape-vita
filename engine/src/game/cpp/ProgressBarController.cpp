#include "../game_all.h"

void ProgressBarController::Start()
{
	sr = gameObject->transform->Find(S("bar"))->GetComponent<SpriteRenderer>();
	bar = gameObject->transform->Find(S("bar"))->gameObject;
	lifeLine = gameObject->transform->Find(S("LifeLine"))->gameObject;
	tf = gameObject->GetComponent<TextFieldController>();
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/progressbar_frame")));
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_bugs")));
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/progressbar_frame_gas")));
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_gas")));
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/progressbar_frame_spiders")));
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_spiders")));
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 2)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_cold_frame")));
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_cold")));
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			if (GameDataController::gd->previousLocation == S("LocationCave"))
			{
				gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_heat2_frame")));
				GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_heat2")));
			}
			else
			{
				gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_heat_frame")));
				GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_heat")));
			}
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 2)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/progressbar_frame_spiders")));
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_spiders")));
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 3)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_d3_0_frame")));
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_d3_0")));
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
		{
			if (GameDataController::gd->getObjective(S("base_outside_dug")))
			{
				gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_storm_b")));
			}
			else
			{
				gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_storm")));
			}
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/background_storm2")));
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 4)
	{
		if (GameDataController::gd->getObjective(S("outpost_hatch_open")))
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/rocket_prelaunchF")));
		}
		else
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/rocket_prelaunchF2")));
		}
		GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/rocket_prelaunch")));
	}
	dayWeFace = GameDataController::gd->getCurrentDay();
}

void ProgressBarController::Update()
{
	delay += Time::get_deltaTime();
	if (delay < 0.0166f)
	{
		return;
	}
	delay = 0.0f;
	bool updateText = false;
	if (visibleCurrent < current)
	{
		if (current - visibleCurrent >= 100)
		{
			visibleCurrent += 10;
		}
		else if (current - visibleCurrent >= 10)
		{
			visibleCurrent += 2;
		}
		else
		{
			visibleCurrent++;
		}
		updateText = true;
	}
	else if (visibleCurrent > current)
	{
		if (visibleCurrent - current >= 100)
		{
			visibleCurrent -= 10;
		}
		else if (visibleCurrent - current >= 10)
		{
			visibleCurrent -= 2;
		}
		else
		{
			visibleCurrent--;
		}
		updateText = true;
	}
	percent = (float)visibleCurrent / (float)total;
	updateView(updateText);
}

void ProgressBarController::setValue(int target)
{
	current = target;
}

void ProgressBarController::updateView(bool updateText)
{
	if (updateText)
	{
		tf->shift = Vector2(0.0f, 47.0f);
		tf->center = true;
		String key = String::Empty;
		if (dayWeFace == 1)
		{
			if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
			{
				key = S("bugs_sufix");
			}
			if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
			{
				key = S("gas_sufix");
			}
			if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
			{
				key = S("spiders_sufix");
			}
		}
		else if (dayWeFace == 2)
		{
			if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
			{
				key = S("cold_sufix");
			}
			if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
			{
				key = S("hot_sufix");
			}
		}
		else if (dayWeFace == 3)
		{
			if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
			{
				key = S("bandits_sufix");
			}
			if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
			{
				key = S("rain_sufix");
			}
		}
		else if (dayWeFace == 4)
		{
			if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
			{
				key = S("air_sufix");
			}
			if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1)
			{
				key = S("fuel_sufix");
			}
		}
		tf->viewText(visibleCurrent + S(" ") + GameStrings::getString(GameStrings::results, key), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f, true);
		tf->keepAlive = true;
	}
	Vector3 vector = coords(Vector2(Mathf::Floor(-200.0f + percent * 200.0f), 0.0f));
	float num = surv / (float)total;
	Vector3 vector2 = coords(Vector2(Mathf::Floor(num * 200.0f), 0.0f));
	bar->transform->set_position(Vector3(vector.x, vector.y, bar->transform->get_position().z));
	lifeLine->transform->set_position(Vector3(vector2.x, vector2.y, lifeLine->transform->get_position().z));
}

Vector3 ProgressBarController::coords(Vector2 source)
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2(source.x, source.y));
	Vector3 result = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	Vector2 vector2 = ScreenControler::gameToScreen(Vector2(0.0f, 0.0f));
	Vector3 vector3 = Camera::get_main()->ScreenToWorldPoint(Vector3(vector2.x, vector2.y, 0.0f));
	result.x -= vector3.x;
	result.y -= vector3.y;
	return result;
}
