#include "../game_all.h"

void HouseBInsideBody::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_inside_body");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("sheet"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), GameStrings::getString(GameStrings::actions, S("house_b_wife_wrong_cover")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanket"), GameStrings::getString(GameStrings::actions, S("house_b_wife_wrong_cover")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("thermalb"), GameStrings::getString(GameStrings::actions, S("house_b_wife_wrong_cover")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat1"), GameStrings::getString(GameStrings::actions, S("house_b_wife_wrong_cover2")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat2"), GameStrings::getString(GameStrings::actions, S("house_b_wife_wrong_cover2")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat3"), GameStrings::getString(GameStrings::actions, S("house_b_wife_wrong_cover2")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat4"), GameStrings::getString(GameStrings::actions, S("house_b_wife_wrong_cover2")), nullptr, String::Empty));
	range = 10.0f;
}

void HouseBInsideBody::pickUpLocket(String val)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("locket"))))
	{
		GameDataController::gd->setObjective(S("house_b_wife_note_taken"), true);
		updateState();
	}
}

void HouseBInsideBody::clickAction()
{
	if (GameDataController::gd->getCurrentDay() > 2)
	{
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("wife_too_late"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->textField, GingerActionController::getColor());
		Timeline::t->addDialogueLines(list);
	}
	else if (!GameDataController::gd->getObjective(S("house_b_wife_covered")) && usedItem == S("sheet"))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_wife_covered")), true);
		GameDataController::gd->setObjective(S("house_b_wife_covered"), true);
		InventoryController::ic->removeItem(S("sheet"));
		updateAll();
	}
	else if (GameDataController::gd->getObjective(S("house_b_wife_covered")) && !GameDataController::gd->getObjective(S("house_b_wife_note_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("sheet"))))
		{
			GameDataController::gd->setObjective(S("house_b_wife_covered"), false);
			updateState();
		}
	}
	else if (!GameDataController::gd->getObjective(S("house_b_wife_note_taken")))
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("locket"))))
		{
			GameDataController::gd->setObjective(S("house_b_wife_note_taken"), true);
			updateState();
		}
	}
	else if (!GameDataController::gd->getObjective(S("house_b_wife_covered")))
	{
		if (!GameDataController::gd->getObjective(S("dialogue_npc2_burial")))
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_wife_cant_move")), true);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_wife_needs_cover")), true);
		}
	}
	else if (!GameDataController::gd->getObjective(S("dialogue_npc2_burial")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_wife_cant_move")), true);
	}
	else
	{
		List<P<DialogueLine>> list2 = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list2, S("ginger_move_body1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->textField, GingerActionController::getColor());
		list2[2]->action = [this](String val) { moveBody(val); };
		list2[2]->actionWithText = false;
		Timeline::t->addDialogueLines(list2);
	}
}

void HouseBInsideBody::moveBody(String val)
{
	GameDataController::gd->setObjective(S("house_b_wife_moved"), true);
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("WaypointHouseBBackBody");
	CurtainController::cc->fadeOut(S("LocationHouseBBack"), WalkController::Direction::W);
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	Timeline::t->doNotUnlock = true;
}

void HouseBInsideBody::updateState()
{
	bool flag = pathBlocker->get_enabled();
	range = 10.0f;
	if (GameDataController::gd->getObjective(S("house_b_wife_moved")))
	{
		colliderManager->setCollider(-1);
		characterAnimationName = S("stand_");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		pathBlocker->set_enabled(false);
	}
	else if (GameDataController::gd->getObjective(S("house_b_wife_covered")))
	{
		objectName = S("house_b_back_body");
		pathBlocker->set_enabled(true);
		colliderManager->setCollider(0);
		characterAnimationName = S("kneel_");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite2);
	}
	else
	{
		objectName = S("house_b_inside_body");
		pathBlocker->set_enabled(true);
		colliderManager->setCollider(0);
		characterAnimationName = S("kneel_");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprite1);
		if (GameDataController::gd->getCurrentDay() > 2)
		{
			GetComponent<ParticleGenerator>()->started = true;
			GetComponent<AudioSource>()->Play();
			characterAnimationName = S("action_stnd_");
			range = 20.0f;
		}
	}
	if (flag != pathBlocker->get_enabled())
	{
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	}
}

void HouseBInsideBody::whatOnClick()
{
	if (GameDataController::gd->getCurrentDay() == 2 && (usedItem == S("sheet") || !GameDataController::gd->getObjective(S("house_b_wife_note_taken"))))
	{
		characterAnimationName = S("kneel_");
	}
	else
	{
		characterAnimationName = S("action_stnd_");
	}
}

void HouseBInsideBody::clickAction2()
{
}

void HouseBInsideBody::clickAction0()
{
	if (GameDataController::gd->getCurrentDay() <= 2 && (!GameDataController::gd->getObjective(S("house_b_wife_covered")) || GameDataController::gd->getObjective(S("house_b_wife_note_taken"))) && !GameDataController::gd->getObjective(S("house_b_wife_note_taken")) && usedItem == String::Empty)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_wife_inspected")), true);
	}
}
