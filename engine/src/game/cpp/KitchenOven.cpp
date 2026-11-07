#include "../game_all.h"

void KitchenOven::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("kitchen_oven");
	range = 1.0f;
	updateState();
}

void KitchenOven::Update()
{
	if (GameDataController::gd->getObjective(S("kitchen_oven_open")) && lightAlfa < 1.0f && GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
	{
		lightAlfa += Time::get_deltaTime() * 2.0f;
	}
	if ((lightAlfa > 0.0f && (!GameDataController::gd->getObjective(S("barn_pump_started")) || GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 1)) || !GameDataController::gd->getObjective(S("kitchen_oven_open")))
	{
		lightAlfa -= Time::get_deltaTime() * 2.0f;
	}
	if (lightAlfa < 0.0f)
	{
		lightAlfa = 0.0f;
	}
	if (lightAlfa > 1.0f)
	{
		lightAlfa = 1.0f;
	}
	ovenLight->set_color(Color(1.0f, 1.0f, 1.0f, lightAlfa));
}

void KitchenOven::clickAction()
{
	GameDataController::gd->setObjective(S("kitchen_oven_open"), !GameDataController::gd->getObjective(S("kitchen_oven_open")));
	updateAll();
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->trunk_open);
	if (GameDataController::gd->getObjective(S("kitchen_oven_open")))
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("kitchen_oven_open"));
		Timeline::t->addAction(timelineAction);
		if (!GameDataController::gd->getObjective(S("barn_pump_started")) || GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 1)
		{
			timelineAction = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("kitchen_oven_off"));
			Timeline::t->addAction(timelineAction);
			return;
		}
		timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("kitchen_oven_on"));
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getCurrentDay() == 1)
		{
			timelineAction = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("kitchen_oven_nogood"));
			Timeline::t->addAction(timelineAction);
		}
	}
	else
	{
		P<TimelineAction> timelineAction2 = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction2->text = GameStrings::getString(GameStrings::actions, S("kitchen_oven_close"));
		Timeline::t->addAction(timelineAction2);
	}
}

void KitchenOven::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("kitchen_oven_open")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
		{
			GetComponent<SpriteRenderer>()->set_sprite(dark);
			ovenLight->set_enabled(true);
			objectName = S("kitchen_oven_hot");
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_sprite(dark);
			ovenLight->set_enabled(false);
			objectName = S("kitchen_oven");
		}
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		ovenLight->set_enabled(false);
		objectName = S("kitchen_oven");
	}
}

void KitchenOven::clickAction2()
{
}

void KitchenOven::clickAction0()
{
}

void KitchenOven::whatOnClick0()
{
}

void KitchenOven::whatOnClick()
{
}
