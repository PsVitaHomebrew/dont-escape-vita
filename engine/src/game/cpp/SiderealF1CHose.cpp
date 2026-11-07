#include "../game_all.h"

void SiderealF1CHose::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_hose");
	range = 1.0f;
	updateState();
	cursorController = GameObject::Find(S("cursor"))->GetComponent<CursorController>();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("rock"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rock2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pipe"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("hammer"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_so_0"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_s_0"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_o_0"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_6"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_0"), String::Empty, nullptr, String::Empty));
}

void SiderealF1CHose::Update()
{
}

void SiderealF1CHose::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_elevator_f1_hosed")) == 0)
	{
		if (usedItem != String::Empty)
		{
			GameDataController::gd->setObjectiveDetail(S("sidereal_elevator_f1_hosed"), 1);
			CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, nullptr, SoundsManagerController::sm->break_window);
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_hose_glass")));
		}
	}
	else if (usedItem != String::Empty)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_hose_glass2")));
	}
	else
	{
		cursorController->selectItem(ItemsManager::im->getItem(S("fire_hose")));
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rope);
	}
}

void SiderealF1CHose::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_elevator_f1_hosed")) == 0)
	{
		sr->set_sprite(glass);
		setCollider(0);
	}
	else if (!GameDataController::gd->getObjective(S("sidereal_elevator_f1_hosed")))
	{
		sr->set_sprite(ready);
		setCollider(0);
	}
	else
	{
		sr->set_sprite(done);
		setCollider(-1);
	}
}

void SiderealF1CHose::clickAction2()
{
}

void SiderealF1CHose::clickAction0()
{
}

void SiderealF1CHose::whatOnClick0()
{
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_elevator_f1_hosed")) == 0 && usedItem == String::Empty)
	{
		range = 30.0f;
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		range = 1.0f;
		animationFlip = false;
		useCurrentDirection = false;
		characterAnimationName = S("action_n");
	}
}

void SiderealF1CHose::whatOnClick()
{
}
