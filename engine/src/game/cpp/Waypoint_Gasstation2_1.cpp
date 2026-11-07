#include "../game_all.h"

void Waypoint_Gasstation2_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_front");
	doubleClickCondition = S("visited_gasstation1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void Waypoint_Gasstation2_1::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Gasstation1_2");
	CurtainController::cc->fadeOut(S("LocationGasstation1"), WalkController::Direction::E);
}

void Waypoint_Gasstation2_1::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("gasstation_spy_mode")))
	{
		setCollider(-1);
	}
}

void Waypoint_Gasstation2_1::clickAction2()
{
}

void Waypoint_Gasstation2_1::clickAction0()
{
}
