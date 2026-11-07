#include "../game_all.h"

void TutorialDoor::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("open_n");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tutorial_door");
	range = 1.0f;
}

void TutorialDoor::creak1()
{
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->door_creak_1);
}

void TutorialDoor::creak2()
{
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->door_creak_2);
}

void TutorialDoor::creak3()
{
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->door_creak_3);
}

void TutorialDoor::clickAction()
{
	if (!GameDataController::gd->getObjective(S("tutorial_door_opened")))
	{
		PlayerController::pc->GetComponent<Animator>()->set_speed(0.5f);
		GameDataController::gd->setObjective(S("tutorial_door_opened"), true);
		gameObject->GetComponent<Animator>()->Play(S("fence_door_open"));
		GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->door_creak_open);
		setCollider(-1);
		GameObject::Find(S("Location"))->transform->Find(S("OtherPath"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	}
}

void TutorialDoor::updateState()
{
	if (!GameDataController::gd->getObjective(S("tutorial_door_opened")))
	{
		setCollider(0);
		gameObject->GetComponent<Animator>()->Play(S("fence_door_creak"));
		GameObject::Find(S("Location"))->transform->Find(S("OtherPath"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	}
	else
	{
		setCollider(-1);
		gameObject->GetComponent<Animator>()->Play(S("fence_door_opened"));
		GameObject::Find(S("Location"))->transform->Find(S("OtherPath"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	}
}

void TutorialDoor::clickAction2()
{
	PlayerController::pc->GetComponent<Animator>()->set_speed(1.0f);
	GameObject::Find(S("tutorial_sledgehammer"))->GetComponent<TutorialHammer>()->updateState();
}

void TutorialDoor::clickAction0()
{
}

void TutorialDoor::whatOnClick0()
{
}

void TutorialDoor::whatOnClick()
{
}
