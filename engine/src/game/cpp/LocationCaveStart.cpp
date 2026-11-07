#include "../game_all.h"

void LocationCaveStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.05f;
	PlayerController::wc->shadow->fadeRateH = 0.008f;
	PlayerController::wc->shadowOffsetY = -4;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -30.0f;
	PlayerController::wc->shadow->startAlpha = 0.75f;
	PlayerController::wc->shadow->source = 80.0f;
	PlayerController::ssg->setStepType(StepSoundGenerator::ROAD);
	PlayerController::wc->shadow->scaleFactor = 0.3f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	if (!GameDataController::gd->getObjective(S("visited_cave")) || Random::Range(0.0f, 1.0f) > 0.8f)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("rv_cave_visit")));
	}
	GameDataController::gd->setObjective(S("visited_cave"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_5a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.4f);
	if (GameDataController::gd->getObjective(S("rv_cave_therm")))
	{
		thermb->set_enabled(true);
	}
	else
	{
		thermb->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("rv_cave_blanketb")))
	{
		blanketb->set_enabled(true);
	}
	else
	{
		blanketb->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("rv_cave_blanket")))
	{
		blanket->set_enabled(true);
	}
	else
	{
		blanket->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("rv_cave_flag")))
	{
		flag->set_enabled(true);
	}
	else
	{
		flag->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("rv_cave_therm")) || GameDataController::gd->getObjective(S("rv_cave_blanketb")) || GameDataController::gd->getObjective(S("rv_cave_blanket")) || GameDataController::gd->getObjective(S("rv_cave_flag")))
	{
		light1->set_enabled(false);
		light2->set_enabled(true);
	}
	else
	{
		light1->set_enabled(true);
		light2->set_enabled(false);
	}
	codyTalked = GameDataController::gd->getObjective(S("place_rv_cody"));
	codyLives = false;
	if (GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc3_joined")))
	{
		codyLives = true;
	}
}

void LocationCaveStart::Update()
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

void LocationCaveStart::grantAchievment(String s)
{
	GameDataController::Achievement(S("S_TREASURE"));
}
