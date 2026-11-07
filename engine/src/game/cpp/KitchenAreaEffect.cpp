#include "../game_all.h"

void KitchenAreaEffect::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	float num = 0.5f;
	if (GameDataController::gd->getObjective(S("location02_door_open")))
	{
		num = 1.0f;
	}
	if (wc != nullptr)
	{
		wc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(num, num, num));
	}
	if (npcwc != nullptr)
	{
		npcwc->colorBlue = num;
		npcwc->colorRed = num;
		npcwc->colorGreen = num;
		npcwc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(npcwc->colorRed, npcwc->colorGreen, npcwc->colorBlue, npcwc->colorAlpha));
	}
	if (gic != nullptr)
	{
		gic->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(num, num, num));
	}
}

void KitchenAreaEffect::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		wc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f));
	}
	if (npcwc != nullptr)
	{
		npcwc->colorBlue = 1.0f;
		npcwc->colorRed = 1.0f;
		npcwc->colorGreen = 1.0f;
		npcwc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(npcwc->colorRed, npcwc->colorGreen, npcwc->colorBlue, npcwc->colorAlpha));
	}
	if (gic != nullptr)
	{
		gic->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f));
	}
}
