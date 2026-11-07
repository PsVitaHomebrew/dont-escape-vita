#include "../game_all.h"

void WorldCaption::Start()
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2(120.0f, 67.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	gameObject->transform->set_position(position);
	t = GetComponent<TextFieldController>();
	if (overrideString != String::Empty)
	{
		t->viewText(overrideString, false, true, true, width, r / 255.0f, g / 255.0f, b / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		t->viewText(GameStrings::getString(GameStrings::world_labels, nameToDisplay), false, true, true, width, r / 255.0f, g / 255.0f, b / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	t->keepAlive = true;
}

void WorldCaption::Update()
{
}

void WorldCaption::manualUpdate()
{
	Start();
}

void WorldCaption::hide()
{
	t = GetComponent<TextFieldController>();
	t->viewText(S(" "), false, true, true, width, r / 255.0f, g / 255.0f, b / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}
