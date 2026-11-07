#include "../game_all.h"

void CS2Maggot::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_maggot");
	range = 1.0f;
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
}

void CS2Maggot::Update()
{
}

void CS2Maggot::clickAction()
{
	PlayerController::pc->aS->PlayOneShot(ItemsManager::im->getItem(S("maggot"))->sound);
	cursorController->selectItem(ItemsManager::im->getItem(S("maggot")));
}

void CS2Maggot::updateState()
{
	if (GameDataController::gd->getObjective(S("cs_thug_shot")) || GameDataController::gd->getObjective(S("cs_safe")))
	{
		setCollider(-1);
	}
	else
	{
		setCollider(0);
	}
}

void CS2Maggot::clickAction2()
{
}

void CS2Maggot::clickAction0()
{
}

void CS2Maggot::whatOnClick0()
{
}

void CS2Maggot::whatOnClick()
{
}
