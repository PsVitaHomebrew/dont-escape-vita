#include "../game_all.h"

void TutorialClimbLowSpeed::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		wc->speed = 0.8f * wc->MAX_SPEED;
	}
}

void TutorialClimbLowSpeed::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
