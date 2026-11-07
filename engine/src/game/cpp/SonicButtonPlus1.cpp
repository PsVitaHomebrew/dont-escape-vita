#include "../game_all.h"

void SonicButtonPlus1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("button");
	teleport = true;
	range = 100.0f;
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
	sr = GetComponent<SpriteRenderer>();
}

void SonicButtonPlus1::clickAction()
{
	int objectiveDetail = GameDataController::gd->getObjectiveDetail(S("sonic_frequency"));
	objectiveDetail += delta;
	if (objectiveDetail > 999)
	{
		objectiveDetail = 999;
	}
	if (objectiveDetail < 100)
	{
		objectiveDetail = 100;
	}
	GameDataController::gd->setObjectiveDetail(S("sonic_frequency"), objectiveDetail);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
	sr->set_sprite(down);
	setCollider(-1);
	Invoke(S("restore"), 0.05f);
}

void SonicButtonPlus1::restore()
{
	setCollider(0);
	sr->set_sprite(up);
}

void SonicButtonPlus1::updateAfterAnimation()
{
	updateAll();
}

void SonicButtonPlus1::updateState()
{
}

void SonicButtonPlus1::clickAction2()
{
}

void SonicButtonPlus1::clickAction0()
{
}
