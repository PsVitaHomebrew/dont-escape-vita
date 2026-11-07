#include "../game_all.h"

Vector3 Npc2Controller::getColor()
{
	return color;
}

void Npc2Controller::continueStart()
{
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("locket"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("food_bag"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("deadbird"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("whiskey"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("lighter"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rope"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ropehook"), String::Empty, nullptr, String::Empty));
	if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		interactions.Add(New<ItemInteraction>(S("revolver_6"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_5"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_4"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_3"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_2"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_1"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_0"), GameStrings::getString(GameStrings::actions, S("revolver_npc_ammo")), nullptr, String::Empty));
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		interactions.Add(New<ItemInteraction>(S("revolver_6"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_5"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_4"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_3"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_2"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_1"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_0"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
	}
	interactions.Add(New<ItemInteraction>(S("pills"), String::Empty, nullptr, String::Empty));
	if (!GameDataController::gd->getObjective(S("npc2_joined")))
	{
		interactions.Add(New<ItemInteraction>(S("rifle_0"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_1"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_2"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_3"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_4"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_5"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_6"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("barry_threaten")), nullptr, String::Empty));
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		interactions.Add(New<ItemInteraction>(S("rifle_0"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_1"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_2"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_3"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_4"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_5"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_6"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_0"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_1"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_2"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_3"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_4"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_5"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_6"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_0"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_1"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_2"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_3"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_4"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_5"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_6"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_0"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_1"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_2"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_3"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_4"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_5"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_6"), GameStrings::getString(GameStrings::actions, S("barry_give_rifle")), nullptr, String::Empty));
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		interactions.Add(New<ItemInteraction>(S("rifle_0"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_1"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_2"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_3"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_4"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_5"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_6"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_0"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_1"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_2"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_3"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_4"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_5"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_6"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_0"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_1"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_2"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_3"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_4"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_5"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_6"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_0"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_1"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_2"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_3"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_4"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_5"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_6"), GameStrings::getString(GameStrings::actions, S("gun_barry_storm")), nullptr, String::Empty));
	}
	actionType = Type::Talk;
}

void Npc2Controller::whatOnClick()
{
}

void Npc2Controller::whatOnClick0()
{
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		range = 250.0f;
		rotateToSpeaker = true;
	}
	else if (GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker_pull"))->gameObject;
		range = 1.0f;
		rotateToSpeaker = false;
	}
	else if (GameDataController::gd->getObjective(S("sidereal_roof_npc_shocked")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker_sit"))->gameObject;
		range = 0.0f;
		rotateToSpeaker = false;
	}
	else if (GameDataController::gd->getObjective(S("moon_shocked2")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker_sit"))->gameObject;
		range = 0.0f;
		rotateToSpeaker = false;
	}
	else if (GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
	{
		actionMarker = GameObject::Find(S("Action_Marker"));
		range = 100.0f;
		rotateToSpeaker = false;
	}
	else if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		range = 25.0f;
		rotateToSpeaker = true;
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		range = 1.0f;
		rotateToSpeaker = false;
	}
}

void Npc2Controller::giveNote(String val)
{
	if (GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
	{
		GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>()->dissmiss();
		GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>()->dissmiss();
		GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->setDistractFalse(String::Empty);
	}
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("BarryShootPoint"))->transform->get_position());
	PlayerController::wc->setSimpleTargetV3(GameObject::Find(S("BarryLocketPoint"))->get_gameObject()->transform->get_position());
	PlayerController::wc->autoAction = [this]() { giveLocket(); };
	PlayerController::wc->forceAnimation(S("walk_e"));
}

void Npc2Controller::siderealFall()
{
	GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::dialogues, S("fall_aah")), false, false, false, 100, getColor().x, getColor().y, getColor().z, 0.0f, 0.0f, 0.0f, 0.75f, false, true);
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("barry_fall"));
	gameObject->GetComponent<NPCWalkController>()->speed = 5.0f;
	gameObject->GetComponent<NPCWalkController>()->setSimpleTarget(Vector2(gameObject->GetComponent<NPCWalkController>()->currentXY.x, -100.0f));
	JukeboxMusic::jb->changeMusic(nullptr, true, 0.0f, 0.0f, 0.01f);
}

void Npc2Controller::fallAccelerate()
{
	if (gameObject->GetComponent<NPCWalkController>()->speed < 10.0f)
	{
		gameObject->GetComponent<NPCWalkController>()->speed += 0.5f;
	}
	if (gameObject->GetComponent<NPCWalkController>()->currentXY.y <= -90.0f)
	{
		gameObject->GetComponent<NPCWalkController>()->speed = 0.0f;
		gameObject->GetComponent<NPCWalkController>()->spawned = false;
		gameObject->GetComponent<NPCWalkController>()->currentXY.x = 0.0f;
		gameObject->GetComponent<NPCWalkController>()->currentXY.y = 0.0f;
		gameObject->GetComponent<NPCWalkController>()->clearTarget();
		gameObject->GetComponent<NPCWalkController>()->fullStop();
		gameObject->GetComponent<TextFieldController>()->dissmiss();
		gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("stand_n"));
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void Npc2Controller::giveLocket()
{
	PlayerController::wc->forceAnimation(S("action1_e_animation"));
}

void Npc2Controller::standUp(String val)
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("get_up"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_action_loop, true, 0.0f, 0.0f);
}

void Npc2Controller::fall(String val)
{
	gameObject->GetComponent<NPCWalkController>()->setBusy(false);
	gameObject->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("BarryAttackPoint"))->transform->get_position());
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("BarryShootPoint2"))->transform->get_position());
	PlayerController::wc->forceAnimation(S("sit_fall"));
	struggled = false;
	Invoke(S("sit_strugle1"), 1.0f);
}

void Npc2Controller::sit_strugle1()
{
	sit_strugle(String::Empty);
}

void Npc2Controller::sit_strugle(String val)
{
	if (!struggled)
	{
		struggled = true;
		gameObject->GetComponent<NPCWalkController>()->setBusy(true);
		PlayerController::wc->forceAnimation(S("sit_strugle"));
		gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("stand_e"), true);
		GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->drawGun(String::Empty);
	}
}

void Npc2Controller::drawGun(String val)
{
}

void Npc2Controller::aimGun(String val)
{
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->aimDown(S("right"));
}

void Npc2Controller::read(String val)
{
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_emotional, false, 15.0f, 80.0f, 0.01f);
	gameObject->GetComponent<NPCWalkController>()->setBusy(false);
	gameObject->GetComponent<NPCWalkController>()->setSimpleTargetV3(GameObject::Find(S("WaypointHouseBDistract"))->transform->Find(S("BarrySpawner"))->transform->get_position());
}

void Npc2Controller::read2(String val)
{
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->holdGunUp(S("right"));
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("npc2_read"));
}

void Npc2Controller::read3(String val)
{
	PlayerController::wc->forceAnimation(S("stand_up"));
}

void Npc2Controller::returnToSpawn(String val)
{
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->holster(S("right"));
}

void Npc2Controller::sitDown(String val)
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("sit_down"), true);
}

void Npc2Controller::goToSleep1(String a)
{
	gameObject->GetComponent<NPCWalkController>()->setSimpleTargetV3(GameObject::Find(S("BarryWalkHere"))->transform->get_position());
}

void Npc2Controller::goToSleep2(String a)
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("barry_pod");
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	CurtainController::cc->fadeOut(S("LocationMoonbase3"), WalkController::Direction::NW, S("stand_ne"), nullptr, false, [this]() { goToSleep3(); });
}

void Npc2Controller::goToSleep3()
{
	P<TextFieldController> component = GameObject::Find(S("Moonbase3Pad4"))->transform->Find(S("TextField"))->GetComponent<TextFieldController>();
	if (GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("moon_cate_sleeps")))
	{
		component->transform->set_position(ScreenControler::roundToNearestFullPixel3(component->transform->get_position()));
		instantLines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(instantLines, S("barry_sleep_cate"), component, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		for (int i = 0; i < instantLines.Count(); i++)
		{
			Timeline::t->addDialogue(instantLines[i]);
		}
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("moon_cody_sleeps")))
	{
		instantLines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(instantLines, S("barry_sleep_cody"), component, color, GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
		for (int j = 0; j < instantLines.Count(); j++)
		{
			Timeline::t->addDialogue(instantLines[j]);
		}
	}
	instantLines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(instantLines, S("barry_sleep_2david"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	instantLines[instantLines.Count() - 1]->action = [this](String s) { closePod(s); };
	for (int k = 0; k < instantLines.Count(); k++)
	{
		Timeline::t->addDialogue(instantLines[k]);
	}
}

void Npc2Controller::closePod(String s)
{
	GameObject::Find(S("Moonbase3Pad4"))->GetComponent<Animator>()->Play(S("moon_pod4_close"));
	GameDataController::gd->setObjectiveDetail(S("moon_barry_sleeps"), 1);
	if (GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("moon_cate_sleeps")))
	{
		GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->pod_rotate();
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("moon_cody_sleeps")))
	{
		GameObject::Find(S("Npc3"))->GetComponent<Npc3Controller>()->pod_rotate();
	}
}

void Npc2Controller::pod_rotate()
{
	Invoke(S("pod_rotate2"), Random::Range(0.5f, 2.0f));
}

void Npc2Controller::pod_rotate2()
{
	GetComponent<NPCWalkController>()->playIdleAnimation(S("stand_se"));
	GetComponent<NPCWalkController>()->setBusy(false);
}

void Npc2Controller::playerStandUp(String v)
{
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->forceAnimation(S("kneel_out_n"));
}

void Npc2Controller::npcClickAction(String item)
{
	Vector3 vector = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	Vector3 vector2 = Npc3Controller::getColor();
	P<TextFieldController> component2 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
	instantLines = List<P<DialogueLine>>::New();
	if (GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
	{
		if (GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) != 1 && !GameDataController::gd->getObjective(S("cody_warned")))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("save_barry")), QuestionController::PopupType::QUESTION, [this]() { uratuj(); });
		}
		else
		{
			uratuj();
		}
		return;
	}
	if (GameDataController::gd->getObjective(S("sidereal_roof_npc_shocked")))
	{
		PlayerController::pc->forceAnimation(S("kneel_in_n"));
		if (GameDataController::gd->getObjective(S("npc3_alive")) || GameDataController::gd->getObjectiveDetail(S("npc3_alive")) != 1)
		{
			DialogueController::dc->initDialogue(instantLines, S("sidereal_nofall_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			instantLines[instantLines.Count() - 1]->action = [this](String val) { endTalkRoof(val); };
			GameDataController::gd->setObjective(S("sidereal_roof_npc_shocked"), false);
			instantLines[instantLines.Count() - 2]->action = [this](String v) { playerStandUp(v); };
			for (int i = 0; i < instantLines.Count(); i++)
			{
				Timeline::t->addDialogue(instantLines[i]);
			}
			return;
		}
		DialogueController::dc->initDialogue(instantLines, S("sidereal_afterfall_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		instantLines[instantLines.Count() - 1]->action = [this](String v) { playerStandUp(v); };
	}
	else
	{
		if (GameDataController::gd->getObjective(S("moon_shocked2")))
		{
			PlayerController::pc->forceAnimation(S("kneel_in_n"));
			DialogueController::dc->initDialogue(instantLines, S("moon_shocked_barry1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			GameDataController::gd->setObjective(S("moon_shocked2"), false);
			if (GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("moon_shocked1")) && (!GameDataController::gd->getObjective(S("npc2_alive")) || !GameDataController::gd->getObjective(S("moon_shocked2"))) && (!GameDataController::gd->getObjective(S("npc3_alive")) || !GameDataController::gd->getObjective(S("moon_shocked3"))) && GameDataController::gd->getObjective(S("npc1_alive")))
			{
				instantLines.Add(New<DialogueLine>(component, vector, GameStrings::getString(GameStrings::dialogues, S("moon_shocked_cate_ending")), nullptr));
			}
			instantLines[instantLines.Count() - 1]->action = [this](String val) { endTalkShip(val); };
			instantLines[instantLines.Count() - 2]->action = [this](String v) { playerStandUp(v); };
			for (int j = 0; j < instantLines.Count(); j++)
			{
				Timeline::t->addDialogue(instantLines[j]);
			}
			if (!GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("moon_shocked1")))
			{
				instantLines = List<P<DialogueLine>>::New();
				DialogueController::dc->initDialogue(instantLines, S("moon_shocked_barry2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
				for (int k = 0; k < instantLines.Count(); k++)
				{
					Timeline::t->addDialogue(instantLines[k]);
				}
			}
			return;
		}
		if (item == S("locket"))
		{
			if (!GameDataController::gd->getObjective(S("house_b_wife_note_read")))
			{
				PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("house_b_locket_unread")), true, false, false, 180);
				return;
			}
			DialogueController::dc->initDialogue(instantLines, S("npc2_locket"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			GameDataController::gd->setObjective(S("npc2_wife_note_given"), true);
			InventoryController::ic->removeItem(S("locket"));
			instantLines[0]->action = [this](String val) { giveNote(val); };
			instantLines[0]->actionWithText = true;
			instantLines[3]->action = [this](String val) { standUp(val); };
			instantLines[3]->actionWithText = true;
			instantLines[4]->action = [this](String val) { fall(val); };
			instantLines[4]->actionWithText = true;
			instantLines[5]->action = [this](String val) { sit_strugle(val); };
			instantLines[5]->actionWithText = true;
			instantLines[8]->action = [this](String val) { drawGun(val); };
			instantLines[8]->actionWithText = true;
			instantLines[10]->action = [this](String val) { aimGun(val); };
			instantLines[10]->actionWithText = true;
			instantLines[16]->action = [this](String val) { read(val); };
			instantLines[16]->actionWithText = true;
			instantLines[17]->action = [this](String val) { read2(val); };
			instantLines[17]->actionWithText = true;
			instantLines[18]->action = [this](String val) { read3(val); };
			instantLines[18]->actionWithText = true;
			instantLines[20]->action = [this](String val) { returnToSpawn(val); };
			instantLines[20]->actionWithText = true;
			instantLines[22]->action = [this](String val) { sitDown(val); };
			instantLines[22]->actionWithText = true;
			if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
			{
				P<DialogueLine> item2 = New<DialogueLine>(component2, vector2, GameStrings::getString(GameStrings::dialogues, S("npc2_locket_CODY_c")), nullptr);
				instantLines.Insert(13, item2);
				component2->gameObject->GetComponent<NPCWalkController>()->forceDirection(NPCWalkController::Direction::SE);
			}
		}
		else
		{
			if (!GameDataController::gd->getObjective(S("dialogue_npc2_intro")))
			{
				DialogueController::dc->initDialogue(instantLines, S("npc2_intro1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
				instantLines[0]->actionWithText = true;
				GameDataController::gd->setObjective(S("dialogue_npc2_intro"), true);
				if (GameDataController::gd->getObjective(S("npc3_joined")))
				{
					instantLines.Insert(6, New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::dialogues, S("npc2_intro1_6_extra_a")), nullptr));
				}
				if (GameDataController::gd->getObjective(S("previous_disc_barry")) || GameDataController::gd->getObjective(S("previous_disc_cody")))
				{
					DialogueController::dc->initDialogue(instantLines, S("npc2_intro3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
				}
			}
			else
			{
				if (GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
				{
					PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("ginger_barry_distracted")), true, false, false, 150);
					return;
				}
				if (GameDataController::gd->getObjective(S("npc2_joined")))
				{
					if (item == S("coat1") || item == S("coat2") || item == S("coat3") || item == S("coat4"))
					{
						if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
						{
							DialogueController::dc->initDialogue(instantLines, S("npc2_bad_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
						}
						else if (GameDataController::gd->getCurrentDay() != 2)
						{
							DialogueController::dc->initDialogue(instantLines, S("npc2_bad2_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
						}
						else if (ItemsManager::im->getItem(S("coat1"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("coat2"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("coat3"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("coat4"))->dataRef->droppedLocation == S("npc2"))
						{
							DialogueController::dc->initDialogue(instantLines, S("npc2_already_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
						}
						else if (GameDataController::gd->getObjective(S("npc3_joined")) && ItemsManager::im->getItem(S("coat1"))->dataRef->droppedLocation != S("npc3") && ItemsManager::im->getItem(S("coat2"))->dataRef->droppedLocation != S("npc3") && ItemsManager::im->getItem(S("coat3"))->dataRef->droppedLocation != S("npc3") && ItemsManager::im->getItem(S("coat4"))->dataRef->droppedLocation != S("npc3"))
						{
							DialogueController::dc->initDialogue(instantLines, S("npc2_cody_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component2, vector2);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
						}
						else if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
						{
							DialogueController::dc->initDialogue(instantLines, S("npc2_give_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
							InventoryController::ic->removeItem(item);
							ItemsManager::im->getItem(item)->dataRef->droppedLocation = S("npc2");
							JournalTexts::pickTexts(GameDataController::gd->getCurrentDay());
						}
					}
					else if (item == S("water1") || item == S("water2") || item == S("water3") || item == S("water4"))
					{
						if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
						{
							DialogueController::dc->initDialogue(instantLines, S("npc2_bad_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
						}
						else if (GameDataController::gd->getCurrentDay() != 2)
						{
							DialogueController::dc->initDialogue(instantLines, S("npc2_bad2_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
						}
						else if (ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation == S("npc2") || ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation == S("npc2"))
						{
							DialogueController::dc->initDialogue(instantLines, S("npc2_already_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
						}
						else if (GameDataController::gd->getObjective(S("npc3_joined")) && ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation != S("npc3") && ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation != S("npc3") && ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation != S("npc3") && ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation != S("npc3"))
						{
							DialogueController::dc->initDialogue(instantLines, S("npc2_cody_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component2, vector2);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
						}
						else if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
						{
							DialogueController::dc->initDialogue(instantLines, S("npc2_give_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
							InventoryController::ic->removeItem(item);
							ItemsManager::im->getItem(item)->dataRef->droppedLocation = S("npc2");
							JournalTexts::pickTexts(GameDataController::gd->getCurrentDay());
						}
					}
					else
					{
						if (usedItem == S("pills"))
						{
							String prefix = S("barry_give_pills");
							if (GameDataController::gd->getObjective(S("barry_pills_taken")))
							{
								prefix = S("barry_gave_pills");
							}
							GameDataController::gd->setObjective(S("barry_pills_taken"), true);
							DialogueController::dc->initDialogue(instantLines, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
							instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
						}
						else if (usedItem.IndexOf(S("revolver")) != -1)
						{
							if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
							{
								DialogueController::dc->initDialogue(instantLines, S("npc2_give_gun"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
								instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
								InventoryController::ic->removeItem(item);
								ItemsManager::im->getItem(item)->dataRef->droppedLocation = S("npc2");
							}
						}
						else
						{
							if (item == S("food_bag"))
							{
								if (GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc3_joined")))
								{
									DialogueController::dc->initDialogue(instantLines, S("barry_bag_of_food1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor(), textField, color);
								}
								else
								{
									DialogueController::dc->initDialogue(instantLines, S("barry_bag_of_food2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor(), textField, color);
								}
								instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
							}
							else if (item == S("deadbird"))
							{
								DialogueController::dc->initDialogue(instantLines, S("dead_bird_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
								instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
							}
							else if (item == S("whiskey"))
							{
								DialogueController::dc->initDialogue(instantLines, S("whiskey_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
								instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
							}
							else if (item == S("lighter"))
							{
								DialogueController::dc->initDialogue(instantLines, S("lighter_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
								instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
							}
							else if (item == S("rope") || item == S("ropehook"))
							{
								DialogueController::dc->initDialogue(instantLines, S("rope_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
								instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
							}
							else
							{
								DialogueController::dc->initDialogue(instantLines, S("npc2_intro2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
							}
						}
					}
				}
				else
				{
					DialogueController::dc->initDialogue(instantLines, S("npc2_intro2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
				}
			}
			if (!GameDataController::gd->getObjective(S("npc2_joined")))
			{
				instantLines[0]->action = [this](String val) { lookUp(val); };
			}
		}
	}
	for (int l = 0; l < instantLines.Count(); l++)
	{
		Timeline::t->addDialogue(instantLines[l]);
	}
	DialogueController::dc->callback = [this]() { dialogues(); };
	dialogues();
}

void Npc2Controller::dialogues()
{
	DialogueController::dc->reset();
	Vector3 vector = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	int num = 0;
	if (!GameDataController::gd->getObjective(S("npc2_joined")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc2_come_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_npc2_come"));
		DialogueController::dc->initDialogue(doc->lines, S("npc2_come"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		num++;
	}
	if (GameDataController::gd->getObjective(S("sidereal_roof_npc_shocked")) && !GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sidereal_afterfall_barry_ans1_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cody")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sidereal_afterfall_barry_ans1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalkRoof(val); };
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sidereal_afterfall_barry_ans2_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cody")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sidereal_afterfall_barry_ans2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalkRoof(val); };
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sidereal_afterfall_barry_ans3_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cody")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sidereal_afterfall_barry_ans3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalkRoof(val); };
		num++;
		takeDoc(0);
		if (doc->caption != String::Empty)
		{
			DialogueController::dc->talking = true;
		}
		updateState();
		return;
	}
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc2_wife_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/dead_wife")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("dialogue_npc2_wife"));
	DialogueController::dc->initDialogue(doc->lines, S("npc2_wife"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
	num++;
	if (!GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("dialogue_npc2_come")) && GameDataController::gd->getObjective(S("dialogue_npc2_wife")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc2_come2_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry_wife")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_npc2_come2"));
		DialogueController::dc->initDialogue(doc->lines, S("npc2_come2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		num++;
	}
	if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		num = locationDialogue(num, color, S("barry"));
		num = dayDialogue(num, color, S("barry"));
		if ((SceneManager::GetActiveScene().get_name() == S("Location1") || SceneManager::GetActiveScene().get_name() == S("Location2") || SceneManager::GetActiveScene().get_name() == S("LocationBaseBathroom") || SceneManager::GetActiveScene().get_name() == S("LocationBaseUpstairs") || SceneManager::GetActiveScene().get_name() == S("LocationBaseOutside0") || SceneManager::GetActiveScene().get_name() == S("LocationBaseOutside1") || SceneManager::GetActiveScene().get_name() == S("LocationBaseOutside2") || SceneManager::GetActiveScene().get_name() == S("LocationBaseOutside3") || SceneManager::GetActiveScene().get_name() == S("LocationAttic2") || SceneManager::GetActiveScene().get_name() == S("LocationAttic1")) && GameDataController::gd->getObjective(S("barry_base_welcome")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("barry_base_family_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/house")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("barry_base_family"));
			DialogueController::dc->initDialogue(doc->lines, S("barry_base_family"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			num++;
		}
		if (GameDataController::gd->getCurrentDay() < 4)
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc2_moon_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/moon")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_npc2_moon"));
			DialogueController::dc->initDialogue(doc->lines, S("npc2_moon"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			num++;
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc2_ship_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/ship")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_npc2_ship"));
			DialogueController::dc->initDialogue(doc->lines, S("npc2_ship"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			num++;
		}
		String empty = String::Empty;
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getCurrentDay() < 5)
		{
			takeDoc(num);
			empty = S("npc2_cody");
			doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cody")));
			doc->lines = List<P<DialogueLine>>::New();
			int num2 = 1;
			if (GameDataController::gd->getCurrentDay() == 2)
			{
				num2 = 1;
			}
			if (GameDataController::gd->getCurrentDay() == 3)
			{
				num2 = 2;
			}
			if (GameDataController::gd->getCurrentDay() == 4)
			{
				num2 = 3;
			}
			doc->setObjective(S("dialogue_") + empty + num2);
			DialogueController::dc->initDialogue(doc->lines, empty + num2, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
			num++;
		}
		else if (GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")) && (GameDataController::gd->getObjective(S("sidereal_npc_found")) || GameDataController::gd->getObjectiveDetail(S("npc3_alive")) != 1))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("barry_cody_dead_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cody")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_npc2_cody_dead"));
			DialogueController::dc->initDialogue(doc->lines, S("barry_cody_dead"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 0)
			{
				doc->lines[3]->text = GameStrings::getString(GameStrings::dialogues, S("barry_cody_dead_day2"));
			}
			if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
			{
				doc->lines[3]->text = GameStrings::getString(GameStrings::dialogues, S("barry_cody_dead_sidereal"));
			}
			num++;
		}
		if (GameDataController::gd->getObjective(S("npc1_alive")))
		{
			if (GameDataController::gd->getCurrentDay() < 5)
			{
				takeDoc(num);
				empty = S("npc2_ginger");
				doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/ginger")));
				doc->lines = List<P<DialogueLine>>::New();
				int num3 = 1;
				if (GameDataController::gd->getCurrentDay() == 2)
				{
					num3 = 1;
				}
				if (GameDataController::gd->getCurrentDay() == 3)
				{
					num3 = 2;
				}
				if (GameDataController::gd->getCurrentDay() == 4)
				{
					num3 = 3;
				}
				doc->setObjective(S("dialogue_") + empty + num3);
				DialogueController::dc->initDialogue(doc->lines, empty + num3, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
				num++;
			}
		}
		else
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc2_ginger_dead_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/ginger")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_npc2_ginger_dead"));
			DialogueController::dc->initDialogue(doc->lines, S("npc2_ginger_dead"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
			num++;
		}
		if (GameDataController::gd->getObjective(S("gasstation_sarge_intro")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 3)
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_sarge_thugs_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge")));
			doc->lines = List<P<DialogueLine>>::New();
			if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
			{
				doc->setObjective(S("dialogue_sarge_thugs4_barry"));
				DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs4_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("gasstation_sarge_convinced")))
			{
				if (GameDataController::gd->getObjective(S("previous_disc_barry")))
				{
					doc->setObjective(S("dialogue_sarge_thugs3_barry"));
					DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs3_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
				}
				else
				{
					doc->setObjective(S("dialogue_sarge_thugs2_barry"));
					DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs2_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
				}
			}
			else
			{
				doc->setObjective(S("dialogue_sarge_thugs1_barry"));
				DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs1_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			num++;
		}
		if (GameDataController::gd->getObjective(S("restaurant_sarge_encountered")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && GameDataController::gd->getCurrentDay() == 3)
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_sarge_storm_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_sarge_storm1_barry"));
			DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_storm1_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			num++;
		}
		if (!GameDataController::gd->getObjective(S("thug_to_kill_bathroom")) && GameDataController::gd->getObjective(S("thug_killed_bathroom")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 4)
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_razor_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("d4_kill_razor_barry"));
			DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor0_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")) && GameDataController::gd->getObjective(S("cs_thug_shot")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor3_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor2_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("cs_thug_shot")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor1_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")) || GameDataController::gd->getObjective(S("cs_thug_shot")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor4_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else
			{
				DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor5_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			num++;
		}
		if (!GameDataController::gd->getObjective(S("thug_to_kill_bathroom")) && !GameDataController::gd->getObjective(S("thug_killed_bathroom")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 4)
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_razor_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("d4_spare_razor_barry"));
			DialogueController::dc->initDialogue(doc->lines, S("d4_spare_razor0_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			num++;
		}
	}
	if (GameDataController::gd->getObjective(S("npc2_wife_note_given")) && !GameDataController::gd->getObjective(S("house_b_garage_open")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc2_burial_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/burial")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_npc2_burial"));
		DialogueController::dc->initDialogue(doc->lines, S("npc2_burial"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		num++;
		doc->lines[4]->action = [this](String val) { gingerFacepalm(val); };
		doc->lines[4]->actionWithText = true;
		doc->lines[10]->action = [this](String val) { openGarage(val); };
		doc->lines[10]->actionWithText = true;
	}
	if (GameDataController::gd->getObjective(S("house_b_grave_dug")) && GameDataController::gd->getObjective(S("house_b_wife_moved")) && !GameDataController::gd->getObjective(S("house_b_grave_filled")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc2_burial2_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/burial")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_npc2_burial2"));
		DialogueController::dc->initDialogue(doc->lines, S("npc2_burial2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		num++;
		doc->lines[2]->action = [this](String val) { goToGrave(val); };
	}
	if (SceneManager::GetActiveScene().get_name() == S("LocationRestaurant2") && !GameDataController::gd->getObjective(S("restaurant_trash_moved")) && GameDataController::gd->getObjective(S("restaurant_trash_tried")) && (!GameDataController::gd->getObjective(S("npc3_alive")) || GameDataController::gd->getObjective(S("dialogue_cody_intro"))))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc2_push_trash_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/push_trash")));
		doc->lines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(doc->lines, S("npc2_push_trash"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { pushTrashCart(val); };
		num++;
	}
	if (SceneManager::GetActiveScene().get_name() == S("SiderealF1C") && !GameDataController::gd->getObjective(S("sidereal_barry_pipe_moved")) && GameDataController::gd->getObjective(S("sidereal_pipe_tried")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc2_push_pipe_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pipe")));
		doc->lines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(doc->lines, S("npc2_push_pipe"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[doc->lines.Count() - 3]->action = [this](String val) { pushPipe(val); };
		num++;
	}
	if (GameDataController::gd->getObjective(S("moon_pods_unlocked")) && SceneManager::GetActiveScene().get_name() == S("LocationMoonbase3"))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("barry_sleep_david_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pod_barry")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("moon_barry_sleeps"));
		DialogueController::dc->initDialogue(doc->lines, S("barry_sleep_david"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[doc->lines.Count() - 3]->action = [this](String a) { goToSleep1(a); };
		doc->lines[doc->lines.Count() - 1]->action = [this](String a) { goToSleep2(a); };
		num++;
	}
	if (!GameDataController::gd->getObjective(S("cody_warned")) && GameDataController::gd->getObjective(S("dream_maggie_future")) && GameDataController::gd->getCurrentDay() == 3 && !GameDataController::gd->getObjective(S("sidereal_roof_collapsed")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("barry_warn_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/where_go")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("barry_warned"));
		DialogueController::dc->initDialogue(doc->lines, S("barry_warn"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		if (GameDataController::gd->getObjective(S("visited_sidereal_outside_1")) && GameDataController::gd->getObjectiveDetail(S("car_location")) == 8)
		{
			doc->lines[2]->text = GameStrings::getString(GameStrings::dialogues, S("barry_warn_variant1b"));
			doc->lines[10]->text = GameStrings::getString(GameStrings::dialogues, S("barry_warn_variant2b"));
		}
		if (GameDataController::gd->getObjective(S("visited_sidereal_outside_1")) && GameDataController::gd->getObjectiveDetail(S("car_location")) != 8)
		{
			doc->lines[2]->text = GameStrings::getString(GameStrings::dialogues, S("barry_warn_variant1a"));
			doc->lines[10]->text = GameStrings::getString(GameStrings::dialogues, S("barry_warn_variant2a"));
		}
		if (SceneManager::GetActiveScene().get_name().ToLower().IndexOf(S("sidereal")) != -1)
		{
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { goAndWait(param); };
		}
		num++;
	}
	if (GameDataController::gd->getCurrentDay() <= 4 && !GameDataController::gd->getObjective(S("barry_improved_car")) && GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("car_driven")))
	{
		if (!GameDataController::gd->getObjective(S("barn_car_wheel_repaired")) || !GameDataController::gd->getObjective(S("barn_car_coil_repaired")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("barry_car0_1_a"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/car")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_barry_car0"));
			DialogueController::dc->initDialogue(doc->lines, S("barry_car0"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			num++;
		}
		else if ((SceneManager::GetActiveScene().get_name() == S("LocationHouseB") || SceneManager::GetActiveScene().get_name() == S("LocationHouseBBack") || SceneManager::GetActiveScene().get_name() == S("LocationHouseBInside")) && GameDataController::gd->getObjectiveDetail(S("car_location")) == 3)
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("barry_car2_1_a"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/car")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_barry_car2"));
			DialogueController::dc->initDialogue(doc->lines, S("barry_car2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			doc->lines[doc->lines.Count() - 1]->action = [this](String val) { upgradeCarQuestion(val); };
			doc->lines[doc->lines.Count() - 1]->actionWithText = false;
			num++;
		}
		else
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("barry_car1_1_a"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/car")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_barry_car1"));
			DialogueController::dc->initDialogue(doc->lines, S("barry_car1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			num++;
		}
	}
	if (GameDataController::gd->getObjective(S("dream_maggie_future")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("barry_wife_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry_wife")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_barry_wife"));
		DialogueController::dc->initDialogue(doc->lines, S("barry_wife"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
	}
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("exit_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, S("npc2_exit"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
	doc->lines[doc->lines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
	updateState();
}

void Npc2Controller::goAndWait(String param)
{
	if (SceneManager::GetActiveScene().get_name() == S("LocationSiderealRoof"))
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->speed = GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->MAX_SPEED * 2.0f;
		GameDataController::gd->setObjective(S("npc2_joined"), false);
		gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("walk_e"), true);
		Invoke(S("stopWalking"), 3.0f);
	}
	GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->setSimpleTargetV3(GameObject::Find(S("BarryGoAway"))->transform->get_position());
	endTalk(String::Empty);
}

void Npc2Controller::stopWalking()
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("stand_se"), true);
}

void Npc2Controller::clickAction2()
{
}

void Npc2Controller::updateState()
{
	if (!GameDataController::gd->getObjective(S("npc2_joined")))
	{
		if (SceneManager::GetActiveScene().get_name() == S("LocationSiderealRoof") && GameDataController::gd->getObjective(S("npc2_alive")))
		{
			return;
		}
		gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("npc2_mourn"), true);
		gameObject->GetComponent<BoxCollider2D>()->set_size(Vector2(0.1161384f, 0.17249104f));
		gameObject->GetComponent<BoxCollider2D>()->set_offset(Vector2(-0.01313657f, -0.11f));
	}
	else
	{
		gameObject->GetComponent<BoxCollider2D>()->set_size(Vector2(0.1161384f, 0.3449821f));
		gameObject->GetComponent<BoxCollider2D>()->set_offset(Vector2(-0.01313657f, -0.04973114f));
	}
	if (!GameDataController::gd->getObjective(S("dialogue_npc2_intro")))
	{
		objectName = S("npc_mourning");
	}
	else
	{
		objectName = S("npc_barry");
	}
	if (GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
	{
		actionType = Type::NormalAction;
	}
	else
	{
		actionType = Type::Talk;
	}
	if (GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
	{
		range = 100.0f;
		rotateToSpeaker = false;
	}
	else if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		range = 25.0f;
		rotateToSpeaker = true;
	}
	else
	{
		range = 1.0f;
		rotateToSpeaker = false;
	}
}

void Npc2Controller::clickAction0()
{
}

void Npc2Controller::upgradeCarQuestion(String val)
{
	DialogueController::dc->talking = false;
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("barry_upgrade_car")), QuestionController::PopupType::QUESTION, [this]() { upgradeCar(); }, 80);
}

void Npc2Controller::upgradeCar()
{
	GameDataController::gd->setObjective(S("barry_improved_car"), true);
	PlayerController::pc->setBusy(true);
	PlayerController::wc->forceAnimation(S("stop"));
	PlayerController::pc->spawnName = S("WaypointHouseB0");
	CurtainController::cc->fadeOut(S("LocationHouseB"), WalkController::Direction::NULL_, nullptr, nullptr, false, [this]() { sayUpgraded(); });
}

void Npc2Controller::sayUpgraded()
{
	instantLines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(instantLines, S("barry_car_upgraded"), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), color);
	for (int i = 0; i < instantLines.Count(); i++)
	{
		Timeline::t->addDialogue(instantLines[i]);
	}
}

void Npc2Controller::pushPipe(String val)
{
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	gameObject->GetComponent<NPCWalkController>()->setBusy(false);
	PlayerController::pc->setBusy(true);
	Object::FindObjectOfType<LocationSiderealF1C_Waypoint_S>()->pushLittleCart();
	Invoke(S("pushTrashCartSound"), 0.2f);
}

void Npc2Controller::pushTrashCart(String val)
{
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	gameObject->GetComponent<NPCWalkController>()->setBusy(false);
	PlayerController::pc->setBusy(true);
	Object::FindObjectOfType<Restaurant2Trash>()->pushLittleCart_Barry();
	Invoke(S("pushTrashCart2"), 0.75f);
	Invoke(S("pushTrashCartSound"), 0.5f);
	Invoke(S("pushTrashCartSound"), 0.75f);
	Invoke(S("pushTrashCartSound"), 1.25f);
}

void Npc2Controller::pushTrashCart2()
{
	gameObject->GetComponent<NPCWalkController>()->currentXY = Vector2(55.0f, 60.0f);
	gameObject->GetComponent<NPCWalkController>()->setSimpleTarget(gameObject->GetComponent<NPCWalkController>()->currentXY);
	GameObject::Find(S("Player"))->GetComponent<WalkController>()->currentXY = Vector2(105.0f, 50.0f);
	GameObject::Find(S("Player"))->GetComponent<WalkController>()->setSimpleTarget(GameObject::Find(S("Player"))->GetComponent<WalkController>()->currentXY);
}

void Npc2Controller::pushTrashCartSound()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_creak1);
}

void Npc2Controller::goToGrave(String val)
{
	GameDataController::gd->setObjective(S("house_b_grave_filled"), true);
	PlayerController::pc->spawnName = S("WaypointHouseBBackBody2");
	CurtainController::cc->fadeOut(S("LocationHouseBBack"), WalkController::Direction::N, S("stand_s"));
	endTalk(String::Empty);
	Timeline::t->doNotUnlock = true;
}

void Npc2Controller::endTalkRoof(String val)
{
	GameDataController::gd->setObjective(S("sidereal_roof_npc_shocked"), false);
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("barry_get_up"));
	endTalk(String::Empty);
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->roofAfterFall();
}

void Npc2Controller::endTalkShip(String val)
{
	GameDataController::gd->setObjective(S("moon_shocked2"), false);
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("barry_get_up"));
	endTalk(String::Empty);
}

void Npc2Controller::gingerFacepalm(String val)
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("ginger_facepalm"));
}

void Npc2Controller::lookUp(String val)
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("npc2_mourn_look"), true);
}

void Npc2Controller::openGarage(String val)
{
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->setBusy(true);
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("npc2_open_garage"), true);
	Invoke(S("openGarage2"), 3.0f);
}

void Npc2Controller::openGarage2()
{
	GameObject::Find(S("Gate"))->GetComponent<Animator>()->Play(S("gate_1"), 0);
	GameDataController::gd->setObjective(S("house_b_garage_open"), true);
	Invoke(S("closeGarage"), 3.0f);
}

void Npc2Controller::closeGarage()
{
	endTalk(String::Empty);
	PlayerController::pc->setBusy(false);
	instantLines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(instantLines, S("npc2_burialz"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	Timeline::t->addDialogueLines(instantLines);
}

void Npc2Controller::uratuj()
{
	PlayerController::pc->setBusy(true);
	PlayerController::wc->forceAnimation(S("save_cody"), true);
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("barry_climb"));
	Invoke(S("naChama"), 0.1f);
}

void Npc2Controller::naChama()
{
	PlayerController::wc->forceAnimation(S("save_cody"), true);
}

void Npc2Controller::barrySaved()
{
	gameObject->GetComponent<NPCWalkController>()->currentXY = ScreenControler::screenToGame(Camera::get_main()->WorldToScreenPoint(GameObject::Find(S("BarrySitHere"))->transform->get_position()));
	gameObject->GetComponent<NPCWalkController>()->clearTarget();
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("barry_sit"));
	Timeline::t->stopChitChat();
	JukeboxMusic::jb->changeMusic(nullptr, true, 0.0f, 0.0f, 0.01f);
	if (GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("cody_warned")))
	{
		GameObject::Find(S("Npc3"))->GetComponent<Npc3Controller>()->siderealFall();
		GameDataController::gd->setObjective(S("npc3_alive"), false);
		GameDataController::gd->setObjectiveDetail(S("npc3_alive"), 1);
		Invoke(S("barrySaved2"), 0.5f);
	}
	else
	{
		PlayerController::pc->setBusy(false);
	}
	GameDataController::gd->setObjective(S("sidereal_roof_wait_for_rescue"), false);
	GameDataController::gd->setObjective(S("sidereal_roof_npc_shocked"), true);
}

void Npc2Controller::barrySaved2()
{
	GameObject::Find(S("fall_plane"))->GetComponent<LetterFall>()->startTalkAfterfall();
}
