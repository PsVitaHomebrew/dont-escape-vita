#include "../game_all.h"

void LocationMixerExit::Start()
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
}

void LocationMixerExit::clickAction()
{
	if (usedItem == String::Empty)
	{
		PlayerController::pc->spawnName = S("SiderealLabMixer");
		PlayerController::wc->fullStop();
		CurtainController::cc->fadeOut(S("SiderealLab13"), WalkController::Direction::W);
	}
}

void LocationMixerExit::whatOnClick0()
{
}

void LocationMixerExit::updateState()
{
	if (InventoryController::ic->isItemInInventory(S("mixer_pills_note")) || InventoryController::ic->isItemInInventory(S("mixer_catalyst_note")))
	{
		setCollider(1);
	}
	else
	{
		setCollider(0);
	}
}

void LocationMixerExit::clickAction2()
{
}

void LocationMixerExit::clickAction0()
{
}
