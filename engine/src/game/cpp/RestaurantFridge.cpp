#include "../game_all.h"

void RestaurantFridge::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_fridge");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("pipe"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("hammer"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
}

void RestaurantFridge::opensond()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fridge);
}

void RestaurantFridge::break_glass()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->break_window);
}

void RestaurantFridge::otherOpen()
{
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("action_stnd_ne"), nullptr, true);
	Invoke(S("break_glass"), 0.5f);
	GameDataController::gd->setObjective(S("restaurant_fridge_broken"), true);
}

void RestaurantFridge::crowbarOpen()
{
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("action_stnd_ne"), nullptr, true);
	Invoke(S("opensond"), 0.5f);
	GameDataController::gd->setObjective(S("restaurant_fridge_open"), true);
}

void RestaurantFridge::clickAction()
{
	if (!GameDataController::gd->getObjective(S("restaurant_fridge_open")) && !GameDataController::gd->getObjective(S("restaurant_fridge_broken")))
	{
		if (usedItem == String::Empty)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("restaurant_fridge_locked")));
		}
		else if (usedItem == S("crowbar"))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("restaurant_fridge_open")), QuestionController::PopupType::QUESTION, [this]() { crowbarOpen(); }, 5);
		}
		else
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("restaurant_fridge_break")), QuestionController::PopupType::QUESTION, [this]() { otherOpen(); }, 10);
		}
	}
	else if (!GameDataController::gd->getObjective(S("restaurant_water_taken1")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("water1"))))
		{
			GameDataController::gd->setObjective(S("restaurant_water_taken1"), true);
			updateAll();
		}
	}
	else if (!GameDataController::gd->getObjective(S("restaurant_water_taken2")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("water2"))))
	{
		GameDataController::gd->setObjective(S("restaurant_water_taken2"), true);
		updateAll();
	}
}

void RestaurantFridge::whatOnClick0()
{
	if (!GameDataController::gd->getObjective(S("restaurant_fridge_open")) && !GameDataController::gd->getObjective(S("restaurant_fridge_broken")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		characterAnimationName = S("action_n");
		animationFlip = true;
		useCurrentDirection = false;
	}
}

void RestaurantFridge::updateState()
{
	if (!GameDataController::gd->getObjective(S("restaurant_fridge_open")) && !GameDataController::gd->getObjective(S("restaurant_fridge_broken")))
	{
		setCollider(0);
		characterAnimationName = S("open_n");
		GetComponent<SpriteRenderer>()->set_sprite(closed);
		objectName = S("restaurant_fridge");
	}
	else if (!GameDataController::gd->getObjective(S("restaurant_water_taken1")) && !GameDataController::gd->getObjective(S("restaurant_fridge_broken")))
	{
		setCollider(1);
		GetComponent<SpriteRenderer>()->set_sprite(open_2);
		characterAnimationName = S("action_n");
		objectName = S("restaurant_fridge_water2");
	}
	else if (!GameDataController::gd->getObjective(S("restaurant_water_taken2")) && !GameDataController::gd->getObjective(S("restaurant_fridge_broken")))
	{
		setCollider(2);
		GetComponent<SpriteRenderer>()->set_sprite(open_1);
		characterAnimationName = S("action_n");
		objectName = S("restaurant_fridge_water1");
	}
	else if (!GameDataController::gd->getObjective(S("restaurant_fridge_broken")))
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_sprite(open_0);
	}
	else if (!GameDataController::gd->getObjective(S("restaurant_water_taken1")))
	{
		setCollider(1);
		GetComponent<SpriteRenderer>()->set_sprite(open_2b);
		characterAnimationName = S("action_n");
		objectName = S("restaurant_fridge_water2");
	}
	else if (!GameDataController::gd->getObjective(S("restaurant_water_taken2")))
	{
		setCollider(2);
		GetComponent<SpriteRenderer>()->set_sprite(open_1b);
		characterAnimationName = S("action_n");
		objectName = S("restaurant_fridge_water1");
	}
	else
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_sprite(open_0b);
	}
}

void RestaurantFridge::clickAction2()
{
}

void RestaurantFridge::clickAction0()
{
}
