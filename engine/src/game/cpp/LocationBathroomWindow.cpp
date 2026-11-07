#include "../game_all.h"

void LocationBathroomWindow::Start()
{
	colliderManager->setTarget(gameObject);
	sr = gameObject->GetComponent<SpriteRenderer>();
	characterAnimationName = S("stop");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_window_3");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("window_foil1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_foil2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_foil3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_bars1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_bars2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_bars3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_net1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_net2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("window_net3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ducttape"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("hammer"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("nails5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("planks1"), GameStrings::getString(GameStrings::actions, S("window_planks")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("planks2"), GameStrings::getString(GameStrings::actions, S("window_planks")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("planks3"), GameStrings::getString(GameStrings::actions, S("window_planks")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("planks4"), GameStrings::getString(GameStrings::actions, S("window_planks")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("planks5"), GameStrings::getString(GameStrings::actions, S("window_planks")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ac"), GameStrings::getString(GameStrings::actions, S("ac_wrong_window")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flag"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanket"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat1"), GameStrings::getString(GameStrings::actions, S("window_jacket")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat2"), GameStrings::getString(GameStrings::actions, S("window_jacket")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat3"), GameStrings::getString(GameStrings::actions, S("window_jacket")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat4"), GameStrings::getString(GameStrings::actions, S("window_jacket")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("board1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("board2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("board3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("tarpaulin"), GameStrings::getString(GameStrings::actions, S("window_tarpaulin")), nullptr, String::Empty));
	updateState();
}

void LocationBathroomWindow::clickAction()
{
	if (!GameDataController::gd->getObjective(S("base_window_3_net")) && !GameDataController::gd->getObjective(S("base_window_3_bars")) && !GameDataController::gd->getObjective(S("base_window_3_foil")) && !GameDataController::gd->getObjective(S("base_window_3_therm")) && !GameDataController::gd->getObjective(S("base_window_3_blanket")) && !GameDataController::gd->getObjective(S("base_window_3_blanketb")) && !GameDataController::gd->getObjective(S("base_window_3_flag")) && !GameDataController::gd->getObjective(S("base_window_3_board")))
	{
		if (usedItem == S("ducttape") || usedItem == S("hammer") || usedItem.IndexOf(S("nails")) != -1)
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("window_needs_material")), true);
			return;
		}
		if (usedItem == String::Empty)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("window_empty")));
			return;
		}
		if (usedItem == S("crowbar"))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("window_crowbar")), true);
			return;
		}
		if (usedItem.IndexOf(S("window_bars")) != -1)
		{
			GameDataController::gd->setObjective(S("base_window_3_bars"), true);
		}
		else if (usedItem.IndexOf(S("window_net")) != -1)
		{
			GameDataController::gd->setObjective(S("base_window_3_net"), true);
		}
		else if (usedItem.IndexOf(S("window_foil")) != -1)
		{
			GameDataController::gd->setObjective(S("base_window_3_foil"), true);
		}
		else if (usedItem == S("blanket"))
		{
			GameDataController::gd->setObjective(S("base_window_3_blanket"), true);
		}
		else if (usedItem == S("blanketb"))
		{
			GameDataController::gd->setObjective(S("base_window_3_blanketb"), true);
		}
		else if (usedItem == S("flag"))
		{
			GameDataController::gd->setObjective(S("base_window_3_flag"), true);
		}
		else if (usedItem == S("thermalb"))
		{
			GameDataController::gd->setObjective(S("base_window_3_therm"), true);
		}
		else if (usedItem.IndexOf(S("board")) != -1)
		{
			GameDataController::gd->setObjective(S("base_window_3_board"), true);
		}
		InventoryController::ic->removeItem(usedItem);
		ItemsManager::im->updateItem(usedItem, S("window3"), 0, 0);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("window_thing_placed")));
		updateState();
		return;
	}
	if (usedItem == String::Empty)
	{
		if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_3_bars_taped")) || GameDataController::gd->getObjective(S("base_window_3_net_nailed")) || GameDataController::gd->getObjective(S("base_window_3_net_taped")) || GameDataController::gd->getObjective(S("base_window_3_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_3_therm_taped")) || GameDataController::gd->getObjective(S("base_window_3_flag_taped")) || GameDataController::gd->getObjective(S("base_window_3_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_3_board_taped")) || GameDataController::gd->getObjective(S("base_window_3_board_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanket_taped")) || GameDataController::gd->getObjective(S("base_window_3_blanketb_taped")) || GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
		{
			if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_3_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_3_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_3_board_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_3_net_nailed")))
			{
				PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("window_remove_nails")), true);
			}
			else
			{
				QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("window_undo")), QuestionController::PopupType::QUESTION, [this]() { yesUndo(); }, 15, 2);
			}
			return;
		}
		Array<P<Item>> array = Array<P<Item>>::Of({
			ItemsManager::im->getItem(S("window_net1")),
			ItemsManager::im->getItem(S("window_net2")),
			ItemsManager::im->getItem(S("window_net3")),
			ItemsManager::im->getItem(S("window_bars1")),
			ItemsManager::im->getItem(S("window_bars2")),
			ItemsManager::im->getItem(S("window_bars3")),
			ItemsManager::im->getItem(S("window_foil1")),
			ItemsManager::im->getItem(S("window_foil2")),
			ItemsManager::im->getItem(S("window_foil3")),
			ItemsManager::im->getItem(S("thermalb")),
			ItemsManager::im->getItem(S("blanket")),
			ItemsManager::im->getItem(S("blanketb")),
			ItemsManager::im->getItem(S("flag")),
			ItemsManager::im->getItem(S("board1")),
			ItemsManager::im->getItem(S("board2")),
			ItemsManager::im->getItem(S("board3"))
		});
		for (int i = 0; i < array.Length(); i++)
		{
			if (array[i]->dataRef->droppedLocation == S("window3") && InventoryController::ic->pickUpItem(array[i]))
			{
				GameDataController::gd->setObjective(S("base_window_3_bars"), false);
				GameDataController::gd->setObjective(S("base_window_3_net"), false);
				GameDataController::gd->setObjective(S("base_window_3_foil"), false);
				GameDataController::gd->setObjective(S("base_window_3_therm"), false);
				GameDataController::gd->setObjective(S("base_window_3_flag"), false);
				GameDataController::gd->setObjective(S("base_window_3_board"), false);
				GameDataController::gd->setObjective(S("base_window_3_blanket"), false);
				GameDataController::gd->setObjective(S("base_window_3_blanketb"), false);
				updateState();
			}
		}
		return;
	}
	if ((GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_3_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_3_board_nailed")) || GameDataController::gd->getObjective(S("base_window_3_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_3_net_nailed"))) && (usedItem == S("hammer") || usedItem == S("crowbar")))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("window_undo")), QuestionController::PopupType::QUESTION, [this]() { yesUndo2(); }, 15, 2);
	}
	if (usedItem.IndexOf(S("window_bars")) != -1 || usedItem.IndexOf(S("window_net")) != -1 || usedItem.IndexOf(S("window_foil")) != -1 || usedItem == S("blanket") || usedItem == S("blanketb") || usedItem == S("thermalb") || usedItem == S("flag") || usedItem.IndexOf(S("board")) != -1)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("window_occupied")), true);
	}
	else
	{
		if (usedItem == S("hammer") && (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_3_net_nailed")) || GameDataController::gd->getObjective(S("base_window_3_flag_nailed")) || GameDataController::gd->getObjective(S("base_window_3_board_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_3_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_nailed"))))
		{
			return;
		}
		if (usedItem == S("ducttape") && (GameDataController::gd->getObjective(S("base_window_3_bars_taped")) || GameDataController::gd->getObjective(S("base_window_3_net_taped")) || GameDataController::gd->getObjective(S("base_window_3_foil_taped")) || GameDataController::gd->getObjective(S("base_window_3_board_taped")) || GameDataController::gd->getObjective(S("base_window_3_flag_taped")) || GameDataController::gd->getObjective(S("base_window_3_blanket_taped")) || GameDataController::gd->getObjective(S("base_window_3_blanketb_taped")) || GameDataController::gd->getObjective(S("base_window_3_therm_taped"))))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("window_already_taped")), true);
		}
		else if (usedItem == S("hammer") && ItemsManager::im->getItem(S("nails1"))->dataRef->droppedLocation != S("inventory") && ItemsManager::im->getItem(S("nails2"))->dataRef->droppedLocation != S("inventory") && ItemsManager::im->getItem(S("nails3"))->dataRef->droppedLocation != S("inventory") && ItemsManager::im->getItem(S("nails4"))->dataRef->droppedLocation != S("inventory") && ItemsManager::im->getItem(S("nails5"))->dataRef->droppedLocation != S("inventory"))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("no_nails")), true);
		}
		else if (usedItem.IndexOf(S("nails")) != -1 && ItemsManager::im->getItem(S("hammer"))->dataRef->droppedLocation != S("inventory"))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nails_fail")), true);
		}
		else if (usedItem == S("crowbar") && !GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) && !GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) && !GameDataController::gd->getObjective(S("base_window_3_flag_nailed")) && !GameDataController::gd->getObjective(S("base_window_3_board_nailed")) && !GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")) && !GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")) && !GameDataController::gd->getObjective(S("base_window_3_therm_nailed")) && !GameDataController::gd->getObjective(S("base_window_3_net_nailed")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("window_crowbar")), true);
		}
		else if (usedItem != S("crowbar"))
		{
			String text = S("window_use");
			text = ((usedItem.IndexOf(S("ducttape")) == -1) ? (text + S("_hammer")) : (text + S("_tape")));
			if (GameDataController::gd->getObjective(S("base_window_3_bars")))
			{
				text += S("_bars");
			}
			if (GameDataController::gd->getObjective(S("base_window_3_net")))
			{
				text += S("_net");
			}
			if (GameDataController::gd->getObjective(S("base_window_3_foil")))
			{
				text += S("_foil");
			}
			if (GameDataController::gd->getObjective(S("base_window_3_flag")))
			{
				text += S("_flag");
			}
			if (GameDataController::gd->getObjective(S("base_window_3_board")))
			{
				text += S("_board");
			}
			if (GameDataController::gd->getObjective(S("base_window_3_therm")))
			{
				text += S("_therm");
			}
			if (GameDataController::gd->getObjective(S("base_window_3_blanket")))
			{
				text += S("_blanket");
			}
			if (GameDataController::gd->getObjective(S("base_window_3_blanketb")))
			{
				text += S("_blanket");
			}
			int time = 20;
			String text2 = String::Empty;
			if (GameDataController::gd->getCurrentDay() >= 2)
			{
				time = 35;
				text2 = S("^") + GameStrings::getString(GameStrings::warnings, S("worn_window"));
			}
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, text) + text2, QuestionController::PopupType::QUESTION, nullptr, time, 4);
			if (usedItem.IndexOf(S("ducttape")) != -1)
			{
				QuestionController::qc->onYesClick = [this]() { yesTaped(); };
			}
			else
			{
				QuestionController::qc->onYesClick = [this]() { yesNailed(); };
			}
		}
	}
}

void LocationBathroomWindow::yesUndo2()
{
	GameDataController::gd->setObjective(S("base_window_3_bars_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_bars_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_net_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_net_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_bars_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_board_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_board_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_foil_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_foil_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_flag_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_flag_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_blanket_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_blanketb_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_blanket_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_blanketb_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_therm_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_therm_nailed"), false);
	removeIfBroken(true);
	PlayerController::wc->dir = WalkController::Direction::N;
	CurtainController::cc->fadeOut();
	Array<P<Item>> array = Array<P<Item>>::Of({
		ItemsManager::im->getItem(S("nails1")),
		ItemsManager::im->getItem(S("nails2")),
		ItemsManager::im->getItem(S("nails3")),
		ItemsManager::im->getItem(S("nails4")),
		ItemsManager::im->getItem(S("nails5"))
	});
	for (int i = 0; i < array.Length(); i++)
	{
		if (array[i]->dataRef->droppedLocation == S("window3"))
		{
			P<Item> item = array[i];
			item->dataRef->locX = (int)PlayerController::wc->currentXY.x;
			item->dataRef->locY = (int)PlayerController::wc->currentXY.y;
			item->dataRef->droppedLocation = S("LocationBaseBathroom");
			Vector2 vector = ScreenControler::gameToScreen(Vector2(item->dataRef->locX, item->dataRef->locY + GroundItemController::yOffset));
			Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
			vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
			P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion()).as<GameObject>();
			gameObject->GetComponent<GroundItemController>()->init(item);
		}
	}
}

void LocationBathroomWindow::removeIfBroken(bool hadNails)
{
	if (GameDataController::gd->getObjective(S("base_window3_broken")))
	{
		GameDataController::gd->setObjective(S("base_window_3_bars"), false);
		GameDataController::gd->setObjective(S("base_window_3_net"), false);
		GameDataController::gd->setObjective(S("base_window_3_foil"), false);
		if (ItemsManager::im->getItem(S("window_bars1"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("window_bars1"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("window_bars2"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("window_bars2"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("window_bars3"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("window_bars3"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("window_net1"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("window_net1"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("window_net2"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("window_net2"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("window_net3"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("window_net3"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("window_foil1"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("window_foil1"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("window_foil2"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("window_foil2"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("window_foil3"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("window_foil3"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("board1"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("board1"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("board2"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("board2"))->dataRef->droppedLocation = S("nowhere");
		}
		if (ItemsManager::im->getItem(S("board3"))->dataRef->droppedLocation == S("window3"))
		{
			ItemsManager::im->getItem(S("board3"))->dataRef->droppedLocation = S("nowhere");
		}
		String key = S("window_it_was_broken");
		if (hadNails)
		{
			key = S("window_it_was_broken2");
		}
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, key));
		GameDataController::gd->setObjective(S("base_window3_broken"), false);
	}
}

void LocationBathroomWindow::yesUndo()
{
	GameDataController::gd->setObjective(S("base_window_3_bars_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_bars_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_net_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_net_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_bars_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_foil_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_foil_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_board_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_board_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_flag_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_flag_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_blanket_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_blanketb_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_blanket_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_blanketb_nailed"), false);
	GameDataController::gd->setObjective(S("base_window_3_therm_taped"), false);
	GameDataController::gd->setObjective(S("base_window_3_therm_nailed"), false);
	removeIfBroken();
	PlayerController::wc->dir = WalkController::Direction::N;
	CurtainController::cc->fadeOut();
}

void LocationBathroomWindow::yesTaped()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->duct_tape_use);
	if (GameDataController::gd->getObjective(S("base_window_3_bars")))
	{
		GameDataController::gd->setObjective(S("base_window_3_bars_taped"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_net")))
	{
		GameDataController::gd->setObjective(S("base_window_3_net_taped"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_foil")))
	{
		GameDataController::gd->setObjective(S("base_window_3_foil_taped"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_flag")))
	{
		GameDataController::gd->setObjective(S("base_window_3_flag_taped"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_blanket")))
	{
		GameDataController::gd->setObjective(S("base_window_3_blanket_taped"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_board")))
	{
		GameDataController::gd->setObjective(S("base_window_3_board_taped"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_blanketb")))
	{
		GameDataController::gd->setObjective(S("base_window_3_blanketb_taped"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_therm")))
	{
		GameDataController::gd->setObjective(S("base_window_3_therm_taped"), true);
	}
	PlayerController::wc->dir = WalkController::Direction::N;
	CurtainController::cc->fadeOut();
}

void LocationBathroomWindow::yesNailed()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->nailed);
	if (GameDataController::gd->getObjective(S("base_window_3_bars")))
	{
		GameDataController::gd->setObjective(S("base_window_3_bars_nailed"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_net")))
	{
		GameDataController::gd->setObjective(S("base_window_3_net_nailed"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_foil")))
	{
		GameDataController::gd->setObjective(S("base_window_3_foil_nailed"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_flag")))
	{
		GameDataController::gd->setObjective(S("base_window_3_flag_nailed"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_board")))
	{
		GameDataController::gd->setObjective(S("base_window_3_board_nailed"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_blanket")))
	{
		GameDataController::gd->setObjective(S("base_window_3_blanket_nailed"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_blanketb")))
	{
		GameDataController::gd->setObjective(S("base_window_3_blanketb_nailed"), true);
	}
	if (GameDataController::gd->getObjective(S("base_window_3_therm")))
	{
		GameDataController::gd->setObjective(S("base_window_3_therm_nailed"), true);
	}
	Array<P<Item>> array = Array<P<Item>>::Of({
		ItemsManager::im->getItem(S("nails1")),
		ItemsManager::im->getItem(S("nails2")),
		ItemsManager::im->getItem(S("nails3")),
		ItemsManager::im->getItem(S("nails4")),
		ItemsManager::im->getItem(S("nails5"))
	});
	P<Item> item = nullptr;
	for (int i = 0; i < array.Length(); i++)
	{
		if (array[i]->dataRef->droppedLocation == S("inventory"))
		{
			item = array[i];
			break;
		}
	}
	InventoryController::ic->removeItem(item->id);
	ItemsManager::im->updateItem(item->id, S("window3"), 0, 0);
	PlayerController::wc->dir = WalkController::Direction::N;
	CurtainController::cc->fadeOut();
}

void LocationBathroomWindow::updateState()
{
	if (!GameDataController::gd->getObjective(S("base_window_3_net")) && !GameDataController::gd->getObjective(S("base_window_3_bars")) && !GameDataController::gd->getObjective(S("base_window_3_foil")) && !GameDataController::gd->getObjective(S("base_window_3_flag")) && !GameDataController::gd->getObjective(S("base_window_3_board")) && !GameDataController::gd->getObjective(S("base_window_3_blanket")) && !GameDataController::gd->getObjective(S("base_window_3_blanketb")) && !GameDataController::gd->getObjective(S("base_window_3_therm")))
	{
		sr->set_sprite(nullptr);
		objectName = S("base_window_3");
	}
	else if (GameDataController::gd->getObjective(S("base_window_3_net")))
	{
		if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")) && GameDataController::gd->getObjective(S("base_window_3_net_taped")))
		{
			sr->set_sprite(net_taped_nailed);
			objectName = S("base_window_net_taped_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(net_taped_nailed_broken);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net_nailed")))
		{
			sr->set_sprite(net_nailed);
			objectName = S("base_window_net_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(net_nailed_broken);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_net_taped")))
		{
			sr->set_sprite(net_taped);
			objectName = S("base_window_net_taped");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(net_taped_broken);
				objectName = S("base_window_barricade_broken");
			}
		}
		else
		{
			sr->set_sprite(net);
			objectName = S("base_window_net");
		}
	}
	else if (GameDataController::gd->getObjective(S("base_window_3_bars")))
	{
		if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) && GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
		{
			sr->set_sprite(bars_taped_nailed);
			objectName = S("base_window_bars_taped_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(bars_taped_nailed_broken);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")))
		{
			sr->set_sprite(bars_nailed);
			objectName = S("base_window_bars_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(bars_nailed_broken);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_taped")))
		{
			sr->set_sprite(bars_taped);
			objectName = S("base_window_bars_taped");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(bars_taped_broken);
				objectName = S("base_window_barricade_broken");
			}
		}
		else
		{
			sr->set_sprite(bars);
			objectName = S("base_window_bars");
		}
	}
	else if (GameDataController::gd->getObjective(S("base_window_3_board")))
	{
		if (GameDataController::gd->getObjective(S("base_window_3_board_nailed")) && GameDataController::gd->getObjective(S("base_window_3_board_taped")))
		{
			sr->set_sprite(board_taped_nailed);
			objectName = S("base_window_board_taped_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_taped_nailed);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_board_nailed")))
		{
			sr->set_sprite(board_nailed);
			objectName = S("base_window_board_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_nailed);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_board_taped")))
		{
			sr->set_sprite(board_taped);
			objectName = S("base_window_board_taped");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_taped);
				objectName = S("base_window_barricade_broken");
			}
		}
		else
		{
			sr->set_sprite(board);
			objectName = S("base_window_board");
		}
	}
	else if (GameDataController::gd->getObjective(S("base_window_3_foil")))
	{
		if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) && GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
		{
			sr->set_sprite(foil_taped_nailed);
			objectName = S("base_window_foil_taped_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(foil_taped_nailed_broken);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_nailed")))
		{
			sr->set_sprite(foil_nailed);
			objectName = S("base_window_foil_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(foil_nailed_broken);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
		{
			sr->set_sprite(foil_taped);
			objectName = S("base_window_foil_taped");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(foil_taped_broken);
				objectName = S("base_window_barricade_broken");
			}
		}
		else
		{
			sr->set_sprite(foil);
			objectName = S("base_window_foil");
		}
	}
	else if (GameDataController::gd->getObjective(S("base_window_3_flag")))
	{
		if (GameDataController::gd->getObjective(S("base_window_3_flag_nailed")) && GameDataController::gd->getObjective(S("base_window_3_flag_taped")))
		{
			sr->set_sprite(flag_taped_nailed);
			objectName = S("base_window_flag_taped_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_taped_nailed);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_flag_nailed")))
		{
			sr->set_sprite(flag_nailed);
			objectName = S("base_window_flag_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_nailed);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_flag_taped")))
		{
			sr->set_sprite(flag_taped);
			objectName = S("base_window_flag_taped");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_taped);
				objectName = S("base_window_barricade_broken");
			}
		}
		else
		{
			sr->set_sprite(flag);
			objectName = S("base_window_flag");
		}
	}
	else if (GameDataController::gd->getObjective(S("base_window_3_blanket")))
	{
		if (GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")) && GameDataController::gd->getObjective(S("base_window_3_blanket_taped")))
		{
			sr->set_sprite(blanket_taped_nailed);
			objectName = S("base_window_blanket_taped_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_taped_nailed);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")))
		{
			sr->set_sprite(blanket_nailed);
			objectName = S("base_window_blanket_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_nailed);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanket_taped")))
		{
			sr->set_sprite(blanket_taped);
			objectName = S("base_window_blanket_taped");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_taped);
				objectName = S("base_window_barricade_broken");
			}
		}
		else
		{
			sr->set_sprite(blanket);
			objectName = S("base_window_blanket");
		}
	}
	else if (GameDataController::gd->getObjective(S("base_window_3_blanketb")))
	{
		if (GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")) && GameDataController::gd->getObjective(S("base_window_3_blanketb_taped")))
		{
			sr->set_sprite(blanketb_taped_nailed);
			objectName = S("base_window_blanketb_taped_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_taped_nailed);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")))
		{
			sr->set_sprite(blanketb_nailed);
			objectName = S("base_window_blanketb_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_nailed);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_blanketb_taped")))
		{
			sr->set_sprite(blanketb_taped);
			objectName = S("base_window_blanketb_taped");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_taped);
				objectName = S("base_window_barricade_broken");
			}
		}
		else
		{
			sr->set_sprite(blanketb);
			objectName = S("base_window_blanketb");
		}
	}
	else
	{
		if (!GameDataController::gd->getObjective(S("base_window_3_therm")))
		{
			return;
		}
		if (GameDataController::gd->getObjective(S("base_window_3_therm_nailed")) && GameDataController::gd->getObjective(S("base_window_3_therm_taped")))
		{
			sr->set_sprite(thermalb_taped_nailed);
			objectName = S("base_window_therm_taped_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_taped_nailed);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_therm_nailed")))
		{
			sr->set_sprite(thermalb_nailed);
			objectName = S("base_window_therm_nailed");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_nailed);
				objectName = S("base_window_barricade_broken");
			}
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_therm_taped")))
		{
			sr->set_sprite(thermalb_taped);
			objectName = S("base_window_therm_taped");
			if (GameDataController::gd->getObjective(S("base_window3_broken")))
			{
				sr->set_sprite(destroyed_taped);
				objectName = S("base_window_barricade_broken");
			}
		}
		else
		{
			sr->set_sprite(thermalb);
			objectName = S("base_window_therm");
		}
	}
}

void LocationBathroomWindow::clickAction2()
{
}

void LocationBathroomWindow::clickAction0()
{
}

void LocationBathroomWindow::whatOnClick()
{
	doubleClickCondition = String::Empty;
	if ((!GameDataController::gd->getObjective(S("base_window_3_bars")) && !GameDataController::gd->getObjective(S("base_window_3_net")) && !GameDataController::gd->getObjective(S("base_window_3_foil")) && (usedItem.IndexOf(S("window_bars")) != -1 || usedItem.IndexOf(S("window_foil")) != -1 || usedItem.IndexOf(S("window_net")) != -1 || usedItem.IndexOf(S("board")) != -1 || usedItem == S("blanket") || usedItem == S("blanketb") || usedItem == S("thermalb") || usedItem == S("flag"))) || (usedItem == String::Empty && (GameDataController::gd->getObjective(S("base_window_3_bars")) || GameDataController::gd->getObjective(S("base_window_3_net")) || GameDataController::gd->getObjective(S("base_window_3_foil")) || GameDataController::gd->getObjective(S("base_window_3_flag")) || GameDataController::gd->getObjective(S("base_window_3_blanket")) || GameDataController::gd->getObjective(S("base_window_3_blanketb")) || GameDataController::gd->getObjective(S("base_window_3_board")) || GameDataController::gd->getObjective(S("base_window_3_therm")))))
	{
		if (usedItem != String::Empty)
		{
			characterAnimationName = S("action_stnd_n");
			animationFlip = false;
		}
		else if (GameDataController::gd->getObjective(S("base_window_3_bars_nailed")) || GameDataController::gd->getObjective(S("base_window_3_bars_taped")) || GameDataController::gd->getObjective(S("base_window_3_net_nailed")) || GameDataController::gd->getObjective(S("base_window_3_net_taped")) || GameDataController::gd->getObjective(S("base_window_3_therm_nailed")) || GameDataController::gd->getObjective(S("base_window_3_therm_taped")) || GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_taped")) || GameDataController::gd->getObjective(S("base_window_3_board_nailed")) || GameDataController::gd->getObjective(S("base_window_3_board_taped")) || GameDataController::gd->getObjective(S("base_window_3_blanketb_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanket_nailed")) || GameDataController::gd->getObjective(S("base_window_3_blanketb_taped")) || GameDataController::gd->getObjective(S("base_window_3_blanket_taped")) || GameDataController::gd->getObjective(S("base_window_3_foil_nailed")) || GameDataController::gd->getObjective(S("base_window_3_foil_taped")))
		{
			characterAnimationName = S("action_stnd_n");
			animationFlip = false;
			doubleClickCondition = String::Empty;
		}
		else
		{
			characterAnimationName = S("action_n");
			animationFlip = false;
		}
	}
	else
	{
		characterAnimationName = S("action_stnd_n");
		animationFlip = false;
	}
}
