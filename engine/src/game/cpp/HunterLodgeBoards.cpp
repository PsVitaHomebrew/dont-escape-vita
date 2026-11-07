#include "../game_all.h"

void HunterLodgeBoards::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n");
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("boards3");
}

void HunterLodgeBoards::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("lodge_board_taken")) == 0)
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("board1"))))
		{
			GameDataController::gd->setObjectiveDetail(S("lodge_board_taken"), 1);
			updateAll();
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("lodge_board_taken")) == 1)
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("board2"))))
		{
			GameDataController::gd->setObjectiveDetail(S("lodge_board_taken"), 2);
			updateAll();
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("lodge_board_taken")) == 2 && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("board3"))))
	{
		GameDataController::gd->setObjectiveDetail(S("lodge_board_taken"), 3);
		updateAll();
	}
}

void HunterLodgeBoards::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("lodge_board_taken")) < 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		if (GameDataController::gd->getObjectiveDetail(S("lodge_board_taken")) == 0)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
			board2->set_enabled(true);
			board3->set_enabled(true);
			colliderManager->setCollider(0);
			objectName = S("boards3");
		}
		else if (GameDataController::gd->getObjectiveDetail(S("lodge_board_taken")) == 1)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
			board2->set_enabled(true);
			board3->set_enabled(true);
			colliderManager->setCollider(1);
			objectName = S("boards2");
		}
		else if (GameDataController::gd->getObjectiveDetail(S("lodge_board_taken")) == 2)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
			board2->set_enabled(false);
			board3->set_enabled(true);
			colliderManager->setCollider(2);
			objectName = S("boards1");
		}
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		board2->set_enabled(false);
		board3->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void HunterLodgeBoards::clickAction2()
{
}

void HunterLodgeBoards::clickAction0()
{
}
