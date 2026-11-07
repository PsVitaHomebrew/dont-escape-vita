#include "../game_all.h"

void TutorialHandle::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tutorial_pole");
	range = 1.0f;
}

void TutorialHandle::clickAction()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("tutorial_time_question")), QuestionController::PopupType::QUESTION, [this]() { pullit(); }, 3);
}

void TutorialHandle::pullit()
{
	PlayerController::wc->forceAnimation(S("action_n"));
}

void TutorialHandle::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("tutorial_handle_taken")))
	{
		colliderManager->setCollider(-1);
		blocker->set_enabled(false);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		blocker->set_enabled(true);
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void TutorialHandle::clickAction2()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sledge_handle"))))
	{
		GameDataController::gd->setObjective(S("tutorial_handle_taken"), true);
		updateAll();
	}
}

void TutorialHandle::clickAction0()
{
}

void TutorialHandle::whatOnClick0()
{
}

void TutorialHandle::whatOnClick()
{
}
