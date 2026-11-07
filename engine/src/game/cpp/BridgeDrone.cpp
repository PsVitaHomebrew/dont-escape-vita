#include "../game_all.h"

void BridgeDrone::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = true;
	characterAnimationName = S("kneel_");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bridge_drone");
	range = 6.0f;
	updateState();
}

void BridgeDrone::clickAction()
{
	pickItUp(nullptr);
}

void BridgeDrone::pickItUp(String param)
{
	updateState();
	if (!InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("drone"))))
	{
		return;
	}
	GameDataController::gd->setObjective(S("drone_taken"), true);
	P<Item> item = ItemsManager::im->getItem(S("drone"));
	List<String> list = List<String>::New();
	if (item->examineTexts != nullptr)
	{
		for (int i = 0; i < item->examineTexts.Count(); i++)
		{
			list.Add(item->examineTexts[i]);
		}
	}
	ExamineSprite::es->textField->shift.x = (float)item->textShiftX;
	ExamineSprite::es->textField->shift.y = (float)item->textShiftY;
	ExamineSprite::es->readyText(list, item->textWidth, item->textColor1.r, item->textColor1.g, item->textColor1.b, item->textColor2.r, item->textColor2.g, item->textColor2.b, item->textColor2.a);
	ExamineSprite::es->show(item->examineSprite, item->examineSprite_1, item->examineSprite_2, item->examineSprite_3, item->examineSprite_4);
	updateState();
}

void BridgeDrone::whatOnClick()
{
}

void BridgeDrone::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 1 || GameDataController::gd->getObjective(S("drone_taken")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void BridgeDrone::clickAction2()
{
}

void BridgeDrone::clickAction0()
{
	P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("bridge_drone_1"));
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("bridge_drone_2"));
	Timeline::t->addAction(timelineAction);
}
