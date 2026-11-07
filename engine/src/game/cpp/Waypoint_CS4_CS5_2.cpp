#include "../game_all.h"

void Waypoint_CS4_CS5_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_rope");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
}

void Waypoint_CS4_CS5_2::clickAction()
{
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		GameDataController::gd->setObjective(S("constructionsite_from_above"), true);
		PlayerController::pc->spawnName = S("Waypoint_CS5_CS4_2");
		CurtainController::cc->fadeOut(S("CS5"), WalkController::Direction::N);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
	}
}

void Waypoint_CS4_CS5_2::updateState()
{
	if (GameDataController::gd->getObjective(S("cs_rope_used")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
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

void Waypoint_CS4_CS5_2::clickAction2()
{
}

void Waypoint_CS4_CS5_2::clickAction0()
{
}
