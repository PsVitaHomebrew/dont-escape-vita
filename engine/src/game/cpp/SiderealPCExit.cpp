#include "../game_all.h"

void SiderealPCExit::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("leave");
	teleport = true;
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
}

void SiderealPCExit::clickAction()
{
	GameObject::Find(S("pc_mail_page_caption"))->GetComponent<WorldCaption>()->hide();
	PlayerController::pc->spawnName = S("SiderealF2SPC2");
	PlayerController::wc->fullStop();
	CurtainController::cc->fadeOut(S("SiderealF2S"), WalkController::Direction::N);
}

void SiderealPCExit::updateState()
{
}

void SiderealPCExit::clickAction2()
{
}

void SiderealPCExit::clickAction0()
{
}
