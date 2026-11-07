#include "../game_all.h"

void InfoExit::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("information_exit");
	teleport = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	actionType = Type::NormalAction;
	trans_dir = WalkController::Direction::S_;
}

void InfoExit::clickAction()
{
	PlayerController::pc->spawnName = S("previous");
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->book_close, 0.5f);
	PlayerController::wc->fullStop();
	CurtainController::cc->fadeOut(GameDataController::gd->previousLocation, WalkController::Direction::S_, S("action_stnd_s"));
}

void InfoExit::updateState()
{
}

void InfoExit::clickAction2()
{
}

void InfoExit::clickAction0()
{
}
