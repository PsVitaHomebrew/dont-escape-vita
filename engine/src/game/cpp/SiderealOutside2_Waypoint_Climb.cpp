#include "../game_all.h"

void SiderealOutside2_Waypoint_Climb::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_climb");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 2.0f;
}

void SiderealOutside2_Waypoint_Climb::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_roof_collapsed")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_climb_collapsed")));
	}
	else
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("sidereal_climbing_up")), QuestionController::PopupType::QUESTION, [this]() { climb(); }, 5);
	}
}

void SiderealOutside2_Waypoint_Climb::climb()
{
	PlayerController::pc->spawnName = S("LocationSiderealClimb_Waypoint_2");
	CurtainController::cc->fadeOut(S("SiderealClimb"), WalkController::Direction::E);
}

void SiderealOutside2_Waypoint_Climb::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_roof_collapsed")))
	{
		range = 100.0f;
		characterAnimationName = S("action_stnd_");
	}
	else
	{
		range = 2.0f;
		characterAnimationName = S("action_stnd_");
	}
}

void SiderealOutside2_Waypoint_Climb::clickAction2()
{
}

void SiderealOutside2_Waypoint_Climb::clickAction0()
{
}
