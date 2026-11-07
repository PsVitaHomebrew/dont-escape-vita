#include "../game_all.h"

void HuntersLodgeCouch::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_couch");
	range = 1.0f;
}

void HuntersLodgeCouch::clickAction()
{
	if (!GameDataController::gd->getObjective(S("hunters_lodge_scratches_found")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hunters_lodge_couch1")));
	}
	else if (!GameDataController::gd->getObjective(S("hunters_lodge_couch_moved")) && !GameDataController::gd->getObjective(S("hunters_lodge_couch_moved")) && GameDataController::gd->getObjective(S("hunters_lodge_scratches_found")))
	{
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.75f;
		PlayerController::wc->setSimpleTarget(Vector2(98.0f, 35.0f));
		gameObject->GetComponent<Animator>()->Play(S("couch_push"));
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->push);
		GameDataController::gd->setObjective(S("hunters_lodge_couch_moved"), true);
	}
}

void HuntersLodgeCouch::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("hunters_lodge_scratches_found")))
	{
		characterAnimationName = S("action_stnd_");
		useCurrentDirection = true;
		animationFlip = false;
		range = 100.0f;
		gameObject->GetComponent<Animator>()->Play(S("right"));
	}
	else if (!GameDataController::gd->getObjective(S("hunters_lodge_couch_moved")))
	{
		gameObject->GetComponent<Animator>()->Play(S("right"));
		characterAnimationName = S("push_e");
		useCurrentDirection = false;
		animationFlip = true;
		range = 1.0f;
	}
	else
	{
		colliderManager->setCollider(-1);
		gameObject->GetComponent<Animator>()->Play(S("left"));
	}
}

void HuntersLodgeCouch::clickAction2()
{
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	updateAll();
}

void HuntersLodgeCouch::clickAction0()
{
}

void HuntersLodgeCouch::whatOnClick0()
{
}

void HuntersLodgeCouch::whatOnClick()
{
}
