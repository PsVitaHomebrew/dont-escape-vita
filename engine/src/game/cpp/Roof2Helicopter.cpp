#include "../game_all.h"

void Roof2Helicopter::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("roof_heli");
	range = 100.0f;
	teleport = false;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("tarpaulin"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ducttape"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flag"), GameStrings::getString(GameStrings::actions, S("cover_too_small")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanket"), GameStrings::getString(GameStrings::actions, S("cover_too_small")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), GameStrings::getString(GameStrings::actions, S("cover_too_small")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("therm"), GameStrings::getString(GameStrings::actions, S("cover_too_small")), nullptr, String::Empty));
}

void Roof2Helicopter::Update()
{
}

void Roof2Helicopter::whatOnClick()
{
}

void Roof2Helicopter::clickAction()
{
	if (usedItem == String::Empty)
	{
		if (GameDataController::gd->getObjective(S("helicopter_covered")))
		{
			if (GameDataController::gd->getObjective(S("helicopter_covered_taped")))
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("helicopter_covered_taped_already")));
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("helicopter_covered_already")));
			}
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("roof_heli")), true, false, false, 150);
		}
	}
	else if (usedItem == S("tarpaulin"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("helicopter_cover")), QuestionController::PopupType::QUESTION, [this]() { yesClick(); }, 40, 8);
	}
	else if (usedItem == S("ducttape"))
	{
		if (GameDataController::gd->getObjective(S("helicopter_covered_taped")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("helicopter_covered_taped_already")));
		}
		else if (GameDataController::gd->getObjective(S("helicopter_covered")))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("helicopter_cover_tape")), QuestionController::PopupType::QUESTION, [this]() { yesClick2(); }, 30, 6);
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("helicopter_duct_tape")));
		}
	}
}

void Roof2Helicopter::yesClick()
{
	CurtainController::cc->fadeOut();
	GameDataController::gd->setObjective(S("helicopter_covered"), true);
	InventoryController::ic->removeItem(S("tarpaulin"));
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("helicopter_covered")));
}

void Roof2Helicopter::yesClick2()
{
	CurtainController::cc->fadeOut();
	GameDataController::gd->setObjective(S("helicopter_covered_taped"), true);
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("helicopter_covered_taped")));
}

void Roof2Helicopter::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("helicopter_covered_taped")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(taped);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else if (GameDataController::gd->getObjective(S("helicopter_covered")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(tarpaulin);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void Roof2Helicopter::clickAction2()
{
}

void Roof2Helicopter::clickAction0()
{
}
