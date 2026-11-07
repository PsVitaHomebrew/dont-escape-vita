#include "../game_all.h"

void LocationSiderealRoofArea::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (wc != nullptr && GameDataController::gd->getObjectiveDetail(S("sidereal_roof_collapsed")) == 0)
	{
		lf->prepare();
		GameDataController::gd->setObjectiveDetail(S("sidereal_roof_collapsed"), 1);
	}
}

void LocationSiderealRoofArea::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
