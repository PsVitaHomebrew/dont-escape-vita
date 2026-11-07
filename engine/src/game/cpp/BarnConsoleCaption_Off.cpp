#include "../game_all.h"

void BarnConsoleCaption_Off::Start()
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2(120.0f, 67.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -0.9f;
	gameObject->transform->set_position(position);
	t = GetComponent<TextFieldController>();
	t->useSeparateCamera = false;
	t->viewText(GameStrings::getString(GameStrings::world_labels, nameToDisplay), false, true, true, 200, colormod * 48.0f / 255.0f, colormod * 82.0f / 255.0f, colormod * 33.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	t->keepAlive = true;
}

void BarnConsoleCaption_Off::Update()
{
}
