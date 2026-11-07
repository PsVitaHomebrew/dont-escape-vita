#include "../game_all.h"

void HuntersLodgeImpreg::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_stnd_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("impregnator");
	range = 7.0f;
}

void HuntersLodgeImpreg::clickAction()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("impregnator")));
}

void HuntersLodgeImpreg::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void HuntersLodgeImpreg::clickAction2()
{
}

void HuntersLodgeImpreg::clickAction0()
{
}
