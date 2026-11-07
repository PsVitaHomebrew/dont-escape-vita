#include "../game_all.h"

void LocationBaseUpstairsLadder::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("climb_up_locked");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("upstairs_ladder");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("flag"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanket"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
	updateState();
}

void LocationBaseUpstairsLadder::clickAction()
{
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("thug_to_kill_bathroom")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("day4_start_stairs_no")));
	}
	else if (!GameDataController::gd->getObjective(S("day1_complete")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("base_hatch_locked")), true);
	}
}

void LocationBaseUpstairsLadder::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("thug_to_kill_bathroom")))
	{
		actionType = Type::Transition;
		doubleClickCondition = String::Empty;
		trans_dir = WalkController::Direction::N;
		GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("upstairs_ladder2");
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void LocationBaseUpstairsLadder::updateState()
{
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("thug_to_kill_bathroom")))
	{
		actionType = Type::Transition;
		doubleClickCondition = String::Empty;
		trans_dir = WalkController::Direction::N;
		GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("upstairs_ladder2");
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else if (GameDataController::gd->getObjective(S("day1_complete")) && GameDataController::gd->getObjective(S("day_2_hatch_fallen")))
	{
		actionType = Type::Transition;
		doubleClickCondition = S("visited_attic1");
		trans_dir = WalkController::Direction::N;
		GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("upstairs_ladder2");
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("flag"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("blanket"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("blanketb"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("thermalb"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		actionType = Type::NormalAction;
		doubleClickCondition = S("false");
		objectName = S("upstairs_ladder");
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("flag"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("blanket"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("blanketb"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("thermalb"), GameStrings::getString(GameStrings::actions, S("hatch_wrong_side")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("crowbar_hatch")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("key2"), GameStrings::getString(GameStrings::actions, S("key_hatch")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("paperclip"), GameStrings::getString(GameStrings::actions, S("paperclip_hatch")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("wrench_hatch")), nullptr, String::Empty));
	}
	if (!GameDataController::gd->getObjective(S("day1_complete")) || !GameDataController::gd->getObjective(S("day_2_hatch_fallen")))
	{
		return;
	}
	if (GameDataController::gd->getObjective(S("base_hatch_flag")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(klapaFlag);
		if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaFlag2);
		}
	}
	else if (GameDataController::gd->getObjective(S("base_hatch_blanket")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(klapaBlanket);
		if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaBlanket2);
		}
	}
	else if (GameDataController::gd->getObjective(S("base_hatch_blanketb")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(klapaBlanketb);
		if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaBlanketb2);
		}
	}
	else if (GameDataController::gd->getObjective(S("base_hatch_therm")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(klapaThermb);
		if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaThermb2);
		}
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(klapa);
		if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapa2);
		}
	}
}

void LocationBaseUpstairsLadder::clickAction2()
{
	if ((GameDataController::gd->getCurrentDay() != 4 || !GameDataController::gd->getObjective(S("thug_to_kill_bathroom"))) && GameDataController::gd->getObjective(S("day1_complete")))
	{
		PlayerController::pc->spawnName = S("Attic1Hatch1");
		CurtainController::cc->fadeOut(S("LocationAttic1"), WalkController::Direction::SW, S("kneel_out_se"), nullptr, true);
	}
}

void LocationBaseUpstairsLadder::clickAction0()
{
}
