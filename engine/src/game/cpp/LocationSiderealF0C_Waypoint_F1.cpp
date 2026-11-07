#include "../game_all.h"

void LocationSiderealF0C_Waypoint_F1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_elevator_1");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
}

void LocationSiderealF0C_Waypoint_F1::clickAction()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("sidereal_elevator_up")), QuestionController::PopupType::QUESTION, [this]() { climb(); }, 5);
}

void LocationSiderealF0C_Waypoint_F1::climb()
{
	PlayerController::pc->spawnName = S("elevator_door");
	CurtainController::cc->fadeOut(S("SiderealF1C"), WalkController::Direction::W);
}

void LocationSiderealF0C_Waypoint_F1::updateState()
{
}

void LocationSiderealF0C_Waypoint_F1::clickAction2()
{
}

void LocationSiderealF0C_Waypoint_F1::clickAction0()
{
}
