#include "../game_all.h"

void RestaurantFlag::Start()
{
	if (GameDataController::gd->getObjective(S("restaurant_flag_lowered")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void RestaurantFlag::Update()
{
}
