#include "../game_all.h"

void DigitalNumber::Start()
{
	sr = GetComponent<SpriteRenderer>();
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
}

void DigitalNumber::Update()
{
	int objectiveDetail = GameDataController::gd->getObjectiveDetail(dataSource);
	sr->set_sprite(digits[int_Parse(str(str(objectiveDetail)[digit]))]);
}
