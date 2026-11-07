#include "../game_all.h"

void LocationOutpostShipLioh::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e_in");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship_lioh0");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("lioh_filter"), String::Empty, nullptr, String::Empty));
}

void LocationOutpostShipLioh::clickAction()
{
	if (usedItem != String::Empty)
	{
		if (GameDataController::gd->getObjective(S("outpost_lioh_filters_inserted")) || GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 0)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("lioh_already_in")));
			return;
		}
		InventoryController::ic->removeItem(S("lioh_filter"));
		GameDataController::gd->setObjective(S("outpost_lioh_filters_inserted"), true);
		updateState();
	}
	else
	{
		ExamineSprite::es->textField->shift.x = -80.0f;
		ExamineSprite::es->textField->shift.y = 10.0f;
		ExamineSprite::es->readyText(List<String>::New({ say }), 90, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f);
		ExamineSprite::es->closingAnimation = S("kneel_e_out");
		ExamineSprite::es->show(examine);
	}
}

void LocationOutpostShipLioh::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("outpost_lioh_filters_inserted")) || GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 0)
	{
		GetComponent<Animator>()->Play(S("ship_lioh_ready"));
		say = GameStrings::getString(GameStrings::actions, S("ship_examine_lioh_1"));
		examine = examine2;
		objectName = S("outpost_ship_lioh1");
	}
	else
	{
		GetComponent<Animator>()->Play(S("ship_lioh_blink"));
		say = GameStrings::getString(GameStrings::actions, S("ship_examine_lioh_0"));
		examine = examine1;
		objectName = S("outpost_ship_lioh0");
	}
}

void LocationOutpostShipLioh::clickAction2()
{
}

void LocationOutpostShipLioh::clickAction0()
{
}

void LocationOutpostShipLioh::whatOnClick0()
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

void LocationOutpostShipLioh::whatOnClick()
{
}
