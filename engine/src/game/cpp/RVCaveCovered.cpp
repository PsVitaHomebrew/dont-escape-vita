#include "../game_all.h"

void RVCaveCovered::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S(" ");
	actionType = Type::NormalAction;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("flag"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanket"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), String::Empty, nullptr, String::Empty));
	trans_dir = WalkController::Direction::S_;
}

void RVCaveCovered::whatOnClick0()
{
	if (usedItem != String::Empty && (GameDataController::gd->getObjective(S("rv_cave_flag")) || GameDataController::gd->getObjective(S("rv_cave_blanket")) || GameDataController::gd->getObjective(S("rv_cave_blanketb")) || GameDataController::gd->getObjective(S("rv_cave_therm"))))
	{
		characterAnimationName = S("action_stnd_");
		range = 100.0f;
	}
	else if (usedItem == String::Empty)
	{
		characterAnimationName = S("action_stnd_");
		range = 1.0f;
	}
}

void RVCaveCovered::clickAction()
{
	if (usedItem == String::Empty)
	{
		String text = String::Empty;
		if (GameDataController::gd->getObjective(S("rv_cave_flag")))
		{
			text = GameStrings::getString(GameStrings::items, S("flag_short"));
		}
		if (GameDataController::gd->getObjective(S("rv_cave_blanket")))
		{
			text = GameStrings::getString(GameStrings::items, S("blanket_short"));
		}
		if (GameDataController::gd->getObjective(S("rv_cave_blanketb")))
		{
			text = GameStrings::getString(GameStrings::items, S("blanketb_short"));
		}
		if (GameDataController::gd->getObjective(S("rv_cave_therm")))
		{
			text = GameStrings::getString(GameStrings::items, S("thermalb_short"));
		}
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("cave_remove_blanket1")) + S(" ") + text + S(" ") + GameStrings::getString(GameStrings::warnings, S("cave_remove_blanket2")), QuestionController::PopupType::QUESTION, [this]() { doRemove(); }, 10, 2);
	}
	else if (GameDataController::gd->getObjective(S("rv_cave_flag")) || GameDataController::gd->getObjective(S("rv_cave_blanket")) || GameDataController::gd->getObjective(S("rv_cave_blanketb")) || GameDataController::gd->getObjective(S("rv_cave_therm")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hatch_busy")));
	}
}

void RVCaveCovered::doRemove()
{
	if (GameDataController::gd->getObjective(S("rv_cave_flag")))
	{
		InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("flag")));
	}
	if (GameDataController::gd->getObjective(S("rv_cave_blanket")))
	{
		InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("blanket")));
	}
	if (GameDataController::gd->getObjective(S("rv_cave_blanketb")))
	{
		InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("blanketb")));
	}
	if (GameDataController::gd->getObjective(S("rv_cave_therm")))
	{
		InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("thermalb")));
	}
	GameDataController::gd->setObjective(S("rv_cave_flag"), false);
	GameDataController::gd->setObjective(S("rv_cave_blanket"), false);
	GameDataController::gd->setObjective(S("rv_cave_blanketb"), false);
	GameDataController::gd->setObjective(S("rv_cave_therm"), false);
	CurtainController::cc->fadeOut();
}

void RVCaveCovered::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_cave_flag")) || GameDataController::gd->getObjective(S("rv_cave_blanket")) || GameDataController::gd->getObjective(S("rv_cave_blanketb")) || GameDataController::gd->getObjective(S("rv_cave_therm")))
	{
		colliderManager->setCollider(0);
	}
	else
	{
		colliderManager->setCollider(-1);
	}
	if (GameDataController::gd->getObjective(S("rv_cave_flag")))
	{
		objectName = S("rv_cave_thing_flag");
	}
	if (GameDataController::gd->getObjective(S("rv_cave_blanket")))
	{
		objectName = S("rv_cave_thing_blanket");
	}
	if (GameDataController::gd->getObjective(S("rv_cave_blanketb")))
	{
		objectName = S("rv_cave_thing_blanket");
	}
	if (GameDataController::gd->getObjective(S("rv_cave_therm")))
	{
		objectName = S("rv_cave_thing_thermalb");
	}
}

void RVCaveCovered::clickAction2()
{
}

void RVCaveCovered::clickAction0()
{
}
