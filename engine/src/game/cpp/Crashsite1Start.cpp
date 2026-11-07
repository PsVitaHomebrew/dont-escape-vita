#include "../game_all.h"

void Crashsite1Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -7.0f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 160.0f;
	PlayerController::ssg->setStepType(S("road"));
	GameDataController::gd->setObjective(S("visited_crashsite1"), true);
	GameDataController::gd->setObjective(S("bridge_westside"), false);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_1a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	if (!GameDataController::gd->getObjective(S("crashsite_discovered_bugs")))
	{
		GameDataController::gd->setObjective(S("crashsite_discovered_bugs"), true);
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("crashsite_discover_bugs1"));
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("crashsite_discover_bugs2"));
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("crashsite_discover_bugs3"));
			Timeline::t->addAction(timelineAction);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			P<TimelineAction> timelineAction2 = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction2->text = GameStrings::getString(GameStrings::actions, S("crashsite_discover_gas1"));
			Timeline::t->addAction(timelineAction2);
			timelineAction2 = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction2->text = GameStrings::getString(GameStrings::actions, S("crashsite_discover_gas2"));
			Timeline::t->addAction(timelineAction2);
			timelineAction2 = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction2->text = GameStrings::getString(GameStrings::actions, S("crashsite_discover_gas3"));
			Timeline::t->addAction(timelineAction2);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			P<TimelineAction> timelineAction3 = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction3->text = GameStrings::getString(GameStrings::actions, S("crashsite_discover_spiders1"));
			Timeline::t->addAction(timelineAction3);
			timelineAction3 = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction3->text = GameStrings::getString(GameStrings::actions, S("crashsite_discover_spiders2"));
			Timeline::t->addAction(timelineAction3);
			timelineAction3 = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction3->text = GameStrings::getString(GameStrings::actions, S("crashsite_discover_spiders3"));
			Timeline::t->addAction(timelineAction3);
		}
	}
	if (GameDataController::gd->getCurrentDay() > 1)
	{
		tloD1->set_enabled(false);
		tloD2->set_enabled(true);
		GameObject::Find(S("ExpandedPath"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("ExpandedPath2"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("RVWaypoint"))->GetComponent<RVWaypoint>()->setCollider(0);
	}
	else
	{
		tloD1->set_enabled(true);
		tloD2->set_enabled(false);
		GameObject::Find(S("ExpandedPath"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("ExpandedPath2"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("RVWaypoint"))->GetComponent<RVWaypoint>()->setCollider(-1);
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void Crashsite1Start::Update()
{
}
