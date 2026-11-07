#include "../game_all.h"

void InventoryButtonController::Awake()
{
	if (ibc == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		ibc = this;
	}
	else if (ibc != P<InventoryButtonController>(this))
	{
		Object::Destroy(gameObject);
	}
}

bool InventoryButtonController::isItOpen()
{
	return isOpen;
}

void InventoryButtonController::Start()
{
	spaceWasPressed = false;
	frame_name = S("inventory_button_closed_");
	frame_name_sufix = S("0");
	inventory = InventoryController::ic;
	invCapCont = InventoryCapMeterController::cm;
	isOpen = true;
	close();
	justClosed = false;
	pozycja = Vector2(14.0f, 127.0f);
	Vector2 vector = ScreenControler::gameToScreen(pozycja);
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -1.5f;
	gameObject->transform->set_position(position);
}

void InventoryButtonController::Update()
{
}

void InventoryButtonController::open(int invno)
{
	Timeline::t->stopChitChat();
	Vector3 position = gameObject->transform->get_position();
	position.z = -3.0f;
	gameObject->transform->set_position(position);
	PlayerController::wc->fullStop(true);
	invCapCont->updateText();
	GameDataController::gd->saveIfOK(String::Empty);
	if (CursorController::cc->selectedItemRef != nullptr && CursorController::cc->selectedItemRef->weight < 0.0f)
	{
		CursorController::cc->deselectItem();
	}
	frame_name = S("inventory_button_open_");
	isOpen = true;
	inventory->gameObject->SetActive(true);
	if (invno == 1)
	{
		inventory->InvTrunkClose->initButton(S("  ") + GameStrings::getString(GameStrings::gui, S("close")) + S("  "));
		InventoryController::ic->trunk->SetActive(true);
	}
	if (invno == 2)
	{
		inventory->InvChestClose->initButton(S("  ") + GameStrings::getString(GameStrings::gui, S("close")) + S("  "));
		InventoryController::ic->chest->SetActive(true);
	}
	gameObject->GetComponent<Animator>()->Play(frame_name + frame_name_sufix, 0);
}

void InventoryButtonController::unstuckTrunk()
{
	GameObject::Find(S("Trunk"))->GetComponent<CarTrunk>()->setCollider(0);
}

void InventoryButtonController::close()
{
	if (isOpen)
	{
		frame_name = S("inventory_button_closed_");
		isOpen = false;
		GameObject::Find(S("bag_drop"))->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
		Vector3 position = gameObject->transform->get_position();
		position.z = -1.5f;
		gameObject->transform->set_position(position);
		spaceWasPressed = false;
		if (!InventoryController::ic->blocker->get_enabled())
		{
			ibc->justClosed = true;
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->trunk_close);
		}
		inventory->cleanUp();
		InventoryController::ic->blocker->set_enabled(true);
		inventory->InvTrunkClose->buttonText->dissmiss(true);
		inventory->InvChestClose->buttonText->dissmiss(true);
		inventory->gameObject->SetActive(false);
		gameObject->GetComponent<Animator>()->Play(frame_name + frame_name_sufix, 0);
		InventoryController::ic->trunk->SetActive(false);
		InventoryController::ic->chest->SetActive(false);
	}
}

void InventoryButtonController::showInventory(String param)
{
	gameObject->GetComponent<BoxCollider2D>()->set_enabled(false);
	Invoke(S("show"), 0.25f);
	Invoke(S("hide"), 0.5f);
	Invoke(S("show"), 0.75f);
	Invoke(S("hide"), 1.0f);
	Invoke(S("show"), 1.25f);
	Invoke(S("hide"), 1.5f);
	Invoke(S("show"), 1.75f);
	Invoke(S("hide"), 2.0f);
	Invoke(S("showFinal"), 2.25f);
}

void InventoryButtonController::showFinal()
{
	show();
	gameObject->GetComponent<BoxCollider2D>()->set_enabled(true);
}

void InventoryButtonController::show()
{
	Vector2 vector = ScreenControler::gameToScreen(pozycja);
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -4.0f;
	gameObject->transform->set_position(position);
}

void InventoryButtonController::hide()
{
	gameObject->GetComponent<BoxCollider2D>()->set_enabled(false);
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-9999.0f, -9999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -4.0f;
	gameObject->transform->set_position(position);
}

void InventoryButtonController::openTrunk()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->trunk_open);
	InventoryController::ic->blocker->set_enabled(false);
	open(1);
}

void InventoryButtonController::openChest()
{
	InventoryController::ic->blocker->set_enabled(false);
	open(2);
}

void InventoryButtonController::OnMouseOver()
{
	if (!PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		CursorController::cc->showCursor(CursorController::PixelCursor::ACTIVE);
		if (frame_name_sufix != S("1"))
		{
			if (isOpen)
			{
			}
			frame_name_sufix = S("1");
			gameObject->GetComponent<Animator>()->Play(frame_name + frame_name_sufix, 0);
			P<GameObject> gameObject = GameObject::Find(S("BottomText"));
			gameObject->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("inventory")), false, true, false, 200);
		}
	}
	else
	{
		OnMouseExit();
	}
}

void InventoryButtonController::OnMouseExit()
{
	if (!PlayerController::wc->busy)
	{
		GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController::PixelCursor::NORMAL);
		P<GameObject> gameObject = GameObject::Find(S("BottomText"));
		gameObject->GetComponent<TextFieldController>()->keepAlive = false;
		frame_name_sufix = S("0");
		this->gameObject->GetComponent<Animator>()->Play(frame_name + frame_name_sufix, 0);
	}
}

void InventoryButtonController::fakeMouseClick(bool spacja)
{
	spaceWasPressed = spacja;
	OnMouseDown();
	PlayerController::pc->clickedSomething = false;
}

void InventoryButtonController::OnMouseDown()
{
	if (!PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		PlayerController::pc->clickedSomething = true;
		if (isOpen)
		{
			close();
		}
		else
		{
			open();
		}
	}
}
