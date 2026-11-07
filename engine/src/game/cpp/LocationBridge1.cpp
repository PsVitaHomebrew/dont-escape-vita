#include "../game_all.h"

void LocationBridge1::Start()
{
	dkvs = GameStrings::objects;
	objectName = String::Empty;
}

void LocationBridge1::clickAction()
{
}

void LocationBridge1::updateState()
{
	if (!GameDataController::gd->getObjective(S("bridge_planks_used_1")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void LocationBridge1::clickAction2()
{
}

void LocationBridge1::clickAction0()
{
}
