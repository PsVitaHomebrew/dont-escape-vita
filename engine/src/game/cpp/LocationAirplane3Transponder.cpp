#include "../game_all.h"

void LocationAirplane3Transponder::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action1_e");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airplane_transponder");
	range = 2.0f;
	dir = 1.0f;
	alpha = 0.0f;
	sr = gameObject->GetComponent<SpriteRenderer>();
	updateAll();
}

void LocationAirplane3Transponder::Update()
{
	if (stopped)
	{
		alpha = 0.0f;
	}
	sr->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	alpha += Time::get_deltaTime() * dir * 1.0f;
	if (alpha >= 1.0f)
	{
		dir = -1.0f;
	}
	else if (alpha <= 0.0f)
	{
		dir = 1.0f;
	}
}

void LocationAirplane3Transponder::clickAction()
{
	if (!GameDataController::gd->getObjective(S("plane_transponder_disabled")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click2);
		GameDataController::gd->setObjective(S("plane_transponder_disabled"), true);
		updateState();
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("transponder_disabled1")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("transponder_disabled2")));
	}
}

void LocationAirplane3Transponder::updateState()
{
	if (GameDataController::gd->getObjective(S("plane_transponder_disabled")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		stopped = true;
		range = 100.0f;
	}
	else
	{
		characterAnimationName = S("action1_e");
		animationFlip = false;
		useCurrentDirection = false;
		range = 2.0f;
		stopped = false;
	}
}

void LocationAirplane3Transponder::clickAction2()
{
}

void LocationAirplane3Transponder::clickAction0()
{
}

void LocationAirplane3Transponder::whatOnClick0()
{
}

void LocationAirplane3Transponder::whatOnClick()
{
}
