#include "../game_all.h"

void CS2Thug::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = true;
	characterAnimationName = S("action_stnd_");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_thug");
	range = 5.0f;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("rifle_so_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_0"), GameStrings::getString(GameStrings::actions, S("rifle_no_ammo")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_0"), GameStrings::getString(GameStrings::actions, S("rifle_no_ammo")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_6"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_5"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_4"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_3"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_2"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_1"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_0"), GameStrings::getString(GameStrings::actions, S("rifle_no_ammo")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_6"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_5"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_4"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_3"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_2"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_1"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_0"), GameStrings::getString(GameStrings::actions, S("rifle_no_ammo")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_6"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_5"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_4"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_3"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_2"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_1"), GameStrings::getString(GameStrings::actions, S("rifle_too_loud")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rock"), GameStrings::getString(GameStrings::actions, S("thug_rock")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rock2"), GameStrings::getString(GameStrings::actions, S("thug_rock")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("maggot"), GameStrings::getString(GameStrings::actions, S("thug_maggot")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("knife"), GameStrings::getString(GameStrings::actions, S("thug_knife")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("revolver_0"), GameStrings::getString(GameStrings::actions, S("rifle_no_ammo")), nullptr, String::Empty));
}

void CS2Thug::clickAction()
{
	if (usedItem != String::Empty)
	{
		ts->getShot();
		setCollider(-1);
		ItemsManager::im->rifleShot(usedItem);
		Invoke(S("thud"), 0.5f);
	}
}

void CS2Thug::thud()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_thud2);
}

void CS2Thug::whatOnClick0()
{
	animationFlip = false;
	useCurrentDirection = true;
	characterAnimationName = S("action_stnd_");
	range = 200.0f;
	if (usedItem != String::Empty)
	{
		range = 10.0f;
		animationFlip = true;
		useCurrentDirection = false;
		characterAnimationName = S("shoot_n");
	}
}

void CS2Thug::updateState()
{
	if (GameDataController::gd->getObjective(S("cs_thug_shot")) || GameDataController::gd->getObjective(S("cs_safe")))
	{
		ts->hide();
		setCollider(-1);
	}
	else
	{
		ts->show();
		setCollider(0);
	}
}

void CS2Thug::clickAction2()
{
}

void CS2Thug::clickAction0()
{
}
