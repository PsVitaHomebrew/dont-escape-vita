#include "../game_all.h"

void LocationHouseBDeadBarry::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("dead_barry");
	range = 50.0f;
	teleport = false;
	updateState();
}

void LocationHouseBDeadBarry::Update()
{
}

void LocationHouseBDeadBarry::whatOnClick()
{
}

void LocationHouseBDeadBarry::clickAction()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	String prefix = ((!GameDataController::gd->getObjective(S("dialogue_npc2_house_blocked")) && !GameDataController::gd->getObjective(S("dialogue_npc2_intro"))) ? S("houseb_dead_barry_unknown") : S("houseb_dead_barry_known"));
	DialogueController::dc->initDialogue(list, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	GameDataController::gd->setObjective(S("house_b_dead_barry_commented"), true);
}

void LocationHouseBDeadBarry::updateState()
{
	if (GameDataController::gd->getCurrentDay() > 2 && !GameDataController::gd->getObjective(S("npc2_joined")))
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			GetComponent<SpriteRenderer>()->set_sprite(heat);
			objectName = S("dead_barry_heat");
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_sprite(cold);
			objectName = S("dead_barry_cold");
		}
	}
	else
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void LocationHouseBDeadBarry::clickAction2()
{
}

void LocationHouseBDeadBarry::clickAction0()
{
}
