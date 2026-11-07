#include "../game_all.h"

void Waypoint_CS4_CS1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_waypoint_4_1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = String::Empty;
}

void Waypoint_CS4_CS1::clickAction()
{
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
		return;
	}
	PlayerController::pc->spawnName = S("CS1_Waypoint_4");
	CurtainController::cc->fadeOut(S("CS1"), WalkController::Direction::S_);
}

void Waypoint_CS4_CS1::updateState()
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

void Waypoint_CS4_CS1::clickAction2()
{
}

void Waypoint_CS4_CS1::clickAction0()
{
}
