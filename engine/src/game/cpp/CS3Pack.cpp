#include "../game_all.h"

void CS3Pack::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_pack");
	range = 30.0f;
	updateState();
}

void CS3Pack::Update()
{
}

void CS3Pack::clickAction()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_pack")));
}

void CS3Pack::updateState()
{
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	objectName = S("cs_pack");
	range = 30.0f;
	if (GameDataController::gd->getObjective(S("cs_rain_enter_left")))
	{
		actionMarker = marker1;
		zmarker1->GetComponent<ObjectZController>()->set_enabled(true);
		zmarker2->GetComponent<ObjectZController>()->set_enabled(false);
	}
	else
	{
		actionMarker = marker2;
		zmarker1->GetComponent<ObjectZController>()->set_enabled(false);
		zmarker2->GetComponent<ObjectZController>()->set_enabled(true);
	}
	setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	pack_hang->set_enabled(false);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 1)
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
		hook->set_enabled(false);
		return;
	}
	if (GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		setCollider(-1);
		pack_hang->set_enabled(true);
		GetComponent<SpriteRenderer>()->set_enabled(false);
		hook->set_enabled(false);
		return;
	}
	setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	GetComponent<SpriteRenderer>()->set_sprite(pack);
	if (GameDataController::gd->getObjective(S("cs_crane_down")))
	{
		hook->set_enabled(true);
		if (!GameDataController::gd->getObjective(S("cs_crane_left")) && GameDataController::gd->getObjective(S("cs_crane_closed")))
		{
			hook->set_sprite(hook1b);
		}
		else if (!GameDataController::gd->getObjective(S("cs_crane_left")) && !GameDataController::gd->getObjective(S("cs_crane_closed")))
		{
			hook->set_sprite(hook1a);
		}
		else if (GameDataController::gd->getObjective(S("cs_crane_left")) && !GameDataController::gd->getObjective(S("cs_crane_closed")))
		{
			hook->set_sprite(hook2a);
		}
		else if (GameDataController::gd->getObjective(S("cs_crane_left")) && GameDataController::gd->getObjective(S("cs_crane_closed")))
		{
			hook->set_sprite(hook2b);
		}
	}
	else
	{
		hook->set_enabled(false);
	}
}

void CS3Pack::clickAction2()
{
}

void CS3Pack::clickAction0()
{
}

void CS3Pack::whatOnClick0()
{
}

void CS3Pack::whatOnClick()
{
}
