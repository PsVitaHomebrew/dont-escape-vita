#include "../game_all.h"

void Waypoint_Crane_CS3::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_crane");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	doubleClickCondition = String::Empty;
}

void Waypoint_Crane_CS3::clickAction()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("climb_down_crane")), QuestionController::PopupType::QUESTION, [this]() { climbCrane(); });
}

void Waypoint_Crane_CS3::climbCrane()
{
	GameDataController::gd->setObjective(S("cs_rain_enter_left"), true);
	PlayerController::pc->spawnName = S("Waypoint_CS3_Crane");
	CurtainController::cc->fadeOut(S("CS3"), WalkController::Direction::S_);
}

void Waypoint_Crane_CS3::updateState()
{
}

void Waypoint_Crane_CS3::clickAction2()
{
}

void Waypoint_Crane_CS3::clickAction0()
{
}
