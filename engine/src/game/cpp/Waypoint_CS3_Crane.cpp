#include "../game_all.h"

void Waypoint_CS3_Crane::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_crane");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
}

void Waypoint_CS3_Crane::clickAction()
{
	if (!GameDataController::gd->getObjective(S("cs_rain_enter_left")) && !GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
	}
	else
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("climb_up_crane")), QuestionController::PopupType::QUESTION, [this]() { climbCrane(); }, 5);
	}
}

void Waypoint_CS3_Crane::climbCrane()
{
	PlayerController::pc->spawnName = S("Waypoint_Crane_CS3");
	CurtainController::cc->fadeOut(S("CS_Crane"), WalkController::Direction::E);
}

void Waypoint_CS3_Crane::updateState()
{
	setCollider(0);
	if (!GameDataController::gd->getObjective(S("cs_rain_enter_left")) && !GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		range = 200.0f;
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		range = 1.0f;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 1)
	{
		setCollider(-1);
	}
}

void Waypoint_CS3_Crane::clickAction2()
{
}

void Waypoint_CS3_Crane::clickAction0()
{
}
