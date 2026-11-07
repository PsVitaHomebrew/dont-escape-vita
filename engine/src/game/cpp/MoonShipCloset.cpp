#include "../game_all.h"

void MoonShipCloset::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action1_e");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("ship_closet");
	actionType = Type::NormalAction;
	doubleClickCondition = String::Empty;
	updateAll();
}

void MoonShipCloset::wearit(String s)
{
	PlayerController::pc->spawnName = S("MoonShipCloset");
	CurtainController::cc->fadeOut(S("MoonShip"));
}

void MoonShipCloset::clickAction()
{
	if (GameDataController::gd->getObjective(S("moon_suited_up")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("already_suited_up")));
	}
	else if (!GameDataController::gd->getObjective(S("moon_shocked1")) && (!GameDataController::gd->getObjective(S("npc2_alive")) || !GameDataController::gd->getObjective(S("moon_shocked2"))) && (!GameDataController::gd->getObjective(S("npc3_alive")) || !GameDataController::gd->getObjective(S("moon_shocked3"))))
	{
		if (!GameDataController::gd->getObjective(S("moon_closet_open")))
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->cabinet_open);
			GameDataController::gd->setObjective(S("moon_closet_open"), true);
			updateAll();
		}
		else
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rope);
			GameDataController::gd->setObjective(S("moon_suited_up"), true);
			wearit(String::Empty);
		}
	}
	else if (GameDataController::gd->getObjective(S("npc2_alive")) || GameDataController::gd->getObjective(S("npc3_alive")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ship_exit_not_yet_others")));
	}
	else if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ship_exit_not_yet_cate")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ship_exit_not_yet_suits")));
	}
}

void MoonShipCloset::updateState()
{
	characterAnimationName = S("action1_e");
	if (GameDataController::gd->getObjective(S("moon_suited_up")))
	{
		characterAnimationName = S("suit_action_stnd_e");
	}
	if (!GameDataController::gd->getObjective(S("moon_suited_up")) && GameDataController::gd->getObjective(S("moon_closet_open")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void MoonShipCloset::clickAction2()
{
}

void MoonShipCloset::clickAction0()
{
}
