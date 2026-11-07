#include "../game_all.h"

void LocationBridgeCarwreck::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	range = 100.0f;
	dkvs = GameStrings::objects;
	objectName = S("bridge_carwreck_wheel");
}

void LocationBridgeCarwreck::clickAction()
{
	if (GameDataController::gd->getObjective(S("bridge_wheel_taken")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("bridge_carwreck")), true, false, false, 150);
	}
	else if (usedItem == String::Empty)
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("bridge_carwreck_wheel"));
		timelineAction->blockG = true;
		if (InventoryController::ic->isItemInInventory(S("wrench")))
		{
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("bridge_carwreck_wheel2"));
			timelineAction->blockG = true;
			Timeline::t->addAction(timelineAction);
		}
		else
		{
			Timeline::t->addAction(timelineAction);
		}
	}
	else
	{
		askQuestion();
	}
}

void LocationBridgeCarwreck::askQuestion()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("bridge_wheel")), QuestionController::PopupType::QUESTION, [this]() { removeWheel(); }, 15, 2);
}

void LocationBridgeCarwreck::removeWheel()
{
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("action_stnd_ne"), nullptr, true, [this]() { sayAboutCarHarvest(); });
}

void LocationBridgeCarwreck::sayAboutCarHarvest()
{
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("wheel")));
	GameDataController::gd->setObjective(S("bridge_wheel_taken"), true);
	updateAll();
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("got_wheel")));
}

void LocationBridgeCarwreck::whatOnClick0()
{
	if (usedItem == S("wrench"))
	{
		range = 2.0f;
	}
	else
	{
		range = 100.0f;
	}
}

void LocationBridgeCarwreck::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("bridge_wheel_taken")))
	{
		objectName = S("bridge_carwreck");
		colliderManager->setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		objectName = S("bridge_carwreck_wheel");
		colliderManager->setCollider(1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void LocationBridgeCarwreck::clickAction2()
{
}

void LocationBridgeCarwreck::clickAction0()
{
}
