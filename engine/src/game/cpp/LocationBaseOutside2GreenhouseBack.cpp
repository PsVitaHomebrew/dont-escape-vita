#include "../game_all.h"

void LocationBaseOutside2GreenhouseBack::Start()
{
	sr = gameObject->GetComponent<SpriteRenderer>();
	dkvs = GameStrings::objects;
	objectName = S("kitchen_exit");
}

void LocationBaseOutside2GreenhouseBack::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 4)
	{
		sr->set_sprite(sprite1);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 3)
	{
		sr->set_sprite(sprite2);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 2)
	{
		sr->set_sprite(sprite3);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 1)
	{
		sr->set_sprite(sprite4);
	}
	else if (GameDataController::gd->getObjectiveDetail(S("greenhouse_nails")) == 0)
	{
		sr->set_sprite(sprite5);
	}
}

void LocationBaseOutside2GreenhouseBack::whatOnClick()
{
}

void LocationBaseOutside2GreenhouseBack::clickAction()
{
}

void LocationBaseOutside2GreenhouseBack::restore()
{
}

void LocationBaseOutside2GreenhouseBack::clickAction2()
{
}

void LocationBaseOutside2GreenhouseBack::clickAction0()
{
}
