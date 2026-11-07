#include "../game_all.h"

void SimpleRounderToNearest::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
}

void SimpleRounderToNearest::Update()
{
}
