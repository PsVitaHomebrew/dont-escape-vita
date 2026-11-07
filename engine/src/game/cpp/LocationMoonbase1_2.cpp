#include "../game_all.h"

void LocationMoonbase1_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moonbase_passage");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	doubleClickCondition = S("moon_allow_fast_travel_now");
}

void LocationMoonbase1_2::clickAction()
{
	if (GameDataController::gd->getObjective(S("moon_door_closed")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moon_window_broken")));
		return;
	}
	PlayerController::pc->spawnName = S("LocationMoonbase2_1");
	CurtainController::cc->fadeOut(S("LocationMoonbase2"), WalkController::Direction::E);
}

void LocationMoonbase1_2::zamyk()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_slide);
}

void LocationMoonbase1_2::unlock()
{
	Invoke(S("unlockPlayer"), 2.0f);
}

void LocationMoonbase1_2::updateState()
{
	if (GameDataController::gd->getObjective(S("moon_door_closed")))
	{
		GetComponent<Animator>()->Play(S("moon_door_closed"));
		objectName = S("moonbase_passage");
		actionType = Type::NormalAction;
	}
	else
	{
		objectName = S("moonbase_passage");
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::E;
		GetComponent<Animator>()->Play(S("moon_door_open"));
	}
}

void LocationMoonbase1_2::clickAction2()
{
}

void LocationMoonbase1_2::clickAction0()
{
}
