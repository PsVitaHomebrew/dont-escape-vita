#include "../game_all.h"

void SiderealCaptionNote::Start()
{
	t = GetComponent<TextFieldController>();
	t->viewText(GameStrings::getString(GameStrings::world_labels, nameToDisplay), false, true, true, 200, 56.0f / 255.0f, 56.0f / 255.0f, 101.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	t->keepAlive = true;
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
}

void SiderealCaptionNote::Update()
{
}
