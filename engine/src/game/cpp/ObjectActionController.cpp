#include "../game_all.h"

void ObjectActionController::Awake()
{
	interactions = List<P<ItemInteraction>>::New();
	walkControllerOAC = PlayerController::wc;
	initCursor();
	initTextField();
	needUpdate = true;
}

void ObjectActionController::initTextField()
{
	textfield = GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>();
}

void ObjectActionController::setCollider(int n)
{
	colliderManager->setCollider(n);
}

void ObjectActionController::initCursor()
{
	cursorCont = GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>();
}

void ObjectActionController::OnMouseOver()
{
	if (!(PlayerController::pc != nullptr) || PlayerController::pc->dialogue != PlayerController::DialogueState::NONE || PlayerController::wc->busy || (InventoryButtonController::ibc->isItOpen() && !InventoryController::ic->blocker->get_enabled()))
	{
		return;
	}
	if (cursorCont == nullptr)
	{
		initCursor();
	}
	if (!PlayerController::wc->busy)
	{
		if (actionType == Type::Transition && CursorController::cc->selectedItemName == String::Empty)
		{
			cursorCont->showCursor(CursorController::PixelCursor::TRANSITION, trans_dir);
		}
		else if (actionType == Type::Talk && CursorController::cc->selectedItemName == String::Empty)
		{
			cursorCont->showCursor(CursorController::PixelCursor::TALK, trans_dir);
		}
		else if (actionType == Type::Secret)
		{
			cursorCont->showCursor(CursorController::PixelCursor::NORMAL);
		}
		else
		{
			cursorCont->showCursor(CursorController::PixelCursor::ACTIVE);
		}
	}
	if (gameObject->GetComponent<GroundItemController>() == nullptr)
	{
		Vector2 vector = Vector2(CursorController::cc->gameObject->transform->get_position().x, CursorController::cc->gameObject->transform->get_position().y);
		Array<RaycastHit2D> array = Physics2D::LinecastAll(vector, vector);
		if (array != nullptr)
		{
			for (int i = 0; i < array.Length(); i++)
			{
				if (array[i].get_collider()->gameObject->GetComponent<GroundItemController>() != nullptr)
				{
					array[i].get_collider()->gameObject->GetComponent<GroundItemController>()->fakeMouseOver();
					return;
				}
			}
		}
	}
	if (Input::GetMouseButtonDown(1) && textfield != nullptr && dkvs != GameStrings::gui && objectName != String::Empty)
	{
		textfield->viewText(GameStrings::getString(dkvs, objectName + S("_long")), false, true, false, BOTTOM_TEXT_WIDTH);
	}
	if (!alreadyMouseEntered)
	{
		OnMouseEnter();
	}
	alreadyMouseEntered = true;
}

void ObjectActionController::fakeMouseOver()
{
	OnMouseOver();
}

void ObjectActionController::fakeMouseDown()
{
	OnMouseDown();
}

void ObjectActionController::OnMouseEnter()
{
	if (PlayerController::pc->dialogue == PlayerController::DialogueState::NONE && !PlayerController::wc->busy && (!InventoryButtonController::ibc->isItOpen() || InventoryController::ic->blocker->get_enabled()))
	{
		if (cursorCont == nullptr)
		{
			initCursor();
		}
		if (textfield == nullptr)
		{
			initTextField();
		}
		if (textfield != nullptr && !PlayerController::wc->busy && actionType != Type::Secret)
		{
			if (cursorCont->selectedItemName.Equals(String::Empty) || dkvs == GameStrings::gui)
			{
				if (dkvs != GameStrings::map && dkvs != GameStrings::gui && objectName != String::Empty)
				{
					String prefixedShort = GameStrings::getPrefixedShort(dkvs, objectName, true);
					textfield->viewText(prefixedShort, false, true, false, BOTTOM_TEXT_WIDTH);
				}
			}
			else
			{
				String text = GameStrings::getString(GameStrings::gui, S("use1"));
				String text2 = GameStrings::getString(GameStrings::gui, S("use2"));
				bool flag = true;
				if ((objectName == S("npc_boy") || objectName == S("npc_cody")) && !GameDataController::gd->getObjective(S("npc3_joined")) && (cursorCont->selectedItemName.IndexOf(S("rifle")) != -1 || cursorCont->selectedItemName == S("wrench") || cursorCont->selectedItemName == S("crowbar") || cursorCont->selectedItemName == S("hammer") || cursorCont->selectedItemName == S("pipe")))
				{
					flag = false;
				}
				if ((objectName == S("npc_mourning") || objectName == S("npc_barry")) && !GameDataController::gd->getObjective(S("npc2_joined")) && (cursorCont->selectedItemName.IndexOf(S("rifle")) != -1 || cursorCont->selectedItemName == S("wrench") || cursorCont->selectedItemName == S("crowbar") || cursorCont->selectedItemName == S("hammer") || cursorCont->selectedItemName == S("pipe")))
				{
					flag = false;
				}
				if (actionType == Type::Talk && flag)
				{
					text = GameStrings::getString(GameStrings::gui, S("give1"));
					text2 = GameStrings::getString(GameStrings::gui, S("give2"));
				}
				if (text2 != S(":"))
				{
					text2 = S(" ") + text2;
				}
				textfield->viewText(text + S(" ") + GameStrings::getString(GameStrings::items, cursorCont->selectedItemName + S("_short")) + text2 + S(" ") + GameStrings::getPrefixedShort(dkvs, objectName) + S("."), false, true, false, BOTTOM_TEXT_WIDTH);
			}
		}
	}
	mouseOver();
}

void ObjectActionController::OnMouseExit()
{
	clicks = 0;
	if (cursorCont == nullptr)
	{
		initCursor();
	}
	cursorCont->showCursor(CursorController::PixelCursor::NORMAL);
	if (textfield != nullptr && !PlayerController::wc->busy)
	{
		textfield->keepAlive = false;
		textfield->dissmiss(true);
	}
	alreadyMouseEntered = false;
	mouseOut();
}

void ObjectActionController::OnMouseDown()
{
	clicks++;
	if (PlayerController::pc->dialogue != PlayerController::DialogueState::NONE || PlayerController::pc->clickedAlreadyForSomething)
	{
		return;
	}
	if (!PlayerController::wc->busy)
	{
		if (gameObject->GetComponent<GroundItemController>() == nullptr)
		{
			Vector2 vector = Vector2(CursorController::cc->gameObject->transform->get_position().x, CursorController::cc->gameObject->transform->get_position().y);
			Array<RaycastHit2D> array = Physics2D::LinecastAll(vector, vector);
			if (array != nullptr)
			{
				for (int i = 0; i < array.Length(); i++)
				{
					if (array[i].get_collider()->gameObject->GetComponent<GroundItemController>() != nullptr)
					{
						array[i].get_collider()->gameObject->GetComponent<GroundItemController>()->fakeMouseDown();
						return;
					}
				}
			}
		}
		usedItemInteraction = nullptr;
		usedItem = String::Empty;
		bool flag = true;
		InventoryButtonController::ibc->close();
		if (CursorController::cc->selectedItemRef != nullptr)
		{
			flag = false;
			bool flag2 = false;
			for (int j = 0; j < interactions.Count(); j++)
			{
				if (CursorController::cc->selectedItemName.Equals(interactions[j]->name))
				{
					flag2 = true;
					if (!interactions[j]->failText.Equals(String::Empty))
					{
						PlayerController::pc->textField->viewText(interactions[j]->failText, true);
						flag = false;
					}
					else
					{
						usedItemInteraction = interactions[j];
						usedItem = interactions[j]->name;
						flag = true;
					}
					break;
				}
			}
			if (allowAllItems)
			{
				usedItem = CursorController::cc->selectedItemName;
				flag2 = true;
				flag = true;
			}
			if (!flag2)
			{
				PlayerController::pc->textField->viewText(GameStrings::getWrongInteractionText(), true);
			}
			CursorController::cc->deselectItem();
		}
		whatOnClick0();
		PlayerController::pc->clickedSomething = true;
		if (flag)
		{
			if (range == 1.0f)
			{
				range = 1.5f;
			}
			MonoBehaviour::print(S("THE RANGE FOR THIS ACTION IS ") + range);
			if (currentLocationManager == nullptr)
			{
				currentLocationManager = GameObject::Find(S("Location"))->GetComponent<LocationManager>();
			}
			PlayerController::wc->onFinishWalking0 = this;
			PlayerController::wc->onFinishWalking = this;
			PlayerController::wc->onFinishWalking2 = this;
			Vector2 finish = currentLocationManager->findNearestClearNode(currentLocationManager->getNodeLocation(ScreenControler::roundToNearestFullPixel(actionMarker->transform->get_position())));
			List<Vector2> list = currentLocationManager->Search2(currentLocationManager->getNodeLocation(PlayerController::wc->currentXY), finish);
			MonoBehaviour::print(S("TRASA: ") + (list != nullptr ? S("System.Collections.Generic.List`1[UnityEngine.Vector2]") : String::Empty));
			Vector2 vector2 = ScreenControler::screenToGame(Camera::get_main()->WorldToScreenPoint(actionMarker->transform->get_position()));
			if (list != nullptr)
			{
				MonoBehaviour::print(S("DLUGOSC: ") + list.Count());
				Vector2 a = ((list.Count() <= 0) ? currentLocationManager->getNodeLocation(PlayerController::wc->currentXY) : currentLocationManager->getNodeLocation(list[list.Count() - 1]));
				MonoBehaviour::print(S("DISTANCE TO ACTION: ") + LocationManager::dist(a, currentLocationManager->getNodeLocation(vector2)));
				if (LocationManager::dist(a, currentLocationManager->getNodeLocation(vector2)) <= range)
				{
					if (list.Count() > 0)
					{
						list.RemoveAt(list.Count() - 1);
					}
					list.Add(vector2);
				}
				else
				{
					PlayerController::wc->onFinishWalking0 = nullptr;
					PlayerController::wc->onFinishWalking = nullptr;
					PlayerController::wc->onFinishWalking2 = nullptr;
				}
				if (clicks >= 2 || PlayerController::wc->speedMultip > 1.0f)
				{
					PlayerController::wc->speedMultip = 2.0f;
				}
				else
				{
					PlayerController::wc->speedMultip = 1.0f;
				}
				runTimeout = 1.0f;
				PlayerController::wc->setTarget(list);
			}
			PlayerController::wc->range = (int)Mathf::Floor(range);
			if (teleport)
			{
				PlayerController::wc->currentXY.x = ScreenControler::screenToGame(Camera::get_main()->WorldToScreenPoint(actionMarker->transform->get_position())).x;
				PlayerController::wc->currentXY.y = ScreenControler::screenToGame(Camera::get_main()->WorldToScreenPoint(actionMarker->transform->get_position())).y;
			}
		}
		else
		{
			PlayerController::pc->setBusy(false);
			PlayerController::wc->fullStop();
		}
	}
	if (!PlayerController::wc->busy)
	{
		whatOnClick();
	}
	if (clicks > 1 && GameDataController::gd->getObjective(doubleClickCondition) && !PlayerController::wc->busy && PlayerController::wc->onFinishWalking != nullptr)
	{
		PlayerController::wc->onFinishWalking->clickAction();
		PlayerController::wc->letOneMoreAnimationBeforeBusy = 20;
	}
}

void ObjectActionController::fakeClick()
{
	OnMouseDown();
}

void ObjectActionController::Update()
{
	if (needUpdate)
	{
		needUpdate = false;
		updateState();
	}
	if (runTimeout > 0.0f)
	{
		runTimeout -= Time::get_deltaTime();
		if (runTimeout <= 0.0f)
		{
			clicks = 0;
		}
	}
}

void ObjectActionController::OnEnable()
{
	needUpdate = true;
}

void ObjectActionController::animationComplete()
{
	updateState();
}

void ObjectActionController::updateAll()
{
	Array<P<ObjectActionController>> array = Object::FindObjectsOfType<ObjectActionController>();
	for (int i = 0; i < array.Length(); i++)
	{
		array[i].cast<ObjectActionController>()->updateState();
	}
}

void ObjectActionController::whatOnClick()
{
}

void ObjectActionController::whatOnClick0()
{
}

void ObjectActionController::mouseOver()
{
}

void ObjectActionController::mouseOut()
{
}
