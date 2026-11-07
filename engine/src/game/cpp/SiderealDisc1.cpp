#include "../game_all.h"

void SiderealDisc1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("disc1");
	range = 1.0f;
	teleport = false;
	updateState();
}

void SiderealDisc1::Update()
{
}

void SiderealDisc1::whatOnClick()
{
}

void SiderealDisc1::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("disc1"))))
	{
		if (GameDataController::KART)
		{
			GameDataController::persistentData->kong_disk = true;
			GameDataController::gd->PersistentSave();
		}
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("pick_disc1")));
		GameDataController::gd->setObjective(S("sidereal_disc1_taken"), true);
		updateAll();
	}
}

void SiderealDisc1::updateState()
{
	GetComponent<SpriteRenderer>()->set_enabled(true);
	blik->set_enabled(true);
	if (GameDataController::gd->getObjective(S("sidereal_disc1_taken")))
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
		blik->set_enabled(false);
	}
	else
	{
		setCollider(0);
	}
}

void SiderealDisc1::clickAction2()
{
}

void SiderealDisc1::clickAction0()
{
}
