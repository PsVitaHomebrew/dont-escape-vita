#include "../game_all.h"

void LocationMoon2_3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moon_base_entrance");
	range = 1.0f;
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
}

void LocationMoon2_3::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("airlock_ring_1")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_2")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_3")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_4")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_5")) == 0)
	{
		PlayerController::pc->spawnName = S("LocationMoon3_Moonbase1");
		CurtainController::cc->fadeOut(S("LocationMoonbase1"), WalkController::Direction::S_, S("stand_s"));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("airlock_locked")));
	}
}

void LocationMoon2_3::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("airlock_ring_1")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_2")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_3")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_4")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_5")) == 0)
	{
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		actionMarker = gameObject->transform->Find(S("Action_Marker2"))->gameObject;
		range = 1.0f;
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		characterAnimationName = S("suit_action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		range = 10.0f;
		actionType = Type::NormalAction;
		trans_dir = WalkController::Direction::N;
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void LocationMoon2_3::clickAction2()
{
}

void LocationMoon2_3::clickAction0()
{
}
