#include "../game_all.h"

void TutorialClimbNormalSpeed::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		wc->speed = wc->MAX_SPEED;
	}
}

void TutorialClimbNormalSpeed::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
