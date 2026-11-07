#include "../game_all.h"

void LocationBridge2::Start()
{
	dkvs = GameStrings::objects;
	objectName = String::Empty;
}

void LocationBridge2::clickAction()
{
}

void LocationBridge2::updateState()
{
	if (!GameDataController::gd->getObjective(S("bridge_planks_used_2")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void LocationBridge2::clickAction2()
{
}

void LocationBridge2::clickAction0()
{
}
