#include "../game_all.h"

void DreamGearsController::Start()
{
	if (GameDataController::gd->getObjective(condition))
	{
		show();
		gameObject->GetComponent<BoxCollider2D>()->set_enabled(true);
		spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(normal);
	}
}

void DreamGearsController::show()
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2(229.0f, 125.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -4.0f;
	gameObject->transform->set_position(position);
}

void DreamGearsController::Update()
{
	if (Input::GetKeyDown(KeyCode::Escape) && !PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		OnMouseDown();
	}
}

void DreamGearsController::OnMouseOver()
{
	if (!PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController::PixelCursor::ACTIVE);
		if (frame_name_sufix != S("1"))
		{
			frame_name_sufix = S("1");
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(active);
			P<GameObject> gameObject = GameObject::Find(S("BottomText"));
			MonoBehaviour::print(S("no i co teraz?"));
			String text = GameStrings::getString(GameStrings::gui, S("gears"));
			gameObject->GetComponent<TextFieldController>()->viewText(text, false, true, false, BottomTextController::bottomTextWidth);
		}
	}
	else
	{
		OnMouseExit();
	}
}

void DreamGearsController::OnMouseExit()
{
	frame_name_sufix = S("0");
	GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController::PixelCursor::NORMAL);
	gameObject->GetComponent<SpriteRenderer>()->set_sprite(normal);
	P<GameObject> gameObject = GameObject::Find(S("BottomText"));
	gameObject->GetComponent<TextFieldController>()->keepAlive = false;
}

void DreamGearsController::OnMouseDown()
{
	if (!PlayerController::wc->busy && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		PlayerController::pc->clickedSomething = true;
		if (InventoryButtonController::ibc->gameObject->GetComponent<BoxCollider2D>()->get_enabled())
		{
			InventoryButtonController::ibc->close();
		}
		CursorController::cc->deselectItem();
		if ((bool)InventoryController::ic)
		{
			InventoryController::ic->gameObject->SetActive(false);
		}
		PlayerController::wc->fullStop(true);
		if (PlayerController::wc->speed != 0.0f)
		{
			PlayerController::wc->forceAnimation(S("stand_"), false, true);
		}
		PlayerController::pc->spawnName = S("InfoExit");
		GameDataController::gd->previousLocation = SceneManager::GetActiveScene().get_name();
		GameDataController::gd->previousX = (int)PlayerController::wc->currentXY.x;
		GameDataController::gd->previousY = (int)PlayerController::wc->currentXY.y;
		ScreenShots::ss->shot();
		CurtainController::cc->fadeOut(S("PauseMenu"), WalkController::Direction::NULL_, nullptr, nullptr, false, nullptr, 1.0f);
		AudioListener::set_pause(true);
	}
}
