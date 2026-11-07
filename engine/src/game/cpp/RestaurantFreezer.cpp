#include "../game_all.h"

void RestaurantFreezer::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_freezer");
	range = 1.0f;
}

void RestaurantFreezer::clickAction()
{
	if (!GameDataController::gd->getObjective(S("restaurant_freezer_open")))
	{
		GameDataController::gd->setObjective(S("restaurant_freezer_open"), true);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fridge);
		updateAll();
	}
	else if (!GameDataController::gd->getObjective(S("restaurant_absorbers_taken")))
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("restaurant_freezer"));
		timelineAction->function = [this](String param) { getHeaters(param); };
		timelineAction->actionWithText = false;
		Timeline::t->addAction(timelineAction);
		Timeline::t->doNotUnlock = true;
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("restaurant_freezer_empty")));
	}
}

void RestaurantFreezer::getHeaters(String param)
{
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("heat_absorber1")));
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("heat_absorber2")));
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("heat_absorber3")));
	PlayerController::pc->forceAnimation(S("action_n"));
	GameDataController::gd->setObjective(S("restaurant_absorbers_taken"), true);
	updateAll();
}

void RestaurantFreezer::updateState()
{
	if (!GameDataController::gd->getObjective(S("restaurant_freezer_open")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_sprite(closed);
		characterAnimationName = S("action_n");
		range = 1.0f;
		animationFlip = false;
		useCurrentDirection = false;
	}
	else if (!GameDataController::gd->getObjective(S("restaurant_absorbers_taken")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_sprite(open_0);
		characterAnimationName = S("action_stnd_n");
		range = 1.0f;
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_sprite(open_0);
		characterAnimationName = S("action_stnd_");
		range = 30.0f;
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void RestaurantFreezer::clickAction2()
{
	if (GameDataController::gd->getObjective(S("restaurant_absorbers_taken")))
	{
	}
}

void RestaurantFreezer::clickAction0()
{
}
