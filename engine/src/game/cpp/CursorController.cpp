#include "../game_all.h"

void CursorController::Awake()
{
	if (cc == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		cc = this;
	}
	else if (cc != P<CursorController>(this))
	{
		Object::Destroy(gameObject);
	}
}

void CursorController::Start()
{
	selectedItem = gameObject->transform->Find(S("item_icon"))->gameObject;
	gameObject->transform->set_position(Vector3(0.0f, 0.0f, -9.0f));
	spriteRenderer = selectedItem->GetComponent<SpriteRenderer>();
	Vector2 vector = ScreenControler::gameToScreen(Vector2(8.0f, -8.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	Vector2 vector2 = ScreenControler::gameToScreen(Vector2(0.0f, 0.0f));
	Vector3 vector3 = Camera::get_main()->ScreenToWorldPoint(Vector3(vector2.x, vector2.y, 0.0f));
	position.x -= vector3.x;
	position.y -= vector3.y;
	position.z = selectedItem->transform->get_position().z;
	selectedItem->transform->set_position(position);
	deselectItem();
	showCursor(PixelCursor::NORMAL);
}

void CursorController::Update()
{
	Vector2 vectorToChange = Input::get_mousePosition();
	vectorToChange = ScreenControler::gameToScreen(ScreenControler::screenToGame(vectorToChange));
	Vector3 vector = Camera::get_main()->ScreenToWorldPoint(Vector3(vectorToChange.x, vectorToChange.y, -0.0f));
	gameObject->transform->set_position(Vector3(vector.x, vector.y, -9.0f));
	Cursor::set_visible(false);
	String stateName = String::Empty;
	if (currentState == PixelCursor::NORMAL)
	{
		stateName = S("cursor_normal");
	}
	if (currentState == PixelCursor::ACTIVE)
	{
		stateName = S("cursor_special1");
	}
	if (currentState == PixelCursor::TALK)
	{
		stateName = S("cursor_talk");
	}
	if (currentState == PixelCursor::INSPECT)
	{
		stateName = ((!Input::GetMouseButton(1)) ? S("cursor_special1") : S("cursor_inspect"));
	}
	if (currentState == PixelCursor::TRANSITION)
	{
		stateName = S("cursor_transition_") + str(trans_dir).ToLower();
	}
	if (overrideState == PixelCursor::BUSY)
	{
		stateName = S("cursor_special2");
	}
	if (PlayerController::wc->busy && !QuestionController::questionAsked && DialogueController::dc->hidden)
	{
		stateName = S("cursor_wait");
	}
	if (overrideState == PixelCursor::OK)
	{
		stateName = S("cursor_ok");
	}
	gameObject->GetComponent<Animator>()->Play(stateName, 0);
}

void CursorController::selectItem(P<Item> it)
{
	selectedItemRef = it;
	spriteRenderer->set_sprite(it->inventorySprite);
	spriteRenderer->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
	selectedItemName = it->id;
}

void CursorController::deselectItem()
{
	if (spriteRenderer != nullptr)
	{
		spriteRenderer->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	}
	selectedItemRef = nullptr;
	selectedItemName = String::Empty;
}

void CursorController::showCursor(CursorController_PixelCursor a, WalkController_Direction newDir)
{
	trans_dir = newDir;
	switch (a)
	{
	case PixelCursor::NORMAL:
		currentState = PixelCursor::NORMAL;
		break;
	case PixelCursor::ACTIVE:
		currentState = PixelCursor::ACTIVE;
		break;
	case PixelCursor::INSPECT:
		currentState = PixelCursor::INSPECT;
		break;
	case PixelCursor::TRANSITION:
		currentState = PixelCursor::TRANSITION;
		break;
	case PixelCursor::BUSY:
		overrideState = PixelCursor::BUSY;
		break;
	case PixelCursor::TALK:
		currentState = PixelCursor::TALK;
		break;
	case PixelCursor::OK:
		overrideState = PixelCursor::OK;
		break;
	}
}

CursorController_PixelCursor CursorController::getCurrentState()
{
	return overrideState;
}

void CursorController::clearOverride()
{
	overrideState = PixelCursor::NORMAL;
}
