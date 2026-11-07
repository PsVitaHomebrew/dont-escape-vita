#include "../game_all.h"

void OutpostOutsideHatch::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = true;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_hatch_open");
	range = 111.0f;
}

void OutpostOutsideHatch::clickAction()
{
	if (GameDataController::gd->getObjective(S("outpost_hatch_open")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_hatch_open")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_hatch_closed")));
	}
}

void OutpostOutsideHatch::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_hatch_open")))
	{
		objectName = S("outpost_hatch_open");
		sr1->set_enabled(true);
		sr2->set_enabled(true);
		interactions = List<P<ItemInteraction>>::New();
	}
	else
	{
		sr1->set_enabled(false);
		sr2->set_enabled(false);
		objectName = S("outpost_hatch_closed");
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("shovel"), GameStrings::getString(GameStrings::actions, S("outpost_hatch_shovel")), nullptr, String::Empty));
	}
}

void OutpostOutsideHatch::clickAction2()
{
}

void OutpostOutsideHatch::clickAction0()
{
}

void OutpostOutsideHatch::whatOnClick0()
{
}

void OutpostOutsideHatch::whatOnClick()
{
}
