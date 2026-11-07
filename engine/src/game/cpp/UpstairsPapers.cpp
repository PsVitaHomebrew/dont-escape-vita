#include "../game_all.h"

void UpstairsPapers::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("upstairs_papers");
}

void UpstairsPapers::clickAction()
{
	GameDataController::gd->setObjective(S("upstairs_papers_taken"), true);
	GameDataController::gd->setObjective(S("upstairs_paperclip_taken"), true);
	PlayerController::wc->forceAnimation(S("stand_n"));
	P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->actionWithText = false;
	timelineAction->blockG = true;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("base_papers1"));
	timelineAction->function = [this](String param) { take1(param); };
	timelineAction->param = S("paperclip");
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->actionWithText = false;
	timelineAction->blockG = true;
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("base_papers2"));
	timelineAction->function = [this](String param) { take1(param); };
	timelineAction->param = S("invoices");
	Timeline::t->addAction(timelineAction);
	updateAll();
}

void UpstairsPapers::take1(String param)
{
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(param));
}

void UpstairsPapers::updateState()
{
	if (GameDataController::gd->getObjective(S("upstairs_papers_taken")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
}

void UpstairsPapers::clickAction2()
{
}

void UpstairsPapers::clickAction0()
{
}
