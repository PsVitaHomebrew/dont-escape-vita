#include "../game_all.h"

void CS2FenceShelf::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = true;
	characterAnimationName = S("action_stnd_");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_shelf");
	range = 200.0f;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("maggot"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ropehook"), GameStrings::getString(GameStrings::actions, S("shelf_ropehook")), nullptr, String::Empty));
}

void CS2FenceShelf::clickAction()
{
	if (usedItem == S("maggot"))
	{
		if (GameDataController::gd->getObjective(S("cs_thug_shot")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("default2")));
			updateState();
		}
		else if (crow->gameObject->GetComponent<CSCrowSprite>()->free && !GameDataController::gd->getObjective(S("cs_guard_distracted")))
		{
			crow->gameObject->GetComponent<CSCrowSprite>()->free = false;
			crow->Play(S("crow_attack"));
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_already_distracted")));
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cs_parapet")));
	}
}

void CS2FenceShelf::whatOnClick0()
{
}

void CS2FenceShelf::updateState()
{
	interactions = List<P<ItemInteraction>>::New();
	if (!GameDataController::gd->getObjective(S("cs_thug_shot")))
	{
		interactions.Add(New<ItemInteraction>(S("maggot"), String::Empty, nullptr, String::Empty));
	}
	interactions.Add(New<ItemInteraction>(S("ropehook"), GameStrings::getString(GameStrings::actions, S("shelf_ropehook")), nullptr, String::Empty));
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 3)
	{
		setCollider(0);
	}
	else
	{
		setCollider(-1);
	}
}

void CS2FenceShelf::clickAction2()
{
}

void CS2FenceShelf::clickAction0()
{
}
