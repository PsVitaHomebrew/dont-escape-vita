#include "../game_all.h"

void HuntersInsideHorns::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_horns");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pipe"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("broom"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("shovel"), String::Empty, nullptr, String::Empty));
}

void HuntersInsideHorns::clickAction()
{
	if (usedItem == String::Empty)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("hunters_horns")));
		return;
	}
	P<DialogueLine> dialogueLine = New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::actions, S("hunters_horns2")), [this](String f) { gogo(f); });
	dialogueLine->actionWithText = false;
	Timeline::t->addDialogue(dialogueLine);
}

void HuntersInsideHorns::gogo(String f)
{
	if (!GameDataController::gd->getObjective(S("hunters_lodge_couch_moved")))
	{
		P<DialogueLine> dl = New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::actions, S("hunters_horns3")), nullptr);
		Timeline::t->addDialogue(dl);
	}
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_locked_1);
	GameDataController::gd->setObjective(S("hunters_lodge_horn_pulled"), true);
	GameDataController::gd->setObjective(S("hunters_lodge_chest_opened"), true);
	updateAll();
}

void HuntersInsideHorns::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("hunters_lodge_horn_pulled")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(antlers1);
		colliderManager->setCollider(0);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(antlers2);
		colliderManager->setCollider(-1);
	}
}

void HuntersInsideHorns::clickAction2()
{
}

void HuntersInsideHorns::clickAction0()
{
}

void HuntersInsideHorns::whatOnClick0()
{
}

void HuntersInsideHorns::whatOnClick()
{
}
