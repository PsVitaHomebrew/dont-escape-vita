#include "../game_all.h"

void SiderealF2SCBody::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_body");
	range = 2.0f;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("knife"), String::Empty, nullptr, String::Empty));
}

void SiderealF2SCBody::clickAction()
{
	if (usedItem != String::Empty)
	{
		if (GameDataController::gd->getObjective(S("sidereal_finger_cut")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("finger_already_cut")));
			return;
		}
		if (!GameDataController::gd->getObjective(S("visited_outpost4")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("finger_why_cut")));
			return;
		}
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("finger_done_cut")));
		InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("finger")));
		GameDataController::gd->setObjective(S("sidereal_finger_cut"), true);
	}
	else if (!GameDataController::gd->getObjective(S("sidereal_keys_taken")))
	{
		pickItUp(nullptr);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_body")), true);
	}
}

void SiderealF2SCBody::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sidereal_id_key"))))
	{
		GameDataController::gd->setObjective(S("sidereal_keys_taken"), true);
		updateState();
	}
}

void SiderealF2SCBody::whatOnClick()
{
	if (usedItem == S("knife") && !GameDataController::gd->getObjective(S("sidereal_finger_cut")) && GameDataController::gd->getObjective(S("visited_outpost4")))
	{
		animationFlip = false;
		useCurrentDirection = false;
		characterAnimationName = S("action_n");
		range = 2.0f;
	}
	if (GameDataController::gd->getObjective(S("sidereal_keys_taken")) || (usedItem != String::Empty && (GameDataController::gd->getObjective(S("sidereal_finger_cut")) || !GameDataController::gd->getObjective(S("visited_outpost4")))))
	{
		animationFlip = false;
		useCurrentDirection = true;
		characterAnimationName = S("action_stnd_");
		range = 50.0f;
	}
	else
	{
		animationFlip = false;
		useCurrentDirection = false;
		characterAnimationName = S("action_n");
		range = 2.0f;
	}
}

void SiderealF2SCBody::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_keys_taken")) || (usedItem != String::Empty && (GameDataController::gd->getObjective(S("sidereal_finger_cut")) || !GameDataController::gd->getObjective(S("visited_outpost4")))))
	{
		animationFlip = false;
		useCurrentDirection = true;
		characterAnimationName = S("action_stnd_");
		range = 50.0f;
	}
	else
	{
		animationFlip = false;
		useCurrentDirection = false;
		characterAnimationName = S("action_n");
		range = 2.0f;
	}
}

void SiderealF2SCBody::clickAction2()
{
}

void SiderealF2SCBody::clickAction0()
{
	if (usedItem != String::Empty && !GameDataController::gd->getObjective(S("sidereal_finger_cut")) && GameDataController::gd->getObjective(S("visited_outpost4")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("finger_start_cut")));
	}
	if (!GameDataController::gd->getObjective(S("sidereal_keys_taken")) && usedItem == String::Empty)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_keys")), true);
	}
}
