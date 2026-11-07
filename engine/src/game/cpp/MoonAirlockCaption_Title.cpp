#include "../game_all.h"

void MoonAirlockCaption_Title::Start()
{
	t = GetComponent<TextFieldController>();
	t->viewText(GameStrings::getString(GameStrings::world_labels, nameToDisplay), false, true, true, 200, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	t->keepAlive = true;
}

void MoonAirlockCaption_Title::Update()
{
}
