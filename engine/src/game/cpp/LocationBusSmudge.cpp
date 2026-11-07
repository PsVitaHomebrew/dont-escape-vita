#include "../game_all.h"

void LocationBusSmudge::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bus_fingerprint");
	range = 2.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("gluegun"), GameStrings::getString(GameStrings::actions, S("gluegun_no_power")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("gluegun_powered"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("screwdriver"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("knife"), String::Empty, nullptr, String::Empty));
}

void LocationBusSmudge::clickAction()
{
	if (usedItem == String::Empty)
	{
		if (GameDataController::gd->getObjectiveDetail(S("bus_fingerprint_molded")) == 1)
		{
			ExamineSprite::es->textField->shift.x = -110.0f;
			ExamineSprite::es->textField->shift.y = 20.0f;
			ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::actions, S("bus_fingerprint2")) }), 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f);
			ExamineSprite::es->show(zoom2);
		}
		else
		{
			ExamineSprite::es->textField->shift.x = -110.0f;
			ExamineSprite::es->textField->shift.y = 20.0f;
			ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::actions, S("bus_fingerprint")) }), 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f);
			ExamineSprite::es->show(zoom);
		}
	}
	else if (usedItem == S("screwdriver") || usedItem == S("knife"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("bus_fingerprint_molded")) == 1)
		{
			if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("fingerprint"))))
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("fingerprint_mold_taken")));
				GameDataController::gd->setObjectiveDetail(S("bus_fingerprint_molded"), 2);
				updateAll();
			}
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("fingerprint_no_mold")));
		}
	}
	else
	{
		P<TimelineAction> timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("gluegun_take_impression_1"));
		timelineAction->actionWithText = false;
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("gluegun_take_impression_2"));
		timelineAction->actionWithText = false;
		Timeline::t->addAction(timelineAction);
		InventoryController::ic->removeItem(S("gluegun_powered"));
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->small_powerup);
		GameDataController::gd->setObjectiveDetail(S("bus_fingerprint_molded"), 1);
		updateAll();
	}
}

void LocationBusSmudge::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("bus_fingerprint_molded")) == 1)
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("bus_fingerprint");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("bus_fingerprint_molded")) == 2)
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		objectName = S("bus_fingerprint");
	}
}

void LocationBusSmudge::clickAction2()
{
}

void LocationBusSmudge::clickAction0()
{
}

void LocationBusSmudge::whatOnClick0()
{
	if (!(usedItem == S("gluegun_powered")))
	{
		characterAnimationName = S("action_stnd_n");
	}
}

void LocationBusSmudge::whatOnClick()
{
}
