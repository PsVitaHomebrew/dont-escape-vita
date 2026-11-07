#include "../game_all.h"

void BaseOutside2Grave1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("grave_cody");
	range = 10.0f;
	teleport = false;
	updateState();
}

void BaseOutside2Grave1::Update()
{
}

void BaseOutside2Grave1::whatOnClick()
{
}

void BaseOutside2Grave1::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("grave_cody")), true, false, false, 150);
}

void BaseOutside2Grave1::updateState()
{
	setCollider(-1);
	GetComponent<SpriteRenderer>()->set_enabled(false);
	if (GameDataController::gd->getCurrentDay() >= 3 && GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) != 1)
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("grave_cody");
	}
}

void BaseOutside2Grave1::clickAction2()
{
}

void BaseOutside2Grave1::clickAction0()
{
}
