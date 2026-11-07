#include "../game_all.h"

void Waypoint_CS5_CS4_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_rope");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	doubleClickCondition = String::Empty;
}

void Waypoint_CS5_CS4_2::clickAction()
{
	GameDataController::gd->setObjective(S("constructionsite_from_above"), true);
	PlayerController::pc->spawnName = S("Waypoint_CS4_CS5_2");
	CurtainController::cc->fadeOut(S("CS4"), WalkController::Direction::S_);
}

void Waypoint_CS5_CS4_2::updateState()
{
	if (GameDataController::gd->getObjective(S("cs_rope_used")))
	{
		setCollider(0);
	}
	else
	{
		setCollider(-1);
	}
}

void Waypoint_CS5_CS4_2::clickAction2()
{
}

void Waypoint_CS5_CS4_2::clickAction0()
{
}
