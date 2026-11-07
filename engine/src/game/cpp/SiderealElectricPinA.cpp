#include "../game_all.h"

void SiderealElectricPinA::Start()
{
	t = GetComponent<TextFieldController>();
	display(S("-"));
	t->keepAlive = true;
}

void SiderealElectricPinA::display(String val)
{
	t->viewText(val, false, true, true, 200, 76.0f / 255.0f, 78.0f / 255.0f, 4.0f / 15.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void SiderealElectricPinA::Update()
{
}
