#include "../game_all.h"

void WaypointRVCave::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_cave");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_cave");
	trans_dir = WalkController::Direction::S_;
	range = 2.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ropehook"), GameStrings::getString(GameStrings::actions, S("rv_cave_hook_missclick")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("ac_cave_down")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flag"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanket"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ext_cord_place"), String::Empty, nullptr, String::Empty));
}

void WaypointRVCave::whatOnClick0()
{
	if (usedItem != String::Empty && (GameDataController::gd->getObjective(S("rv_cave_flag")) || GameDataController::gd->getObjective(S("rv_cave_blanket")) || GameDataController::gd->getObjective(S("rv_cave_blanketb")) || GameDataController::gd->getObjective(S("rv_cave_therm"))))
	{
		characterAnimationName = S("action_stnd_");
		range = 100.0f;
	}
	else if (usedItem != String::Empty && usedItem != S("ext_cord_place"))
	{
		characterAnimationName = S("kneel_");
		range = 1.0f;
	}
	else
	{
		range = 1.0f;
		characterAnimationName = S("stop");
	}
	if (usedItem == S("ext_cord_place"))
	{
		range = 1000.0f;
	}
}

void WaypointRVCave::clickAction()
{
	if (usedItem == String::Empty || usedItem == S("ext_cord_place"))
	{
		if (GameDataController::gd->getObjective(S("rv_hook_installed")))
		{
			if (usedItem == S("ext_cord_place"))
			{
				GameDataController::gd->setObjective(S("rv_cord_caved"), true);
				PlayerController::pc->spawnName = S("WaypointCave");
				CurtainController::cc->fadeOut(S("LocationCave"), WalkController::Direction::S_);
			}
			else
			{
				PlayerController::pc->spawnName = S("WaypointCave");
				CurtainController::cc->fadeOut(S("LocationCave"), WalkController::Direction::S_);
			}
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_cave_cant")));
		}
	}
	else if (GameDataController::gd->getObjective(S("rv_cave_flag")) || GameDataController::gd->getObjective(S("rv_cave_blanket")) || GameDataController::gd->getObjective(S("rv_cave_blanketb")) || GameDataController::gd->getObjective(S("rv_cave_therm")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hatch_busy")));
	}
	else
	{
		whatYouGet = usedItem;
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("cave_put_blanket1")) + S(" ") + GameStrings::getString(GameStrings::items, usedItem + S("_short")) + S(" ") + GameStrings::getString(GameStrings::warnings, S("cave_put_blanket2")), QuestionController::PopupType::QUESTION, [this]() { doPut(); }, 40, 6);
	}
}

void WaypointRVCave::doPut()
{
	if (whatYouGet == S("flag"))
	{
		GameDataController::gd->setObjective(S("rv_cave_flag"), true);
	}
	else if (whatYouGet == S("blanket"))
	{
		GameDataController::gd->setObjective(S("rv_cave_blanket"), true);
	}
	else if (whatYouGet == S("blanketb"))
	{
		GameDataController::gd->setObjective(S("rv_cave_blanketb"), true);
	}
	else if (whatYouGet == S("thermalb"))
	{
		GameDataController::gd->setObjective(S("rv_cave_therm"), true);
	}
	InventoryController::ic->removeItem(whatYouGet);
	CurtainController::cc->fadeOut();
}

void WaypointRVCave::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_hook_installed")))
	{
		actionType = Type::Transition;
		doubleClickCondition = S("visited_cave");
	}
	else
	{
		doubleClickCondition = S("none");
		actionType = Type::NormalAction;
	}
	if (GameDataController::gd->getObjective(S("rv_cave_flag")) || GameDataController::gd->getObjective(S("rv_cave_blanket")) || GameDataController::gd->getObjective(S("rv_cave_blanketb")) || GameDataController::gd->getObjective(S("rv_cave_therm")))
	{
		colliderManager->setCollider(1);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjective(S("rv_cave_flag")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaFlag);
		}
		if (GameDataController::gd->getObjective(S("rv_cave_blanket")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaBlanket);
		}
		if (GameDataController::gd->getObjective(S("rv_cave_blanketb")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(klapaBlanketb);
		}
		if (GameDataController::gd->getObjective(S("rv_cave_therm")))
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

void WaypointRVCave::clickAction2()
{
}

void WaypointRVCave::clickAction0()
{
}
