#include "../game_all.h"

void rv_body2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("rv_body2_gas");
	range = 1.0f;
}

void rv_body2::clickAction()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("rv_body2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	Timeline::t->addDialogue(list[0]);
	if (GameDataController::gd->getObjective(S("npc2_joined")))
	{
		for (int i = 1; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
}

void rv_body2::updateState()
{
	colliderManager->setCollider(0);
	if (GameDataController::gd->getCurrentDay() < 3)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			objectName = S("rv_body2_bugs");
			GetComponent<SpriteRenderer>()->set_sprite(bugs);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			objectName = S("rv_body2_gas");
			GetComponent<SpriteRenderer>()->set_sprite(gas);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
		{
			objectName = S("rv_body2_spiders");
			GetComponent<SpriteRenderer>()->set_sprite(spiders);
		}
	}
	else if (GameDataController::gd->getCurrentDay() == 3)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			objectName = S("rv_body2_hot");
			GetComponent<SpriteRenderer>()->set_sprite(heat);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			objectName = S("rv_body2_cold");
			GetComponent<SpriteRenderer>()->set_sprite(ice);
		}
	}
	else
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_sprite(gone);
	}
}

void rv_body2::clickAction2()
{
}

void rv_body2::clickAction0()
{
}

void rv_body2::whatOnClick0()
{
}

void rv_body2::whatOnClick()
{
}
