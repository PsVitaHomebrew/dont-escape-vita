#include "../game_all.h"

void rv_body1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_body1_gas");
	range = 1.0f;
}

void rv_body1::clickAction()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_body1")));
}

void rv_body1::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getCurrentDay() < 3)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			objectName = S("rv_body1_bugs");
			GetComponent<SpriteRenderer>()->set_sprite(bugs);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			objectName = S("rv_body1_gas");
			GetComponent<SpriteRenderer>()->set_sprite(gas);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			objectName = S("rv_body1_spiders");
			GetComponent<SpriteRenderer>()->set_sprite(spiders);
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 3)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			objectName = S("rv_body1_hot");
			GetComponent<SpriteRenderer>()->set_sprite(heat);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			objectName = S("rv_body1_cold");
			GetComponent<SpriteRenderer>()->set_sprite(ice);
		}
	}
	else
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_sprite(gone);
	}
}

void rv_body1::clickAction2()
{
}

void rv_body1::clickAction0()
{
}

void rv_body1::whatOnClick0()
{
}

void rv_body1::whatOnClick()
{
}
