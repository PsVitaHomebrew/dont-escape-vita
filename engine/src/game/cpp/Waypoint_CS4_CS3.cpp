#include "../game_all.h"

void Waypoint_CS4_CS3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_waypoint_4_3");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	doubleClickCondition = String::Empty;
}

void Waypoint_CS4_CS3::clickAction()
{
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
		return;
	}
	GameDataController::gd->setObjective(S("cs_rain_enter_left"), false);
	PlayerController::pc->spawnName = S("Waypoint_CS3_CS4");
	CurtainController::cc->fadeOut(S("CS3"), WalkController::Direction::S_);
}

void Waypoint_CS4_CS3::updateState()
{
	if (!GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		range = 1.0f;
		characterAnimationName = S("stop");
	}
	else
	{
		range = 100.0f;
		characterAnimationName = S("action_stnd_");
	}
}

void Waypoint_CS4_CS3::clickAction2()
{
}

void Waypoint_CS4_CS3::clickAction0()
{
}
