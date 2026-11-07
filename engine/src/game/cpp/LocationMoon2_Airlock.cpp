#include "../game_all.h"

void LocationMoon2_Airlock::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moon_airlock_control");
	range = 1.0f;
	actionType = Type::NormalAction;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
	updateAll();
}

void LocationMoon2_Airlock::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("airlock_ring_1")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_2")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_3")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_4")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_5")) == 0)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("already_airlock")));
		return;
	}
	PlayerController::pc->spawnName = S("MoonAirlockExit");
	CurtainController::cc->fadeOut(S("MoonAirlock"), WalkController::Direction::S_);
}

void LocationMoon2_Airlock::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("airlock_ring_1")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_2")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_3")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_4")) == 0 && GameDataController::gd->getObjectiveDetail(S("airlock_ring_5")) == 0)
	{
		characterAnimationName = S("suit_action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void LocationMoon2_Airlock::clickAction2()
{
}

void LocationMoon2_Airlock::clickAction0()
{
}
