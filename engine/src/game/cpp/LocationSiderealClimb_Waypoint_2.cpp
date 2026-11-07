#include "../game_all.h"

void LocationSiderealClimb_Waypoint_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_climb2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	range = 2.0f;
}

void LocationSiderealClimb_Waypoint_2::clickAction()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("sidereal_climbing_down")), QuestionController::PopupType::QUESTION, [this]() { climb(); }, 5);
}

void LocationSiderealClimb_Waypoint_2::climb()
{
	PlayerController::pc->spawnName = S("SiderealOutside2_Waypoint_Climb");
	CurtainController::cc->fadeOut(S("SiderealOutside2"), WalkController::Direction::S_);
}

void LocationSiderealClimb_Waypoint_2::updateState()
{
}

void LocationSiderealClimb_Waypoint_2::clickAction2()
{
}

void LocationSiderealClimb_Waypoint_2::clickAction0()
{
}
