#include "../game_all.h"

void HuntersLodgeInside1_Waypoint_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_to_inside2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	doubleClickCondition = S("visited_hunters_lodge_2");
}

void HuntersLodgeInside1_Waypoint_2::clickAction()
{
	PlayerController::pc->spawnName = S("HuntersLodgeInside2_Waypoint_1");
	CurtainController::cc->fadeOut(S("HuntersLodgeInside2"), WalkController::Direction::N);
}

void HuntersLodgeInside1_Waypoint_2::updateState()
{
	if (GameDataController::gd->getObjective(S("hunters_lodge_trap4_taken")) || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && GameDataController::gd->getObjectiveDetail(S("lodge_board_taken")) < 3)
		{
			GetComponent<SpriteRenderer>()->set_sprite(boards);
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_sprite(no_trap);
		}
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void HuntersLodgeInside1_Waypoint_2::clickAction2()
{
}

void HuntersLodgeInside1_Waypoint_2::clickAction0()
{
}
