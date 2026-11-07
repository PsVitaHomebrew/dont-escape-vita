#include "../game_all.h"

void HuntersLodgeHatch::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_in_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_hatch");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
}

void HuntersLodgeHatch::yesClearIt()
{
	PlayerController::pc->setBusy(true);
	GameDataController::gd->setObjective(S("hunters_lodge_chest_opened"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("action1_e"), nullptr, true, [this]() { doneClearing(); });
}

void HuntersLodgeHatch::noCliear()
{
	standup(String::Empty);
}

void HuntersLodgeHatch::doneClearing()
{
	standup(String::Empty);
}

void HuntersLodgeHatch::standup(String param)
{
	PlayerController::pc->setBusy(false);
}

void HuntersLodgeHatch::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("bear_trap_3"))))
	{
		GameDataController::gd->setObjective(S("hunters_lodge_trap_picked"), true);
		updateAll();
	}
}

void HuntersLodgeHatch::clickAction()
{
	if (!GameDataController::gd->getObjective(S("hunters_lodge_chest_opened")))
	{
		if (usedItem == String::Empty)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hunters_hatch_locked")));
		}
		else
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("lodge_back_hatch_force")), QuestionController::PopupType::QUESTION, [this]() { yesClearIt(); }, 30, 5, [this]() { noCliear(); });
		}
	}
	else if (!GameDataController::gd->getObjective(S("hunters_lodge_hatch_gun_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("revolver_0"))))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hunters_take_revolver")));
			GameDataController::gd->setObjective(S("hunters_lodge_hatch_gun_taken"), true);
			updateAll();
		}
	}
	else if (!GameDataController::gd->getObjective(S("hunters_lodge_hatch_ammo1_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("rifle_ammo"))))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hunters_take_ammo1")));
			GameDataController::gd->setObjective(S("hunters_lodge_hatch_ammo1_taken"), true);
			updateAll();
		}
	}
	else if (!GameDataController::gd->getObjective(S("hunters_lodge_hatch_ammo2_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("gun_ammo"))))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hunters_take_ammo2")));
			GameDataController::gd->setObjective(S("hunters_lodge_hatch_ammo2_taken"), true);
			updateAll();
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hunters_hatch_empty")));
	}
}

void HuntersLodgeHatch::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("hunters_lodge_couch_moved")))
	{
		colliderManager->setCollider(-1);
	}
	if (!GameDataController::gd->getObjective(S("hunters_lodge_chest_opened")))
	{
		characterAnimationName = S("action_stnd_n");
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		characterAnimationName = S("kneel_n");
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void HuntersLodgeHatch::clickAction2()
{
}

void HuntersLodgeHatch::clickAction0()
{
}

void HuntersLodgeHatch::whatOnClick0()
{
}

void HuntersLodgeHatch::whatOnClick()
{
}
