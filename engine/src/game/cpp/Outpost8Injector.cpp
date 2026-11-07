#include "../game_all.h"

void Outpost8Injector::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_injector");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("catalyst"), String::Empty, nullptr, String::Empty));
}

void Outpost8Injector::beep()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
	Invoke(S("bzzt"), 0.2f);
}

void Outpost8Injector::bzzt()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->mixer, 0.2f);
}

void Outpost8Injector::clickAction()
{
	if (usedItem != String::Empty)
	{
		InventoryController::ic->removeItem(S("catalyst"));
		GameDataController::gd->setObjective(S("outpost_catalyst_used"), true);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour_small);
		Invoke(S("beep"), 0.2f);
		updateAll();
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("catalyst_added")));
	}
	else if (GameDataController::gd->getObjective(S("outpost_catalyst_used")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("catalyst_already_used")));
	}
	else
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("GingerInlet"))->transform->get_position());
		component->viewText(GameStrings::getString(GameStrings::actions, S("outpost_injector")), true, false, false, 150, color.x, color.y, color.z);
	}
}

void Outpost8Injector::updateState()
{
}

void Outpost8Injector::clickAction2()
{
}

void Outpost8Injector::clickAction0()
{
}

void Outpost8Injector::whatOnClick0()
{
	if (usedItem == String::Empty)
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 10.0f;
	}
	else
	{
		characterAnimationName = S("action_n");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
	}
}

void Outpost8Injector::whatOnClick()
{
}
