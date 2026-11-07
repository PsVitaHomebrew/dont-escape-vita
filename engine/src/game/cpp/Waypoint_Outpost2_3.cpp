#include "../game_all.h"

void Waypoint_Outpost2_3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_base_entrance1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = S("outpost_door_open");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("sidereal_id"), String::Empty, nullptr, String::Empty));
}

void Waypoint_Outpost2_3::clickAction()
{
	if (GameDataController::gd->getObjective(S("outpost_door_open")))
	{
		PlayerController::pc->spawnName = S("Waypoint_Outpost3_2");
		CurtainController::cc->fadeOut(S("LocationOutpost3"), WalkController::Direction::E);
		return;
	}
	if (usedItem == String::Empty)
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_door_locked);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("generic_locked")));
		return;
	}
	GameDataController::gd->setObjective(S("outpost_door_open"), true);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->door_slide);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click1);
	GameDataController::gd->setObjective(S("outpost_doormat_triggered"), false);
	GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 0);
	mataEl->set_enabled(false);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->small_powerdown);
	loc->letItGo();
	animator->Play(S("outside_door_opening"));
	actionType = Type::Transition;
	objectName = S("outpost_base_entrance2");
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
}

void Waypoint_Outpost2_3::closedo()
{
	actionType = Type::NormalAction;
	animator->Play(S("outside_door_closing"));
	objectName = S("outpost_base_entrance1");
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
}

void Waypoint_Outpost2_3::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_door_open")))
	{
		animator->Play(S("outside_door_open"));
		actionType = Type::Transition;
		objectName = S("outpost_base_entrance2");
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		actionType = Type::NormalAction;
		animator->Play(S("outside_door_closed"));
		objectName = S("outpost_base_entrance1");
		characterAnimationName = S("action_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void Waypoint_Outpost2_3::clickAction2()
{
}

void Waypoint_Outpost2_3::clickAction0()
{
}
