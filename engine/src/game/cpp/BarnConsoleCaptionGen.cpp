#include "../game_all.h"

void BarnConsoleCaptionGen::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	t = GetComponent<TextFieldController>();
	t->useSeparateCamera = false;
	t->viewText(GameStrings::getString(GameStrings::world_labels, nameToDisplay), false, true, true, 200, 122.0f / 255.0f, 89.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	t->keepAlive = true;
}

void BarnConsoleCaptionGen::Update()
{
}
