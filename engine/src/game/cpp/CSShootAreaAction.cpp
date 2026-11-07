#include "../game_all.h"

void CSShootAreaAction::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		exitcs1->doubleClickCondition = String::Empty;
		exitcs3->doubleClickCondition = String::Empty;
		cs2->shootArea = true;
	}
	if (npcwc != nullptr)
	{
	}
	if (!(gic != nullptr))
	{
	}
}

void CSShootAreaAction::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		cs2->shootArea = false;
	}
}
