#include "../game_all.h"

void LocationOutside2Thugs::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("heap_of_thugs");
	range = 100.0f;
}

void LocationOutside2Thugs::clickAction()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("heap_of_thugs")));
}

void LocationOutside2Thugs::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 4)
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void LocationOutside2Thugs::clickAction2()
{
}

void LocationOutside2Thugs::clickAction0()
{
}

void LocationOutside2Thugs::whatOnClick0()
{
}

void LocationOutside2Thugs::whatOnClick()
{
}
