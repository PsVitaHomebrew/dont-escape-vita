#include "../game_all.h"

void Location1Stairs::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_stairs_up");
	doubleClickCondition = S("visited_baseUpstairs");
	actionType = Type::Transition;
	trans_dir = WalkController_Direction::N;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ac_cord"), GameStrings::getString(GameStrings::actions, S("cord_upfloor")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ext_cord_place"), GameStrings::getString(GameStrings::actions, S("cord_upfloor")), nullptr, String::Empty));
}

void Location1Stairs::clickAction()
{
	PlayerController::pc->spawnName = S("Stairs_Exit");
	CurtainController::cc->fadeOut(S("LocationBaseUpstairs"), WalkController_Direction::W);
}

void Location1Stairs::updateState()
{
}

void Location1Stairs::clickAction2()
{
}

void Location1Stairs::clickAction0()
{
}
