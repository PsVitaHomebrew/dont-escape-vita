#include "../game_all.h"

void LocationOutpost10Item1::Start()
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

void LocationOutpost10Item1::Update()
{
}

void LocationOutpost10Item1::whatOnClick()
{
}

void LocationOutpost10Item1::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("engine_calibrator"))))
	{
		GameDataController::gd->setObjective(S("outpost_calibrator_taken"), true);
		updateState();
	}
}

void LocationOutpost10Item1::updateState()
{
	if (!GameDataController::gd->getObjective(S("outpost_calibrator_taken")))
	{
		characterAnimationName = S("action1_e");
		animationFlip = true;
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

void LocationOutpost10Item1::clickAction2()
{
}

void LocationOutpost10Item1::clickAction0()
{
}
