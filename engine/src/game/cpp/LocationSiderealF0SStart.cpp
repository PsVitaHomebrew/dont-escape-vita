#include "../game_all.h"

void LocationSiderealF0SStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 60.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.5f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 120.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::NORMAL, AudioReverbPreset::Cave);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->underground_1, 1.0f);
	Invoke(S("sypnij"), 1.0f);
	GameDataController::gd->setObjective(S("visited_sidereal_f0s"), true);
	npcTextField->gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(npcTextField->gameObject->transform->get_position()));
	if ((GameDataController::gd->getObjective(S("npc3_alive")) || GameDataController::gd->getObjectiveDetail(S("npc3_alive")) != 1) && (GameDataController::gd->getObjective(S("npc2_alive")) || GameDataController::gd->getObjectiveDetail(S("npc2_alive")) != 1))
	{
		GameDataController::gd->setObjective(S("sidereal_npc_found"), true);
	}
	if (GameDataController::gd->getObjective(S("dialogue_ginger_reunited")) && !GameDataController::gd->getObjective(S("dialogue_ginger_dead_mourned")))
	{
		GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->mourn();
	}
}

void LocationSiderealF0SStart::sypnij()
{
	pg->started = true;
	float num = Random::Range(0.2f, 3.0f);
	Invoke(S("dosc"), num);
	if (num < 0.75f)
	{
		audio->PlayOneShot(SoundsManagerController::sm->sand_pour1);
	}
	else if (num < 1.5f)
	{
		audio->PlayOneShot(SoundsManagerController::sm->sand_pour3);
	}
	else if (num < 2.25f)
	{
		audio->PlayOneShot(SoundsManagerController::sm->sand_pour4);
	}
	else
	{
		audio->PlayOneShot(SoundsManagerController::sm->sand_pour2);
	}
}

void LocationSiderealF0SStart::dosc()
{
	pg->started = false;
	Invoke(S("sypnij"), Random::Range(1.1f, 15.75f));
}

void LocationSiderealF0SStart::Update()
{
	if (PlayerController::wc->currentXY.y > 40.0f)
	{
		PlayerController::wc->shadow->downwards = false;
	}
	else
	{
		PlayerController::wc->shadow->downwards = true;
	}
	float num = (PlayerController::wc->currentXY.y - 40.0f) / 20.0f;
	if (num > 1.0f)
	{
		num = 1.0f;
	}
	if (num < -1.0f)
	{
		num = -1.0f;
	}
	num = 1.0f - Mathf::Abs(num);
	PlayerController::wc->shadow->fadeRateV = 0.075f * num;
	float num2 = Mathf::Sqrt(Mathf::Pow(120.0f - PlayerController::wc->currentXY.x, 2.0f) + Mathf::Pow(67.0f - PlayerController::wc->currentXY.y - 20.0f, 2.0f));
	num2 /= 120.0f;
	PlayerController::wc->shadow->scaleFactor = 0.65f * num2;
	PlayerController::wc->shadowOffsetY = (int)(2.0f - PlayerController::wc->shadow->scaleFactor);
	if (GameDataController::gd->getObjective(S("npc2_alive")))
	{
		shadowNPC(barry);
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")))
	{
		shadowNPC(cody);
	}
	if (GameDataController::gd->getObjective(S("dialogue_ginger_reunited")))
	{
		shadowNPC(ginger);
	}
	npcTextField->setAlpha(txtAlpha);
	if (GameDataController::gd->getObjective(S("sidereal_npc_found")))
	{
		return;
	}
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_npc_found")) == 0)
	{
		if (PlayerController::wc->currentXY.x < 145.0f)
		{
			PlayerController::wc->fullStop(true);
			PlayerController::wc->forceAnimation(S("stand_s"));
			List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
			PlayerController::pc->textField->shift.y = 18.0f;
			if (!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
			{
				DialogueController::dc->initDialogue(list, S("sidereal_cody_death1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), npcTextField, Npc3Controller::getColor());
			}
			else
			{
				DialogueController::dc->initDialogue(list, S("sidereal_barry_death1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), npcTextField, Npc2Controller::getColor(), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
			}
			for (int i = 0; i < list.Count(); i++)
			{
				Timeline::t->addDialogue(list[i]);
			}
			if (!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
			{
				Timeline::t->actions[1]->function = [this](String s) { walkNPC(s); };
			}
			Timeline::t->actions[list.Count() - 1]->function = [this](String s) { walkDown(s); };
			npcTextField->setAlpha(1.0f);
			txtAlpha = 1.0f;
			GameDataController::gd->setObjectiveDetail(S("sidereal_npc_found"), 1);
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("sidereal_npc_found")) == 2)
	{
		PlayerController::pc->setBusy(true);
		PlayerController::wc->forceAnimation(S("walk_se"), true);
		PlayerController::wc->setSimpleTargetV3(npc->transform->get_position());
		GameDataController::gd->setObjectiveDetail(S("sidereal_npc_found"), 3);
	}
	else
	{
		if (GameDataController::gd->getObjectiveDetail(S("sidereal_npc_found")) != 3 || PlayerController::wc->targetXY.y != PlayerController::wc->currentXY.y)
		{
			return;
		}
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 1.0f;
		GameDataController::gd->setObjectiveDetail(S("sidereal_npc_found"), 4);
		GameDataController::gd->setObjective(S("sidereal_npc_found"), true);
		PlayerController::wc->forceAnimation(S("kneel_se_in"));
		List<P<DialogueLine>> list2 = List<P<DialogueLine>>::New();
		PlayerController::pc->textField->shift.y = 4.0f;
		if (!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
		{
			DialogueController::dc->initDialogue(list2, S("sidereal_cody_death2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), npcTextField, Npc3Controller::getColor(), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
			for (int j = 0; j < list2.Count(); j++)
			{
				list2[j]->action = [this](String s) { txtColor(s); };
				list2[j]->actionParam = String::Empty + (float)(list2.Count() - j) / (float)list2.Count();
				Timeline::t->addDialogue(list2[j]);
			}
			Timeline::t->actions[4]->function = [this](String s) { walkNPC(s); };
			Timeline::t->actions[6]->function = [this](String s) { mourn(s); };
			Timeline::t->actions[11]->function = [this](String s) { music(s); };
			Timeline::t->actions[list2.Count() - 1]->function = [this](String s) { die(s); };
		}
		else
		{
			DialogueController::dc->initDialogue(list2, S("sidereal_barry_death2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), npcTextField, Npc2Controller::getColor(), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
			for (int k = 0; k < list2.Count(); k++)
			{
				list2[k]->action = [this](String s) { txtColor(s); };
				list2[k]->actionParam = String::Empty + (float)(list2.Count() - k) / (float)list2.Count();
				Timeline::t->addDialogue(list2[k]);
			}
			Timeline::t->actions[3]->function = [this](String s) { mourn(s); };
			Timeline::t->actions[21]->function = [this](String s) { music(s); };
			Timeline::t->actions[list2.Count() - 1]->function = [this](String s) { die(s); };
		}
	}
}

void LocationSiderealF0SStart::mourn(String s)
{
	MonoBehaviour::print(S("MOURN"));
	if (!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("barry_mourn_cody"));
	}
	else
	{
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("cody_mourn_barry"));
	}
}

void LocationSiderealF0SStart::music(String s)
{
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_sorrow, false);
}

void LocationSiderealF0SStart::txtColor(String s)
{
	txtAlpha = float_Parse(s);
	if (!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
	{
		txtAlpha *= 5.0f;
	}
}

void LocationSiderealF0SStart::walkDown(String s)
{
	GameDataController::gd->setObjectiveDetail(S("sidereal_npc_found"), 2);
	Timeline::t->doNotUnlock = true;
}

void LocationSiderealF0SStart::die(String s)
{
	Invoke(S("die2"), 4.0f);
	Timeline::t->doNotUnlock = true;
}

void LocationSiderealF0SStart::die2()
{
	PlayerController::pc->textField->shift.y = 18.0f;
	PlayerController::wc->forceDirection(WalkController::Direction::SW);
	PlayerController::wc->forceAnimation(S("kneel_se_out"));
}

void LocationSiderealF0SStart::walkNPC(String s)
{
	if (!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->setSimpleTargetV3(npcTarget->transform->get_position());
	}
	else
	{
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setSimpleTargetV3(npcTarget->transform->get_position());
	}
	Timeline::t->doNotUnlock = true;
}

void LocationSiderealF0SStart::shadowNPC(P<NPCWalkController> npcWC)
{
	if (npcWC->currentXY.y > 40.0f)
	{
		npcWC->shadow->downwards = false;
	}
	else
	{
		npcWC->shadow->downwards = true;
	}
	float num = (npcWC->currentXY.y - 40.0f) / 20.0f;
	if (num > 1.0f)
	{
		num = 1.0f;
	}
	if (num < -1.0f)
	{
		num = -1.0f;
	}
	num = 1.0f - Mathf::Abs(num);
	npcWC->shadow->fadeRateV = 0.075f * num;
	float num2 = Mathf::Sqrt(Mathf::Pow(120.0f - npcWC->currentXY.x, 2.0f) + Mathf::Pow(67.0f - npcWC->currentXY.y - 20.0f, 2.0f));
	num2 /= 120.0f;
	npcWC->shadow->scaleFactor = 0.65f * num2;
	npcWC->shadowOffsetY = (int)(2.0f - npcWC->shadow->scaleFactor);
}
