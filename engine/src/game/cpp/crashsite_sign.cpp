#include "../game_all.h"

void crashsite_sign::Start()
{
	gameObject->transform->Find(S("pest_control"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->transform->Find(S("chem_control"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->transform->Find(S("spider_control"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		gameObject->transform->Find(S("pest_control"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		gameObject->transform->Find(S("chem_control"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		gameObject->transform->Find(S("spider_control"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void crashsite_sign::Update()
{
}
