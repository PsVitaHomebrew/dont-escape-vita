#include "../game_all.h"

void LocationOutpost11Board::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_board");
	range = 0.0f;
	teleport = false;
	updateState();
	actionType = Type::NormalAction;
}

void LocationOutpost11Board::Update()
{
}

void LocationOutpost11Board::whatOnClick()
{
}

void LocationOutpost11Board::clickAction()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moon_presentation")));
}

void LocationOutpost11Board::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_switch_pressed")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 30.0f;
		setCollider(0);
	}
	else
	{
		setCollider(-1);
	}
}

void LocationOutpost11Board::clickAction2()
{
}

void LocationOutpost11Board::clickAction0()
{
}
