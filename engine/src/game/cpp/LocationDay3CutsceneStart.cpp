#include "../game_all.h"

void LocationDay3CutsceneStart::Start()
{
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_main, false);
	JukeboxAmbient::jb->changeAmbient(nullptr, 0.0f);
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->maxWidth = 180;
	DialogueController::dc->initDialogue(list, S("day3_intro_cutscene"), GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>(), Vector3(1.0f, 1.0f, 1.0f));
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	Timeline::t->actions[Timeline::t->actions.Count() - 2]->function = [this](String s) { fadeOut(s); };
	Timeline::t->actions[Timeline::t->actions.Count() - 1]->function = [this](String s) { transportToSidereal(s); };
	hazy->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
	clear->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
}

void LocationDay3CutsceneStart::fadeOut(String s)
{
	aalfa = 0.0f;
}

void LocationDay3CutsceneStart::transportToSidereal(String s)
{
	PlayerController::pc->spawnName = S("SiderealOutside1_Waypoint_Map");
	if (GameDataController::gd->getObjectiveDetail(S("car_location")) == 8)
	{
		PlayerController::pc->spawnName = S("car");
	}
	CurtainController::cc->fadeOut(S("SiderealOutside1"), WalkController::Direction::N, nullptr, nullptr, true, nullptr, 0.1f);
}

void LocationDay3CutsceneStart::Update()
{
	if (aalfa >= 0.0f && aalfa <= 1.0f)
	{
		aalfa += Time::get_deltaTime() * 0.25f;
		if (aalfa >= 1.0f)
		{
			aalfa = 1.0f;
		}
		clear->set_color(Color(1.0f, 1.0f, 1.0f, aalfa));
	}
}
