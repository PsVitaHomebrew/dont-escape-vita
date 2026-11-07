#include "../game_all.h"

void LocationRV1Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 5.0f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("dirt"));
	PlayerController::wc->shadow->scaleFactor = 0.5f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	if (!GameDataController::gd->getObjective(S("visited_rv")))
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("rv_encounter"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		for (int i = 0; i < 5; i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			Timeline::t->addDialogue(list[5]);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			Timeline::t->addDialogue(list[6]);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			Timeline::t->addDialogue(list[7]);
		}
	}
	if (!GameDataController::gd->getObjective(S("rv_started")))
	{
		GameObject::Find(S("Smoke"))->GetComponent<ParticleGenerator>()->started = false;
	}
	else
	{
		GameObject::Find(S("Smoke"))->GetComponent<ParticleGenerator>()->started = true;
	}
	GameDataController::gd->setObjective(S("visited_rv"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_3a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.4f);
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			sr->set_sprite(snow);
			if (GameDataController::gd->gameTime < 600)
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (GameDataController::gd->gameTime < 650)
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.8f));
			}
			else if (GameDataController::gd->gameTime < 700)
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.6f));
			}
			else if (GameDataController::gd->gameTime < 750)
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.4f));
			}
			else if (GameDataController::gd->gameTime < 800)
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.2f));
			}
			else
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.1f));
			}
		}
		else
		{
			sr->set_sprite(scorch);
		}
	}
	else
	{
		sr->set_sprite(normal);
	}
	codyTalked = GameDataController::gd->getObjective(S("place_rv_cody"));
	codyLives = false;
	if (GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc3_joined")))
	{
		codyLives = true;
	}
	Invoke(S("checkCodyTalk"), 2.0f);
}

void LocationRV1Start::checkCodyTalk()
{
	codyTalked = GameDataController::gd->getObjective(S("place_rv_cody"));
	if (!codyTalked)
	{
		Invoke(S("checkCodyTalk"), 2.0f);
	}
}

void LocationRV1Start::Update()
{
	if (codyTalked && codyLives && CursorController::cc->selectedItemName == S("shovel"))
	{
		CursorController::cc->deselectItem();
		InventoryButtonController::ibc->close();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("dig_treasure"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		list[list.Count() - 1]->action = [this](String s) { grantAchievment(s); };
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
}

void LocationRV1Start::grantAchievment(String s)
{
	GameDataController::Achievement(S("S_TREASURE"));
}
