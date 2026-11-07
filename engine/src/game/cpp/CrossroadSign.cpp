#include "../game_all.h"

void CrossroadSign::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("crossroad_sign");
	range = 15.0f;
}

void CrossroadSign::clickAction()
{
	ExamineSprite::es->textField->shift.x = -80.0f;
	ExamineSprite::es->textField->shift.y = -40.0f;
	ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("crossroad_sign")) }), 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	ExamineSprite::es->show(sign);
	if (GameDataController::gd->getObjectiveDetail(S("map_gasstation_revealed")) != TravelAgency::LOCATION_STATUS_REACHABLE)
	{
		GameDataController::gd->setObjectiveDetail(S("map_gasstation_revealed"), TravelAgency::LOCATION_STATUS_UNREACHABLE);
	}
}

void CrossroadSign::updateState()
{
	colliderManager->setCollider(0);
}

void CrossroadSign::clickAction2()
{
}

void CrossroadSign::clickAction0()
{
}

void CrossroadSign::whatOnClick0()
{
}

void CrossroadSign::whatOnClick()
{
}
