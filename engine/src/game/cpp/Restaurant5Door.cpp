#include "../game_all.h"

void Restaurant5Door::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("open_door2");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_chem_door");
	actionType = Type::NormalAction;
	range = 1.0f;
}

void Restaurant5Door::clickAction()
{
	GetComponent<Animator>()->Play(S("door_open"));
	block->set_enabled(false);
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	setCollider(-1);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_open_01);
	GameDataController::gd->setObjective(S("restaurant_chem_door_open"), true);
}

void Restaurant5Door::shadowpop()
{
	shadow->set_enabled(true);
	updateAll();
}

void Restaurant5Door::updateState()
{
	colliderManager->setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	shadow->set_enabled(false);
	if (GameDataController::gd->getCurrentDay() > 2)
	{
		if (GameDataController::gd->getObjective(S("restaurant_chem_door_open")))
		{
			shadow->set_enabled(true);
			colliderManager->setCollider(-1);
			GetComponent<Animator>()->Play(S("door_opened"));
			shadow->set_enabled(true);
		}
		else
		{
			colliderManager->setCollider(0);
			GetComponent<Animator>()->Play(S("door_closed"));
		}
	}
	else
	{
		colliderManager->setCollider(-1);
		GetComponent<Animator>()->Play(S("door_closed"));
	}
}

void Restaurant5Door::clickAction2()
{
}

void Restaurant5Door::clickAction0()
{
}
