#include "../game_all.h"

void LocationElectricExit::Start()
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

void LocationElectricExit::clickAction()
{
	if (usedItem == String::Empty)
	{
		PlayerController::pc->spawnName = S("LocationSiderealF2B_Generator");
		PlayerController::wc->fullStop();
		CurtainController::cc->fadeOut(S("SiderealF2B"), WalkController::Direction::E);
	}
}

void LocationElectricExit::whatOnClick0()
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

void LocationElectricExit::updateState()
{
}

void LocationElectricExit::clickAction2()
{
}

void LocationElectricExit::clickAction0()
{
}
