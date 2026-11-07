#include "../game_all.h"

void LocationBaseOutside1Bike::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e_in");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("crashed_bike");
	range = 1.0f;
	dir = 1.0f;
	sr = gameObject->GetComponent<SpriteRenderer>();
}

void LocationBaseOutside1Bike::Update()
{
}

void LocationBaseOutside1Bike::clickAction()
{
	if (!GameDataController::gd->getObjective(S("gloves_taken")))
	{
		P<TimelineAction> timelineAction = New<TimelineAction>();
		timelineAction->blockG = true;
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("gloves_taken"));
		timelineAction->function = [this](String a) { standup(a); };
		Timeline::t->addAction(timelineAction);
		Timeline::t->doNotUnlock = true;
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("gloves_taken2")));
	}
}

void LocationBaseOutside1Bike::standup(String s)
{
	PlayerController::wc->forceAnimation(S("kneel_e_out"));
}

void LocationBaseOutside1Bike::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 4)
	{
		setCollider(0);
		sr->set_enabled(true);
		if (GameDataController::gd->getObjective(S("gloves_taken")))
		{
			characterAnimationName = S("kneel_e");
		}
		else
		{
			characterAnimationName = S("kneel_e_in");
		}
	}
	else
	{
		setCollider(-1);
		sr->set_enabled(false);
	}
}

void LocationBaseOutside1Bike::clickAction2()
{
	if (!GameDataController::gd->getObjective(S("gloves_taken")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hose);
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("gloves"))))
		{
			GameDataController::gd->setObjective(S("gloves_taken"), true);
		}
		updateState();
	}
}

void LocationBaseOutside1Bike::clickAction0()
{
}

void LocationBaseOutside1Bike::whatOnClick0()
{
}

void LocationBaseOutside1Bike::whatOnClick()
{
}
