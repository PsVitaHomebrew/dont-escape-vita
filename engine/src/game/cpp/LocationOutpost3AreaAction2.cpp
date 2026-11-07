#include "../game_all.h"

void LocationOutpost3AreaAction2::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		wc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.6f, 0.6f, 0.6f));
	}
	if (npcwc != nullptr)
	{
		npcwc->colorBlue = 0.6f;
		npcwc->colorRed = 0.6f;
		npcwc->colorGreen = 0.6f;
		npcwc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(npcwc->colorRed, npcwc->colorGreen, npcwc->colorBlue, npcwc->colorAlpha));
	}
	if (gic != nullptr)
	{
		gic->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.6f, 0.6f, 0.6f));
	}
}

void LocationOutpost3AreaAction2::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		wc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.4f, 0.4f, 0.4f));
	}
	if (npcwc != nullptr)
	{
		npcwc->colorBlue = 0.4f;
		npcwc->colorRed = 0.4f;
		npcwc->colorGreen = 0.4f;
		npcwc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(npcwc->colorRed, npcwc->colorGreen, npcwc->colorBlue, npcwc->colorAlpha));
	}
	if (gic != nullptr)
	{
		gic->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.4f, 0.4f, 0.4f));
	}
}
