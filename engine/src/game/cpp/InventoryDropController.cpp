#include "../game_all.h"

void InventoryDropController::Start()
{
	inventoryButton = GameObject::Find(S("inventory_button"));
	animationFlip = false;
	characterAnimationName = S("kneel_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
	invetoryController = GameObject::Find(S("inventory"))->GetComponent<InventoryController>();
	itemsManager = GameObject::Find(S("ItemsManager"))->GetComponent<ItemsManager>();
	walkControllerr = PlayerController::wc;
	dkvs = GameStrings::gui;
	objectName = S("drop");
}

void InventoryDropController::whatOnClick0()
{
	if (PlayerController::wc->dir == WalkController::Direction::N)
	{
		if (Random::Range(0.0f, 1.0f) >= 0.5f)
		{
			PlayerController::wc->forceDirection(WalkController::Direction::E);
		}
		else
		{
			PlayerController::wc->forceDirection(WalkController::Direction::W);
		}
	}
	else if (PlayerController::wc->dir == WalkController::Direction::NE)
	{
		PlayerController::wc->forceDirection(WalkController::Direction::E);
	}
	else if (PlayerController::wc->dir == WalkController::Direction::NW)
	{
		PlayerController::wc->forceDirection(WalkController::Direction::W);
	}
}

void InventoryDropController::clickAction()
{
	PlayerController::pc->clickedSomething = false;
	if (PlayerController::pc->allowDrop && CursorController::cc->selectedItemName != String::Empty)
	{
		Vector2 vector = ScreenControler::gameToScreen(Vector2(walkControllerr->currentXY.x, walkControllerr->currentXY.y + (float)GroundItemController::yOffset));
		Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
		vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
		PlayerController::pc->aS->PlayOneShot(cursorController->selectedItemRef->sound);
		P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion()).as<GameObject>();
		gameObject->GetComponent<GroundItemController>()->init(cursorController->selectedItemRef);
		invetoryController->removeItem(cursorController->selectedItemName);
		cursorController->selectedItemRef->dataRef->locX = (int)walkControllerr->currentXY.x;
		cursorController->selectedItemRef->dataRef->locY = (int)walkControllerr->currentXY.y;
		cursorController->selectedItemRef->dataRef->droppedLocation = SceneManager::GetActiveScene().get_name();
		JournalTexts::pickTexts(GameDataController::gd->getCurrentDay());
		cursorController->deselectItem();
	}
}

void InventoryDropController::updateState()
{
}

void InventoryDropController::clickAction2()
{
}

void InventoryDropController::OnMouseEnter()
{
	CursorController::cc->showCursor(CursorController::PixelCursor::ACTIVE);
	if (!PlayerController::wc->busy)
	{
		gameObject->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
		P<GameObject> gameObject = GameObject::Find(S("BottomText"));
		if (!PlayerController::pc->allowDrop)
		{
			gameObject->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("no_drop")), false, true, false, 200);
			return;
		}
		if (CursorController::cc->selectedItemName.Equals(String::Empty))
		{
			gameObject->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("drop_a")) + S("^") + GameStrings::getString(GameStrings::gui, S("drop_b")), false, true, false, 240);
			return;
		}
		gameObject->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("drop1")) + S(" ") + GameStrings::getString(GameStrings::items, CursorController::cc->selectedItemName + S("_short")) + S(" ") + GameStrings::getString(GameStrings::gui, S("drop2")), false, true, false, 240);
	}
}

void InventoryDropController::OnMouseExit()
{
	CursorController::cc->showCursor(CursorController::PixelCursor::NORMAL);
	P<GameObject> gameObject = GameObject::Find(S("BottomText"));
	if (!PlayerController::wc->busy)
	{
		this->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	}
	gameObject->GetComponent<TextFieldController>()->keepAlive = false;
}

void InventoryDropController::OnMouseDown()
{
	PlayerController::pc->clickedSomething = true;
	if (PlayerController::wc->busy || !(CursorController::cc->selectedItemName != String::Empty) || !PlayerController::pc->allowDrop)
	{
		return;
	}
	PlayerController::wc->setSimpleTarget(PlayerController::wc->currentXY);
	PlayerController::wc->onFinishWalking = this;
	inventoryButton->GetComponent<InventoryButtonController>()->close();
	P<GameObject> gameObject = GameObject::Find(S("BottomText"));
	gameObject->GetComponent<TextFieldController>()->keepAlive = false;
	this->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	CursorController::cc->showCursor(CursorController::PixelCursor::NORMAL);
	if (PlayerController::wc->dir == WalkController::Direction::N)
	{
		if (Random::Range(0.0f, 1.0f) >= 0.5f)
		{
			PlayerController::wc->forceDirection(WalkController::Direction::E);
		}
		else
		{
			PlayerController::wc->forceDirection(WalkController::Direction::W);
		}
	}
	else if (PlayerController::wc->dir == WalkController::Direction::NE)
	{
		PlayerController::wc->forceDirection(WalkController::Direction::E);
	}
	else if (PlayerController::wc->dir == WalkController::Direction::NW)
	{
		PlayerController::wc->forceDirection(WalkController::Direction::W);
	}
}

void InventoryDropController::clickAction0()
{
}
