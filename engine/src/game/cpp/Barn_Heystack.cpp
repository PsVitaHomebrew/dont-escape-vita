#include "../game_all.h"

void Barn_Heystack::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kick_ne");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_heystack");
	setCollider(0);
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ducttape"), String::Empty, nullptr, String::Empty));
}

void Barn_Heystack::updateState()
{
	if (!GameDataController::gd->getObjective(S("barn_haystack_3")))
	{
		interactions = List<P<ItemInteraction>>::New();
	}
	if (!GameDataController::gd->getObjective(S("barn_haystack_1")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/Barn/barn_hay1")));
		setCollider(0);
		objectName = S("barn_haystack");
	}
	else if (!GameDataController::gd->getObjective(S("barn_haystack_2")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/Barn/barn_hay2")));
		setCollider(0);
		objectName = S("barn_haystack");
	}
	else if (!GameDataController::gd->getObjective(S("barn_haystack_3")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/Barn/barn_hay3")));
		setCollider(0);
		objectName = S("barn_haystack");
	}
	else if (!GameDataController::gd->getObjective(S("barn_pipe_fixed")))
	{
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("ducttape"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("window_foil1"), GameStrings::getString(GameStrings::actions, S("foil_pipe")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("window_foil2"), GameStrings::getString(GameStrings::actions, S("foil_pipe")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("window_foil3"), GameStrings::getString(GameStrings::actions, S("foil_pipe")), nullptr, String::Empty));
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/Barn/barn_hay4")));
		objectName = S("barn_pipe_broken");
		setCollider(1);
	}
	else
	{
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("ducttape"), String::Empty, nullptr, String::Empty));
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Locations/Barn/pipe_fixed")));
		objectName = S("barn_pipe_fixed");
		setCollider(1);
	}
}

void Barn_Heystack::whatOnClick()
{
	if (GameDataController::gd->getObjective(S("barn_haystack_3")))
	{
		characterAnimationName = S("action_stnd_n");
	}
	else
	{
		characterAnimationName = S("kick_ne");
	}
}

void Barn_Heystack::clickAction()
{
	if (!GameDataController::gd->getObjective(S("barn_haystack_1")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hay_rustle);
		GameDataController::gd->setObjective(S("barn_haystack_1"), true);
		updateState();
	}
	else if (!GameDataController::gd->getObjective(S("barn_haystack_2")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hay_rustle);
		GameDataController::gd->setObjective(S("barn_haystack_2"), true);
		updateState();
	}
	else if (!GameDataController::gd->getObjective(S("barn_haystack_3")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hay_rustle);
		GameDataController::gd->setObjective(S("barn_haystack_3"), true);
		updateState();
	}
	else if (!GameDataController::gd->getObjective(S("barn_pipe_fixed")))
	{
		if (usedItem == S("ducttape"))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barn_pipe_broken")), QuestionController::PopupType::QUESTION, [this]() { yesClicked(); }, 5);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_pipe_broken")), true);
		}
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("barn_pipe_fixed")), true);
	}
	PlayerController::wc->forceDirection(WalkController::Direction::NE);
}

void Barn_Heystack::yesClicked()
{
	GameDataController::gd->setObjective(S("barn_pipe_fixed"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("kneel_n"), SoundsManagerController::sm->duct_tape_use);
}

void Barn_Heystack::clickAction2()
{
}

void Barn_Heystack::clickAction0()
{
}
