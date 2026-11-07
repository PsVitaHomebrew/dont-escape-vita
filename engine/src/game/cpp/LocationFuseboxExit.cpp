#include "../game_all.h"

void LocationFuseboxExit::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("leave");
	teleport = true;
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("puzzle_cable"), String::Empty, nullptr, String::Empty));
}

void LocationFuseboxExit::clickAction()
{
	if (usedItem == String::Empty)
	{
		PlayerController::pc->spawnName = S("Waypoint_Outpost3_Fusebox");
		PlayerController::wc->fullStop();
		CurtainController::cc->fadeOut(S("LocationOutpost3"), WalkController::Direction::SE);
	}
}

void LocationFuseboxExit::whatOnClick0()
{
	if (usedItem == String::Empty)
	{
		characterAnimationName = S("stop");
	}
	else
	{
		characterAnimationName = S("action_stnd_");
	}
}

void LocationFuseboxExit::updateState()
{
}

void LocationFuseboxExit::clickAction2()
{
}

void LocationFuseboxExit::clickAction0()
{
}
