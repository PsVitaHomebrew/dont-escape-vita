#include "../game_all.h"

void LocationRVHook::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_hook");
	range = 2.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rope"), String::Empty, nullptr, String::Empty));
}

void LocationRVHook::clickAction()
{
	if (usedItem == S("wrench"))
	{
		InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("hook")));
		GameDataController::gd->setObjective(S("rv_hook_taken"), true);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_hook_detach")));
		updateState();
	}
	else if (usedItem == S("rope"))
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("rv_rope"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		Timeline::t->addDialogue(list[0]);
		for (int i = 1; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_hook")));
	}
}

void LocationRVHook::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getObjective(S("rv_hook_taken")))
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void LocationRVHook::clickAction2()
{
}

void LocationRVHook::clickAction0()
{
}

void LocationRVHook::whatOnClick0()
{
	if (usedItem == S("wrench"))
	{
		range = 2.0f;
		characterAnimationName = S("kneel_n");
		useCurrentDirection = false;
	}
	else
	{
		range = 20.0f;
		characterAnimationName = S("action_stnd_");
		useCurrentDirection = true;
	}
}

void LocationRVHook::whatOnClick()
{
}
