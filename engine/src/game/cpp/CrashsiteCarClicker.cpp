#include "../game_all.h"

void CrashsiteCarClicker::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_stnd_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("crashsite_car_unexamined");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("wrench"), String::Empty, nullptr, String::Empty));
	updateState();
	ENGINE_TODO("MonoBehaviour.print(dkvs)");
}

void CrashsiteCarClicker::clickAction()
{
	if (!GameDataController::gd->getObjective(S("crashsite_car_examined")))
	{
		P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("crashsite_car_examine"));
		timelineAction->function = [this](String str_) { examineCar(str_); };
		timelineAction->actionWithText = false;
		Timeline::t->addAction(timelineAction);
	}
	else if (!GameDataController::gd->getObjective(S("crashsite_car_harvested")))
	{
		if (usedItem == String::Empty)
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_car_could_harvest")), true);
			return;
		}
		P<TimelineAction> timelineAction2 = New<TimelineAction>(PlayerController::pc->textField);
		timelineAction2->text = GameStrings::getString(GameStrings::actions, S("crashsite_car_harvest"));
		timelineAction2->function = [this](String str_) { harvestCar(str_); };
		timelineAction2->actionWithText = false;
		Timeline::t->addAction(timelineAction2);
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_car_empty")), true);
	}
}

void CrashsiteCarClicker::updateState()
{
	if (!GameDataController::gd->getObjective(S("crashsite_car_examined")))
	{
		objectName = S("crashsite_car_unexamined");
	}
	else if (!GameDataController::gd->getObjective(S("crashsite_car_harvested")))
	{
		objectName = S("crashsite_car_examined");
	}
	else
	{
		objectName = S("crashsite_car_harvested");
	}
}

void CrashsiteCarClicker::clickAction2()
{
}

void CrashsiteCarClicker::clickAction0()
{
}

void CrashsiteCarClicker::examineCar(String str_)
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("crashsite_car_examine")), QuestionController::PopupType::QUESTION, [this]() { doExamineCar(); }, 15, 2);
}

void CrashsiteCarClicker::harvestCar(String str_)
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("crashsite_car_harvest")), QuestionController::PopupType::QUESTION, [this]() { doHarvestCar(); }, 45, 10);
}

void CrashsiteCarClicker::doHarvestCar()
{
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("action1_e"), nullptr, true, [this]() { sayAboutCarHarvest(); });
}

void CrashsiteCarClicker::doExamineCar()
{
	GameDataController::gd->setObjective(S("crashsite_car_examined"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("action1_e"), nullptr, true, [this]() { sayAboutCarExplore(); });
}

void CrashsiteCarClicker::sayAboutCarHarvest()
{
	GameDataController::gd->setObjective(S("crashsite_car_harvested"), true);
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_car_harvested")), true);
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("ignitioncoil")));
	updateAll();
}

void CrashsiteCarClicker::sayAboutCarExplore()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("crashsite_car_examined")), true);
	updateAll();
}
