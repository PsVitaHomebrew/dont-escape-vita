#include "../game_all.h"

void MapOController::Start()
{
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
	travelAgencies = Object::FindObjectsOfType<TravelAgency>();
	currentTravelAgency = getCurrentTravelAgency();
	updateLocation(currentTravelAgency);
	xMark = GameObject::Find(S("travel_target"))->GetComponent<MapXController>();
	xMark->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 1.0f / 17.0f, 104.0f / 255.0f, 1.0f));
	gameObject->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 1.0f / 17.0f, 104.0f / 255.0f, 1.0f));
}

void MapOController::Update()
{
}

P<TravelAgency> MapOController::getCurrentTravelAgency()
{
	for (int i = 0; i < travelAgencies.Length(); i++)
	{
		for (int j = 0; j < travelAgencies[i]->locations.Length(); j++)
		{
			if (GameDataController::gd->previousLocation == travelAgencies[i]->locations[j])
			{
				return travelAgencies[i];
			}
		}
	}
	return nullptr;
}

void MapOController::clearRoutes()
{
	xMark->hide();
	for (int i = 0; i < travelAgencies.Length(); i++)
	{
		travelAgencies[i]->renderRoute();
	}
}

void MapOController::updateLocation(P<TravelAgency> target)
{
	currentTravelAgency = target;
	transform->set_position(ScreenControler::roundToNearestFullPixel2(target->gameObject->transform->Find(S("Action_Marker"))->transform->get_position()));
}
