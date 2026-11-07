#include "../game_all.h"

void TutorialFenceArea3::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
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

void TutorialFenceArea3::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
