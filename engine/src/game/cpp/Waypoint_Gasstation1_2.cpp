#include "../game_all.h"

void Waypoint_Gasstation1_2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_back");
	doubleClickCondition = S("visited_gasstation2");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void Waypoint_Gasstation1_2::clickAction()
{
	if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && !GameDataController::gd->getObjective(S("thugs_gasstation_talk")) && GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("gasstation_thugs_are_there")));
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && !GameDataController::gd->getObjective(S("gasstation_sarge_intro")) && !GameDataController::gd->getObjective(S("gasstation_sarge_shot")) && GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("gasstation_meet_thug"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		if (GameDataController::gd->getObjective(S("npc2_alive")) || GameDataController::gd->getObjective(S("npc3_alive")))
		{
			list[0]->text = GameStrings::getString(GameStrings::dialogues, S("gasstation_meet_thug2_1_a"));
		}
		list[2]->action = [this](String a) { goThere(a); };
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
	else
	{
		GameDataController::gd->setObjective(S("gasstation_thugs_safe"), true);
		GameDataController::gd->setObjective(S("gasstation_spy_mode"), false);
		PlayerController::pc->spawnName = S("Waypoint_Gasstation2_1");
		CurtainController::cc->fadeOut(S("LocationGasstation2"), WalkController::Direction::E);
	}
}

void Waypoint_Gasstation1_2::whatOnClick0()
{
	doubleClickCondition = S("visited_gasstation2");
	if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && !GameDataController::gd->getObjective(S("gasstation_sarge_intro")) && !GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		doubleClickCondition = String::Empty;
	}
}

void Waypoint_Gasstation1_2::goThere(String a)
{
	GameDataController::gd->setObjective(S("gasstation_thugs_safe"), false);
	GameDataController::gd->setObjective(S("gasstation_spy_mode"), false);
	PlayerController::pc->spawnName = S("Waypoint_Gasstation2_1");
	CurtainController::cc->fadeOut(S("LocationGasstation2"), WalkController::Direction::E, S("walk_e"));
}

void Waypoint_Gasstation1_2::updateState()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && ItemsManager::im->getItem(S("rifle_6"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
	{
		colliderManager->setCollider(-1);
	}
	else
	{
		colliderManager->setCollider(0);
	}
}

void Waypoint_Gasstation1_2::clickAction2()
{
}

void Waypoint_Gasstation1_2::clickAction0()
{
}
