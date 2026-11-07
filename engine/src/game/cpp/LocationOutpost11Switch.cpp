#include "../game_all.h"

void LocationOutpost11Switch::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_switch");
	range = 1.0f;
	teleport = false;
	sr = gameObject->GetComponent<SpriteRenderer>();
	updateState();
	actionType = Type::NormalAction;
	projectorCutscene = false;
}

void LocationOutpost11Switch::Update()
{
	if (projectorCutscene && PlayerController::wc->currentXY.x == 100.0f)
	{
		PlayerController::pc->forceAnimation(S("stand_ne"));
		projectorCutscene = false;
	}
}

void LocationOutpost11Switch::whatOnClick()
{
}

void LocationOutpost11Switch::clickAction()
{
	if (!GameDataController::gd->getObjective(S("outpost_switch_pressed")))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
		GameDataController::gd->setObjective(S("outpost_switch_pressed"), true);
		updateAll();
		GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("GingerWalk"))->transform->get_position());
		GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("BarryWalk"))->transform->get_position());
		GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("CodyWalk"))->transform->get_position());
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_switch_pressed")));
	}
}

void LocationOutpost11Switch::updateState()
{
	if (!GameDataController::gd->getObjective(S("outpost_switch_pressed")))
	{
		characterAnimationName = S("action_n_busy");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
		light1->set_enabled(true);
		light2->set_enabled(false);
		darkness->set_enabled(true);
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 200.0f;
		light1->set_enabled(false);
		light2->set_enabled(true);
		darkness->set_enabled(false);
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void LocationOutpost11Switch::clickAction2()
{
	PlayerController::pc->forceAnimation(S("stand_ne"));
	Invoke(S("rotate1"), 0.2f);
}

void LocationOutpost11Switch::rotate2(String var)
{
	PlayerController::wc->setSimpleTarget(Vector2(100.0f, 45.0f));
	PlayerController::pc->forceAnimation(S("walk_e"));
}

void LocationOutpost11Switch::gingerwalk(String var)
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("GingerWalk"))->transform->get_position());
	GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("BarryWalk"))->transform->get_position());
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("CodyWalk"))->transform->get_position());
}

void LocationOutpost11Switch::rotateLeft(String v)
{
	PlayerController::wc->forceDirection(WalkController::Direction::E);
	PlayerController::wc->forceAnimation(S("stand_se"), true);
	PlayerController::pc->gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
}

void LocationOutpost11Switch::rotateRight(String v)
{
	PlayerController::wc->forceDirection(WalkController::Direction::W);
	PlayerController::wc->forceAnimation(S("stand_ne"));
	PlayerController::pc->gameObject->GetComponent<SpriteRenderer>()->set_flipX(false);
}

void LocationOutpost11Switch::rotate1()
{
	PlayerController::pc->forceAnimation(S("stand_e"));
	projectorCutscene = true;
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("moon_reveal"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	list[10]->action = [this](String s) { rotateLeft(s); };
	list[10]->actionWithText = true;
	list[12]->action = [this](String s) { rotateRight(s); };
	list[12]->actionWithText = true;
	list[17]->action = [this](String s) { rotateLeft(s); };
	list[17]->actionWithText = true;
	list[20]->action = [this](String s) { rotateRight(s); };
	list[20]->actionWithText = true;
	if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
	{
		Vector3 color2 = GingerActionController::getColor();
		Vector3 color3 = Npc2Controller::getColor();
		component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		P<TextFieldController> component2 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
		list.Insert(6, New<DialogueLine>(component2, color3, GameStrings::getString(GameStrings::dialogues, S("outpost_travel_reveal_Barry_1")), nullptr));
		list.Insert(17, New<DialogueLine>(component2, color3, GameStrings::getString(GameStrings::dialogues, S("outpost_travel_reveal_Barry_2")), nullptr));
		DialogueController::dc->initDialogue(list, S("moon_reveal_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color2, component2, color3);
	}
	if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
	{
		Vector3 color4 = GingerActionController::getColor();
		Vector3 color5 = Npc3Controller::getColor();
		P<TextFieldController> component3 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
		list.Insert(6, New<DialogueLine>(component3, color5, GameStrings::getString(GameStrings::dialogues, S("outpost_travel_reveal_Cody_1")), nullptr));
		DialogueController::dc->initDialogue(list, S("moon_reveal_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color4, component3, color5);
	}
	list[2]->action = [this](String s) { rotate2(s); };
	list[3]->action = [this](String s) { gingerwalk(s); };
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void LocationOutpost11Switch::clickAction0()
{
}
