#include "../game_all.h"

void LocationOutpost10Item2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_item1");
	range = 1.0f;
	teleport = false;
	sr = gameObject->GetComponent<SpriteRenderer>();
	updateState();
	actionType = Type::NormalAction;
}

void LocationOutpost10Item2::Update()
{
}

void LocationOutpost10Item2::whatOnClick()
{
}

void LocationOutpost10Item2::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("lioh_filter"))))
	{
		GameDataController::gd->setObjective(S("outpost_filter_taken"), true);
		updateState();
	}
}

void LocationOutpost10Item2::updateState()
{
	if (!GameDataController::gd->getObjective(S("outpost_filter_taken")))
	{
		characterAnimationName = S("action1_e");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
		setCollider(0);
		sr->set_enabled(true);
	}
	else
	{
		setCollider(-1);
		sr->set_enabled(false);
	}
}

void LocationOutpost10Item2::clickAction2()
{
}

void LocationOutpost10Item2::clickAction0()
{
}
