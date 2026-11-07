#include "../game_all.h"

void SiderealDisc2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action1_e");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("disc2");
	range = 1.0f;
	teleport = false;
	updateState();
}

void SiderealDisc2::Update()
{
}

void SiderealDisc2::whatOnClick()
{
}

void SiderealDisc2::clickAction()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("disc2"))))
	{
		if (GameDataController::KART)
		{
			GameDataController::persistentData->kong_disk = true;
			GameDataController::gd->PersistentSave();
		}
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("pick_disc2")));
		GameDataController::gd->setObjective(S("sidereal_disc2_taken"), true);
		updateAll();
	}
}

void SiderealDisc2::updateState()
{
	GetComponent<SpriteRenderer>()->set_enabled(true);
	blik->set_enabled(true);
	if (GameDataController::gd->getObjective(S("sidereal_disc2_taken")))
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

void SiderealDisc2::clickAction2()
{
}

void SiderealDisc2::clickAction0()
{
}
