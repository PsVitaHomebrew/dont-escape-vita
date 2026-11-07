#include "../game_all.h"

void MapXController::Start()
{
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
	hide();
}

void MapXController::Update()
{
}

void MapXController::hide()
{
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
}

void MapXController::updateLocation(P<TravelAgency> target)
{
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	targetTravelAgency = target;
	transform->set_position(ScreenControler::roundToNearestFullPixel2(target->gameObject->transform->Find(S("Action_Marker"))->transform->get_position()));
}
