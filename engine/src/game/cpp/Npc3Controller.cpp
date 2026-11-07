#include "../game_all.h"

void Npc3Controller::_cctor()
{
	color = Vector3(390.0f / 1024.0f, 0.5683594f, 330.0f / 1024.0f);
}

Vector3 Npc3Controller::getColor()
{
	return color;
}

void Npc3Controller::continueStart()
{
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("foodcan"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("foodcanopen"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("coat4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("water4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("food_bag"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("whiskey"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("deadbird"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ropehook"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rope"), String::Empty, nullptr, String::Empty));
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
		interactions.Add(New<ItemInteraction>(S("revolver_6"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_5"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_4"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_3"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_2"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_1"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("revolver_0"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
	}
	interactions.Add(New<ItemInteraction>(S("pills"), String::Empty, nullptr, String::Empty));
	if (!GameDataController::gd->getObjective(S("restaurant_door_opened")))
	{
		interactions.Add(New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_6"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_5"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_4"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_3"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_2"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_1"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_0"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("cody_intro_threat")), nullptr, String::Empty));
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		interactions.Add(New<ItemInteraction>(S("rifle_0"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_1"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_2"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_3"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_4"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_5"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_6"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_0"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_1"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_2"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_3"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_4"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_5"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_6"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_0"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_1"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_2"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_3"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_4"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_5"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_6"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_0"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_1"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_2"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_3"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_4"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_5"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_6"), GameStrings::getString(GameStrings::actions, S("cody_give_rifle")), nullptr, String::Empty));
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		interactions.Add(New<ItemInteraction>(S("rifle_0"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_1"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_2"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_3"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_4"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_5"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_6"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_0"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_1"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_2"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_3"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_4"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_5"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_6"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_0"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_1"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_2"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_3"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_4"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_5"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_6"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_0"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_1"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_2"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_3"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_4"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_5"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s0_6"), GameStrings::getString(GameStrings::actions, S("gun_cody_storm")), nullptr, String::Empty));
	}
	actionType = Type::Talk;
}

void Npc3Controller::giveFoodCan(String val)
{
	GameDataController::gd->setObjective(S("dialogue_cody_food_closed_given"), true);
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("can_shake"), true);
}

void Npc3Controller::giveBackFoodCan(String val)
{
	GameDataController::gd->setObjective(S("dialogue_cody_food_closed_given"), false);
}

void Npc3Controller::giveFoodCanOpen(String val)
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("can_opened"), true);
}

void Npc3Controller::whatOnClick0()
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
	else if (GameDataController::gd->getObjective(S("moon_shocked3")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker_sit"))->gameObject;
		range = 0.0f;
		rotateToSpeaker = false;
	}
	else if (GameDataController::gd->getObjective(S("sidereal_roof_npc_shocked")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker_sit"))->gameObject;
		range = 0.0f;
		rotateToSpeaker = false;
	}
	else if (GameDataController::gd->getObjective(S("restaurant_door_opened2")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		range = 25.0f;
		rotateToSpeaker = true;
	}
	else
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		range = 1000.0f;
		rotateToSpeaker = false;
	}
}

void Npc3Controller::whatOnClick()
{
}

void Npc3Controller::uratuj()
{
	PlayerController::pc->setBusy(true);
	PlayerController::wc->forceAnimation(S("save_cody"), true);
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("cody_climb"));
	Invoke(S("naChama"), 0.1f);
}

void Npc3Controller::naChama()
{
	PlayerController::wc->forceAnimation(S("save_cody"), true);
}

void Npc3Controller::codySaved()
{
	if (GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
	{
		Timeline::t->stopChitChat();
		gameObject->GetComponent<NPCWalkController>()->currentXY = ScreenControler::screenToGame(Camera::get_main()->WorldToScreenPoint(GameObject::Find(S("CodySitHere"))->transform->get_position()));
		gameObject->GetComponent<NPCWalkController>()->clearTarget();
		gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("cody_sit"));
		JukeboxMusic::jb->changeMusic(nullptr, true, 0.0f, 0.0f, 0.01f);
		if (GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("barry_warned")))
		{
			GameObject::Find(S("Npc2"))->GetComponent<Npc2Controller>()->siderealFall();
			GameDataController::gd->setObjective(S("npc2_alive"), false);
			GameDataController::gd->setObjectiveDetail(S("npc2_alive"), 1);
			Invoke(S("codySaved2"), 0.5f);
		}
		else
		{
			PlayerController::pc->setBusy(false);
		}
		GameDataController::gd->setObjective(S("sidereal_roof_wait_for_rescue"), false);
		GameDataController::gd->setObjective(S("sidereal_roof_npc_shocked"), true);
	}
}

void Npc3Controller::codySaved2()
{
	GameObject::Find(S("fall_plane"))->GetComponent<LetterFall>()->startTalkAfterfall();
}

void Npc3Controller::siderealFall()
{
	GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::dialogues, S("fall_aah")), false, false, false, 100, getColor().x, getColor().y, getColor().z, 0.0f, 0.0f, 0.0f, 0.75f, false, true);
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("cody_fall"));
	gameObject->GetComponent<NPCWalkController>()->speed = 5.0f;
	gameObject->GetComponent<NPCWalkController>()->setSimpleTarget(Vector2(gameObject->GetComponent<NPCWalkController>()->currentXY.x, -100.0f));
	JukeboxMusic::jb->changeMusic(nullptr, true, 0.0f, 0.0f, 0.01f);
}

void Npc3Controller::fallAccelerate()
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

void Npc3Controller::endTalkRoof(String val)
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("cody_get_up"));
	endTalk(String::Empty);
	GameDataController::gd->setObjective(S("sidereal_roof_npc_shocked"), false);
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->roofAfterFall();
}

void Npc3Controller::endTalkShip(String val)
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("cody_get_up"));
	endTalk(String::Empty);
	GameDataController::gd->setObjective(S("moon_shocked3"), false);
}

void Npc3Controller::playerStandUp(String v)
{
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->forceAnimation(S("kneel_out_n"));
}

void Npc3Controller::npcClickAction(String item)
{
	Vector3 vector = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	Vector3 vector2 = Npc2Controller::getColor();
	P<TextFieldController> component2 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
	instantLines = List<P<DialogueLine>>::New();
	if (GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
	{
		if (GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) != 1 && !GameDataController::gd->getObjective(S("barry_warned")))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("save_cody")), QuestionController::PopupType::QUESTION, [this]() { uratuj(); });
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
		if (GameDataController::gd->getObjective(S("npc2_alive")) || GameDataController::gd->getObjectiveDetail(S("npc2_alive")) != 1 || GameDataController::gd->getObjective(S("barry_warned")))
		{
			DialogueController::dc->initDialogue(instantLines, S("sidereal_nofall_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			instantLines[instantLines.Count() - 1]->action = [this](String val) { endTalkRoof(val); };
			instantLines[instantLines.Count() - 2]->action = [this](String v) { playerStandUp(v); };
			for (int i = 0; i < instantLines.Count(); i++)
			{
				Timeline::t->addDialogue(instantLines[i]);
			}
			return;
		}
		DialogueController::dc->initDialogue(instantLines, S("sidereal_afterfall_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		instantLines[instantLines.Count() - 1]->action = [this](String v) { playerStandUp(v); };
	}
	else
	{
		if (GameDataController::gd->getObjective(S("moon_shocked3")))
		{
			PlayerController::pc->forceAnimation(S("kneel_in_n"));
			DialogueController::dc->initDialogue(instantLines, S("moon_shocked_cody1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			GameDataController::gd->setObjective(S("moon_shocked3"), false);
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
				DialogueController::dc->initDialogue(instantLines, S("moon_shocked_cody2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
				for (int k = 0; k < instantLines.Count(); k++)
				{
					Timeline::t->addDialogue(instantLines[k]);
				}
			}
			return;
		}
		if (item == S("foodcan"))
		{
			DialogueController::dc->initDialogue(instantLines, S("cody_food_locked"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			instantLines[2]->action = [this](String val) { giveFoodCan(val); };
			instantLines[2]->actionWithText = true;
			instantLines[instantLines.Count() - 2]->action = [this](String val) { giveBackFoodCan(val); };
			instantLines[instantLines.Count() - 2]->actionWithText = true;
			instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
			instantLines[instantLines.Count() - 1]->actionWithText = true;
		}
		else if (item == S("foodcanopen"))
		{
			DialogueController::dc->initDialogue(instantLines, S("cody_food"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			GameDataController::gd->setObjective(S("npc3_joined"), true);
			InventoryController::ic->removeItem(S("foodcanopen"));
			GameDataController::gd->setObjectiveDetail(S("chitchat"), -50);
			instantLines[1]->action = [this](String val) { startTalkRestaurant(val); };
			instantLines[2]->action = [this](String val) { giveFoodCanOpen(val); };
			instantLines[2]->actionWithText = true;
			if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
			{
				DialogueController::dc->initDialogue(instantLines, S("barry_cody_first_meet"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor(), textField, color);
				instantLines[instantLines.Count() - 2]->action = [this](String val) { endTalkRestaurant2(val); };
			}
			instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
			instantLines[instantLines.Count() - 1]->actionWithText = true;
		}
		else if (!GameDataController::gd->getObjective(S("dialogue_cody_intro")))
		{
			DialogueController::dc->initDialogue(instantLines, S("cody_intro1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			instantLines[0]->actionWithText = true;
			GameDataController::gd->setObjective(S("dialogue_cody_intro"), true);
			if (GameDataController::gd->getObjective(S("npc2_joined")))
			{
				instantLines.Add(New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::dialogues, S("cody_intro1_6_extra_a")), nullptr));
			}
			if (GameDataController::gd->getObjective(S("previous_disc_barry")) || GameDataController::gd->getObjective(S("previous_disc_cody")))
			{
				DialogueController::dc->initDialogue(instantLines, S("cody_intro2b"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			}
			else
			{
				DialogueController::dc->initDialogue(instantLines, S("cody_intro2a"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			}
		}
		else if (!GameDataController::gd->getObjective(S("npc3_joined")))
		{
			if (!GameDataController::gd->getObjective(S("dialogue_cody_door_opened")) && GameDataController::gd->getObjective(S("restaurant_door_opened2")))
			{
				DialogueController::dc->initDialogue(instantLines, S("cody_door_opened_intro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
				instantLines[0]->actionWithText = true;
			}
			else if (GameDataController::gd->getObjective(S("dialogue_cody_door_opened")) && GameDataController::gd->getObjective(S("restaurant_door_opened2")))
			{
				if (item == S("water1") || item == S("water2") || item == S("water3") || item == S("water4"))
				{
					String key2 = S("cody_water_not_joined");
					PlayerController::pc->say(GameStrings::getString(GameStrings::actions, key2));
					return;
				}
				else if (item == S("coat1") || item == S("coat2") || item == S("coat3") || item == S("coat4"))
				{
					String key = S("cody_coat_not_joined");
					PlayerController::pc->say(GameStrings::getString(GameStrings::actions, key));
					return;
				}
				DialogueController::dc->initDialogue(instantLines, S("cody_intro2c"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
				instantLines[0]->actionWithText = true;
			}
			else
			{
				if (item == S("water1") || item == S("water2") || item == S("water3") || item == S("water4"))
				{
					String key4 = S("cody_water_coat_unknown");
					if (GameDataController::gd->getObjective(S("dialogue_cody_door_closed")) || GameDataController::gd->getObjective(S("dialogue_cody_come")))
					{
						key4 = S("cody_water_not_joined");
					}
					PlayerController::pc->say(GameStrings::getString(GameStrings::actions, key4));
					return;
				}
				else if (item == S("coat1") || item == S("coat2") || item == S("coat3") || item == S("coat4"))
				{
					String key3 = S("cody_water_coat_unknown");
					if (GameDataController::gd->getObjective(S("dialogue_cody_door_closed")) || GameDataController::gd->getObjective(S("dialogue_cody_come")))
					{
						key3 = S("cody_coat_not_joined");
					}
					PlayerController::pc->say(GameStrings::getString(GameStrings::actions, key3));
					return;
				}
				DialogueController::dc->initDialogue(instantLines, S("cody_intro2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
				instantLines[0]->actionWithText = true;
			}
		}
		else
		{
			if (item == S("coat1") || item == S("coat2") || item == S("coat3") || item == S("coat4"))
			{
				if (ItemsManager::im->getItem(S("coat1"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("coat2"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("coat3"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("coat4"))->dataRef->droppedLocation == S("npc3"))
				{
					DialogueController::dc->initDialogue(instantLines, S("cody_already_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
					instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
				}
				else if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
				{
					DialogueController::dc->initDialogue(instantLines, S("cody_give_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
					if (!GingerActionController::isGingerHere())
					{
						instantLines.RemoveAt(6);
						instantLines.RemoveAt(5);
						instantLines.RemoveAt(4);
					}
					instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
					InventoryController::ic->removeItem(item);
					ItemsManager::im->getItem(item)->dataRef->droppedLocation = S("npc3");
					JournalTexts::pickTexts(GameDataController::gd->getCurrentDay());
				}
				else if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
				{
					DialogueController::dc->initDialogue(instantLines, S("cody_bad_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
					instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
				}
				else
				{
					DialogueController::dc->initDialogue(instantLines, S("cody_bad2_coat"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
					instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
				}
			}
			else if (item == S("water1") || item == S("water2") || item == S("water3") || item == S("water4"))
			{
				if (ItemsManager::im->getItem(S("water1"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("water2"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("water3"))->dataRef->droppedLocation == S("npc3") || ItemsManager::im->getItem(S("water4"))->dataRef->droppedLocation == S("npc3"))
				{
					DialogueController::dc->initDialogue(instantLines, S("cody_already_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
					instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
				}
				else if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
				{
					DialogueController::dc->initDialogue(instantLines, S("cody_give_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
					if (!GingerActionController::isGingerHere())
					{
						instantLines.RemoveAt(6);
						instantLines.RemoveAt(5);
						instantLines.RemoveAt(4);
					}
					instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
					InventoryController::ic->removeItem(item);
					ItemsManager::im->getItem(item)->dataRef->droppedLocation = S("npc3");
					JournalTexts::pickTexts(GameDataController::gd->getCurrentDay());
				}
				else if (GameDataController::gd->getCurrentDay() == 2 && GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
				{
					DialogueController::dc->initDialogue(instantLines, S("cody_bad_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
					instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
				}
				else
				{
					DialogueController::dc->initDialogue(instantLines, S("cody_bad2_water"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
					instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
				}
			}
			else
			{
				if (usedItem == S("pills"))
				{
					String prefix = S("cody_give_pills");
					if (GameDataController::gd->getObjective(S("cody_pills_taken")))
					{
						prefix = S("cody_gave_pills");
					}
					GameDataController::gd->setObjective(S("cody_pills_taken"), true);
					DialogueController::dc->initDialogue(instantLines, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
					instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
				}
				else if (item.IndexOf(S("revolver")) != -1)
				{
					if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
					{
						DialogueController::dc->initDialogue(instantLines, S("npc3_give_gun"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
						instantLines[instantLines.Count() - 1]->action = [this](String s) { revolverQuestion(s); };
					}
				}
				else
				{
					if (item == S("food_bag"))
					{
						DialogueController::dc->initDialogue(instantLines, S("cody_bag_of_food"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), getColor(), textField, color);
						InventoryController::ic->removeItem(item);
						ItemsManager::im->getItem(item)->dataRef->droppedLocation = S("npc3");
						instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
					}
					else if (item == S("deadbird"))
					{
						DialogueController::dc->initDialogue(instantLines, S("dead_bird_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
						instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
					}
					else if (item == S("whiskey"))
					{
						DialogueController::dc->initDialogue(instantLines, S("whiskey_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
						instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
					}
					else if (item == S("rope") || item == S("ropehook"))
					{
						DialogueController::dc->initDialogue(instantLines, S("rope_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
						instantLines[instantLines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
					}
					else
					{
						DialogueController::dc->initDialogue(instantLines, S("cody_intro3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
					}
				}
			}
		}
	}
	if (!GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("restaurant_door_opened2")))
	{
		instantLines[0]->action = [this](String val) { fightStance(val); };
	}
	for (int l = 0; l < instantLines.Count(); l++)
	{
		Timeline::t->addDialogue(instantLines[l]);
	}
	DialogueController::dc->callback = [this]() { dialogues(); };
	dialogues();
}

void Npc3Controller::revolverQuestion(String s)
{
	endTalk(String::Empty);
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("cody_gun")), QuestionController::PopupType::QUESTION, [this]() { revolverTeach(); }, 60);
}

void Npc3Controller::revolverTeach()
{
	String text = String::Empty;
	if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("revolver_6")))
	{
		text = S("revolver_6");
	}
	if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("revolver_5")))
	{
		text = S("revolver_5");
	}
	if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("revolver_4")))
	{
		text = S("revolver_4");
	}
	if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("revolver_3")))
	{
		text = S("revolver_3");
	}
	if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("revolver_2")))
	{
		text = S("revolver_2");
	}
	if (InventoryController::ic->isItemInInventoryOrTrunkOrWhatever(S("revolver_1")))
	{
		text = S("revolver_1");
	}
	InventoryController::ic->removeItem(text);
	ItemsManager::im->getItem(text)->dataRef->droppedLocation = S("npc3");
	PlayerController::pc->setBusy(true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::S_, nullptr, nullptr, false, [this]() { revolverDone(); });
}

void Npc3Controller::revolverDone()
{
	Vector3 color_c = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	instantLines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(instantLines, S("npc3_gave_gun"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, color_c);
	for (int i = 0; i < instantLines.Count(); i++)
	{
		Timeline::t->addDialogue(instantLines[i]);
	}
}

void Npc3Controller::goToSleep1(String a)
{
	gameObject->GetComponent<NPCWalkController>()->setSimpleTargetV3(GameObject::Find(S("CodyWalkHere"))->transform->get_position());
}

void Npc3Controller::goToSleep2(String a)
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("cody_pod");
	DialogueController::dc->talking = false;
	Timeline::t->doNotUnlock = true;
	CurtainController::cc->fadeOut(S("LocationMoonbase3"), WalkController::Direction::NW, S("stand_ne"), nullptr, true, [this]() { goToSleep3(); });
}

void Npc3Controller::goToSleep3()
{
	P<TextFieldController> component = GameObject::Find(S("Moonbase3Pad3"))->transform->Find(S("TextField"))->GetComponent<TextFieldController>();
	if (GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("moon_cate_sleeps")))
	{
		component->transform->set_position(ScreenControler::roundToNearestFullPixel3(component->transform->get_position()));
		instantLines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(instantLines, S("cody_sleep_cate"), component, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		for (int i = 0; i < instantLines.Count(); i++)
		{
			Timeline::t->addDialogue(instantLines[i]);
		}
	}
	if (GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("moon_barry_sleeps")))
	{
		instantLines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(instantLines, S("cody_sleep_barry"), component, color, GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
		for (int j = 0; j < instantLines.Count(); j++)
		{
			Timeline::t->addDialogue(instantLines[j]);
		}
	}
	instantLines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(instantLines, S("cody_sleep_2david"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	instantLines[instantLines.Count() - 1]->action = [this](String s) { closePod(s); };
	for (int k = 0; k < instantLines.Count(); k++)
	{
		Timeline::t->addDialogue(instantLines[k]);
	}
}

void Npc3Controller::closePod(String s)
{
	GameObject::Find(S("Moonbase3Pad3"))->GetComponent<Animator>()->Play(S("moon_pod3_close"));
	GameDataController::gd->setObjectiveDetail(S("moon_cody_sleeps"), 1);
	if (GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("moon_barry_sleeps")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<Npc2Controller>()->pod_rotate();
	}
	if (GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("moon_cate_sleeps")))
	{
		GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->pod_rotate();
	}
}

void Npc3Controller::pod_rotate()
{
	Invoke(S("pod_rotate2"), Random::Range(0.5f, 2.0f));
}

void Npc3Controller::pod_rotate2()
{
	GetComponent<NPCWalkController>()->playIdleAnimation(S("cody_stand_se"));
	GetComponent<NPCWalkController>()->setBusy(false);
}

void Npc3Controller::dialogues()
{
	String empty = String::Empty;
	DialogueController::dc->reset();
	Vector3 vector = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	int num = 0;
	if (!GameDataController::gd->getObjective(S("npc3_joined")) && !GameDataController::gd->getObjective(S("restaurant_door_opened2")))
	{
		takeDoc(num);
		empty = S("cody_orwhat");
		doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/orwhat")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_") + empty);
		DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		num++;
	}
	if (GameDataController::gd->getObjective(S("sidereal_roof_npc_shocked")) && !GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sidereal_afterfall_cody_ans1_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sidereal_afterfall_cody_ans1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalkRoof(val); };
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sidereal_afterfall_cody_ans2_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sidereal_afterfall_cody_ans2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalkRoof(val); };
		num++;
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("sidereal_afterfall_cody_ans3_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(String::Empty);
		DialogueController::dc->initDialogue(doc->lines, S("sidereal_afterfall_cody_ans3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
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
	if ((GameDataController::gd->getObjective(S("npc3_joined")) || !GameDataController::gd->getObjective(S("restaurant_door_opened2")) || GameDataController::gd->getObjective(S("dialogue_cody_door_opened"))) && GingerActionController::isGingerHere())
	{
		takeDoc(num);
		empty = S("cody_parents");
		doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/parents2")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_") + empty);
		DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		num++;
	}
	if (!GameDataController::gd->getObjective(S("npc3_joined")) && (!GameDataController::gd->getObjective(S("restaurant_door_opened2")) || GameDataController::gd->getObjective(S("dialogue_cody_door_opened"))))
	{
		if (!GameDataController::gd->getObjective(S("restaurant_door_opened2")))
		{
			takeDoc(num);
			empty = S("cody_door_closed");
			doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/door1")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_") + empty);
			DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			num++;
		}
		if (!GameDataController::gd->getObjective(S("restaurant_door_opened2")) || GameDataController::gd->getObjective(S("dialogue_cody_door_opened")))
		{
			takeDoc(num);
			empty = S("cody_come");
			doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cody")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_") + empty);
			DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			num++;
		}
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")))
	{
		num = locationDialogue(num, color, S("cody"));
		num = dayDialogue(num, color, S("cody"));
		if (GingerActionController::isGingerHere())
		{
			takeDoc(num);
			empty = S("cody_age");
			doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/age")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_") + empty);
			DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			num++;
			if (GameDataController::gd->getCurrentDay() < 5)
			{
				takeDoc(num);
				empty = S("cody_moon");
				doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
				doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/moon")));
				doc->lines = List<P<DialogueLine>>::New();
				doc->setObjective(S("dialogue_") + empty);
				DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
				num++;
			}
		}
		if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getCurrentDay() < 5)
		{
			takeDoc(num);
			empty = S("cody_barry");
			doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry")));
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
			DialogueController::dc->initDialogue(doc->lines, empty + num2, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
			num++;
		}
		else if (GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("npc2_alive")) && (GameDataController::gd->getObjective(S("sidereal_npc_found")) || GameDataController::gd->getObjectiveDetail(S("npc2_alive")) != 1))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("cody_barry_dead_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_cody_barry_dead"));
			DialogueController::dc->initDialogue(doc->lines, S("cody_barry_dead"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
			if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 0)
			{
				doc->lines[3]->text = GameStrings::getString(GameStrings::dialogues, S("cody_barry_dead_day2"));
			}
			if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
			{
				doc->lines[3]->text = GameStrings::getString(GameStrings::dialogues, S("cody_barry_dead_sidereal"));
			}
			num++;
		}
		if (GameDataController::gd->getObjective(S("npc1_alive")) && GameDataController::gd->getCurrentDay() < 5)
		{
			takeDoc(num);
			empty = S("npc3_ginger");
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
		else if (!GameDataController::gd->getObjective(S("npc1_alive")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc3_ginger_dead_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/ginger")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_npc3_ginger_dead"));
			DialogueController::dc->initDialogue(doc->lines, S("npc3_ginger_dead"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, vector, textField, color);
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
				doc->setObjective(S("dialogue_sarge_thugs4_cody"));
				DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs4_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("gasstation_sarge_convinced")))
			{
				if (GameDataController::gd->getObjective(S("previous_disc_cody")))
				{
					doc->setObjective(S("dialogue_sarge_thugs3_cody"));
					DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs3_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
				}
				else
				{
					doc->setObjective(S("dialogue_sarge_thugs2_cody"));
					DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs2_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
				}
			}
			else
			{
				doc->setObjective(S("dialogue_sarge_thugs1_cody"));
				DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_thugs1_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			num++;
		}
		if (GameDataController::gd->getObjective(S("restaurant_sarge_encountered")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && GameDataController::gd->getCurrentDay() == 3)
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_sarge_storm_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_sarge_storm1_cody"));
			DialogueController::dc->initDialogue(doc->lines, S("dialogue_sarge_storm1_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			num++;
		}
		if (!GameDataController::gd->getObjective(S("thug_to_kill_bathroom")) && GameDataController::gd->getObjective(S("thug_killed_bathroom")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 4)
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_razor_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("d4_kill_razor_cody"));
			DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor0_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")) && GameDataController::gd->getObjective(S("cs_thug_shot")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor3_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor2_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else if (GameDataController::gd->getObjective(S("cs_thug_shot")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor1_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")) || GameDataController::gd->getObjective(S("cs_thug_shot")))
			{
				DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor4_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			else
			{
				DialogueController::dc->initDialogue(doc->lines, S("d4_kill_razor5_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			}
			num++;
		}
		if (!GameDataController::gd->getObjective(S("thug_to_kill_bathroom")) && !GameDataController::gd->getObjective(S("thug_killed_bathroom")) && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 4)
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_razor_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/razor")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("d4_spare_razor_cody"));
			DialogueController::dc->initDialogue(doc->lines, S("d4_spare_razor0_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			num++;
		}
		if (GameDataController::gd->getObjective(S("cody_killed_someone")) && GameDataController::gd->getCurrentDay() == 4)
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dialogue_cody_killed_bandit_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bloodbath")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dialogue_cody_killed_bandit"));
			DialogueController::dc->initDialogue(doc->lines, S("dialogue_cody_killed_bandit"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
			num++;
		}
	}
	if (GameDataController::gd->getObjective(S("restaurant_door_opened2")) && !GameDataController::gd->getObjective(S("dialogue_cody_door_opened")))
	{
		takeDoc(num);
		empty = S("cody_door_opened_owner");
		doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/restaurant_chief")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_cody_door_opened"));
		DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		doc->lines.Add(New<DialogueLine>(textField, color, GameStrings::getString(GameStrings::dialogues, S("cody_intro2c_1_b")), nullptr));
		doc->lines[doc->lines.Count() - 2]->action = [this](String val) { endTalkRestaurant(val); };
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
		num++;
		takeDoc(num);
		empty = S("cody_door_opened_magic");
		doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/restaurant_wizard")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_cody_door_opened"));
		DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		doc->lines.Add(New<DialogueLine>(textField, color, GameStrings::getString(GameStrings::dialogues, S("cody_intro2c_1_b")), nullptr));
		doc->lines[doc->lines.Count() - 2]->action = [this](String val) { endTalkRestaurant(val); };
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
		num++;
		takeDoc(num);
		empty = S("cody_door_opened_backdoor");
		doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/restaurant_thief")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_cody_door_opened"));
		DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		doc->lines.Add(New<DialogueLine>(textField, color, GameStrings::getString(GameStrings::dialogues, S("cody_intro2c_1_b")), nullptr));
		doc->lines[doc->lines.Count() - 2]->action = [this](String val) { endTalkRestaurant(val); };
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
		num++;
		takeDoc(num);
		empty = S("cody_door_opened_twin");
		doc->caption = GameStrings::getString(GameStrings::dialogues, empty + S("_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/restaurant_twin")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_cody_door_opened"));
		DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		doc->lines.Add(New<DialogueLine>(textField, color, GameStrings::getString(GameStrings::dialogues, S("cody_intro2c_1_b")), nullptr));
		doc->lines[doc->lines.Count() - 2]->action = [this](String val) { endTalkRestaurant(val); };
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
		num++;
	}
	if (SceneManager::GetActiveScene().get_name() == S("SiderealF1C") && !GameDataController::gd->getObjective(S("sidereal_f1c_b_open")) && GameDataController::gd->getObjective(S("sidereal_vent_open")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("npc3_go_vent_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/vents")));
		doc->lines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(doc->lines, S("npc3_go_vent"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[doc->lines.Count() - 2]->action = [this](String val) { goVent1(val); };
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { goVent(val); };
		num++;
	}
	if (GameDataController::gd->getObjective(S("moon_pods_unlocked")) && SceneManager::GetActiveScene().get_name() == S("LocationMoonbase3"))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("cody_sleep_david_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pod_cody")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("moon_cody_sleeps"));
		DialogueController::dc->initDialogue(doc->lines, S("cody_sleep_david"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		doc->lines[doc->lines.Count() - 3]->action = [this](String a) { goToSleep1(a); };
		doc->lines[doc->lines.Count() - 1]->action = [this](String a) { goToSleep2(a); };
		num++;
	}
	if (!GameDataController::gd->getObjective(S("barry_warned")) && GameDataController::gd->getObjective(S("dream_tiger_future")) && GameDataController::gd->getCurrentDay() == 3 && !GameDataController::gd->getObjective(S("sidereal_roof_collapsed")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("cody_warn_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/where_go")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("cody_warned"));
		DialogueController::dc->initDialogue(doc->lines, S("cody_warn"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		if (GameDataController::gd->getObjective(S("visited_sidereal_outside_1")) && GameDataController::gd->getObjectiveDetail(S("car_location")) == 8)
		{
			doc->lines[2]->text = GameStrings::getString(GameStrings::dialogues, S("cody_warn_variant1b"));
			doc->lines[10]->text = GameStrings::getString(GameStrings::dialogues, S("cody_warn_variant2b"));
		}
		if (GameDataController::gd->getObjective(S("visited_sidereal_outside_1")) && GameDataController::gd->getObjectiveDetail(S("car_location")) != 8)
		{
			doc->lines[2]->text = GameStrings::getString(GameStrings::dialogues, S("cody_warn_variant1a"));
			doc->lines[10]->text = GameStrings::getString(GameStrings::dialogues, S("cody_warn_variant2a"));
		}
		if (SceneManager::GetActiveScene().get_name().ToLower().IndexOf(S("sidereal")) != -1)
		{
			doc->lines[doc->lines.Count() - 1]->action = [this](String param) { goAndWait(param); };
		}
		num++;
	}
	if (GameDataController::gd->getObjective(S("dream_tiger_future")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("cody_tiger_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/tiger")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dialogue_cody_tiger"));
		DialogueController::dc->initDialogue(doc->lines, S("cody_tiger"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
		num++;
	}
	if (!GameDataController::gd->getObjective(S("restaurant_door_opened2")) || GameDataController::gd->getObjective(S("dialogue_cody_door_opened")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("exit_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
		doc->lines = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(doc->lines, S("cody_exit"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, component, vector);
		doc->setObjective(String::Empty);
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { NPCActionController::endTalk(val); };
		num++;
	}
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
	updateState();
}

void Npc3Controller::goAndWait(String param)
{
	if (SceneManager::GetActiveScene().get_name() == S("LocationSiderealRoof"))
	{
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->speed = GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->MAX_SPEED * 2.0f;
		GameDataController::gd->setObjective(S("npc3_joined"), false);
		gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("walk_e"), true);
		Invoke(S("stopWalking"), 3.0f);
	}
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setSimpleTargetV3(GameObject::Find(S("CodyGoAway"))->transform->get_position());
	endTalk(String::Empty);
}

void Npc3Controller::stopWalking()
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("stand_se"), true);
}

void Npc3Controller::startTalkRestaurant(String val)
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_ne"));
	if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_n"));
	}
}

void Npc3Controller::endTalkRestaurant(String val)
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("surprised_end"), true);
}

void Npc3Controller::endTalkRestaurant2(String val)
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_se"));
	if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_se"));
	}
}

void Npc3Controller::flip()
{
	gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
}

void Npc3Controller::clickAction2()
{
}

void Npc3Controller::updateState()
{
	setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	if (!GameDataController::gd->getObjective(S("npc3_alive")))
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
		return;
	}
	if (!GameDataController::gd->getObjective(S("dialogue_cody_intro")))
	{
		objectName = S("npc_boy");
	}
	else
	{
		objectName = S("npc_cody");
	}
	if (GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
	{
		actionType = Type::NormalAction;
	}
	else
	{
		actionType = Type::Talk;
	}
	gameObject->GetComponent<BoxCollider2D>()->set_offset(Vector2(-0.01313657f, -0.04973114f));
	range = 25.0f;
	rotateToSpeaker = true;
	if (GameDataController::gd->getObjective(S("restaurant_door_opened2")) && SceneManager::GetActiveScene().get_name() == S("LocationRestaurant3"))
	{
		if (GameDataController::gd->getObjective(S("dialogue_cody_food_closed_given")))
		{
			gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("can_shake"), true);
		}
		else if (GameDataController::gd->getObjective(S("dialogue_cody_door_opened")))
		{
			rotateToSpeaker = true;
			gameObject->GetComponent<NPCWalkController>()->playIdleAnimation(S("cody_stand_se"));
		}
		else
		{
			rotateToSpeaker = false;
		}
	}
	else if (SceneManager::GetActiveScene().get_name() == S("LocationRestaurant3"))
	{
		range = 1000.0f;
		rotateToSpeaker = false;
		if (!DialogueController::dc->talking)
		{
			gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("pull_door"), true);
		}
	}
}

void Npc3Controller::clickAction0()
{
}

void Npc3Controller::goVent1(String val)
{
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setSimpleTarget(Vector2(55.0f, 50.0f));
}

void Npc3Controller::goVent(String val)
{
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	Timeline::t->doNotUnlock = true;
	gameObject->GetComponent<NPCWalkController>()->setBusy(false);
	PlayerController::pc->setBusy(true);
	Object::FindObjectOfType<LocationSiderealF1C_Waypoint_B>()->pushLittleCart();
	Invoke(S("openDoorSound"), 0.2f);
}

void Npc3Controller::fightStance(String val)
{
	gameObject->GetComponent<NPCWalkController>()->forceAnimation(S("fight_stance"), true);
}

void Npc3Controller::openDoorSound()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_door_open);
}
