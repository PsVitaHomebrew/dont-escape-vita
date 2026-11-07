#include "../game_all.h"

void CrashsiteBodies::Start()
{
	gameObject->transform->Find(S("bodies_gas"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->transform->Find(S("bodies_bugs"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->transform->Find(S("bodies_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->transform->Find(S("remains_a"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->transform->Find(S("remains_b"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->transform->Find(S("remains_c"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		gameObject->transform->Find(S("bodies_bugs"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getCurrentDay() > 1)
		{
			gameObject->transform->Find(S("remains_a"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		gameObject->transform->Find(S("bodies_gas"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getCurrentDay() > 1)
		{
			gameObject->transform->Find(S("remains_b"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		gameObject->transform->Find(S("bodies_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getCurrentDay() > 1)
		{
			gameObject->transform->Find(S("remains_c"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
	}
	if (GameDataController::gd->getCurrentDay() > 1)
	{
		gameObject->transform->Find(S("bodies_gas"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		gameObject->transform->Find(S("bodies_bugs"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		gameObject->transform->Find(S("bodies_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void CrashsiteBodies::Update()
{
}
