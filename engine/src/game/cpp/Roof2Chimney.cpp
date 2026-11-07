#include "../game_all.h"

void Roof2Chimney::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("roof_chimney");
	range = 1.0f;
	teleport = false;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ropehook"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wire"), String::Empty, nullptr, String::Empty));
}

void Roof2Chimney::Update()
{
}

void Roof2Chimney::whatOnClick()
{
	if (usedItem == S("ropehook") && !GameDataController::gd->getObjective(S("chimney_cleaned")))
	{
		characterAnimationName = S("unclog");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		characterAnimationName = S("action_stnd_s");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void Roof2Chimney::clickAction()
{
	if (usedItem == String::Empty)
	{
		if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
		{
			if (GameDataController::gd->getObjective(S("lighting_rod_installed")))
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("lighting_rod_installed_already")));
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("good_spot_for_a_lighting_rod")));
			}
		}
		else if (GameDataController::gd->getObjective(S("chimney_cleaned")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("roof_chimney_unclogged")), true, false, false, 150);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("roof_chimney_clogged")), true, false, false, 150);
		}
		return;
	}
	if (usedItem == S("ropehook"))
	{
		if (GameDataController::gd->getObjective(S("chimney_cleaned")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("roof_chimney_unclogged")), true, false, false, 150);
		}
		else
		{
			GameDataController::gd->setObjective(S("chimney_cleaned"), true);
			updateAll();
		}
	}
	if (usedItem == S("wire"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("install_lighting_rod")), QuestionController::PopupType::QUESTION, [this]() { yesClick(); }, 40, 6);
	}
}

void Roof2Chimney::yesClick()
{
	CurtainController::cc->fadeOut();
	GameDataController::gd->setObjective(S("lighting_rod_installed"), true);
	InventoryController::ic->removeItem(S("wire"));
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("lighting_rod_installed")));
}

void Roof2Chimney::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("lighting_rod_installed")))
	{
		piorunochron->set_enabled(true);
	}
	else
	{
		piorunochron->set_enabled(false);
	}
	if (!GameDataController::gd->getObjective(S("chimney_cleaned")))
	{
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("ropehook"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("wire"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("sonic"), GameStrings::getString(GameStrings::actions, S("chimney_longer")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("sonic2"), GameStrings::getString(GameStrings::actions, S("chimney_longer")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("shovel"), GameStrings::getString(GameStrings::actions, S("chimney_longer")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("chimney_longer")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("chimney_longer")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("chimney_longer")), nullptr, String::Empty));
	}
}

void Roof2Chimney::clickAction2()
{
}

void Roof2Chimney::clickAction0()
{
}
