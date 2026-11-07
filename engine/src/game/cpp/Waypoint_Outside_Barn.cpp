#include "../game_all.h"

void Waypoint_Outside_Barn::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_entry");
	doubleClickCondition = S("visited_barn");
	engineRun = SoundsManagerController::sm->engine_run;
	aS = gameObject->AddComponent<AudioSource>();
	if (GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) != 0 && GameDataController::gd->getObjective(S("barn_pump_started")))
	{
		aS->set_clip(engineRun);
		aS->set_loop(true);
		aS->set_volume(0.1f);
		aS->Play();
	}
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void Waypoint_Outside_Barn::clickAction()
{
	PlayerController::pc->spawnName = S("Waypoint_Barn_Outside");
	CurtainController::cc->fadeOut(S("Barn"), WalkController::Direction::E);
}

void Waypoint_Outside_Barn::updateState()
{
	colliderManager->setCollider(0);
}

void Waypoint_Outside_Barn::clickAction2()
{
}

void Waypoint_Outside_Barn::clickAction0()
{
}
