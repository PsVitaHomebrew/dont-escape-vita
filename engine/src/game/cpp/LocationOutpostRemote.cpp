#include "../game_all.h"

void LocationOutpostRemote::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_remote");
	range = 1.0f;
	teleport = false;
	sr = gameObject->GetComponent<SpriteRenderer>();
	updateState();
	actionType = Type::NormalAction;
}

void LocationOutpostRemote::Update()
{
	if (fastcheck || (PlayerController::wc->currentXY.x >= 170.0f && PlayerController::wc->currentXY.x <= 180.0f))
	{
		light1->set_enabled(false);
	}
	else
	{
		light1->set_enabled(true);
	}
}

void LocationOutpostRemote::whatOnClick()
{
}

void LocationOutpostRemote::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("remote"))))
	{
		GameDataController::gd->setObjective(S("outpost_remote_taken"), true);
		updateState();
	}
}

void LocationOutpostRemote::updateState()
{
	if (!GameDataController::gd->getObjective(S("outpost_remote_taken")) && GameDataController::gd->getObjective(S("outpost_switch_pressed")))
	{
		characterAnimationName = S("action_n");
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
	fastcheck = GameDataController::gd->getObjective(S("outpost_remote_taken")) || !GameDataController::gd->getObjective(S("outpost_switch_pressed"));
}

void LocationOutpostRemote::clickAction2()
{
}

void LocationOutpostRemote::clickAction0()
{
}
