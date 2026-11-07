#include "../game_all.h"

void SiderealPCCaptionBlack::Start()
{
	t = GetComponent<TextFieldController>();
	t->viewText(GameStrings::getString(GameStrings::world_labels, nameToDisplay), false, true, true, 100, 111.0f / 255.0f, 111.0f / 255.0f, 111.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	t->keepAlive = true;
}

void SiderealPCCaptionBlack::Update()
{
}
