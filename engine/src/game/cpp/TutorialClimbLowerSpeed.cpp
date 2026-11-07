#include "../game_all.h"

void TutorialClimbLowerSpeed::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		wc->speed = 0.7f * wc->MAX_SPEED;
	}
}

void TutorialClimbLowerSpeed::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
