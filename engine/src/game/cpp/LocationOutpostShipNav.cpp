#include "../game_all.h"

void LocationOutpostShipNav::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e_in");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship_nav0");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("nav_chip"), String::Empty, nullptr, String::Empty));
}

void LocationOutpostShipNav::clickAction()
{
	if (usedItem != String::Empty)
	{
		if (GameDataController::gd->getObjective(S("outpost_navigation_chip_inserted")) || GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 1)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("nav_already_in")));
			return;
		}
		InventoryController::ic->removeItem(S("nav_chip"));
		GameDataController::gd->setObjective(S("outpost_navigation_chip_inserted"), true);
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

void LocationOutpostShipNav::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("outpost_navigation_chip_inserted")) || GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 1)
	{
		GetComponent<Animator>()->Play(S("ship_nav_ready"));
		say = GameStrings::getString(GameStrings::actions, S("ship_examine_nav_1"));
		examine = examine2;
		objectName = S("outpost_ship_nav1");
	}
	else
	{
		GetComponent<Animator>()->Play(S("ship_nav_blink"));
		say = GameStrings::getString(GameStrings::actions, S("ship_examine_nav_0"));
		examine = examine1;
		objectName = S("outpost_ship_nav0");
	}
}

void LocationOutpostShipNav::clickAction2()
{
}

void LocationOutpostShipNav::clickAction0()
{
}

void LocationOutpostShipNav::whatOnClick0()
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

void LocationOutpostShipNav::whatOnClick()
{
}
