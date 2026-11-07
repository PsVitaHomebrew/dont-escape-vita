#include "../game_all.h"

void TentDistanceThings::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_ne");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	range = 30.0f;
	gameObject->transform->Find(S("thing_gas"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->transform->Find(S("thing"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->transform->Find(S("thing_webs"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		thingToShow = gameObject->transform->Find(S("thing"))->gameObject;
		objectName = S("tent_distance_swarm");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		thingToShow = gameObject->transform->Find(S("thing_gas"))->gameObject;
		objectName = S("tent_distance_gas");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		thingToShow = gameObject->transform->Find(S("thing_webs"))->gameObject;
		objectName = S("tent_distance_webs");
	}
	thingToShow->GetComponent<SpriteRenderer>()->set_enabled(true);
	pozycja = Vector3(thingToShow->transform->get_position().x, thingToShow->transform->get_position().y, thingToShow->transform->get_position().z);
	if (GameDataController::gd->getObjective(S("tent_distance_checked")))
	{
		pozycja.y = -0.68f;
	}
	updateState();
}

void TentDistanceThings::Update()
{
	if (PlayerController::wc->currentXY.x > 60.0f && !GameDataController::gd->getObjective(S("tent_distance_triggered")))
	{
		GameDataController::gd->setObjective(S("tent_distance_triggered"), true);
		updateState();
	}
	if (GameDataController::gd->getObjective(S("tent_distance_triggered")) && (double)pozycja.y < -0.66)
	{
		if ((double)pozycja.y < -0.76)
		{
			pozycja.y += 0.012f * Time::get_deltaTime();
		}
		if ((double)pozycja.y < -0.74)
		{
			pozycja.y += 0.01f * Time::get_deltaTime();
		}
		if ((double)pozycja.y < -0.72)
		{
			pozycja.y += 0.007f * Time::get_deltaTime();
		}
		if ((double)pozycja.y < -0.7)
		{
			pozycja.y += 0.005f * Time::get_deltaTime();
		}
		if ((double)pozycja.y < -0.68)
		{
			pozycja.y += 0.002f * Time::get_deltaTime();
		}
		pozycja.y += 0.001f * Time::get_deltaTime();
		thingToShow->transform->set_position(ScreenControler::roundToNearestFullPixel2(pozycja));
	}
	PlayerController::wc->shadowOffsetY = -5;
}

void TentDistanceThings::whatOnClick()
{
}

void TentDistanceThings::clickAction()
{
	PlayerController::wc->fullStop(true);
	P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, objectName);
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("tent_distance_2"));
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("tent_distance_3"));
	Timeline::t->addAction(timelineAction);
	if (!GameDataController::gd->getObjective(S("tent_distance_checked")))
	{
		timelineAction = New<TimelineAction>(GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>());
		timelineAction->textWidth = BottomTextController::bottomTextWidth;
		timelineAction->text = S("[") + GameStrings::getString(GameStrings::gui, S("gui_hint")) + S("]");
		timelineAction->actionWithText = true;
		timelineAction->function = [obj = GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()](String param) { obj->showJournal(param); };
		Timeline::t->addAction(timelineAction);
	}
	GameDataController::gd->setObjective(S("tent_distance_checked"), true);
}

void TentDistanceThings::updateState()
{
	if (!GameDataController::gd->getObjective(S("tent_distance_triggered")))
	{
		colliderManager->setCollider(-1);
	}
	else
	{
		colliderManager->setCollider(0);
	}
}

void TentDistanceThings::clickAction2()
{
}

void TentDistanceThings::clickAction0()
{
}
