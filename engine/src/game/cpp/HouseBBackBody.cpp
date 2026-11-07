#include "../game_all.h"

void HouseBBackBody::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	range = 20.0f;
	dkvs = GameStrings::objects;
	objectName = S("house_b_back_body");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("shovel"), GameStrings::getString(GameStrings::actions, S("shovel_body")), nullptr, String::Empty));
}

void HouseBBackBody::clickAction()
{
	if (GameDataController::gd->getCurrentDay() > 2)
	{
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("wife_too_late"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->textField, GingerActionController::getColor());
		Timeline::t->addDialogueLines(list);
	}
	else if (GameDataController::gd->getObjective(S("house_b_grave_dug")) && !GameDataController::gd->getObjective(S("house_b_grave_filled")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_wife_time_for_barry")), true);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_wife_needs_grave")), true);
	}
}

void HouseBBackBody::updateState()
{
	if (GameDataController::gd->getObjective(S("house_b_grave_filled")) || !GameDataController::gd->getObjective(S("house_b_wife_moved")))
	{
		colliderManager->setCollider(-1);
		characterAnimationName = S("stand_");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Body2"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else if (!GameDataController::gd->getObjective(S("house_b_grave_filled")) && GameDataController::gd->getObjective(S("house_b_body_in_grave")))
	{
		colliderManager->setCollider(0);
		characterAnimationName = S("stand_");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Body2"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		colliderManager->setCollider(0);
		characterAnimationName = S("stand_");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Body2"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void HouseBBackBody::whatOnClick()
{
	if (!GameDataController::gd->getObjective(S("house_b_grave_dug")))
	{
		characterAnimationName = S("action_stnd_");
	}
	else
	{
		characterAnimationName = S("action_stnd_");
	}
}

void HouseBBackBody::clickAction2()
{
}

void HouseBBackBody::clickAction0()
{
}
