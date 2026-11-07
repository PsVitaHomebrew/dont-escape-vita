#include "../game_all.h"

void WaypointHouseB1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_waypoint1");
	actionType = Type::Transition;
	doubleClickCondition = S("visited_house_b_back");
	trans_dir = WalkController::Direction::N;
}

void WaypointHouseB1::clickAction()
{
	if (!GameDataController::gd->getObjective(S("day2_complete")) && !GameDataController::gd->getObjective(S("npc2_wife_note_given")) && !GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
	{
		int num = GameDataController::gd->getObjectiveDetail(S("dialogue_npc2_house_blocked"));
		if (num < 4)
		{
			num++;
		}
		Vector3 color = Npc2Controller::getColor();
		P<TextFieldController> component = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
		Vector3 color2 = GingerActionController::getColor();
		P<TextFieldController> component2 = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("npc2_block_house") + num, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color, component2, color2);
		GameDataController::gd->setObjectiveDetail(S("dialogue_npc2_house_blocked"), num);
		list[0]->action = [this](String var) { turnAround(var); };
		list[0]->actionWithText = false;
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
	else
	{
		PlayerController::pc->spawnName = S("WaypointHouseBBack0");
		CurtainController::cc->fadeOut(S("LocationHouseBBack"), WalkController::Direction::E);
	}
}

void WaypointHouseB1::turnAround(String var)
{
	PlayerController::wc->forceAnimation(S("action_stnd_se"));
}

void WaypointHouseB1::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("day2_complete")) && !GameDataController::gd->getObjective(S("npc2_wife_note_given")) && !GameDataController::gd->getObjective(S("dialogue_ginger_barry_distracted")))
	{
		doubleClickCondition = String::Empty;
		range = 20.0f;
	}
	else
	{
		doubleClickCondition = S("visited_house_b_back");
		range = 1.0f;
	}
}

void WaypointHouseB1::clickAction2()
{
}

void WaypointHouseB1::clickAction0()
{
}
