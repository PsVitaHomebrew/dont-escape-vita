#include "../game_all.h"

void LetterFall::Start()
{
}

void LetterFall::startTalkAfterfall()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_ne"));
	DialogueController::dc->initDialogue(list, S("sidereal_afterfall"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	if (!GameDataController::gd->getObjective(S("ncp2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
	{
		list[1]->text = GameStrings::getString(GameStrings::dialogues, S("sidereal_afterfallb_2_a"));
		list[2]->text = GameStrings::getString(GameStrings::dialogues, S("sidereal_afterfallb_3_a"));
		list[9]->text = GameStrings::getString(GameStrings::dialogues, S("sidereal_afterfallb_10_a"));
	}
	list[1]->action = [this](String a) { kneel(a); };
	list[list.Count() - 1]->action = [this](String a) { kneelEnd(a); };
	Timeline::t->doNotUnlock = true;
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	Timeline::t->doNotUnlock = true;
}

void LetterFall::kneel(String a)
{
	if (!GameDataController::gd->getObjective(S("ncp2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
	{
		PlayerController::wc->forceAnimation(S("kneel_e_in"), true);
	}
	else
	{
		PlayerController::wc->forceAnimation(S("kneel_se_in"), true);
	}
}

void LetterFall::kneelEnd(String a)
{
	MonoBehaviour::print(S("WSTAJEMY"));
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->setBusy(true);
	if (!GameDataController::gd->getObjective(S("ncp2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
	{
		PlayerController::wc->forceAnimation(S("kneel_e_out"), true);
	}
	else
	{
		PlayerController::wc->forceAnimation(S("kneel_se_out"), true);
	}
}

void LetterFall::Update()
{
	if (GameDataController::gd->getObjective(S("sidereal_roof_collapsed")) && GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
	{
		GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->randomLinesTalkOrNot(true);
	}
}

void LetterFall::quickFall()
{
	showBelka();
	showBelka2();
	gameObject->GetComponent<Animator>()->Play(S("letter_fallen"));
}

void LetterFall::hideAndWait()
{
	gameObject->GetComponent<Animator>()->Play(S("letter_wait_fall"));
}

void LetterFall::showBelka()
{
	barLow->set_enabled(true);
}

void LetterFall::showBelka2()
{
	barLow->transform->set_position(Vector3(barLow->transform->get_position().x, barLow->transform->get_position().y, -1.9f));
}

void LetterFall::startAnim(String a)
{
	GameDataController::gd->setObjectiveDetail(S("letter_fallen"), 2);
	gameObject->GetComponent<Animator>()->Play(S("letter_fall"));
	barLow->set_enabled(false);
	barLow->transform->set_position(Vector3(barLow->transform->get_position().x, barLow->transform->get_position().y, -0.8f));
	aS->set_pitch(1.0f);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_moan2, 0.5f);
	if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		barryW->forceAnimation(S("surprised_n"));
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")))
	{
		codyW->forceAnimation(S("surprised_n"));
	}
	gingerW->forceAnimation(S("surprised_ne"));
	PlayerController::wc->fullStop(true);
	PlayerController::pc->setBusy(true);
	playerJumpSource->transform->set_position(PlayerController::pc->gameObject->transform->get_position());
	PlayerController::wc->forceAnimation(S("surprised_ne"), true);
}

void LetterFall::gingerWindUp()
{
	gingerW->speed = 4.0f;
	gingerW->forceAnimation(S("jump_back"));
}

void LetterFall::gingerJump()
{
	gingerW->setSimpleTargetV3(gingerJumpTarget->transform->get_position());
}

void LetterFall::playerJump()
{
	PlayerController::pc->setBusy(true);
	PlayerController::wc->setSimpleTarget(Vector2(157.0f - 30.0f * (PlayerController::wc->currentXY.y / 75.0f), PlayerController::wc->currentXY.y));
	PlayerController::wc->forceAnimation(S("jump_side"));
	PlayerController::wc->forceDirection(WalkController_Direction::SW);
}

void LetterFall::swingLoop()
{
	aS->set_pitch(Random::Range(0.9f, 1.1f));
	aS->PlayOneShot(SoundsManagerController::sm->metal_moan);
}

void LetterFall::prepare()
{
	GameDataController::gd->setObjective(S("sidereal_roof_collapsed"), true);
	gameObject->GetComponent<Animator>()->Play(S("letter_swing"));
	PlayerController::wc->fullStop();
	PlayerController::wc->forceAnimation(S("surprised_ne"), true);
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("surprised_ne"));
	if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("surprised_n"));
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")))
	{
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->forceAnimation(S("surprised_n"));
	}
	GameObject::Find(S("Npc2"))->GetComponent<Npc2Controller>()->actionType = ObjectActionController_Type::NormalAction;
	GameObject::Find(S("Npc3"))->GetComponent<Npc3Controller>()->actionType = ObjectActionController_Type::NormalAction;
	GameObject::Find(S("LocationSiderealRoof_Waypoint_Climb"))->GetComponent<LocationSiderealRoof_Waypoint_Climb>()->updateState();
	int num = 0;
	if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
	{
		num++;
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
	{
		num++;
	}
	if (num > 0)
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_action_loop, true, 0.0f, 0.0f);
	}
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("sidereal_watchout"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	Timeline::t->actions[0]->actionWithText = false;
	Timeline::t->actions[0]->function = [this](String a) { startAnim(a); };
	Timeline::t->doNotUnlock = true;
}

void LetterFall::codyRun()
{
	if (GameDataController::gd->getObjective(S("npc3_joined")))
	{
		codyW->speed = 4.0f;
		codyW->setSimpleTargetV3(codyRunTarget->transform->get_position());
		codyW->forceAnimation(S("run"));
	}
}

void LetterFall::codyJump()
{
	if (GameDataController::gd->getObjective(S("npc3_joined")))
	{
		codyW->speed = 4.0f;
		codyW->setSimpleTargetV3(codyJumpTarget->transform->get_position());
	}
}

void LetterFall::piachSyp()
{
}

void LetterFall::barryWindUp()
{
	if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		barryW->speed = 4.0f;
		barryW->forceAnimation(S("jump2"));
	}
}

void LetterFall::barryJump()
{
	if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		barryW->setSimpleTargetV3(barryJumpTarget->transform->get_position());
	}
}

void LetterFall::startLaunch()
{
	sandLauch->started = true;
}

void LetterFall::endLaunch()
{
	sandLauch->started = false;
}

void LetterFall::startSandMove()
{
	sandMove1->started = true;
	sandMove2->started = true;
	sandMove3->started = true;
	sandMove4->started = true;
}

void LetterFall::stopSandMove()
{
	sandMove1->started = false;
	sandMove2->started = false;
	sandMove3->started = false;
	sandMove4->started = false;
	GameDataController::gd->setObjectiveDetail(S("sidereal_roof_collapsed"), 4);
}

void LetterFall::startSandFall()
{
	sandFall1->started = true;
	sandFall2->started = true;
	sandFall3->started = true;
	sandFall4->started = true;
	aS->set_pitch(1.0f);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->break_glass_big);
	GameObject::Find(S("Location"))->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->sand_big);
}

void LetterFall::stopSandFall()
{
	sandFall1->started = false;
	sandFall2->started = false;
	sandFall3->started = false;
	sandFall4->started = false;
}

void LetterFall::endAnim()
{
	GameObject::Find(S("LocationManager"))->GetComponent<LocationSiderealRoofStart>()->setWalkablePath();
	if (GameDataController::gd->getObjective(S("npc2_joined")) || GameDataController::gd->getObjective(S("npc3_joined")))
	{
		PlayerController::pc->setBusy(false);
		GameDataController::gd->setObjective(S("sidereal_roof_wait_for_rescue"), true);
	}
	else
	{
		GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->roofAfterFall();
	}
}
