#include "../game_all.h"

void SiderealLabVials2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lab_vials");
	range = 1.0f;
	teleport = false;
	updateState();
}

void SiderealLabVials2::Update()
{
}

void SiderealLabVials2::whatOnClick()
{
}

void SiderealLabVials2::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("vials2"))))
	{
		GameDataController::gd->setObjective(S("sidereal_vials2_taken"), true);
		updateAll();
	}
}

void SiderealLabVials2::updateState()
{
	GetComponent<SpriteRenderer>()->set_enabled(true);
	if (GameDataController::gd->getObjective(S("sidereal_vials2_taken")))
	{
		setCollider(-1);
		if (GameDataController::gd->getObjective(S("sidereal_components_2")))
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

void SiderealLabVials2::clickAction2()
{
}

void SiderealLabVials2::clickAction0()
{
}
