#include "../game_all.h"

void InventoryController::Awake()
{
	if (ic == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		ic = this;
		MonoBehaviour::print(S("Inventory controler initialized"));
	}
	else if (ic != P<InventoryController>(this))
	{
		Object::Destroy(gameObject);
	}
}

void InventoryController::Start()
{
	maxCapacity = 30;
	if (GameDataController::gd->getObjectiveDetail(S("day1_complete")) == 1)
	{
		maxCapacity += 5;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day2_complete")) == 1)
	{
		maxCapacity += 5;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day3_complete")) == 1)
	{
		maxCapacity += 5;
	}
	inventoryButton = GameObject::Find(S("inventory_button"));
	invItems = Array<P<InventoryItemController>>::New(4 * 5);
	trunkItems = Array<P<InventoryItemController>>::New(4 * 3);
	chestItems = Array<P<InventoryItemController>>::New(5 * 7);
	aS = InventoryButtonController::ibc->gameObject->GetComponent<AudioSource>();
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			invItems[(i - 1) * 5 + (j - 1)] = gameObject->transform->Find(S("inventory_item_") + i + j)->gameObject->GetComponent<InventoryItemController>();
		}
	}
	trunk = gameObject->transform->Find(S("TrunkInventory"))->gameObject;
	for (int k = 1; k <= 4; k++)
	{
		for (int l = 1; l <= 3; l++)
		{
			trunkItems[(k - 1) * 3 + (l - 1)] = trunk->transform->Find(S("inventory_trunk_item_") + (k + 4) + l)->gameObject->GetComponent<InventoryItemController>();
		}
	}
	chest = gameObject->transform->Find(S("ChestInventory"))->gameObject;
	for (int m = 1; m <= 5; m++)
	{
		for (int n = 1; n <= 7; n++)
		{
			chestItems[(m - 1) * 7 + (n - 1)] = chest->transform->Find(S("inventory_chest_item_") + m + n)->gameObject->GetComponent<InventoryItemController>();
		}
	}
	blocker = gameObject->GetComponent<PolygonCollider2D>();
	InvTrunkClose = GameObject::Find(S("InvTrunkClose"))->GetComponent<Button>();
	InvTrunkClose->initButton(S(" "));
	InvTrunkClose->onClick = [this]() { CloseTrunkButtonClicked(); };
	InvTrunkClose->workIfBusy = false;
	InvChestClose = GameObject::Find(S("InvChestClose"))->GetComponent<Button>();
	InvChestClose->initButton(S(" "));
	InvChestClose->onClick = [this]() { CloseChestButtonClicked(); };
	InvChestClose->workIfBusy = false;
	inventoryCloseButtonTextfield = InvTrunkClose->GetComponent<TextFieldController>();
	inventoryCloseButtonTextfield->transform->set_parent(gameObject->transform);
	inventoryCloseButtonTextfield->container->transform->set_parent(gameObject->transform);
	inventoryCloseButtonTextfield2 = InvChestClose->GetComponent<TextFieldController>();
	inventoryCloseButtonTextfield2->transform->set_parent(gameObject->transform);
	inventoryCloseButtonTextfield2->container->transform->set_parent(gameObject->transform);
}

void InventoryController::cleanUp()
{
	for (int num = 4; num >= 1; num--)
	{
		for (int i = 1; i <= 5; i++)
		{
			invItems[(num - 1) * 5 + (i - 1)]->znik();
		}
	}
	for (int num2 = 4; num2 >= 1; num2--)
	{
		for (int j = 1; j <= 3; j++)
		{
			trunkItems[(num2 - 1) * 3 + (j - 1)]->znik();
		}
	}
	for (int num3 = 5; num3 >= 1; num3--)
	{
		for (int k = 1; k <= 7; k++)
		{
			chestItems[(num3 - 1) * 7 + (k - 1)]->znik();
		}
	}
	CursorController::cc->showCursor(CursorController::PixelCursor::NORMAL);
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->keepAlive = false;
}

void InventoryController::CloseTrunkButtonClicked()
{
	PlayerController::pc->clickedSomething = true;
	InventoryButtonController::ibc->close();
}

void InventoryController::CloseChestButtonClicked()
{
	PlayerController::pc->clickedSomething = true;
	InventoryButtonController::ibc->close();
}

void InventoryController::Update()
{
}

void InventoryController::OnMouseEnter()
{
	if (!ExamineSprite::es->get_Active() && !inventoryButton->GetComponent<InventoryButtonController>()->spaceWasPressed)
	{
		inventoryButton->GetComponent<InventoryButtonController>()->close();
	}
}

void InventoryController::OnMouseExit()
{
	inventoryButton->GetComponent<InventoryButtonController>()->spaceWasPressed = false;
}

void InventoryController::loadItem(P<Item> item)
{
	MonoBehaviour::print(S("LOADING ITEM: ") + item->id);
	P<Transform> transform = gameObject->transform->Find(S("inventory_item_") + item->dataRef->locX + item->dataRef->locY);
	if (item->dataRef->droppedLocation == S("chest"))
	{
		loadChestItem(item);
	}
	else if (transform != nullptr)
	{
		transform->gameObject->GetComponent<InventoryItemController>()->loadItem(item);
	}
	else
	{
		loadTrunkItem(item);
	}
}

void InventoryController::loadChestItem(P<Item> item)
{
	chest->transform->Find(S("inventory_chest_item_") + item->dataRef->locX + item->dataRef->locY)->gameObject->GetComponent<InventoryItemController>()->loadItem(item);
}

void InventoryController::loadTrunkItem(P<Item> item)
{
	trunk->transform->Find(S("inventory_trunk_item_") + item->dataRef->locX + item->dataRef->locY)->gameObject->GetComponent<InventoryItemController>()->loadItem(item);
}

P<InventoryItemController> InventoryController::findFreeSpot()
{
	P<InventoryItemController> result = nullptr;
	for (int num = 4; num >= 1; num--)
	{
		for (int i = 1; i <= 5; i++)
		{
			if (invItems[(num - 1) * 5 + (i - 1)]->getName().Length() == 0)
			{
				result = invItems[(num - 1) * 5 + (i - 1)];
				break;
			}
		}
	}
	return result;
}

P<InventoryItemController> InventoryController::findFreeSpotInTrunk()
{
	P<InventoryItemController> result = nullptr;
	for (int num = 4; num >= 1; num--)
	{
		for (int i = 1; i <= 3; i++)
		{
			if (trunkItems[(num - 1) * 3 + (i - 1)]->getName().Length() == 0)
			{
				result = trunkItems[(num - 1) * 3 + (i - 1)];
				break;
			}
		}
	}
	return result;
}

P<InventoryItemController> InventoryController::findFreeSpotInChest()
{
	P<InventoryItemController> result = nullptr;
	for (int num = 5; num >= 1; num--)
	{
		for (int i = 1; i <= 7; i++)
		{
			if (chestItems[(num - 1) * 7 + (i - 1)]->getName().Length() == 0)
			{
				result = chestItems[(num - 1) * 7 + (i - 1)];
				break;
			}
		}
	}
	return result;
}

bool InventoryController::putItemInTrunk(String itemName, bool quiet)
{
	P<InventoryItemController> inventoryItemController = findFreeSpotInTrunk();
	if (inventoryItemController == nullptr)
	{
		if (!quiet)
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::gui, S("trunk_full")), true);
		}
		return false;
	}
	ic->removeItem(itemName);
	P<Item> item = ItemsManager::im->getItem(itemName);
	ItemsManager::im->updateItem(item->id, S("trunk"), inventoryItemController->lx, inventoryItemController->ly);
	loadTrunkItem(item);
	PlayerController::pc->aS->PlayOneShot(item->sound);
	return true;
}

bool InventoryController::putItemInChest(String itemName, bool quiet)
{
	P<InventoryItemController> inventoryItemController = findFreeSpotInChest();
	if (inventoryItemController == nullptr)
	{
		if (!quiet)
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::gui, S("chest_full")), true);
		}
		return false;
	}
	ic->removeItem(itemName);
	P<Item> item = ItemsManager::im->getItem(itemName);
	ItemsManager::im->updateItem(item->id, S("chest"), inventoryItemController->lx, inventoryItemController->ly);
	loadChestItem(item);
	PlayerController::pc->aS->PlayOneShot(item->sound);
	return true;
}

float InventoryController::getCurrentWeight()
{
	float num = 0.0f;
	for (int num2 = 4; num2 >= 1; num2--)
	{
		for (int i = 1; i <= 5; i++)
		{
			if (invItems[(num2 - 1) * 5 + (i - 1)]->getName().Length() > 0)
			{
				num += invItems[(num2 - 1) * 5 + (i - 1)]->getWeight();
			}
		}
	}
	return num;
}

void InventoryController::removeItem(String name)
{
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			if (invItems[(i - 1) * 5 + (j - 1)]->getName().Equals(name))
			{
				invItems[(i - 1) * 5 + (j - 1)]->removeItem();
				break;
			}
		}
	}
	for (int k = 1; k <= 4; k++)
	{
		for (int l = 1; l <= 3; l++)
		{
			if (trunkItems[(k - 1) * 3 + (l - 1)]->getName().Equals(name))
			{
				trunkItems[(k - 1) * 3 + (l - 1)]->removeItem();
				break;
			}
		}
	}
	for (int m = 1; m <= 5; m++)
	{
		for (int n = 1; n <= 7; n++)
		{
			if (chestItems[(m - 1) * 7 + (n - 1)]->getName().Equals(name))
			{
				chestItems[(m - 1) * 7 + (n - 1)]->removeItem();
				break;
			}
		}
	}
}

void InventoryController::clearInventory()
{
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			invItems[(i - 1) * 5 + (j - 1)]->removeItem();
		}
	}
	for (int k = 1; k <= 4; k++)
	{
		for (int l = 1; l <= 3; l++)
		{
			trunkItems[(k - 1) * 3 + (l - 1)]->removeItem();
		}
	}
	for (int m = 1; m <= 5; m++)
	{
		for (int n = 1; n <= 7; n++)
		{
			chestItems[(m - 1) * 7 + (n - 1)]->removeItem();
		}
	}
}

String InventoryController::getRoundedWeightLeft()
{
	float num = (float)ic->maxCapacity;
	float currentWeight = ic->getCurrentWeight();
	float f = num * 10.0f - 10.0f * currentWeight;
	f = Mathf::Round(f);
	f /= 10.0f;
	return f + String::Empty;
}

bool InventoryController::pickUpItem(P<Item> itemRef, bool silent)
{
	P<InventoryItemController> inventoryItemController = ic->findFreeSpot();
	if (inventoryItemController == nullptr)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::gui, S("inventory_full")), true);
		return false;
	}
	if (ic->getCurrentWeight() + itemRef->weight > (float)ic->maxCapacity)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::gui, S("capacity_full")), true);
		GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("capacity_1")) + S(" ") + itemRef->weight + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")) + S(" ") + GameStrings::getString(GameStrings::gui, S("capacity_2")) + S(" ") + getRoundedWeightLeft() + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")) + S(" ") + GameStrings::getString(GameStrings::gui, S("capacity_3")), false, true, false, BottomTextController::bottomTextWidth, 1.0f, 1.0f, 0.0f);
		return false;
	}
	MonoBehaviour::print(S("im.updateItem"));
	ItemsManager::im->updateItem(itemRef->id, S("inventory"), inventoryItemController->lx, inventoryItemController->ly);
	MonoBehaviour::print(S("ic.loadItem"));
	ic->loadItem(itemRef);
	if (!silent)
	{
		PlayerController::pc->aS->PlayOneShot(itemRef->sound);
	}
	return true;
}

void InventoryController::dropItem(P<Item> itemRef, bool remov, bool bow)
{
	if (bow)
	{
		PlayerController::wc->forceAnimation(S("kneel_s"));
	}
	if (remov)
	{
		ic->removeItem(itemRef->dataRef->id);
	}
	Vector2 vector = ScreenControler::gameToScreen(Vector2(PlayerController::wc->currentXY.x, PlayerController::wc->currentXY.y + (float)GroundItemController::yOffset));
	Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
	vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
	P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion()).as<GameObject>();
	gameObject->GetComponent<GroundItemController>()->init(ItemsManager::im->getItem(itemRef->id));
	ItemsManager::im->updateItem(itemRef->id, SceneManager::GetActiveScene().get_name(), (int)PlayerController::wc->currentXY.x, (int)PlayerController::wc->currentXY.y);
}

bool InventoryController::pickOrDropItem(P<Item> itemRef, bool silent)
{
	if (pickUpItem(itemRef, silent))
	{
		return true;
	}
	dropItem(itemRef);
	return false;
}

bool InventoryController::isItemEquipped(String item)
{
	if (ItemsManager::im->getItem(item)->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1 && GameDataController::gd->equipped == item)
	{
		return true;
	}
	return false;
}

bool InventoryController::isUnequipped(String item)
{
	if (!isItemInInventory(item))
	{
		return false;
	}
	if (isItemEquipped(item))
	{
		return false;
	}
	return true;
}

bool InventoryController::isItemInInventory(String item)
{
	if (ItemsManager::im->getItem(item)->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
	{
		return true;
	}
	return false;
}

bool InventoryController::isItemInInventoryOrTrunkOrWhatever(String item)
{
	if (ItemsManager::im->getItem(item)->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
	{
		return true;
	}
	if (ItemsManager::im->getItem(item)->dataRef->droppedLocation.ToLower().IndexOf(S("trunk")) != -1)
	{
		return true;
	}
	if (ItemsManager::im->getItem(item)->dataRef->droppedLocation.ToLower().IndexOf(S("chest")) != -1)
	{
		return true;
	}
	return false;
}
