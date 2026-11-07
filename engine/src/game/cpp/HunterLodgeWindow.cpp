#include "../game_all.h"

void HunterLodgeWindow::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_window");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ext_cord_place"), String::Empty, nullptr, String::Empty));
	updateState();
}

void HunterLodgeWindow::Update()
{
}

void HunterLodgeWindow::clickAction()
{
	if (usedItem == String::Empty)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("lodge_window")));
		return;
	}
	GameDataController::gd->setObjective(S("lodge_cord_dragged"), true);
	updateAll();
}

void HunterLodgeWindow::updateState()
{
}

void HunterLodgeWindow::clickAction2()
{
}

void HunterLodgeWindow::clickAction0()
{
}

void HunterLodgeWindow::whatOnClick0()
{
	if (usedItem != String::Empty)
	{
		range = 1.0f;
		characterAnimationName = S("action_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		range = 20.0f;
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
}

void HunterLodgeWindow::whatOnClick()
{
}
