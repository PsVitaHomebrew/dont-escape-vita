#include "../game_all.h"

void PesttruckNote::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pest_note");
}

void PesttruckNote::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0 && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("pest_note"))))
	{
		GameDataController::gd->setObjective(S("pesttruck_note_taken"), !GameDataController::gd->getObjective(S("pesttruck_note_taken")));
		ExamineSprite::es->show(ItemsManager::im->getItem(S("pest_note"))->examineSprite);
		updateState();
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1 && InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("gas_note"))))
	{
		ExamineSprite::es->textField->shift.x = ItemsManager::im->getItem(S("gas_note"))->textShiftX;
		ExamineSprite::es->textField->shift.y = ItemsManager::im->getItem(S("gas_note"))->textShiftY;
		List<String> list = List<String>::New();
		if (ItemsManager::im->getItem(S("gas_note"))->examineTexts != nullptr)
		{
			for (int i = 0; i < ItemsManager::im->getItem(S("gas_note"))->examineTexts.Count(); i++)
			{
				list.Add(ItemsManager::im->getItem(S("gas_note"))->examineTexts[i]);
			}
		}
		ExamineSprite::es->readyText(list, ItemsManager::im->getItem(S("gas_note"))->textWidth, ItemsManager::im->getItem(S("gas_note"))->textColor1.r, ItemsManager::im->getItem(S("gas_note"))->textColor1.g, ItemsManager::im->getItem(S("gas_note"))->textColor1.b, ItemsManager::im->getItem(S("gas_note"))->textColor2.r, ItemsManager::im->getItem(S("gas_note"))->textColor2.g, ItemsManager::im->getItem(S("gas_note"))->textColor2.b, ItemsManager::im->getItem(S("gas_note"))->textColor2.a);
		GameDataController::gd->setObjective(S("pesttruck_note_taken"), !GameDataController::gd->getObjective(S("pesttruck_note_taken")));
		ExamineSprite::es->show(ItemsManager::im->getItem(S("gas_note"))->examineSprite);
		updateState();
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 2 || !InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("spider_note"))))
	{
		return;
	}
	ExamineSprite::es->textField->shift.x = ItemsManager::im->getItem(S("spider_note"))->textShiftX;
	ExamineSprite::es->textField->shift.y = ItemsManager::im->getItem(S("spider_note"))->textShiftY;
	List<String> list2 = List<String>::New();
	if (ItemsManager::im->getItem(S("spider_note"))->examineTexts != nullptr)
	{
		for (int j = 0; j < ItemsManager::im->getItem(S("spider_note"))->examineTexts.Count(); j++)
		{
			list2.Add(ItemsManager::im->getItem(S("spider_note"))->examineTexts[j]);
		}
	}
	ExamineSprite::es->readyText(list2, ItemsManager::im->getItem(S("spider_note"))->textWidth, ItemsManager::im->getItem(S("spider_note"))->textColor1.r, ItemsManager::im->getItem(S("spider_note"))->textColor1.g, ItemsManager::im->getItem(S("spider_note"))->textColor1.b, ItemsManager::im->getItem(S("spider_note"))->textColor2.r, ItemsManager::im->getItem(S("spider_note"))->textColor2.g, ItemsManager::im->getItem(S("spider_note"))->textColor2.b, ItemsManager::im->getItem(S("spider_note"))->textColor2.a);
	GameDataController::gd->setObjective(S("pesttruck_note_taken"), !GameDataController::gd->getObjective(S("pesttruck_note_taken")));
	ExamineSprite::es->show(ItemsManager::im->getItem(S("spider_note"))->examineSprite);
	updateState();
}

void PesttruckNote::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		objectName = S("pest_note");
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		objectName = S("gas_note");
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		objectName = S("spider_note");
	}
	if (!GameDataController::gd->getObjective(S("pesttruck_note_taken")) && GameDataController::gd->getObjective(S("pesttruck_locker4_open")))
	{
		characterAnimationName = S("action_n");
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		colliderManager->setCollider(0);
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
}

void PesttruckNote::clickAction2()
{
	PlayerController::wc->forceAnimation(S("action_stnd_n"));
}

void PesttruckNote::clickAction0()
{
}
