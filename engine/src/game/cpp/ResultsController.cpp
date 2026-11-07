#include "../game_all.h"

void ResultsController::Start()
{
}

void ResultsController::Update()
{
}

void ResultsController::init()
{
	pbc = GameObject::Find(S("ProgressBar"))->GetComponent<ProgressBarController>();
	rf = GameObject::Find(S("c_frame"))->GetComponent<ResultsFrame>();
	rf->move(-0.63f, 0.0f);
	chapterResult();
}

void ResultsController::skipFast(String val)
{
	changeDanger(val);
	Timeline::t->killText();
	Timeline::t->proceedWithPurpose();
}

int ResultsController::check(int danger, String label, String pic, bool trackWasShortened)
{
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->function = [this](String v) { changeDanger(v); };
	timelineAction->actionWithText = false;
	removeDanger += danger;
	timelineAction->param = S("-") + danger;
	if (pic == S("hide"))
	{
		timelineAction->param += S("|hide");
		timelineAction->actionWithText = true;
	}
	else if (pic != String::Empty)
	{
		timelineAction->param = timelineAction->param + S("|Bitmaps/Locations/LocationResults/") + pic;
		timelineAction->actionWithText = true;
	}
	else
	{
		timelineAction->actionWithText = false;
	}
	if (trackWasShortened)
	{
		timelineAction->text = GameStrings::getString(GameStrings::results, label);
	}
	else
	{
		timelineAction->text = label;
	}
	Timeline::t->addAction(timelineAction);
	return danger;
}

void ResultsController::liveOrDie2(String val)
{
	GameDataController::gd->finishingLocation = GameDataController::gd->previousLocation;
	if (danger > surviavbleDanger)
	{
		PlayerController::pc->spawnName = S("InfoExit");
		if (GameDataController::gd->getCurrentDay() == 1)
		{
			GameDataController::gd->setObjective(S("day1_complete"), false);
			GameDataController::gd->setObjectiveDetail(S("day1_complete"), -danger);
			CurtainController::cc->fadeOut(S("LocationBugDeath"), WalkController::Direction::S_);
		}
		else if (GameDataController::gd->getCurrentDay() == 2)
		{
			GameDataController::gd->setObjective(S("day2_complete"), false);
			GameDataController::gd->setObjectiveDetail(S("day2_complete"), -danger);
			CurtainController::cc->fadeOut(S("LocationCh2Death"), WalkController::Direction::S_);
		}
		else if (GameDataController::gd->getCurrentDay() == 3)
		{
			GameDataController::gd->setObjective(S("day3_complete"), false);
			GameDataController::gd->setObjectiveDetail(S("day3_complete"), -danger);
			CurtainController::cc->fadeOut(S("LocationCh3Death"), WalkController::Direction::S_);
		}
		else
		{
			GameDataController::gd->setObjective(S("day4_complete"), false);
			GameDataController::gd->setObjectiveDetail(S("day4_complete"), -danger);
			CurtainController::cc->fadeOut(S("LocationCh4Death"), WalkController::Direction::S_);
		}
		return;
	}
	PlayerController::pc->spawnName = S("InfoExit");
	GameDataController::gd->gameTime = 480;
	int num = 0;
	if (winQuality == 3)
	{
		num = 1;
	}
	else if (winQuality == 2)
	{
		num = 0;
	}
	else
	{
		num = -danger;
		if (danger == 0)
		{
			num = -1;
		}
	}
	if (GameDataController::gd->getCurrentDay() == 1)
	{
		GameDataController::gd->setObjective(S("day1_complete"), true);
		GameDataController::gd->setObjectiveDetail(S("day1_complete"), num);
		CurtainController::cc->fadeOut(S("LocationDay1Win"), WalkController::Direction::S_);
	}
	else if (GameDataController::gd->getCurrentDay() == 2)
	{
		GameDataController::gd->setObjective(S("day2_complete"), true);
		GameDataController::gd->setObjectiveDetail(S("day2_complete"), num);
		CurtainController::cc->fadeOut(S("LocationDay2Win"), WalkController::Direction::S_);
	}
	else if (GameDataController::gd->getCurrentDay() == 3)
	{
		GameDataController::gd->setObjective(S("day3_complete"), true);
		GameDataController::gd->setObjectiveDetail(S("day3_complete"), num);
		CurtainController::cc->fadeOut(S("LocationDay3Win"), WalkController::Direction::S_);
	}
	else if (GameDataController::gd->getCurrentDay() == 4)
	{
		GameDataController::gd->setObjective(S("day4_complete"), true);
		GameDataController::gd->setObjectiveDetail(S("day4_complete"), num);
		CurtainController::cc->fadeOut(S("LocationDay4Win"), WalkController::Direction::S_);
	}
}

void ResultsController::liveOrDie(String val)
{
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->function = [this](String v) { liveOrDie2(v); };
	timelineAction->actionWithText = false;
	timelineAction->param = S("0");
	timelineAction->text = S("[") + GameStrings::getString(GameStrings::results, S("results_end")) + S("]");
	Timeline::t->addAction(timelineAction);
}

void ResultsController::changeDanger(String val)
{
	GameObject::Find(S("ProgressBar"))->GetComponent<ProgressBarController>()->surv = surviavbleDanger;
	Array<String> array = val.Split(u'|');
	int num = ((array.Length() > 0 && array[0] != String::Empty) ? int_Parse(array[0]) : 0);
	danger += num;
	if (danger <= 0)
	{
		danger = 0;
	}
	MonoBehaviour::print(str(danger));
	pbc->setValue(danger);
	if (array.Length() > 1)
	{
		if (array[1] == S("hide"))
		{
			rf->hide();
		}
		else
		{
			rf->show(Resources::Load<Sprite>(array[1]));
		}
	}
	if (danger == 0 && Timeline::t->actions.Count() > 1)
	{
		MonoBehaviour::print(S("OK THE DANGER IS NONE AND ACTIONS ARE MORE THAN ONE..."));
		while (Timeline::t->actions.Count() > 1)
		{
			Timeline::t->actions.RemoveAt(1);
		}
		liveOrDie(String::Empty);
	}
}

void ResultsController::chapterResult()
{
}
