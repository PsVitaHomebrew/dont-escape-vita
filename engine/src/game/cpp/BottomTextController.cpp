#include "../game_all.h"

void BottomTextController::Start()
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2(3.0f, 15.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	gameObject->transform->set_position(position);
	gameObject->GetComponent<TextFieldController>()->maxWidth = bottomTextWidth;
	gameObject->GetComponent<TextFieldController>()->shift.x = 3.0f;
}

void BottomTextController::Update()
{
}
