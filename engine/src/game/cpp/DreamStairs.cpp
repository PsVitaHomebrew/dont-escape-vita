#include "../game_all.h"

void DreamStairs::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("dream_stairs");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = String::Empty;
}

void DreamStairs::clickAction()
{
	if (GameDataController::gd->getObjective(S("dream_tiger_future")) || GameDataController::gd->getObjective(S("dream_maggie_future")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("not_going_back")));
		return;
	}
	PlayerController::pc->spawnName = S("DreamStairs");
	CurtainController::cc->fadeOut(S("Dream3B"), WalkController::Direction::W);
}

void DreamStairs::updateState()
{
	if ((GameDataController::gd->getObjective(S("previous_disc_barry")) || GameDataController::gd->getObjective(S("previous_disc_cody"))) && GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc2_joined")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void DreamStairs::clickAction2()
{
}

void DreamStairs::clickAction0()
{
}

void DreamStairs::whatOnClick0()
{
}

void DreamStairs::whatOnClick()
{
}
