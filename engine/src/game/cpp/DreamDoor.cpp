#include "../game_all.h"

void DreamDoor::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action1_e_lock");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("basedoor");
	range = 1.0f;
	teleport = false;
	updateState();
}

void DreamDoor::Update()
{
}

void DreamDoor::whatOnClick()
{
}

void DreamDoor::clickAction()
{
	if (GameDataController::gd->getCurrentDay() == 4 && !GameDataController::gd->getObjective(S("dream_day_4_door_open")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_open_01);
		GetComponent<Animator>()->Play(S("dream_door_open"));
		GameDataController::gd->setObjective(S("dream_day_4_door_open"), true);
		characterAnimationName = S("stop");
		animationFlip = true;
		useCurrentDirection = false;
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::W;
	}
	else if (GameDataController::gd->getCurrentDay() == 4)
	{
		GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss(true);
		GameObject::Find(S("LocationManager"))->GetComponent<LocationDream4Start>()->fallMoon();
		GameObject::Find(S("gears"))->GetComponent<GearsController>()->hide();
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("generic_locked")));
	}
}

void DreamDoor::updateState()
{
	if ((GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("dream_day_1_started"))) || (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjective(S("dream_day_2_started"))) || (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjective(S("dream_day_3_started"))) || (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjective(S("dream_day_4_started"))))
	{
		colliderManager->setCollider(0);
		if (GameDataController::gd->getCurrentDay() == 4)
		{
			if (GameDataController::gd->getObjective(S("dream_day_4_door_open")))
			{
				characterAnimationName = S("stop");
				animationFlip = true;
				useCurrentDirection = false;
				actionType = Type::Transition;
				trans_dir = WalkController::Direction::W;
				GetComponent<Animator>()->Play(S("dream_door_opened"));
			}
			else
			{
				characterAnimationName = S("action1_e");
				animationFlip = true;
				useCurrentDirection = false;
				GetComponent<Animator>()->Play(S("dream_door_closed"));
				actionType = Type::NormalAction;
			}
		}
	}
	else
	{
		colliderManager->setCollider(-1);
	}
}

void DreamDoor::clickAction2()
{
}

void DreamDoor::clickAction0()
{
}
