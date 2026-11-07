#include "../game_all.h"

void LocationBaseOutsideRowy::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_ground");
	range = 100.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("shovel"), String::Empty, nullptr, String::Empty));
}

void LocationBaseOutsideRowy::yesDig()
{
	GameDataController::gd->setObjective(S("base_outside_dug"), true);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->digger);
	CurtainController::cc->fadeOut();
	updateAll();
}

void LocationBaseOutsideRowy::clickAction()
{
	if (GameDataController::gd->getObjective(S("base_outside_dug")))
	{
		if (usedItem == String::Empty)
		{
			if (GameDataController::gd->getCurrentDay() == 3)
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("base_outside_ditches")));
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("after_rain_thing")));
			}
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("base_outside_already_dug")));
		}
	}
	else if (usedItem == String::Empty)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("base_outside_could_dig")));
	}
	else if (usedItem == S("shovel"))
	{
		if (!GameDataController::gd->getObjective(S("sidereal_base_located")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("find_base_first")));
		}
		else
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("base_dig")), QuestionController_PopupType::QUESTION, [this]() { yesDig(); }, 120, 10);
		}
	}
}

void LocationBaseOutsideRowy::updateState()
{
	if (GameDataController::gd->getCurrentDay() >= 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		colliderManager->setCollider(0);
	}
	else
	{
		colliderManager->setCollider(-1);
	}
	if (GameDataController::gd->getObjective(S("base_outside_dug")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("base_ditches");
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		objectName = S("base_ground");
	}
}

void LocationBaseOutsideRowy::clickAction2()
{
}

void LocationBaseOutsideRowy::clickAction0()
{
}

void LocationBaseOutsideRowy::whatOnClick0()
{
}

void LocationBaseOutsideRowy::whatOnClick()
{
}
