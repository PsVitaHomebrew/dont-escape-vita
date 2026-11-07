#include "../game_all.h"

void Waypoint_CS5_CS4::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("cs_scaffolding");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::S_;
	doubleClickCondition = String::Empty;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("gloves"), String::Empty, nullptr, String::Empty));
}

void Waypoint_CS5_CS4::clickAction()
{
	if (usedItem == S("gloves"))
	{
		GameDataController::gd->setObjective(S("constructionsite_from_above"), false);
		PlayerController::pc->spawnName = S("Waypoint_CS4_CS5");
		CurtainController::cc->fadeOut(S("CS4"), WalkController::Direction::S_, S("window_jump"));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("scffolding")));
	}
}

void Waypoint_CS5_CS4::updateState()
{
}

void Waypoint_CS5_CS4::clickAction2()
{
}

void Waypoint_CS5_CS4::clickAction0()
{
}
