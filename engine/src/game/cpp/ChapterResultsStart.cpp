#include "../game_all.h"

void ChapterResultsStart::Start()
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
	Vector3 vector2 = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	vector2.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(vector2);
	GameObject::Find(S("inventory_button"))->transform->set_position(vector2);
	MonoBehaviour::print(String::Concat(S("CHOWAM PLECAK "), vector2.ToString(), S(" VS "), InventoryButtonController::ibc->gameObject->transform->get_position().ToString()));
	Timeline::t->textField->directionY = 1.0f;
	Timeline::t->textField->shift = Vector2(-25.0f, 20.0f);
	Timeline::defaultTwidth = 130;
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			GameObject::Find(S("ResultsController"))->transform->Find(S("ResultsBugs"))->GetComponent<ResultsChapterBugs>()->init();
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			GameObject::Find(S("ResultsController"))->transform->Find(S("ResultsGas"))->GetComponent<ResultsChapterGas>()->init();
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			GameObject::Find(S("ResultsController"))->transform->Find(S("ResultsSpiders"))->GetComponent<ResultsChapterSpiders>()->init();
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 2)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			GameObject::Find(S("ResultsController"))->transform->Find(S("ResultsHot"))->GetComponent<ResultsChapterHot>()->init();
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			GameObject::Find(S("ResultsController"))->transform->Find(S("ResultsCold"))->GetComponent<ResultsChapterCold>()->init();
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 3)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
		{
			GameObject::Find(S("ResultsController"))->transform->Find(S("ResultsBandits"))->GetComponent<ResultsChapterBandits>()->init();
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
		{
			GameObject::Find(S("ResultsController"))->transform->Find(S("ResultsStorm"))->GetComponent<ResultsChapterStorm>()->init();
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 4)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
		{
			GameObject::Find(S("ResultsController"))->transform->Find(S("ResultsShipAir"))->GetComponent<ResultsChapterShipAir>()->init();
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1)
		{
			GameObject::Find(S("ResultsController"))->transform->Find(S("ResultsShipFuel"))->GetComponent<ResultsChapterShipFuel>()->init();
		}
	}
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_attack, true, 0.0f, 0.0f);
	JukeboxAmbient::jb->changeAmbient(nullptr, 0.0f);
}

void ChapterResultsStart::Update()
{
}
