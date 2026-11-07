#include "../game_all.h"

void LocationHouseBBackStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.03f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -5.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 140.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::DIRT);
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_house_b_back"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_4a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	GameObject::Find(S("Location"))->transform->Find(S("plane00a (2)"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	if (!GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("house_b_grave_filled")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<SpriteRenderer>()->set_flipX(false);
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("npc2_burial3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
		list[0]->action = [this](String val) { joinTeam(val); };
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
		{
			DialogueController::dc->initDialogue(list, S("cody_barry_first_meet"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor(), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
			list[list.Count() - 15]->action = [this](String v) { codyJump0(v); };
			list[list.Count() - 12]->action = [this](String v) { codyJump(v); };
			list[list.Count() - 10]->action = [this](String v) { codyJump2(v); };
			list[list.Count() - 7]->action = [this](String v) { codyJump4(v); };
			list[list.Count() - 1]->action = [this](String v) { codyJump3(v); };
		}
		else
		{
			list[list.Count() - 1]->action = [this](String v) { codyJump4(v); };
		}
		Timeline::t->addDialogueLines(list);
	}
	if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
	{
		snow->set_enabled(true);
		if (GameDataController::gd->gameTime < 600)
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else if (GameDataController::gd->gameTime < 650)
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 0.8f));
		}
		else if (GameDataController::gd->gameTime < 700)
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 0.6f));
		}
		else if (GameDataController::gd->gameTime < 750)
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 0.4f));
		}
		else if (GameDataController::gd->gameTime < 800)
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 0.2f));
		}
		else
		{
			snow->set_color(Color(1.0f, 1.0f, 1.0f, 0.1f));
		}
	}
	else
	{
		snow->set_enabled(false);
	}
}

void LocationHouseBBackStart::codyJump0(String v)
{
	GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_s"));
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_n"));
}

void LocationHouseBBackStart::codyJump(String v)
{
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("can_shake"));
}

void LocationHouseBBackStart::codyJump2(String v)
{
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_n"));
}

void LocationHouseBBackStart::codyJump4(String v)
{
	GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_se"), true);
}

void LocationHouseBBackStart::codyJump3(String v)
{
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_se"));
	PlayerController::wc->dir = WalkController::Direction::SE;
	PlayerController::wc->forceAnimation(S("stand_se"), false, false, false);
	PlayerController::wc->dir = WalkController::Direction::SE;
}

void LocationHouseBBackStart::joinTeam(String val)
{
	GameDataController::gd->setObjective(S("npc2_joined"), true);
	GameDataController::gd->setObjectiveDetail(S("chitchat"), -50);
	GameObject::Find(S("Npc2"))->GetComponent<Npc2Controller>()->updateState();
}

void LocationHouseBBackStart::Update()
{
}
