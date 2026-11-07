#include "../game_all.h"

void SiderealLabVials1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_up_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lab_vials");
	range = 1.0f;
	teleport = false;
	updateState();
}

void SiderealLabVials1::Update()
{
}

void SiderealLabVials1::whatOnClick()
{
}

void SiderealLabVials1::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("vials1"))))
	{
		GameDataController::gd->setObjective(S("sidereal_vials1_taken"), true);
		updateAll();
	}
}

void SiderealLabVials1::updateState()
{
	GetComponent<SpriteRenderer>()->set_enabled(true);
	if (GameDataController::gd->getObjective(S("sidereal_vials1_taken")))
	{
		setCollider(-1);
		if (GameDataController::gd->getObjective(S("sidereal_components_1")))
		{
			GetComponent<SpriteRenderer>()->set_sprite(vb);
			setCollider(-1);
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(va);
		setCollider(0);
	}
}

void SiderealLabVials1::clickAction2()
{
}

void SiderealLabVials1::clickAction0()
{
}
