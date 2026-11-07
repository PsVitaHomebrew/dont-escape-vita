#include "../game_all.h"

void BaseWindow::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("break_window2");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_window");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("pipe"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("watersprayer"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flag"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanket"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_foil1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_foil2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_foil3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_bars1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_bars2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_bars3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_net1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_net2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_net3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("board1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("board2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("board3"), String::Empty, nullptr, String::Empty));
}

void BaseWindow::clickAction2()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->break_window);
}

void BaseWindow::clickAction()
{
	if (GameDataController::gd->getObjective(S("outside0_window_broken")))
	{
		if (usedItem == String::Empty)
		{
			if (GameDataController::gd->getObjective(S("base_window_1_foil")) || GameDataController::gd->getObjective(S("base_window_1_net")) || GameDataController::gd->getObjective(S("base_window_1_bars")) || GameDataController::gd->getObjective(S("base_window_1_foil")) || GameDataController::gd->getObjective(S("base_window_1_blanket")) || GameDataController::gd->getObjective(S("base_window_1_blanketb")) || GameDataController::gd->getObjective(S("base_window_1_therm")) || GameDataController::gd->getObjective(S("base_window_1_board")) || GameDataController::gd->getObjective(S("base_window_1_flag")))
			{
				PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("window_blocked")), true);
				return;
			}
			PlayerController::pc->spawnName = S("Window");
			CurtainController::cc->fadeOut(S("Location1"), WalkController::Direction::S_, S("window_jump"));
		}
		else if (!(usedItem == S("pipe")) && !(usedItem == S("watersprayer")))
		{
		}
	}
	else if (usedItem == S("pipe"))
	{
		GameDataController::gd->setObjective(S("outside0_window_broken"), !GameDataController::gd->getObjective(S("outside0_window_broken")));
		updateState();
		PlayerController::wc->dir = WalkController::Direction::NW;
	}
	else if (usedItem == S("watersprayer"))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("window_watersprayer")));
	}
	else if (usedItem != String::Empty)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("window_wrong_side")));
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("window_glass")), true);
	}
}

void BaseWindow::updateState()
{
	doubleClickCondition = String::Empty;
	if (GameDataController::gd->getObjective(S("outside0_window_broken")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		actionType = Type::NormalAction;
		if (GameDataController::gd->getObjective(S("base_window_1_foil")))
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(foil);
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_net")))
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(net);
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_bars")))
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(bars);
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_board")))
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(board);
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_therm")))
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(therm);
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_flag")))
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(flag);
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanket")))
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(blanket);
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else if (GameDataController::gd->getObjective(S("base_window_1_blanketb")))
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(blanketb);
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else
		{
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
			doubleClickCondition = S("visited_location1");
			actionType = Type::Transition;
			trans_dir = WalkController::Direction::E;
		}
		objectName = S("base_window_broken");
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(glass);
		objectName = S("base_window");
	}
}

void BaseWindow::whatOnClick()
{
	if (usedItem == S("pipe"))
	{
		if (GameDataController::gd->getObjective(S("outside0_window_broken")))
		{
			characterAnimationName = S("action_stnd_n");
			animationFlip = false;
		}
		else
		{
			characterAnimationName = S("break_window2");
			animationFlip = true;
		}
	}
	else
	{
		animationFlip = false;
		characterAnimationName = S("action_stnd_n");
	}
}

void BaseWindow::clickAction0()
{
}
