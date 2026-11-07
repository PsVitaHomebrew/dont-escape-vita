#include "../game_all.h"

void LocationOutpostCard::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_card");
	range = 0.0f;
	teleport = false;
	sr = gameObject->GetComponent<SpriteRenderer>();
	updateState();
	actionType = Type::NormalAction;
}

void LocationOutpostCard::Update()
{
	if (fastcheck || (PlayerController::wc->currentXY.x >= 158.0f && PlayerController::wc->currentXY.x <= 170.0f && PlayerController::wc->currentXY.y < 18.0f))
	{
		light1->set_enabled(false);
	}
	else
	{
		light1->set_enabled(true);
	}
}

void LocationOutpostCard::whatOnClick()
{
}

void LocationOutpostCard::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("outpost_card"))))
	{
		GameDataController::gd->setObjective(S("outpost_card_taken"), true);
		updateState();
	}
}

void LocationOutpostCard::updateState()
{
	if (!GameDataController::gd->getObjective(S("outpost_card_taken")) && GameDataController::gd->getObjective(S("outpost_switch_pressed")))
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
	fastcheck = GameDataController::gd->getObjective(S("outpost_card_taken")) || !GameDataController::gd->getObjective(S("outpost_switch_pressed"));
}

void LocationOutpostCard::clickAction2()
{
}

void LocationOutpostCard::clickAction0()
{
}
