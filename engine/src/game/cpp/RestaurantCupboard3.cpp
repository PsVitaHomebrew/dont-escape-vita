#include "../game_all.h"

void RestaurantCupboard3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_cupboard");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("paperclip"), GameStrings::getString(GameStrings::actions, S("cupboard_clip")), nullptr, String::Empty));
}

void RestaurantCupboard3::clickAction()
{
	if (usedItem == S("crowbar"))
	{
		if (!GameDataController::gd->getObjective(S("restaurant_cupboard3_open")))
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->wood_crack_2);
			GameDataController::gd->setObjective(S("restaurant_cupboard3_open"), true);
			updateAll();
		}
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->wood_crack_1);
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_kitchen_cupboard_locked")), true);
	}
}

void RestaurantCupboard3::whatOnClick()
{
	if (usedItem == S("crowbar"))
	{
		characterAnimationName = S("crowbar_e_low");
	}
	else
	{
		characterAnimationName = S("kneel_n");
	}
}

void RestaurantCupboard3::updateState()
{
	if (GameDataController::gd->getObjective(S("restaurant_cupboard3_open")))
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

void RestaurantCupboard3::clickAction2()
{
}

void RestaurantCupboard3::clickAction0()
{
}
