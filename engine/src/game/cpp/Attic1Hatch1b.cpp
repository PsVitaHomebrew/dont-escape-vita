#include "../game_all.h"

void Attic1Hatch1b::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("attic_hatch1");
	actionType = Type::NormalAction;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("flag"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanket"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("hatch_nails_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ducttape"), GameStrings::getString(GameStrings::actions, S("hatch_nails_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails1"), GameStrings::getString(GameStrings::actions, S("hatch_nails_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails2"), GameStrings::getString(GameStrings::actions, S("hatch_nails_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails3"), GameStrings::getString(GameStrings::actions, S("hatch_nails_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails4"), GameStrings::getString(GameStrings::actions, S("hatch_nails_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails5"), GameStrings::getString(GameStrings::actions, S("hatch_nails_no_need")), nullptr, String::Empty));
	trans_dir = WalkController::Direction::S_;
}

void Attic1Hatch1b::whatOnClick0()
{
	if (usedItem != String::Empty && (GameDataController::gd->getObjective(S("rv_cave_flag")) || GameDataController::gd->getObjective(S("rv_cave_blanket")) || GameDataController::gd->getObjective(S("rv_cave_blanketb")) || GameDataController::gd->getObjective(S("rv_cave_therm"))))
	{
		characterAnimationName = S("action_stnd_");
		range = 100.0f;
	}
	else if (usedItem != String::Empty || GameDataController::gd->getObjective(S("base_hatch_flag")) || GameDataController::gd->getObjective(S("base_hatch_blanket")) || GameDataController::gd->getObjective(S("base_hatch_blanketb")) || GameDataController::gd->getObjective(S("base_hatch_therm")))
	{
		characterAnimationName = S("kneel_");
		range = 1.0f;
	}
	else
	{
		range = 1.0f;
		characterAnimationName = S("stop");
	}
}

void Attic1Hatch1b::clickAction()
{
	if (usedItem == String::Empty)
	{
		if (GameDataController::gd->getObjective(S("base_hatch_flag")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("flag"))))
		{
			GameDataController::gd->setObjective(S("base_hatch_flag"), false);
		}
		if (GameDataController::gd->getObjective(S("base_hatch_blanket")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("blanket"))))
		{
			GameDataController::gd->setObjective(S("base_hatch_blanket"), false);
		}
		if (GameDataController::gd->getObjective(S("base_hatch_blanketb")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("blanketb"))))
		{
			GameDataController::gd->setObjective(S("base_hatch_blanketb"), false);
		}
		if (GameDataController::gd->getObjective(S("base_hatch_therm")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("thermalb"))))
		{
			GameDataController::gd->setObjective(S("base_hatch_therm"), false);
		}
		updateAll();
	}
	else if (GameDataController::gd->getObjective(S("base_hatch_flag")) || GameDataController::gd->getObjective(S("base_hatch_blanket")) || GameDataController::gd->getObjective(S("base_hatch_blanketb")) || GameDataController::gd->getObjective(S("base_hatch_therm")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hatch_busy")));
	}
}

void Attic1Hatch1b::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("base_hatch_flag")) || GameDataController::gd->getObjective(S("base_hatch_blanket")) || GameDataController::gd->getObjective(S("base_hatch_blanketb")) || GameDataController::gd->getObjective(S("base_hatch_therm")))
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjective(S("attic_hatch_open")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(light2);
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_sprite(light1);
		}
	}
	else
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("base_hatch_flag")))
	{
		objectName = S("attic_hatch_thing_flag");
	}
	if (GameDataController::gd->getObjective(S("base_hatch_blanket")))
	{
		objectName = S("attic_hatch_thing_blanket");
	}
	if (GameDataController::gd->getObjective(S("base_hatch_blanketb")))
	{
		objectName = S("attic_hatch_thing_blanket");
	}
	if (GameDataController::gd->getObjective(S("base_hatch_therm")))
	{
		objectName = S("attic_hatch_thing_thermalb");
	}
}

void Attic1Hatch1b::clickAction2()
{
}

void Attic1Hatch1b::clickAction0()
{
}
