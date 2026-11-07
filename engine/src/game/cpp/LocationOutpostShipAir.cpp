#include "../game_all.h"

void LocationOutpostShipAir::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e_in");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship_air0");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("air_tanks"), String::Empty, nullptr, String::Empty));
}

void LocationOutpostShipAir::clickAction()
{
	if (usedItem != String::Empty)
	{
		if (GameDataController::gd->getObjective(S("outpost_air_tanks_inserted")) || GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 0)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("air_already_in")));
			return;
		}
		InventoryController::ic->removeItem(S("air_tanks"));
		GameDataController::gd->setObjective(S("outpost_air_tanks_inserted"), true);
		updateState();
	}
	else
	{
		ExamineSprite::es->textField->shift.x = 20.0f;
		ExamineSprite::es->textField->shift.y = 10.0f;
		ExamineSprite::es->readyText(List<String>::New({ say }), 90, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f);
		ExamineSprite::es->closingAnimation = S("kneel_e_out");
		ExamineSprite::es->show(examine);
	}
}

void LocationOutpostShipAir::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("outpost_air_tanks_inserted")) || GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 0)
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		say = GameStrings::getString(GameStrings::actions, S("ship_examine_air_1"));
		examine = examine2;
		objectName = S("outpost_ship_air1");
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		say = GameStrings::getString(GameStrings::actions, S("ship_examine_air_0"));
		examine = examine1;
		objectName = S("outpost_ship_air0");
	}
}

void LocationOutpostShipAir::clickAction2()
{
}

void LocationOutpostShipAir::clickAction0()
{
}

void LocationOutpostShipAir::whatOnClick0()
{
	if (usedItem != String::Empty)
	{
		characterAnimationName = S("kneel_e");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		characterAnimationName = S("kneel_e_in");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void LocationOutpostShipAir::whatOnClick()
{
}
