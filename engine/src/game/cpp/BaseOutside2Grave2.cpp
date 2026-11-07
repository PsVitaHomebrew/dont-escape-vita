#include "../game_all.h"

void BaseOutside2Grave2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("grave_barry");
	range = 10.0f;
	teleport = false;
	updateState();
}

void BaseOutside2Grave2::Update()
{
}

void BaseOutside2Grave2::whatOnClick()
{
}

void BaseOutside2Grave2::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("grave_barry")), true, false, false, 150);
}

void BaseOutside2Grave2::updateState()
{
	setCollider(-1);
	GetComponent<SpriteRenderer>()->set_enabled(false);
	if (GameDataController::gd->getCurrentDay() >= 3 && GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) != 1)
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		objectName = S("grave_barry");
	}
}

void BaseOutside2Grave2::clickAction2()
{
}

void BaseOutside2Grave2::clickAction0()
{
}
