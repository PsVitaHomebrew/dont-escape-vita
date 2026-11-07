#include "../game_all.h"

void SiderealLabMixer::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_mixer");
	actionType = Type::NormalAction;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("vials1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("vials2"), String::Empty, nullptr, String::Empty));
}

void SiderealLabMixer::clickAction()
{
	if (usedItem == S("vials1"))
	{
		InventoryController::ic->removeItem(S("vials1"));
		GameDataController::gd->setObjective(S("sidereal_components_1"), true);
		updateAll();
		PlayerController::pc->aS->PlayOneShot(clank);
	}
	else if (usedItem == S("vials2"))
	{
		InventoryController::ic->removeItem(S("vials2"));
		GameDataController::gd->setObjective(S("sidereal_components_2"), true);
		updateAll();
		PlayerController::pc->aS->PlayOneShot(clank);
	}
	else
	{
		PlayerController::pc->spawnName = S("LocationMixerExit");
		CurtainController::cc->fadeOut(S("SiderealMixer"), WalkController::Direction::S_);
	}
}

void SiderealLabMixer::whatOnClick()
{
	animationFlip = false;
	useCurrentDirection = true;
	characterAnimationName = S("stop");
	if (usedItem != String::Empty)
	{
		characterAnimationName = S("action1_e");
		animationFlip = true;
		useCurrentDirection = false;
	}
}

void SiderealLabMixer::updateState()
{
}

void SiderealLabMixer::clickAction2()
{
}

void SiderealLabMixer::clickAction0()
{
}
