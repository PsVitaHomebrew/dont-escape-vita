#include "../game_all.h"

void CS3Ammo::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_in_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_ammobox");
	range = 1.0f;
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("oil"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water4"), String::Empty, nullptr, String::Empty));
}

void CS3Ammo::Update()
{
}

void CS3Ammo::clickAction()
{
	if (GameDataController::gd->getCurrentDay() == 4)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("ammo_day4")));
		return;
	}
	if (usedItem == S("oil"))
	{
		GameDataController::gd->setObjective(S("cs_ammo_oiled"), true);
		PlayerController::pc->forceAnimation(S("kneel_out_n"));
		InventoryController::ic->removeItem(usedItem);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour_small, 0.5f);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_ammobox_oil")));
	}
	else if (usedItem.IndexOf(S("water")) != -1)
	{
		GameDataController::gd->setObjective(S("cs_ammo_watered"), true);
		PlayerController::pc->forceAnimation(S("kneel_out_n"));
		InventoryController::ic->removeItem(usedItem);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour_small, 0.5f);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_ammobox_water")));
	}
	else if (!GameDataController::gd->getObjective(S("cs_ammo_oiled")) && !GameDataController::gd->getObjective(S("cs_ammo_watered")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->trunk_open);
		ExamineSprite::es->textField->shift.x = -80.0f;
		ExamineSprite::es->textField->shift.y = -20.0f;
		ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("cs_ammobox")) }), 200, 242.0f / 255.0f, 201.0f / 255.0f, 0.0f, 1.0f, 1.0f, 0.8f, 0.0f);
		ExamineSprite::es->cycleSprites = true;
		ExamineSprite::es->closingAnimation = S("kneel_out_n");
		ExamineSprite::es->show(ammobox2, ammobox2, ammobox2, nullptr, nullptr, [this]() { aaa(); }, false);
	}
	else
	{
		if (!GameDataController::gd->getObjective(S("cs_ammo_oiled")) && !GameDataController::gd->getObjective(S("cs_ammo_watered")))
		{
			PlayerController::pc->forceAnimation(S("kneel_out_n"));
		}
		aaa();
	}
	updateState();
}

void CS3Ammo::aaa()
{
	if (GameDataController::gd->getObjective(S("cs_ammo_oiled")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_ammobox_oil")));
		return;
	}
	if (GameDataController::gd->getObjective(S("cs_ammo_watered")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_ammobox_water")));
		return;
	}
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->trunk_close);
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_ammobox_2")));
}

void CS3Ammo::updateState()
{
	box1->set_enabled(true);
	box2->set_enabled(true);
	setCollider(0);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		box1->set_enabled(false);
		box2->set_enabled(false);
		setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("cs_ammo_oiled")) && !GameDataController::gd->getObjective(S("cs_ammo_watered")))
	{
		characterAnimationName = S("kneel_in_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void CS3Ammo::clickAction2()
{
}

void CS3Ammo::clickAction0()
{
	if (usedItem != String::Empty)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_ammobox_1")));
	}
}

void CS3Ammo::whatOnClick0()
{
	if (usedItem != String::Empty)
	{
		characterAnimationName = S("kneel_in_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void CS3Ammo::whatOnClick()
{
}
