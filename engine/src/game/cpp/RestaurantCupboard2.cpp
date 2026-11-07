#include "../game_all.h"

void RestaurantCupboard2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_cupboard");
	range = 1.0f;
}

void RestaurantCupboard2::clickAction()
{
	if (!GameDataController::gd->getObjective(S("restaurant_cupboard2_open")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->cabinet_1);
		GameDataController::gd->setObjective(S("restaurant_cupboard2_open"), true);
		updateState();
	}
}

void RestaurantCupboard2::updateState()
{
	if (GameDataController::gd->getObjective(S("restaurant_cupboard2_open")))
	{
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(s2);
	}
	else
	{
		setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(s1);
	}
}

void RestaurantCupboard2::clickAction2()
{
}

void RestaurantCupboard2::clickAction0()
{
}
