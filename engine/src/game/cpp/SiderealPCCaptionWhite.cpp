#include "../game_all.h"

void SiderealPCCaptionWhite::Start()
{
	t = GetComponent<TextFieldController>();
	t->viewText(GameStrings::getString(GameStrings::world_labels, nameToDisplay), false, true, true, 200, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	t->keepAlive = true;
}

void SiderealPCCaptionWhite::Update()
{
}
