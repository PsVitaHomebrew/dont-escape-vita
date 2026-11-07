#include "../game_all.h"

void WaypointCave::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_cave_exit");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_rv");
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ac"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ext_cord_place"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flag"), GameStrings::getString(GameStrings::actions, S("cave_do_it_outside")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanket"), GameStrings::getString(GameStrings::actions, S("cave_do_it_outside")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), GameStrings::getString(GameStrings::actions, S("cave_do_it_outside")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), GameStrings::getString(GameStrings::actions, S("cave_do_it_outside")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), GameStrings::getString(GameStrings::actions, S("cave_do_it_outside")), nullptr, String::Empty));
}

void WaypointCave::whatOnClick0()
{
	if (usedItem == S("ac"))
	{
		characterAnimationName = S("kneel_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else if (usedItem != String::Empty)
	{
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void WaypointCave::clickAction()
{
	if (usedItem == S("ac"))
	{
		GameDataController::gd->setObjective(S("cave_ac_placed"), true);
		InventoryController::ic->removeItem(S("ac"));
		updateAll();
	}
	else if (usedItem == S("ext_cord_place"))
	{
		GameDataController::gd->setObjective(S("rv_cord_caved"), false);
		PlayerController::pc->spawnName = S("WaypointRVCave");
		CurtainController::cc->fadeOut(S("LocationRV"), WalkController::Direction::W);
	}
	else
	{
		PlayerController::pc->spawnName = S("WaypointRVCave");
		CurtainController::cc->fadeOut(S("LocationRV"), WalkController::Direction::W);
	}
}

void WaypointCave::updateState()
{
	colliderManager->setCollider(0);
}

void WaypointCave::clickAction2()
{
}

void WaypointCave::clickAction0()
{
}
