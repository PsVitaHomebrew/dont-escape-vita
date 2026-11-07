#include "../game_all.h"

void Location1Start::Start()
{
	memoryGo = false;
	normalMat = New<Material>(Shader::Find(S("Sprites/Default")));
	decideShadows();
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_5a);
	if (GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
	{
		shadowrenderer->set_sprite(lightShadow);
		shadowrenderer->set_material(lightMat);
		if (GameDataController::gd->getObjective(S("base_heater_cord_plugged")))
		{
			GameObject::Find(S("location1_heater"))->GetComponent<Location1HeaterOrFan>()->lightAlfa = 1.0f;
		}
		else
		{
			GameObject::Find(S("location1_heater"))->GetComponent<Location1HeaterOrFan>()->lightAlfa = 0.0f;
		}
	}
	else
	{
		shadowrenderer->set_sprite(darkShadow);
		shadowrenderer->set_material(normalMat);
	}
	if (!GameDataController::gd->getObjective(S("base_discovered")))
	{
		memoryGo = true;
	}
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("cody_base_welcome")))
	{
		GameDataController::gd->setObjective(S("cody_base_welcome"), true);
		Vector3 color = GingerActionController::getColor();
		Vector3 color2 = Npc3Controller::getColor();
		P<TextFieldController> component = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("cody_base_welcome"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color, component, color2);
	}
	if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("barry_base_welcome")))
	{
		GameDataController::gd->setObjective(S("barry_base_welcome"), true);
		Vector3 color3 = GingerActionController::getColor();
		Vector3 color4 = Npc2Controller::getColor();
		P<TextFieldController> component2 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("barry_base_welcome"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color3, component2, color4);
	}
	if (list.Count() > 0)
	{
		list[0]->action = [this](String a) { davidStand(a); };
		list[0]->actionWithText = true;
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void Location1Start::davidStand(String s)
{
	PlayerController::wc->forceAnimation(S("stand_se"));
}

void Location1Start::decideShadows()
{
	if (GameDataController::gd->getObjective(S("base_fireplace_lit")))
	{
		PlayerController::wc->shadow->fadeRateV = 0.005f;
		PlayerController::wc->shadow->fadeRateH = 0.005f;
		PlayerController::wc->shadowOffsetY = 0;
		PlayerController::wc->shadow->skewFactor = 60.0f;
		PlayerController::wc->shadow->skewFactor2 = 0.0f;
		PlayerController::wc->shadow->startAlpha = 0.5f;
		PlayerController::wc->shadow->source = 100.0f;
		PlayerController::ssg->setStepType(S("normal"));
		PlayerController::wc->shadow->scaleFactor = 0.75f;
		PlayerController::wc->shadow->downwards = true;
		PlayerController::pc->copySettingsToNPCs();
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_fire_1, 1.0f);
	}
	else if (GameDataController::gd->getObjective(S("barn_pump_started")) && GameDataController::gd->getObjectiveDetail(S("barn_pump_started")) == 1)
	{
		PlayerController::wc->shadow->fadeRateV = 0.005f;
		PlayerController::wc->shadow->fadeRateH = 0.0005f;
		PlayerController::wc->shadowOffsetY = -4;
		PlayerController::wc->shadow->skewFactor = 50.0f;
		PlayerController::wc->shadow->skewFactor2 = 0.0f;
		PlayerController::wc->shadow->startAlpha = 0.5f;
		PlayerController::wc->shadow->source = 120.0f;
		PlayerController::ssg->setStepType(S("normal"));
		PlayerController::wc->shadow->scaleFactor = 0.3f;
		PlayerController::wc->shadow->downwards = true;
		PlayerController::pc->copySettingsToNPCs();
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.25f);
	}
	else
	{
		PlayerController::wc->shadow->fadeRateV = 0.0f;
		PlayerController::wc->shadow->fadeRateH = 0.0035f;
		PlayerController::wc->shadowOffsetY = -4;
		PlayerController::wc->shadow->skewFactor = 0.0f;
		PlayerController::wc->shadow->skewFactor2 = -15.0f;
		PlayerController::wc->shadow->startAlpha = 0.75f;
		PlayerController::wc->shadow->source = 0.0f;
		PlayerController::ssg->setStepType(StepSoundGenerator::NORMAL);
		PlayerController::wc->shadow->scaleFactor = 0.4f;
		PlayerController::wc->shadow->downwards = true;
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.25f);
	}
}

void Location1Start::showMemoryOfCrossroad(String param)
{
	ExamineSprite::es->textField->shift.x = -110.0f;
	ExamineSprite::es->textField->shift.y = 10.0f;
	ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::actions, S("story_base3")) }), 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f);
	ExamineSprite::es->show(memoryOfCrossroad);
}

void Location1Start::initStory()
{
	GameDataController::gd->autoSave();
	PlayerController::wc->fullStop(true);
	P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("story_base1"));
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(PlayerController::pc->textField);
	timelineAction->text = GameStrings::getString(GameStrings::actions, S("story_base2"));
	timelineAction->function = [this](String a) { showMemoryOfCrossroad(a); };
	Timeline::t->addAction(timelineAction);
	GameDataController::gd->setObjective(S("visited_location1"), true);
	GameDataController::gd->setObjective(S("base_discovered"), true);
}

void Location1Start::Update()
{
	if (memoryGo && !PlayerController::wc->busy)
	{
		memoryGo = false;
		initStory();
	}
	fireLight->set_color(Color(1.0f, 1.0f, 1.0f, Random::Range(0.85f, 1.0f)));
	fireLight2->set_color(Color(1.0f, 1.0f, 1.0f, Random::Range(0.85f, 1.0f)));
}

void Location1Start::clockShow(String param)
{
	GameObject::Find(S("clock"))->GetComponent<ClockController>()->showClock(String::Empty);
}
