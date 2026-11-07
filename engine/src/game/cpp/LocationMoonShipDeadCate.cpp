#include "../game_all.h"

void LocationMoonShipDeadCate::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_ne");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("npc_cathy");
	range = 1.0f;
	Vector2 vector = ScreenControler::gameToScreen(Vector2(120.0f, 67.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	tf->transform->set_position(position);
}

void LocationMoonShipDeadCate::playerStandUp(String v)
{
	Timeline::t->doNotUnlock = true;
	PlayerController::pc->forceAnimation(S("kneel_out_n"));
}

void LocationMoonShipDeadCate::lookAtMe(String s)
{
	GetComponent<SpriteRenderer>()->set_sprite(ded2);
}

void LocationMoonShipDeadCate::stopLooking(String s)
{
	GetComponent<SpriteRenderer>()->set_sprite(ded);
	if (GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("moon_shocked2")))
	{
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->setBusy(false);
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("barry_walk"))->transform->get_position());
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("moon_shocked3")))
	{
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setBusy(false);
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("cody_walk"))->transform->get_position());
	}
}

void LocationMoonShipDeadCate::clickAction()
{
	if (!GameDataController::gd->getObjective(S("moon_shocked1")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moon_dead_cate")));
		return;
	}
	GameDataController::gd->setObjective(S("moon_shocked1"), false);
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("moon_dead_cate1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tf, GingerActionController::getColor());
	list[2]->action = [this](String s) { lookAtMe(s); };
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	if (GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjective(S("npc3_alive")))
	{
		list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("moon_dead_cate_both"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tf, GingerActionController::getColor());
		for (int j = 0; j < list.Count(); j++)
		{
			Timeline::t->addDialogue(list[j]);
		}
	}
	if (GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("npc3_alive")))
	{
		list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("moon_dead_cate_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tf, GingerActionController::getColor());
		for (int k = 0; k < list.Count(); k++)
		{
			Timeline::t->addDialogue(list[k]);
		}
	}
	if (!GameDataController::gd->getObjective(S("npc2_alive")) && GameDataController::gd->getObjective(S("npc3_alive")))
	{
		list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("moon_dead_cate_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tf, GingerActionController::getColor());
		for (int l = 0; l < list.Count(); l++)
		{
			Timeline::t->addDialogue(list[l]);
		}
	}
	list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("moon_dead_cate2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tf, GingerActionController::getColor());
	list[list.Count() - 3]->action = [this](String s) { stopLooking(s); };
	for (int m = 0; m < list.Count(); m++)
	{
		Timeline::t->addDialogue(list[m]);
	}
	if (GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("moon_shocked2")))
	{
		list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("moon_dead_cate3_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor());
		for (int n = 0; n < list.Count(); n++)
		{
			Timeline::t->addDialogue(list[n]);
		}
	}
	if (GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("moon_shocked3")))
	{
		list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("moon_dead_cate3_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
		for (int num = 0; num < list.Count(); num++)
		{
			Timeline::t->addDialogue(list[num]);
		}
	}
}

void LocationMoonShipDeadCate::updateState()
{
	if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(alive_);
		setCollider(-1);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(ded);
		setCollider(0);
	}
	characterAnimationName = S("action_stnd_ne");
	if (GameDataController::gd->getObjective(S("moon_suited_up")))
	{
		characterAnimationName = S("suit_action_stnd_ne");
	}
}

void LocationMoonShipDeadCate::clickAction2()
{
}

void LocationMoonShipDeadCate::clickAction0()
{
}

void LocationMoonShipDeadCate::whatOnClick0()
{
}

void LocationMoonShipDeadCate::whatOnClick()
{
}
