#include "../game_all.h"

void Door1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("kitchen_door1");
	doubleClickCondition = S("visited_location2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ext_cord_place"), String::Empty, nullptr, String::Empty));
}

void Door1::whatOnClick0()
{
	range = 1.0f;
	if (usedItem == S("ext_cord_place"))
	{
		range = 1000.0f;
	}
}

void Door1::clickAction()
{
	if (usedItem == S("ext_cord_place"))
	{
		GameDataController::gd->setObjective(S("kitchen_cord_dragged"), false);
		PlayerController::pc->spawnName = S("ExtCordPlace");
		CurtainController::cc->fadeOut(S("Location2"), WalkController::Direction::E);
	}
	else
	{
		PlayerController::pc->spawnName = S("KitchenDoor2");
		CurtainController::cc->fadeOut(S("Location2"), WalkController::Direction::E);
	}
}

void Door1::updateState()
{
}

void Door1::clickAction2()
{
}

void Door1::clickAction0()
{
}
