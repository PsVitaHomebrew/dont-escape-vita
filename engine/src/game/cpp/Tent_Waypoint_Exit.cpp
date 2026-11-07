#include "../game_all.h"

void Tent_Waypoint_Exit::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tent_waypoint");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	doubleClickCondition = S("impossible");
}

void Tent_Waypoint_Exit::clickAction()
{
	if (!GameDataController::gd->getObjective(S("tent_distance_triggered")))
	{
		PlayerController::wc->fullStop(true);
		PlayerController::pc->setBusy(false);
	}
	else
	{
		PlayerController::pc->spawnName = S("Fence1Waypoint1");
		CurtainController::cc->fadeOut(S("LocationDesertFence1"), WalkController::Direction::E);
	}
}

void Tent_Waypoint_Exit::updateState()
{
	if (!GameDataController::gd->getObjective(S("tent_awake")))
	{
		colliderManager->setCollider(-1);
		return;
	}
	if (!GameDataController::gd->getObjective(S("tent_backpack_taken")))
	{
		colliderManager->setCollider(-1);
		return;
	}
	teleport = false;
	colliderManager->setCollider(0);
}

void Tent_Waypoint_Exit::clickAction2()
{
}

void Tent_Waypoint_Exit::clickAction0()
{
}
