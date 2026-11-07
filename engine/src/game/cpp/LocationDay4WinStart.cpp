#include "../game_all.h"

void LocationDay4WinStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -5.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("none"));
	MonoBehaviour::print(S("............................. LOCATION INFO  .................................."));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	GameDataController::Achievement(S("DAY_4"));
	GameDataController::gd->gameTime = 480;
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_success);
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	if (GameDataController::gd->getObjectiveDetail(S("day4_complete")) > 0)
	{
		GameDataController::gd->setObjective(S("npc1_alive"), true);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { continueGame(param); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("0");
		Timeline::t->textField->directionY = -1.0f;
		timelineAction->textWidth = 190;
		Timeline::t->textField->shift.x = -80.0f;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day4_normal"));
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
		{
			GameDataController::Achievement(S("P_AIR"));
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1)
		{
			GameDataController::Achievement(S("P_FUEL"));
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day4_complete")) <= 0)
	{
		GameDataController::gd->setObjective(S("npc1_alive"), false);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String param) { continueGame(param); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("0");
		Timeline::t->textField->directionY = -1.0f;
		timelineAction->textWidth = 190;
		Timeline::t->textField->shift.x = -80.0f;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day4_penalty"));
		Timeline::t->addAction(timelineAction);
	}
	if (GameDataController::gd->equipped == S("pills"))
	{
		InventoryController::ic->removeItem(GameDataController::gd->equipped);
	}
	String empty = String::Empty;
	empty = ((!GameDataController::gd->getObjective(S("npc3_joined"))) ? S("not joined/") : S("joined/"));
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		empty += S("alive");
	}
	else
	{
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 0)
		{
			empty += S("died on day 2");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
		{
			empty += S("died in Sidereal");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2)
		{
			empty += S("died on day 3");
		}
	}
	String empty2 = String::Empty;
	empty2 = ((!GameDataController::gd->getObjective(S("npc2_joined"))) ? S("not joined/") : S("joined/"));
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		empty2 += S("alive");
	}
	else
	{
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 0)
		{
			empty2 += S("died on day 2");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
		{
			empty2 += S("died in Sidereal");
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2)
		{
			empty2 += S("died on day 3");
		}
	}
	String empty3 = String::Empty;
	if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		empty3 = S("alive");
	}
	else
	{
		empty3 = S("died on day 4");
	}
}

void LocationDay4WinStart::continueGame(String param)
{
	JukeboxMusic::jb->changeMusic(nullptr);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("MoonIntro0"), WalkController::Direction::E);
}

void LocationDay4WinStart::Update()
{
}
