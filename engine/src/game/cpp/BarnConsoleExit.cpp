#include "../game_all.h"

void BarnConsoleExit::Start()
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

void BarnConsoleExit::clickAction()
{
	if (SceneManager::GetActiveScene().get_name() == S("BarnGenerator"))
	{
		PlayerController::pc->spawnName = S("Pump");
	}
	else
	{
		PlayerController::pc->spawnName = S("Sprinklers");
	}
	PlayerController::wc->fullStop();
	CurtainController::cc->fadeOut(S("Barn"), WalkController::Direction::N);
}

void BarnConsoleExit::updateState()
{
}

void BarnConsoleExit::clickAction2()
{
}

void BarnConsoleExit::clickAction0()
{
}
