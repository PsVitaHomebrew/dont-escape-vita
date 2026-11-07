#include "../game_all.h"

void CS3Food::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_food");
	range = 1.0f;
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("poison"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("whiskey"), String::Empty, nullptr, String::Empty));
}

void CS3Food::Update()
{
}

void CS3Food::poisionit()
{
	GameDataController::gd->setObjective(S("cs_food_poisioned"), true);
	InventoryController::ic->removeItem(S("poison"));
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour_small, 0.5f);
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_food_poisioned")));
}

void CS3Food::clickAction()
{
	if (GameDataController::gd->getCurrentDay() == 4)
	{
		if (GameDataController::gd->getObjective(S("cs_food_poisioned")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_food_poisioned2")));
		}
		else if (usedItem == String::Empty && !GameDataController::gd->getObjective(S("cs_food_taken")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_food_taken")));
			InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("food_bag")));
			GameDataController::gd->setObjective(S("cs_food_taken"), true);
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("food_day4")));
		}
		return;
	}
	if (usedItem == S("poison"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("poision_food")), QuestionController::PopupType::QUESTION, [this]() { poisionit(); });
	}
	else if (usedItem == S("whiskey"))
	{
		InventoryController::ic->dropItem(ItemsManager::im->getItem(S("whiskey")), true);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_food_whiskey")));
	}
	else if (GameDataController::gd->getObjective(S("cs_food_poisioned")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_food_poisioned2")));
	}
	else if (GameDataController::gd->getObjective(S("cs_food_taken")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_food_taken2")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_food_taken")));
		InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("food_bag")));
		GameDataController::gd->setObjective(S("cs_food_taken"), true);
	}
	updateState();
}

void CS3Food::updateState()
{
	setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else if (!GameDataController::gd->getObjective(S("cs_food_poisioned")))
	{
		objectName = S("cs_food");
	}
	else
	{
		objectName = S("cs_food_poisioned");
	}
	interactions = List<P<ItemInteraction>>::New();
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		interactions.Add(New<ItemInteraction>(S("poison"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("whiskey"), String::Empty, nullptr, String::Empty));
	}
}

void CS3Food::clickAction2()
{
}

void CS3Food::clickAction0()
{
}

void CS3Food::whatOnClick0()
{
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	if (usedItem == String::Empty && !GameDataController::gd->getObjective(S("cs_food_taken")))
	{
		characterAnimationName = S("action1_e");
		animationFlip = false;
		useCurrentDirection = false;
	}
	if (usedItem == S("whiskey"))
	{
		characterAnimationName = S("kneel_s");
		animationFlip = false;
		useCurrentDirection = false;
	}
}

void CS3Food::whatOnClick()
{
}
