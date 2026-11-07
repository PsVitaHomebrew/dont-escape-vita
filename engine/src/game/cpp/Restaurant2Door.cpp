#include "../game_all.h"

void Restaurant2Door::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action1_e");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_backdoor");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("restaurant_door_crowbar")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("paperclip"), GameStrings::getString(GameStrings::actions, S("restaurant_door_lockpick")), nullptr, String::Empty));
}

void Restaurant2Door::clickAction()
{
	if (!GameDataController::gd->getObjective(S("dialogue_cody_intro")) && GameDataController::gd->getCurrentDay() == 2)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("restaurant_first_check_front")));
		return;
	}
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_locked_2);
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_backdoor")), true);
}

void Restaurant2Door::whatOnClick0()
{
	if (GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("dialogue_cody_intro")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 200.0f;
	}
	else
	{
		characterAnimationName = S("action1_e");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
	}
}

void Restaurant2Door::updateState()
{
	if (!GameDataController::gd->getObjective(S("restaurant_trash_moved")))
	{
		setCollider(0);
	}
	else
	{
		setCollider(-1);
	}
}

void Restaurant2Door::clickAction2()
{
}

void Restaurant2Door::clickAction0()
{
}
