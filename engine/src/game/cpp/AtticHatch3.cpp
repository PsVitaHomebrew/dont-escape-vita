#include "../game_all.h"

void AtticHatch3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_up_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("attic_hatch2");
	range = 5.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("blanket"), GameStrings::getString(GameStrings::actions, S("roof_hatch_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), GameStrings::getString(GameStrings::actions, S("roof_hatch_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), GameStrings::getString(GameStrings::actions, S("roof_hatch_no_need")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flag"), GameStrings::getString(GameStrings::actions, S("roof_hatch_no_need")), nullptr, String::Empty));
	trans_dir = WalkController::Direction::N;
}

void AtticHatch3::clickAction()
{
	if (GameDataController::gd->getObjective(S("attic_hatch_open")))
	{
		GameDataController::gd->setObjective(S("attic_hatch_open"), false);
		updateAll();
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_creak1);
		GameObject::Find(S("LocationManager"))->GetComponent<LoctionAttic1Start>()->backgroundCheck();
	}
}

void AtticHatch3::updateState()
{
	if (!GameDataController::gd->getObjective(S("attic_hatch_open")))
	{
		setCollider(-1);
	}
	else
	{
		setCollider(0);
	}
}

void AtticHatch3::clickAction2()
{
}

void AtticHatch3::clickAction0()
{
}
