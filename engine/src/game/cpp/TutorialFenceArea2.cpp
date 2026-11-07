#include "../game_all.h"

void TutorialFenceArea2::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		wc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.3f, 0.3f, 0.3f));
	}
	if (npcwc != nullptr)
	{
		npcwc->colorBlue = 0.3f;
		npcwc->colorRed = 0.3f;
		npcwc->colorGreen = 0.3f;
		npcwc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(npcwc->colorRed, npcwc->colorGreen, npcwc->colorBlue, npcwc->colorAlpha));
	}
	if (gic != nullptr)
	{
		gic->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.3f, 0.3f, 0.3f));
	}
}

void TutorialFenceArea2::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
