#include "../game_all.h"

void JournalButtonController::Start()
{
	pozycja = Vector2(30.0f, 124.0f);
	Vector2 vector = ScreenControler::gameToScreen(pozycja);
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -1.5f;
	gameObject->transform->set_position(position);
	exc = gameObject->transform->Find(S("exc"))->GetComponent<Animator>();
	exc->Play(S("journalW_0"), 0);
	excSprite = gameObject->transform->Find(S("exc"))->GetComponent<SpriteRenderer>();
	excSprite->set_enabled(false);
	if (GameDataController::gd->getCurrentDay() > 4)
	{
		hide();
	}
}

void JournalButtonController::showJournal(String param)
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

void JournalButtonController::setWarning(bool yesno)
{
	if (excSprite == nullptr)
	{
		excSprite = gameObject->transform->Find(S("exc"))->GetComponent<SpriteRenderer>();
	}
	if (yesno)
	{
		excSprite->set_enabled(true);
	}
	else
	{
		excSprite->set_enabled(false);
	}
}

void JournalButtonController::showFinal()
{
	if (GameDataController::gd->getCurrentDay() > 4)
	{
		hide();
		return;
	}
	show();
	gameObject->GetComponent<BoxCollider2D>()->set_enabled(true);
}

void JournalButtonController::show()
{
	Vector2 vector = ScreenControler::gameToScreen(pozycja);
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -4.0f;
	gameObject->transform->set_position(position);
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	frame_name_prefix = S("journal_");
	if (excSprite == nullptr)
	{
		excSprite = gameObject->transform->Find(S("exc"))->GetComponent<SpriteRenderer>();
	}
	if (excSprite == nullptr)
	{
		excSprite->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void JournalButtonController::hide()
{
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->GetComponent<BoxCollider2D>()->set_enabled(false);
	if (excSprite == nullptr)
	{
		excSprite = gameObject->transform->Find(S("exc"))->GetComponent<SpriteRenderer>();
	}
	if (excSprite != nullptr)
	{
		excSprite->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	}
}

void JournalButtonController::Update()
{
}

void JournalButtonController::OnMouseOver()
{
	if (!PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController_DialogueState::NONE)
	{
		GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController_PixelCursor::ACTIVE);
		if (frame_name_sufix != S("1"))
		{
			frame_name_sufix = S("1");
			this->gameObject->GetComponent<Animator>()->Play(frame_name_prefix + frame_name_sufix, 0);
			P<GameObject> gameObject = GameObject::Find(S("BottomText"));
			gameObject->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("journal")), false, true, false, ObjectActionController::BOTTOM_TEXT_WIDTH);
		}
	}
	else
	{
		OnMouseExit();
	}
}

void JournalButtonController::OnMouseExit()
{
	if (!PlayerController::wc->busy)
	{
		GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController_PixelCursor::NORMAL);
		P<GameObject> gameObject = GameObject::Find(S("BottomText"));
		gameObject->GetComponent<TextFieldController>()->keepAlive = false;
		frame_name_sufix = S("0");
		this->gameObject->GetComponent<Animator>()->Play(frame_name_prefix + frame_name_sufix, 0);
	}
}

void JournalButtonController::fakeClick()
{
	OnMouseDown();
}

void JournalButtonController::OnMouseDown()
{
	if (!PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController_DialogueState::NONE)
	{
		PlayerController::pc->clickedSomething = true;
		P<AudioClip> clip;
		switch (Random::Range(1, 5))
		{
		case 1:
			clip = SoundsManagerController::sm->page_turn_01;
			break;
		case 2:
			clip = SoundsManagerController::sm->page_turn_02;
			break;
		case 3:
			clip = SoundsManagerController::sm->page_turn_03;
			break;
		default:
			clip = SoundsManagerController::sm->page_turn_04;
			break;
		}
		if (InventoryButtonController::ibc->gameObject->GetComponent<BoxCollider2D>()->get_enabled())
		{
			InventoryButtonController::ibc->close();
		}
		CursorController::cc->deselectItem();
		inventory = InventoryController::ic;
		if (inventory != nullptr)
		{
			inventory->gameObject->SetActive(false);
		}
		PlayerController::pc->aS->PlayOneShot(clip, 0.5f);
		PlayerController::wc->fullStop(true);
		if (PlayerController::wc->speed != 0.0f)
		{
			PlayerController::wc->forceAnimation(S("stand_"), false, true);
		}
		PlayerController::pc->spawnName = S("InfoExit");
		GameDataController::gd->previousLocation = SceneManager::GetActiveScene().get_name();
		GameDataController::gd->previousX = (int)PlayerController::wc->currentXY.x;
		GameDataController::gd->previousY = (int)PlayerController::wc->currentXY.y;
		CurtainController::cc->fadeOut(S("InfoLocation"));
	}
}
