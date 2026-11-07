#include "../game_all.h"

void LocationMoonbase1_3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moonbase_passage");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = S("moon_allow_fast_travel_now");
}

void LocationMoonbase1_3::clickAction()
{
	PlayerController::pc->spawnName = S("LocationMoonbase3_1");
	if (!GameDataController::gd->getObjective(S("visited_moonbase3")))
	{
		CurtainController::cc->fadeOut(S("LocationMoonbase3"), WalkController::Direction::W, S("walk_e"));
	}
	else
	{
		CurtainController::cc->fadeOut(S("LocationMoonbase3"), WalkController::Direction::W);
	}
}

void LocationMoonbase1_3::updateState()
{
}

void LocationMoonbase1_3::clickAction2()
{
}

void LocationMoonbase1_3::clickAction0()
{
}
