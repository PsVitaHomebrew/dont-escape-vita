#include "../game_all.h"

void Attic1Hatch2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_up_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("attic_hatch2");
	range = 5.0f;
	doubleClickCondition = S("visited_roof");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("blanket"), GameStrings::getString(GameStrings::actions, S("roof_hatch_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), GameStrings::getString(GameStrings::actions, S("roof_hatch_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), GameStrings::getString(GameStrings::actions, S("roof_hatch_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flag"), GameStrings::getString(GameStrings::actions, S("roof_hatch_no_need")), nullptr, String::Empty));
	trans_dir = WalkController::Direction::N;
}

void Attic1Hatch2::clickAction()
{
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("no_roof")));
	}
	else if (!GameDataController::gd->getObjective(S("attic_hatch_open")))
	{
		GameDataController::gd->setObjective(S("attic_hatch_open"), true);
		updateAll();
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_creak1);
		GameObject::Find(S("LocationManager"))->GetComponent<LoctionAttic1Start>()->backgroundCheck();
	}
	else
	{
		PlayerController::pc->spawnName = S("WaypointRoof1Hatch");
		CurtainController::cc->fadeOut(S("LocationRoof1"), WalkController::Direction::W, S("kneel_out_se"), nullptr, true);
	}
}

void Attic1Hatch2::updateState()
{
	range = 5.0f;
	if (GameDataController::gd->getCurrentDay() == 4 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && (!GameDataController::gd->getObjective(S("lighting_rod_installed")) || GameDataController::gd->getObjectiveDetail(S("day3_complete")) < 1))
	{
		actionType = Type::NormalAction;
		characterAnimationName = S("action_stnd_");
		useCurrentDirection = true;
		doubleClickCondition = S("none");
		objectName = S("attic_roof_destroyed");
		setCollider(0);
		range = 100.0f;
		interactions = List<P<ItemInteraction>>::New();
	}
	else if (!GameDataController::gd->getObjective(S("attic_hatch_open")))
	{
		actionType = Type::NormalAction;
		characterAnimationName = S("action_up_n");
		useCurrentDirection = false;
		doubleClickCondition = S("none");
		objectName = S("attic_hatch2");
		setCollider(0);
	}
	else
	{
		actionType = Type::Transition;
		characterAnimationName = S("stop");
		useCurrentDirection = true;
		setCollider(1);
		doubleClickCondition = S("visited_roof");
		objectName = S("attic_hatch2");
	}
}

void Attic1Hatch2::clickAction2()
{
}

void Attic1Hatch2::clickAction0()
{
}
