#include "../game_all.h"

void Waypoint_CS4_CS5::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_scaffolding");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("gloves"), String::Empty, nullptr, String::Empty));
}

void Waypoint_CS4_CS5::clickAction()
{
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
	}
	else if (usedItem == S("gloves"))
	{
		GameDataController::gd->setObjective(S("constructionsite_from_above"), false);
		PlayerController::pc->spawnName = S("Waypoint_CS5_CS4");
		CurtainController::cc->fadeOut(S("CS5"), WalkController::Direction::N);
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("scffolding")));
	}
}

void Waypoint_CS4_CS5::updateState()
{
	if (!GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		range = 1.0f;
		characterAnimationName = S("stop");
	}
	else
	{
		range = 100.0f;
		characterAnimationName = S("action_stnd_");
	}
}

void Waypoint_CS4_CS5::clickAction2()
{
}

void Waypoint_CS4_CS5::clickAction0()
{
}
