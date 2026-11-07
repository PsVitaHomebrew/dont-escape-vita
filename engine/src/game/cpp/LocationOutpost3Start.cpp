#include "../game_all.h"

void LocationOutpost3Start::setEntered(String s)
{
	GameDataController::gd->setObjective(S("outpost_doormat_they_enter"), true);
}

void LocationOutpost3Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.003f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -20.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::ROAD);
	PlayerController::wc->shadow->scaleFactor = 0.25f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	if (PlayerController::pc->spawnName != S("Waypoint_Outpost3_4") && PlayerController::pc->spawnName != S("previous"))
	{
		GameObject::Find(S("Waypoint_Outpost3_4"))->GetComponent<Waypoint_Outpost3_4>()->closeDoorQuickAndFast();
	}
	if (GameDataController::gd->getObjective(S("outpost_elevator_open")))
	{
		GameObject::Find(S("Waypoint_Outpost3_4"))->GetComponent<Waypoint_Outpost3_4>()->closeDoorInFive();
	}
	if (!GameDataController::gd->getObjective(S("outpost_doormat_just_disabled")) && !GameDataController::gd->getObjective(S("outpost_door_powered")))
	{
		GameDataController::gd->setObjective(S("outpost_doormat_just_disabled"), true);
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("outpost_elevator_fuse_done_first"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		list[list.Count() - 1]->action = [this](String s) { setEntered(s); };
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
		{
			P<DialogueLine> dl = New<DialogueLine>(GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor(), GameStrings::getString(GameStrings::dialogues, S("outpost_elevator_fuse_done_first_2_Cody")), nullptr);
			Timeline::t->addDialogue(dl);
		}
		if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
		{
			P<DialogueLine> dl2 = New<DialogueLine>(GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor(), GameStrings::getString(GameStrings::dialogues, S("outpost_elevator_fuse_done_first_3_Barry")), nullptr);
			Timeline::t->addDialogue(dl2);
		}
	}
	GameDataController::gd->setObjective(S("visited_outpost3"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_metal_inside, 0.6f);
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
}

void LocationOutpost3Start::Update()
{
	if (PlayerController::wc->currentXY.x > 165.0f && PlayerController::wc->currentXY.y > 50.0f)
	{
		PlayerController::pc->allowDrop = false;
	}
	else
	{
		PlayerController::pc->allowDrop = true;
	}
}
