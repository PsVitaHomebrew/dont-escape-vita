#include "../game_all.h"

void KitchenDoor2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("kitchen_door2");
	range = 10.0f;
	doubleClickCondition = S("visited_location1");
	actionType = Type::Transition;
	trans_dir = WalkController_Direction::W;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ext_cord_place"), String::Empty, nullptr, String::Empty));
}

void KitchenDoor2::whatOnClick0()
{
	range = 10.0f;
	if (usedItem == S("ext_cord_place"))
	{
		range = 1000.0f;
	}
}

void KitchenDoor2::clickAction()
{
	if (usedItem == S("ext_cord_place"))
	{
		GameDataController::gd->setObjective(S("kitchen_cord_dragged"), true);
		PlayerController::pc->spawnName = S("location1_ext_cord");
		CurtainController::cc->fadeOut(S("Location1"), WalkController_Direction::W);
	}
	else
	{
		PlayerController::pc->spawnName = S("Door1");
		CurtainController::cc->fadeOut(S("Location1"), WalkController_Direction::W);
	}
}

void KitchenDoor2::updateState()
{
	colliderManager->setCollider(0);
}

void KitchenDoor2::clickAction2()
{
}

void KitchenDoor2::clickAction0()
{
}
