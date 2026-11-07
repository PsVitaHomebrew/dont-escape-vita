#include "../game_all.h"

void InventoryItemController::Start()
{
	Vector2 tmp;
	tmp.x = -5 + ly * 18 + shiftX;
	tmp.y = 111 - lx * 18 - shiftY;
	Vector2 vector = ScreenControler::gameToScreen(tmp);
	Vector3 position = Vector3(vector.x, vector.y, -0.01f);
	gameObject->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position));
	gameObject->transform->set_position(Vector3(gameObject->transform->get_position().x, gameObject->transform->get_position().y, GameObject::Find(S("inventory"))->transform->get_position().z - 0.01f));
}

void InventoryItemController::Awake()
{
	cursor = GameObject::Find(S("cursor"));
	cursorController = cursor->GetComponent<CursorController>();
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	itemIcon = gameObject->transform->Find(S("item_icon"))->gameObject;
	spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
	iconSpriteRenderer = itemIcon->GetComponent<SpriteRenderer>();
	iconSpriteRenderer->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	spriteRenderer->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	playerController = GameObject::FindGameObjectWithTag(S("Player"))->GetComponent<PlayerController>();
	walkController = GameObject::FindGameObjectWithTag(S("Player"))->GetComponent<WalkController>();
	hover = 0.0f;
	displayHover = 0.0f;
	invetoryController = GameObject::Find(S("inventory"))->GetComponent<InventoryController>();
	itemsManager = GameObject::Find(S("ItemsManager"))->GetComponent<ItemsManager>();
	textfield = GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>();
}

void InventoryItemController::Update()
{
	String selectedItemName = cursorController->selectedItemName;
	if (selectedItemName.Length() > 0 && selectedItemName.Equals(itemName))
	{
		spriteRenderer->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		spriteRenderer->set_color(Color(1.0f, 1.0f, 1.0f, displayHover));
	}
	float num = 2.0f;
	if (hover > displayHover)
	{
		displayHover += num * Time::get_deltaTime();
	}
	if (hover < displayHover)
	{
		displayHover -= num * Time::get_deltaTime();
	}
	if (displayHover < 0.0f)
	{
		displayHover = 0.0f;
	}
	if (displayHover > 1.0f)
	{
		displayHover = 1.0f;
	}
}

void InventoryItemController::OnEnable()
{
}

void InventoryItemController::OnMouseEnter()
{
	if (textfield == nullptr)
	{
		textfield = GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>();
	}
	if (itemName.Length() <= 0 || PlayerController::wc->busy || !(textfield != nullptr))
	{
		return;
	}
	String empty = String::Empty;
	if (cursorController->selectedItemName.Equals(String::Empty) || itemName.Equals(cursorController->selectedItemName))
	{
		empty = GameStrings::getPrefixedShort(GameStrings::items, itemName, true);
		String text = empty;
		empty = text + S(" (") + weight + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")) + S(")");
		if (itemRef != nullptr && itemRef->examineSprite != nullptr)
		{
			empty = empty + S(" ^[") + GameStrings::getString(GameStrings::gui, S("right_click_to_view")) + S("]");
		}
		if (itemName == S("bear_trap_1") || itemName == S("bear_trap_2") || itemName == S("sonic") || itemName == S("bear_trap_3") || itemName == S("bear_trap_4") || itemName == S("gasheater") || itemName == S("heat_absorber1A") || itemName == S("heat_absorber2A") || itemName == S("heat_absorber3A"))
		{
			empty = empty + S(" ^[") + GameStrings::getString(GameStrings::gui, S("drop_to_setup")) + S("]");
		}
	}
	else
	{
		empty = GameStrings::getString(GameStrings::gui, S("use1")) + S(" ") + GameStrings::getString(GameStrings::items, cursorController->selectedItemName + S("_short")) + S(" ") + GameStrings::getString(GameStrings::gui, S("use2")) + S(" ") + GameStrings::getPrefixedShort(GameStrings::items, itemName) + S(".");
	}
	textfield->viewText(empty, false, true, false, ObjectActionController::BOTTOM_TEXT_WIDTH);
}

void InventoryItemController::OnMouseExit()
{
	cursorController->showCursor(CursorController::PixelCursor::NORMAL);
	textfield->keepAlive = false;
	hover = 0.0f;
}

void InventoryItemController::loadItem(P<Item> item)
{
	itemRef = item;
	itemName = item->id;
	weight = item->weight;
	if (itemIcon == nullptr)
	{
		itemIcon = gameObject->transform->Find(S("item_icon"))->gameObject;
	}
	if (iconSpriteRenderer == nullptr)
	{
		iconSpriteRenderer = itemIcon->GetComponent<SpriteRenderer>();
	}
	iconSpriteRenderer->set_sprite(item->inventorySprite);
	iconSpriteRenderer->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
}

void InventoryItemController::removeItem()
{
	if (itemRef != nullptr && itemRef->dataRef != nullptr)
	{
		itemRef->dataRef->droppedLocation = S("nowhere");
	}
	itemName = String::Empty;
	weight = 0.0f;
	itemRef = nullptr;
	itemIcon->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
}

void InventoryItemController::OnMouseDown()
{
	if (walkController->busy)
	{
		return;
	}
	playerController->clickedSomething = true;
	if (cursorController->selectedItemName.Length() > 0)
	{
		if (itemRef != nullptr && !itemName.Equals(cursorController->selectedItemName))
		{
			bool flag = false;
			if (itemRef->usableItemsInventory != nullptr && itemRef->usableItemsInventory.Count() > 0)
			{
				for (int i = 0; i < itemRef->usableItemsInventory.Count(); i++)
				{
					if (itemRef->usableItemsInventory[i]->name == cursorController->selectedItemName)
					{
						flag = true;
						if (itemRef->usableItemsInventory[i]->failText != String::Empty)
						{
							PlayerController::pc->textField->viewText(itemRef->usableItemsInventory[i]->failText, true);
						}
						else if (itemRef->usableItemsInventory[i]->action != nullptr)
						{
							P<ItemInteraction>(itemRef->usableItemsInventory[i])->action();
							InventoryCapMeterController::cm->updateText();
							if (itemRef == nullptr)
							{
								break;
							}
							OnMouseEnter();
						}
					}
					if (itemRef == nullptr || (itemRef != nullptr && itemRef->usableItemsInventory == nullptr))
					{
						break;
					}
				}
			}
			if (!flag)
			{
				PlayerController::pc->textField->viewText(GameStrings::getWrongInteractionText(), true);
			}
			return;
		}
		if (itemName.Equals(cursorController->selectedItemName))
		{
			cursorController->deselectItem();
			return;
		}
		bool flag2 = true;
		if (lx < 5 && cursorController->selectedItemRef->dataRef->droppedLocation == S("trunk") && InventoryController::ic->getCurrentWeight() + cursorController->selectedItemRef->weight > (float)InventoryController::ic->maxCapacity)
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::gui, S("capacity_full")), true);
			GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("capacity_1")) + S(" ") + cursorController->selectedItemRef->weight + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")) + S(" ") + GameStrings::getString(GameStrings::gui, S("capacity_2")) + S(" ") + InventoryController::getRoundedWeightLeft() + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")) + S(" ") + GameStrings::getString(GameStrings::gui, S("capacity_3")), false, true, false, BottomTextController::bottomTextWidth, 1.0f, 1.0f, 0.0f);
			flag2 = false;
		}
		if (gameObject->get_name().ToLower().IndexOf(S("chest")) == -1 && cursorController->selectedItemRef->dataRef->droppedLocation == S("chest") && InventoryController::ic->getCurrentWeight() + cursorController->selectedItemRef->weight > (float)InventoryController::ic->maxCapacity)
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::gui, S("capacity_full")), true);
			GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("capacity_1")) + S(" ") + cursorController->selectedItemRef->weight + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")) + S(" ") + GameStrings::getString(GameStrings::gui, S("capacity_2")) + S(" ") + InventoryController::getRoundedWeightLeft() + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")) + S(" ") + GameStrings::getString(GameStrings::gui, S("capacity_3")), false, true, false, BottomTextController::bottomTextWidth, 1.0f, 1.0f, 0.0f);
			flag2 = false;
		}
		if (flag2)
		{
			invetoryController->removeItem(cursorController->selectedItemName);
			loadItem(cursorController->selectedItemRef);
			if (gameObject->get_name().ToLower().IndexOf(S("chest")) != -1)
			{
				itemsManager->updateItem(cursorController->selectedItemName, S("chest"), lx, ly);
			}
			else if (lx >= 5)
			{
				itemsManager->updateItem(cursorController->selectedItemName, S("trunk"), lx, ly);
			}
			else
			{
				itemsManager->updateItem(cursorController->selectedItemName, S("inventory"), lx, ly);
			}
			cursorController->deselectItem();
			OnMouseEnter();
			InventoryCapMeterController::cm->updateText();
		}
	}
	else if (itemName.Length() > 0)
	{
		InventoryController::ic->aS->PlayOneShot(itemRef->sound);
		if (cursorController->selectedItemName.Equals(itemName))
		{
			cursorController->deselectItem();
		}
		else
		{
			cursorController->selectItem(itemRef);
		}
	}
}

void InventoryItemController::examineItem()
{
	ItemsManager::exmineItem(itemRef);
}

void InventoryItemController::OnMouseOver()
{
	if (itemRef != nullptr && !PlayerController::wc->busy)
	{
		if (Input::GetMouseButtonDown(1))
		{
			if (textfield == nullptr)
			{
				textfield = GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>();
			}
			if (itemRef->examineSprite != nullptr)
			{
				examineItem();
			}
			else
			{
				textfield->viewText(GameStrings::getString(GameStrings::items, itemName + S("_long")), false, true, false, ObjectActionController::BOTTOM_TEXT_WIDTH);
			}
		}
		if (itemName.Length() > 0)
		{
			cursorController->showCursor(CursorController::PixelCursor::INSPECT);
			hover = 0.5f;
		}
	}
	else if (CursorController::cc->selectedItemRef != nullptr)
	{
		hover = 0.25f;
	}
}

String InventoryItemController::getName()
{
	return itemName;
}

float InventoryItemController::getWeight()
{
	return weight;
}

void InventoryItemController::znik()
{
	hover = 0.0f;
	displayHover = 0.0f;
}
