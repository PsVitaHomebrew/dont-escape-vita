#include "../game_all.h"

void LocationBaseUpstairsDesk::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_open_ne");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_upstairs_desk");
}

void LocationBaseUpstairsDesk::clickAction()
{
	if (!GameDataController::gd->getObjective(S("upstairs_paperclip_taken")) && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("paperclip"))))
	{
		GameDataController::gd->setObjective(S("upstairs_paperclip_taken"), true);
		updateState();
		PlayerController::pc->textField->viewText(S("I picked a paperclip that was on the desk."), true);
	}
	else
	{
		PlayerController::pc->textField->viewText(S("Nothing interesting here."), true);
	}
}

void LocationBaseUpstairsDesk::updateState()
{
	if (!GameDataController::gd->getObjective(S("upstairs_paperclip_taken")))
	{
		objectName = S("base_upstairs_desk");
		characterAnimationName = S("action_open_ne");
	}
	else
	{
		objectName = S("base_upstairs_desk_cleared");
		characterAnimationName = S("stand_n");
	}
}

void LocationBaseUpstairsDesk::clickAction2()
{
}

void LocationBaseUpstairsDesk::clickAction0()
{
}
