#include "../game_all.h"

void GearsController::Start()
{
	if (condition == S("auto"))
	{
		condition = S("dream_day_") + GameDataController::gd->getCurrentDay() + S("_started");
	}
	if (condition == nullptr || condition == String::Empty || GameDataController::gd->getObjective(condition))
	{
		showGears();
	}
}

void GearsController::show()
{
	if (condition == nullptr || condition == String::Empty || GameDataController::gd->getObjective(condition))
	{
		Vector2 vector = ScreenControler::gameToScreen(Vector2(229.0f, 125.0f));
		Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
		position.z = -2.5f;
		gameObject->transform->set_position(position);
		gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel3(gameObject->transform->get_position()));
		spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(normal);
		spriteRenderer->set_enabled(true);
	}
}

void GearsController::showFinal()
{
	gameObject->GetComponent<BoxCollider2D>()->set_enabled(true);
	show();
}

void GearsController::hide()
{
	spriteRenderer->set_enabled(false);
}

void GearsController::showGears(bool fast)
{
	if (!fast)
	{
		gameObject->GetComponent<BoxCollider2D>()->set_enabled(true);
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
	else
	{
		show();
	}
}

void GearsController::Update()
{
	if (Input::GetKeyDown(KeyCode::Escape) && !PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE && (condition == nullptr || condition == String::Empty || GameDataController::gd->getObjective(condition)))
	{
		OnMouseDown();
	}
}

void GearsController::OnMouseOver()
{
	if (!PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController::PixelCursor::ACTIVE);
		if (frame_name_sufix != S("1"))
		{
			frame_name_sufix = S("1");
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(active);
			P<GameObject> gameObject = GameObject::Find(S("BottomText"));
			String text = GameStrings::getString(GameStrings::gui, S("gears"));
			gameObject->GetComponent<TextFieldController>()->viewText(text, false, true, false, BottomTextController::bottomTextWidth);
		}
	}
	else
	{
		OnMouseExit();
	}
}

void GearsController::OnMouseExit()
{
	if (!PlayerController::wc->busy)
	{
		frame_name_sufix = S("0");
		GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController::PixelCursor::NORMAL);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(normal);
		P<GameObject> gameObject = GameObject::Find(S("BottomText"));
		gameObject->GetComponent<TextFieldController>()->keepAlive = false;
	}
}

void GearsController::OnMouseDown()
{
	if (!PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		PlayerController::pc->clickedSomething = true;
		if (InventoryButtonController::ibc->gameObject->GetComponent<BoxCollider2D>()->get_enabled())
		{
			InventoryButtonController::ibc->close();
		}
		CursorController::cc->deselectItem();
		if (InventoryController::ic != nullptr)
		{
			InventoryController::ic->gameObject->SetActive(false);
		}
		PlayerController::wc->fullStop(true);
		if (PlayerController::wc->speed != 0.0f)
		{
			PlayerController::wc->forceAnimation(S("stand_"), false, true);
		}
		PlayerController::pc->spawnName = S("InfoExit");
		PlayerController::pc->textField->dissmiss(true);
		GameDataController::gd->previousLocation = SceneManager::GetActiveScene().get_name();
		GameDataController::gd->previousX = (int)PlayerController::wc->currentXY.x;
		GameDataController::gd->previousY = (int)PlayerController::wc->currentXY.y;
		ScreenShots::ss->shot();
		CurtainController::cc->fadeOut(S("PauseMenu"), WalkController::Direction::NULL_, nullptr, nullptr, false, nullptr, 1.0f);
		AudioListener::set_pause(true);
	}
}
