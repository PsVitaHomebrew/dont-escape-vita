#include "../game_all.h"

void Attic1AreaAction1::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	Color color = Color(0.8f, 0.8f, 0.8f);
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		color = Color(1.0f, 1.0f, 1.0f);
	}
	if (wc != nullptr)
	{
		wc->gameObject->GetComponent<SpriteRenderer>()->set_color(color);
	}
	if (gic != nullptr)
	{
		gic->gameObject->GetComponent<SpriteRenderer>()->set_color(color);
	}
	if (npcwc != nullptr)
	{
		npcwc->colorBlue = color.b;
		npcwc->colorRed = color.r;
		npcwc->colorGreen = color.g;
		npcwc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(npcwc->colorRed, npcwc->colorGreen, npcwc->colorBlue, npcwc->colorAlpha));
	}
}

void Attic1AreaAction1::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
	{
		return;
	}
	if (gic != nullptr)
	{
		if (!GameDataController::gd->getObjective(S("attic_hatch_open")))
		{
			gic->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.3f, 0.3f, 0.3f));
		}
		else
		{
			gic->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.6f, 0.6f, 0.6f));
		}
	}
	if (wc != nullptr)
	{
		if (!GameDataController::gd->getObjective(S("attic_hatch_open")))
		{
			PlayerController::pc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.3f, 0.3f, 0.3f));
		}
		else
		{
			PlayerController::pc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.6f, 0.6f, 0.6f));
		}
	}
	if (!(npcwc != nullptr))
	{
		return;
	}
	if (!GameDataController::gd->getObjective(S("attic_hatch_open")))
	{
		if (npcwc != nullptr)
		{
			npcwc->colorBlue = 0.3f;
			npcwc->colorRed = 0.3f;
			npcwc->colorGreen = 0.3f;
			npcwc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(npcwc->colorRed, npcwc->colorGreen, npcwc->colorBlue, npcwc->colorAlpha));
		}
	}
	else if (npcwc != nullptr)
	{
		npcwc->colorBlue = 0.6f;
		npcwc->colorRed = 0.6f;
		npcwc->colorGreen = 0.6f;
		npcwc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(npcwc->colorRed, npcwc->colorGreen, npcwc->colorBlue, npcwc->colorAlpha));
	}
}
