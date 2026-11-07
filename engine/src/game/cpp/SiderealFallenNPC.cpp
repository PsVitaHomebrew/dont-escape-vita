#include "../game_all.h"

void SiderealFallenNPC::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = true;
	characterAnimationName = S("action_stnd_");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("npc_cody");
	range = 2.0f;
	updateState();
}

void SiderealFallenNPC::bury()
{
	GameDataController::Achievement(S("S_GRAVE"));
	GameDataController::gd->setObjective(S("sidereal_npc_buried"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, nullptr, nullptr, false, [this]() { cateTalk(); });
}

void SiderealFallenNPC::cateTalk()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	Vector3 color = GingerActionController::getColor();
	DialogueController::dc->initDialogue(list, S("cate_after_sidereal_burial1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color);
	if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
	{
		Vector3 color2 = Npc2Controller::getColor();
		P<TextFieldController> component = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("cate_after_sidereal_burial2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color, component, color2);
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
	{
		Vector3 color3 = Npc3Controller::getColor();
		P<TextFieldController> component2 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("cate_after_sidereal_burial3"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color, component2, color3);
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void SiderealFallenNPC::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_npc_buried")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("npc_grave")));
	}
	else if (GameDataController::gd->getObjective(S("dialogue_ginger_reunited")))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("sidereal_burial")), QuestionController::PopupType::QUESTION, [this]() { bury(); }, 30, 6);
	}
	else if (!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("poor_barry")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("poor_cody")));
	}
}

void SiderealFallenNPC::whatOnClick()
{
}

void SiderealFallenNPC::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_npc_buried")))
	{
		setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(grave);
		objectName = S("npc_grave");
	}
	else if (!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 1)
	{
		setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(barry);
		objectName = S("npc_barry");
	}
	else if (!GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 1)
	{
		setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(cody);
		objectName = S("npc_cody");
	}
	else
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void SiderealFallenNPC::clickAction2()
{
}

void SiderealFallenNPC::clickAction0()
{
}
