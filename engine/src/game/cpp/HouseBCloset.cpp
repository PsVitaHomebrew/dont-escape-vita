#include "../game_all.h"

void HouseBCloset::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("open_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_inside_closet");
}

void HouseBCloset::clickAction()
{
	if (!GameDataController::gd->getObjective(S("house_b_closet_open")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_open_01);
		GameDataController::gd->setObjective(S("house_b_closet_open"), true);
		updateAll();
	}
}

void HouseBCloset::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("house_b_closet_open")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(-1);
		GameObject::Find(S("plane00a (1)"))->GetComponent<SpriteRenderer>()->set_sprite(shadow1);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("plane00a (1)"))->GetComponent<SpriteRenderer>()->set_sprite(shadow2);
	}
}

void HouseBCloset::clickAction2()
{
}

void HouseBCloset::clickAction0()
{
}
