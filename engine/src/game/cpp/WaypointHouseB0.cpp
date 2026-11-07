#include "../game_all.h"

void WaypointHouseB0::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_waypoint0");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_house_b");
	range = 10.0f;
}

void WaypointHouseB0::clickAction()
{
	if (!GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
	{
		exitToMap(String::Empty);
		return;
	}
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->distractBarryEnd();
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->function = [this](String val) { exitToMap(val); };
	timelineAction->actionWithText = true;
	Timeline::t->addAction(timelineAction);
	PlayerController::pc->setBusy(true);
}

void WaypointHouseB0::exitToMap(String val)
{
	PlayerController::pc->setBusy(true);
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
}

void WaypointHouseB0::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointHouseB0::clickAction2()
{
}

void WaypointHouseB0::clickAction0()
{
}
