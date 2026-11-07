#include "../game_all.h"

void TutorialFenceArea1::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		wc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.7f, 0.7f, 0.7f));
	}
	if (npcwc != nullptr)
	{
		npcwc->colorBlue = 0.7f;
		npcwc->colorRed = 0.7f;
		npcwc->colorGreen = 0.7f;
		npcwc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(npcwc->colorRed, npcwc->colorGreen, npcwc->colorBlue, npcwc->colorAlpha));
	}
	if (gic != nullptr)
	{
		gic->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.7f, 0.7f, 0.7f));
	}
}

void TutorialFenceArea1::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
