#include "../game_all.h"

void Attic1Hatch1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("attic_hatch1");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_baseUpstairs");
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
	interactions.Add(New<ItemInteraction>(S("rock"), GameStrings::getString(GameStrings::actions, S("hatch_nails_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rock2"), GameStrings::getString(GameStrings::actions, S("hatch_nails_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("tarpaulin"), GameStrings::getString(GameStrings::actions, S("hatch_tarp")), nullptr, String::Empty));
	trans_dir = WalkController::Direction::S_;
}

void Attic1Hatch1::whatOnClick0()
{
	if (usedItem != String::Empty && (GameDataController::gd->getObjective(S("base_hatch_flag")) || GameDataController::gd->getObjective(S("base_hatch_blanket")) || GameDataController::gd->getObjective(S("base_hatch_blanketb")) || GameDataController::gd->getObjective(S("base_hatch_therm"))))
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

void Attic1Hatch1::clickAction()
{
	if (usedItem == String::Empty)
	{
		PlayerController::pc->spawnName = S("Ladder");
		CurtainController::cc->fadeOut(S("LocationBaseUpstairs"), WalkController::Direction::E, S("ladder_climb_down"));
		return;
	}
	if (GameDataController::gd->getObjective(S("base_hatch_flag")) || GameDataController::gd->getObjective(S("base_hatch_blanket")) || GameDataController::gd->getObjective(S("base_hatch_blanketb")) || GameDataController::gd->getObjective(S("base_hatch_therm")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hatch_busy")));
		return;
	}
	if (usedItem == S("flag"))
	{
		GameDataController::gd->setObjective(S("base_hatch_flag"), true);
	}
	else if (usedItem == S("blanket"))
	{
		GameDataController::gd->setObjective(S("base_hatch_blanket"), true);
	}
	else if (usedItem == S("blanketb"))
	{
		GameDataController::gd->setObjective(S("base_hatch_blanketb"), true);
	}
	else if (usedItem == S("thermalb"))
	{
		GameDataController::gd->setObjective(S("base_hatch_therm"), true);
	}
	InventoryController::ic->removeItem(usedItem);
	updateAll();
}

void Attic1Hatch1::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("base_hatch_flag")) || GameDataController::gd->getObjective(S("base_hatch_blanket")) || GameDataController::gd->getObjective(S("base_hatch_blanketb")) || GameDataController::gd->getObjective(S("base_hatch_therm")))
	{
		colliderManager->setCollider(1);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjective(S("base_hatch_flag")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaFlag);
		}
		if (GameDataController::gd->getObjective(S("base_hatch_blanket")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaBlanket);
		}
		if (GameDataController::gd->getObjective(S("base_hatch_blanketb")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaBlanketb);
		}
		if (GameDataController::gd->getObjective(S("base_hatch_therm")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaThermb);
		}
	}
	else
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void Attic1Hatch1::clickAction2()
{
}

void Attic1Hatch1::clickAction0()
{
}
