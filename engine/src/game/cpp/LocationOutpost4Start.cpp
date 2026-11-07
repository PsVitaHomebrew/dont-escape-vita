#include "../game_all.h"

void LocationOutpost4Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.006f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 70.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	gingerShowFinger = false;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 160.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Hallway);
	PlayerController::wc->shadow->scaleFactor = 0.25f;
	PlayerController::wc->shadow->downwards = true;
	GameDataController::gd->setObjective(S("outpost_spaceship_discovered"), true);
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	if (PlayerController::pc->spawnName != S("Waypoint_Outpost4_3") && PlayerController::pc->spawnName != S("previous"))
	{
		GameObject::Find(S("Waypoint_Outpost4_3"))->GetComponent<Waypoint_Outpost4_3>()->closeDoorQuickAndFast();
	}
	if (GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		GameObject::Find(S("Waypoint_Outpost4_3"))->GetComponent<Waypoint_Outpost4_3>()->closeDoorInFive();
	}
	GameDataController::gd->setObjective(S("visited_outpost4"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	if (GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("ClosedElevator"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	}
	else
	{
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("ClosedElevator"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	}
	if (GameDataController::gd->getObjectiveDetail(S("outpost_underground_light")) == 0)
	{
		light1->set_enabled(true);
		light2->set_enabled(false);
		light3->set_enabled(false);
		JukeboxAmbient::jb->changeAmbient(nullptr, 1.0f);
	}
	if (GameDataController::gd->getObjectiveDetail(S("outpost_underground_light")) == 1)
	{
		light1->set_enabled(false);
		light2->set_enabled(true);
		light3->set_enabled(false);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->buzz, 0.15f);
	}
	if (GameDataController::gd->getObjectiveDetail(S("outpost_underground_light")) == 2)
	{
		light1->set_enabled(false);
		light2->set_enabled(false);
		light3->set_enabled(true);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->buzz, 0.3f);
	}
	if (!GameDataController::gd->getObjective(S("outpost_underground_light")))
	{
		lights_bool = false;
	}
	else
	{
		lights_bool = true;
	}
	lights_int = GameDataController::gd->getObjectiveDetail(S("outpost_underground_light"));
}

void LocationOutpost4Start::moveNpc2()
{
	GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->setSimpleTargetV3(npc2_target->transform->get_position());
}

void LocationOutpost4Start::moveNpc3()
{
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setSimpleTargetV3(npc3_target->transform->get_position());
}

void LocationOutpost4Start::Update()
{
	if (gingerShowFinger && ginger->currentXY.y >= 30.0f && ginger->currentXY.y <= 32.0f && ginger->currentXY.x <= 68.0f && ginger->currentXY.x >= 66.0f)
	{
		gingerShowFinger = false;
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		P<TextFieldController> component2 = GameObject::Find(S("diode"))->GetComponent<TextFieldController>();
		GameObject::Find(S("diode"))->GetComponent<Locationoutpost4FingerScanner>()->scansound();
		P<TimelineAction> timelineAction = New<TimelineAction>();
		timelineAction = New<TimelineAction>();
		timelineAction->textfield = component2;
		timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
		timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("fingerprint_reader3"));
		timelineAction->actionWithText = true;
		timelineAction->function = [target = GameObject::Find(S("diode"))->GetComponent<Locationoutpost4FingerScanner>()](String s) { target->failsound(s); };
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>();
		timelineAction->textfield = component;
		timelineAction->backgroundColor = Vector3(0.0f, 0.0f, 0.0f);
		timelineAction->textColor = GingerActionController::getColor();
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("fingerprint_reader_cate"));
		timelineAction->actionWithText = true;
		timelineAction->function = [this](String s) { gingerGoAway(s); };
		Timeline::t->addAction(timelineAction);
	}
	if (PlayerController::wc->currentXY.x > 100.0f)
	{
		PlayerController::wc->shadow->source = 160.0f;
	}
	else
	{
		PlayerController::wc->shadow->source = 40.0f;
	}
	if (PlayerController::wc->currentXY.x > 190.0f)
	{
		PlayerController::pc->allowDrop = false;
	}
	else
	{
		PlayerController::pc->allowDrop = true;
	}
	PlayerController::wc->shadow->scaleFactor = 0.1f + Mathf::Abs(PlayerController::wc->currentXY.y - 25.0f) / 60.0f;
	if (PlayerController::wc->currentXY.y > 25.0f)
	{
		PlayerController::wc->shadow->downwards = false;
	}
	else
	{
		PlayerController::wc->shadow->downwards = true;
	}
	if (lights_int == 0)
	{
		if (PlayerController::wc->currentXY.x < 200.0f)
		{
			GameDataController::gd->setObjectiveDetail(S("outpost_underground_light"), 1);
			lights_int = 1;
			light1->set_enabled(false);
			light2->set_enabled(true);
			light3->set_enabled(false);
			lights_bool = true;
			GameDataController::gd->setObjective(S("outpost_underground_light"), true);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->lamp_on);
			JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->buzz, 0.15f);
			GameObject::Find(S("diode"))->GetComponent<Locationoutpost4FingerScanner>()->updateAll();
			GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setSimpleTargetV3(npc1_target->transform->get_position());
			if (GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjective(S("npc2_joined")))
			{
				Invoke(S("moveNpc2"), 0.5f);
			}
			if (GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc3_joined")))
			{
				Invoke(S("moveNpc3"), 1.0f);
			}
		}
	}
	else if (lights_int == 1 && PlayerController::wc->currentXY.x < 100.0f)
	{
		GameDataController::gd->setObjectiveDetail(S("outpost_underground_light"), 2);
		lights_int = 2;
		GameObject::Find(S("diode"))->GetComponent<Locationoutpost4FingerScanner>()->updateAll();
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->neon_on);
		light1->set_enabled(false);
		light2->set_enabled(false);
		light3->set_enabled(true);
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->buzz, 0.3f);
	}
}

void LocationOutpost4Start::gingerGoAway(String val)
{
	ginger->setSimpleTarget(Vector2(80.0f, 30.0f));
}
