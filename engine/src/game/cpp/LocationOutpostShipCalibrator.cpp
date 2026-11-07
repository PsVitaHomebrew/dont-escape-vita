#include "../game_all.h"

void LocationOutpostShipCalibrator::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_in_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship_calib0");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("engine_calibrator"), String::Empty, nullptr, String::Empty));
}

void LocationOutpostShipCalibrator::clickAction()
{
	if (usedItem != String::Empty)
	{
		if (GameDataController::gd->getObjective(S("outpost_calibrator_inserted")) || GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 1)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("calibrator_already_in")));
			return;
		}
		InventoryController::ic->removeItem(S("engine_calibrator"));
		GameDataController::gd->setObjective(S("outpost_calibrator_inserted"), true);
		updateState();
	}
	else
	{
		ExamineSprite::es->textField->shift.x = -80.0f;
		ExamineSprite::es->textField->shift.y = 10.0f;
		ExamineSprite::es->readyText(List<String>::New({ say }), 90, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f);
		ExamineSprite::es->closingAnimation = S("kneel_out_n");
		ExamineSprite::es->show(examine);
	}
}

void LocationOutpostShipCalibrator::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("outpost_calibrator_inserted")) || GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 1)
	{
		GetComponent<SpriteRenderer>()->set_sprite(present);
		say = GameStrings::getString(GameStrings::actions, S("ship_examine_calib_1"));
		examine = examine2;
		objectName = S("outpost_ship_calib1");
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(missing);
		say = GameStrings::getString(GameStrings::actions, S("ship_examine_calib_0"));
		examine = examine1;
		objectName = S("outpost_ship_calib0");
	}
}

void LocationOutpostShipCalibrator::clickAction2()
{
}

void LocationOutpostShipCalibrator::clickAction0()
{
}

void LocationOutpostShipCalibrator::whatOnClick0()
{
	if (usedItem != String::Empty)
	{
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		characterAnimationName = S("kneel_in_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void LocationOutpostShipCalibrator::whatOnClick()
{
}
