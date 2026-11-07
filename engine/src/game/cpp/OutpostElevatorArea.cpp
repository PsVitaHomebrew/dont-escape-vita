#include "../game_all.h"

void OutpostElevatorArea::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::pc->allowDrop = false;
	}
}

void OutpostElevatorArea::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr)
	{
		PlayerController::pc->allowDrop = true;
	}
}
