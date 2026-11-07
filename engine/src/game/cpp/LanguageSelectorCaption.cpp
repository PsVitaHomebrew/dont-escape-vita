#include "../game_all.h"

void LanguageSelectorCaption::Start()
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2(15.0f, 15.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	gameObject->transform->set_position(position);
	t = GetComponent<TextFieldController>();
	updateText();
}

void LanguageSelectorCaption::updateText()
{
	t->viewText(GameStrings::getString(GameStrings::languages, PlayerPrefs::GetString(S("lang"), str(GameStrings_Language::EN))), false, true, true, 200, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f);
	t->keepAlive = true;
}

void LanguageSelectorCaption::hideText()
{
	t->dissmiss(true);
	t->keepAlive = false;
}

void LanguageSelectorCaption::Update()
{
}
