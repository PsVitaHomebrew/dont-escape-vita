#include "../game_all.h"

void RestaurantPole::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_pole_clamp");
	range = 1.0f;
	teleport = false;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("pipe"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("restaurant_pole_wrong")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("restaurant_pole_wrong")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("screwdriver"), GameStrings::getString(GameStrings::actions, S("restaurant_pole_wrong")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("knife"), GameStrings::getString(GameStrings::actions, S("restaurant_pole_wrong")), nullptr, String::Empty));
}

void RestaurantPole::Update()
{
}

void RestaurantPole::whatOnClick0()
{
	if (usedItem == S("pipe") || (GameDataController::gd->getObjective(S("restaurant_pipe_inserted")) && !GameDataController::gd->getObjective(S("restaurant_pipe_switched"))))
	{
		range = 1.0f;
		characterAnimationName = S("action_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		range = 10.0f;
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void RestaurantPole::clickAction()
{
	if (usedItem == String::Empty)
	{
		if (GameDataController::gd->getObjective(S("restaurant_pipe_inserted")))
		{
			if (GameDataController::gd->getObjective(S("restaurant_pipe_switched")))
			{
				PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_pole_done")), true, false, false, 150);
				return;
			}
			GameDataController::gd->setObjective(S("restaurant_pipe_switched"), true);
			updateAll();
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_pole")), true, false, false, 150);
		}
	}
	else if (usedItem == S("pipe"))
	{
		GameDataController::gd->setObjective(S("restaurant_pipe_inserted"), true);
		InventoryController::ic->removeItem(S("pipe"));
		updateAll();
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_pole_pipe")), true, false, false, 150);
	}
}

void RestaurantPole::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("restaurant_pipe_inserted")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else if (GameDataController::gd->getObjective(S("restaurant_pipe_inserted")) && GameDataController::gd->getObjective(S("restaurant_pipe_switched")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(lever1);
	}
	else if (GameDataController::gd->getObjective(S("restaurant_pipe_inserted")) && !GameDataController::gd->getObjective(S("restaurant_pipe_switched")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(lever2);
	}
}

void RestaurantPole::clickAction2()
{
}

void RestaurantPole::clickAction0()
{
}
