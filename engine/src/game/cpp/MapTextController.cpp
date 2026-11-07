#include "../game_all.h"

void MapTextController::Start()
{
	textfield = GameObject::Find(S("TopText"))->GetComponent<TextFieldController>();
	updateTime();
}

void MapTextController::Update()
{
}

void MapTextController::updateTime()
{
	Vector3 timeColor = ClockController::getTimeColor();
	textfield->viewText(ClockController::getClockTimeWithRemaining(), false, true, true, 200, timeColor.x, timeColor.y, timeColor.z, 0.0f, 0.0f, 0.0f, 0.2f);
	textfield->keepAlive = true;
}
