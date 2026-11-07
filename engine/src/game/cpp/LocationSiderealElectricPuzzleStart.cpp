#include "../game_all.h"

void LocationSiderealElectricPuzzleStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -5.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("none"));
	PlayerController::pc->copySettingsToNPCs();
	MonoBehaviour::print(S("............................. LOCATION INFO  .................................."));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->esc = GameObject::Find(S("ElectricExit"))->GetComponent<LocationElectricExit>();
	failsafe = false;
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) == 50 && GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) == 10)
	{
		s1->set_enabled(false);
		s2->set_enabled(false);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->buzz, 0.65f);
	}
	else
	{
		s1->set_enabled(true);
		s2->set_enabled(true);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
	}
	GameObject::Find(S("ButtonReset"))->GetComponent<Button>()->initButton(GameStrings::getString(GameStrings::world_labels, S("generic_reset")));
	GameObject::Find(S("ButtonReset"))->GetComponent<Button>()->onClick = [this]() { onclick(); };
	updateManual();
	GameObject::Find(S("Pin_A1"))->GetComponent<Electric_Pin>()->startWithCheck();
	GameObject::Find(S("Pin_B2"))->GetComponent<Electric_Pin>()->startWithCheck();
	butbut->showOrNot();
}

void LocationSiderealElectricPuzzleStart::onclick()
{
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_a1"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_a2"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_b1"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_b2"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_b3"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_c1"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_c2"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_d1"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_d2"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_d3"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_d4"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_e1"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_e2"), 0);
	GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_e3"), 0);
	GameObject::Find(S("Pin_A1"))->GetComponent<Electric_Pin>()->startWithCheck();
	GameObject::Find(S("Pin_B2"))->GetComponent<Electric_Pin>()->startWithCheck();
}

void LocationSiderealElectricPuzzleStart::updateManual()
{
	if (CursorController::cc->selectedItemRef == nullptr)
	{
		easycome = true;
		for (int i = 0; i <= 13; i++)
		{
			String text = String::Empty;
			if (i == 0)
			{
				text = S("sidereal_electric_pin_a1");
			}
			if (i == 1)
			{
				text = S("sidereal_electric_pin_a2");
			}
			if (i == 2)
			{
				text = S("sidereal_electric_pin_b1");
			}
			if (i == 3)
			{
				text = S("sidereal_electric_pin_b2");
			}
			if (i == 4)
			{
				text = S("sidereal_electric_pin_b3");
			}
			if (i == 5)
			{
				text = S("sidereal_electric_pin_c1");
			}
			if (i == 6)
			{
				text = S("sidereal_electric_pin_c2");
			}
			if (i == 7)
			{
				text = S("sidereal_electric_pin_d1");
			}
			if (i == 8)
			{
				text = S("sidereal_electric_pin_d2");
			}
			if (i == 9)
			{
				text = S("sidereal_electric_pin_d3");
			}
			if (i == 10)
			{
				text = S("sidereal_electric_pin_d4");
			}
			if (i == 11)
			{
				text = S("sidereal_electric_pin_e1");
			}
			if (i == 12)
			{
				text = S("sidereal_electric_pin_e2");
			}
			if (i == 13)
			{
				text = S("sidereal_electric_pin_e3");
			}
			String id = text;
			if (GameDataController::gd->getObjective(id))
			{
				if (GameDataController::gd->getObjectiveDetail(id) == -1)
				{
					GameDataController::gd->setObjectiveDetail(id, 0);
				}
				if (GameDataController::gd->getObjectiveDetail(id) == 0)
				{
					easycome = false;
				}
			}
		}
		if (GameObject::Find(S("Pin_A1")) != nullptr)
		{
			GameObject::Find(S("Pin_A1"))->GetComponent<Electric_Pin>()->updateAll();
		}
	}
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) == 50 && GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) == 10)
	{
		if (s1->get_enabled())
		{
			s1->set_enabled(false);
			s2->set_enabled(false);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->neon_on);
			JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->buzz, 0.65f);
		}
	}
	else if (!s1->get_enabled())
	{
		s1->set_enabled(true);
		s2->set_enabled(true);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->neon_off);
	}
	Invoke(S("updateManual"), 0.1f);
}

void LocationSiderealElectricPuzzleStart::Update()
{
}
