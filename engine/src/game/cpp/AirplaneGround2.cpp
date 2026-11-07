#include "../game_all.h"

void AirplaneGround2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airplane_nose");
	range = 100.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("shovel"), GameStrings::getString(GameStrings::actions, S("plane_ground2")), nullptr, String::Empty));
}

void AirplaneGround2::clickAction()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("plane_ground")));
}

void AirplaneGround2::updateState()
{
}

void AirplaneGround2::clickAction2()
{
}

void AirplaneGround2::clickAction0()
{
}

void AirplaneGround2::whatOnClick0()
{
}

void AirplaneGround2::whatOnClick()
{
}
