#include "../game_all.h"

void OutpostOutsideRadarKreci::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_radar_plate");
	range = 100.0f;
	updateAll();
}

void OutpostOutsideRadarKreci::clickAction()
{
	if (!GameDataController::gd->getObjective(S("outpost_radar_repaired")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outside_radar_broken")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outside_radar_working")));
	}
}

void OutpostOutsideRadarKreci::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_radar_repaired")))
	{
		GetComponent<Animator>()->Play(S("outside_radar1"));
	}
	else
	{
		GetComponent<Animator>()->Play(S("outside_radar0"));
	}
}

void OutpostOutsideRadarKreci::clickAction2()
{
}

void OutpostOutsideRadarKreci::clickAction0()
{
}

void OutpostOutsideRadarKreci::whatOnClick0()
{
}

void OutpostOutsideRadarKreci::whatOnClick()
{
}
