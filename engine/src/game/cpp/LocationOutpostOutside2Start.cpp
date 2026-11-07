#include "../game_all.h"

void LocationOutpostOutside2Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = -2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 2.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("dirt"));
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	GameDataController::gd->setObjective(S("visited_outpost2"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_1a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_3, 0.9f);
	if (GameDataController::gd->getObjective(S("outpost_doormat_triggered")))
	{
		doormat();
	}
}

void LocationOutpostOutside2Start::Update()
{
	playerShadow->transform->set_position(PlayerController::pc->transform->get_position());
	playerShadow->transform->set_position(Vector3(PlayerController::pc->transform->get_position().x + modX, PlayerController::pc->transform->get_position().y + modY, -0.2f));
	playerShadow->transform->set_position(ScreenControler::roundToNearestFullPixel2(playerShadow->transform->get_position()));
	playerShadow->set_sprite(PlayerController::wc->sr->get_sprite());
	playerShadow->set_flipX(PlayerController::wc->sr->get_flipX());
}

void LocationOutpostOutside2Start::doormat()
{
	if (gameObject == nullptr || GameDataController::gd->location != S("LocationOutpostOutside2") || CurtainController::cc->targetLocaiton != String::Empty)
	{
		return;
	}
	if (GameDataController::gd->getObjective(S("outpost_doormat_triggered")))
	{
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->buzz, 0.2f);
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 0)
		{
			PlayerController::wc->fullStop(true);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 6);
			PlayerController::wc->forceAnimation(S("stand_"), false, true);
			List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
			DialogueController::dc->initDialogue(list, S("outpost_doormat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), scannerTxt, Vector3(1.0f, 0.5f, 0.0f));
			if (!GameDataController::gd->getObjective(S("outpost_doormat_first_time")))
			{
				list.Add(New<DialogueLine>(GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameStrings::getString(GameStrings::dialogues, S("outpost_doormat_cate")), nullptr));
				GameDataController::gd->setObjective(S("outpost_doormat_first_time"), true);
			}
			list[list.Count() - 1]->action = [this](String t) { doormatGo(t); };
			list[list.Count() - 1]->actionWithText = false;
			for (int i = 0; i < list.Count(); i++)
			{
				Timeline::t->addDialogue(list[i]);
			}
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 1)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.25f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_10")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 2);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 2)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.25f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_9")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 3);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 3)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.25f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_8")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 4);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 4)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.25f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_7")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 5);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 5)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.25f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_6")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 6);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 6)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.25f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_5")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 7);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 7)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.3f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_4")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 8);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 8)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.35f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_3")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 9);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
			{
				Vector3 color = Npc2Controller::getColor();
				P<TextFieldController> component = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
				component->viewText(GameStrings::getString(GameStrings::dialogues, S("outpost_doormat_barry")), false, false, false, 100, color.x, color.y, color.z);
				component->setTime(2.0f);
			}
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 9)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.4f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_2")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 10);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 10)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.45f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_1")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 11);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			return;
		}
		if (GameDataController::gd->getObjectiveDetail(S("outpost_doormat_triggered")) == 11)
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2, 0.5f);
			scannerTxt->viewText(GameStrings::getString(GameStrings::actions, S("outpost_doormat_0")), false, false, false, 100, 1.0f, 0.5f, 0.0f);
			GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 12);
			Invoke(S("doormat"), 1.0f);
			scannerTxt->setTime(2.0f);
			return;
		}
		PlayerController::pc->interruptDialogueProbablyToKillPlayer();
		PlayerController::wc->fullStop(true);
		PlayerController::pc->setBusy(true);
		PlayerController::wc->forceAnimation(S("electrocute"), PlayerController::wc->sr->get_flipX());
		electro->transform->set_position(PlayerController::pc->gameObject->transform->get_position());
		electro->transform->set_position(Vector3(electro->transform->get_position().x, electro->transform->get_position().y, -3.0f));
		electro->GetComponent<SpriteRenderer>()->set_flipX(PlayerController::wc->sr->get_flipX());
		electro->GetComponent<Animator>()->Play(S("electrocute"));
		GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("surprised_se"));
		if (GameDataController::gd->getObjective(S("npc2_alive")))
		{
			GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("surprised_se"));
		}
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("surprised2"));
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
		{
			Vector3 color2 = Npc3Controller::getColor();
			P<TextFieldController> component2 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
			component2->viewText(GameStrings::getString(GameStrings::dialogues, S("outpost_doormat_cody")), false, true, false, 100, color2.x, color2.y, color2.z);
		}
		smoke->started = true;
		sparks->started = true;
		Invoke(S("disableSparks"), 4.0f);
		Invoke(S("resetStage"), 5.0f);
	}
	else
	{
		JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_3, 0.9f);
	}
}

void LocationOutpostOutside2Start::disableSparks()
{
	for (int i = 0; i < sparks->particles.Count(); i++)
	{
		sparks->particles[i]->GetComponent<ParticleController>()->currentXY.x = 1000.0f;
	}
	sparks->started = false;
}

void LocationOutpostOutside2Start::resetStage()
{
	GameDataController::gd->setObjectiveDetail(S("outpost_doormat_triggered"), 0);
	GameDataController::gd->setObjective(S("outpost_doormat_triggered"), false);
	smoke->started = false;
	PlayerController::pc->spawnName = S("Dieded");
	CurtainController::cc->fadeOut(S("LocationOutpostOutside2"), WalkController::Direction::E);
}

void LocationOutpostOutside2Start::doormatGo(String t)
{
	Invoke(S("doormat"), 0.25f);
}

void LocationOutpostOutside2Start::letItGo()
{
	CancelInvoke();
	doormat();
	scannerTxt->setTime(1.0f);
}
