#include "../game_all.h"

void LocationSiderealF1C_Waypoint_B::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("locked_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_door2");
	range = 2.0f;
}

void LocationSiderealF1C_Waypoint_B::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_f1c_b_open")))
	{
		PlayerController::pc->spawnName = S("LocationSiderealF1B_Waypoint_C");
		CurtainController::cc->fadeOut(S("SiderealF1B"), WalkController::Direction::N);
	}
	else
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_locked_1);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_cody_door_locked")));
	}
}

void LocationSiderealF1C_Waypoint_B::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) != 15 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) != 40)
	{
		setCollider(-1);
		return;
	}
	setCollider(0);
	if (GameDataController::gd->getObjective(S("sidereal_f1c_b_open")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = false;
		objectName = S("sidereal_exit4");
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
	}
	else
	{
		characterAnimationName = S("locked_n");
		animationFlip = false;
		useCurrentDirection = false;
		objectName = S("sidereal_door2");
		actionType = Type::NormalAction;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void LocationSiderealF1C_Waypoint_B::clickAction2()
{
}

void LocationSiderealF1C_Waypoint_B::clickAction0()
{
}

void LocationSiderealF1C_Waypoint_B::pushLittleCart()
{
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("stand_n"), nullptr, false, [this]() { positionThem(); });
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void LocationSiderealF1C_Waypoint_B::positionThem()
{
	GameDataController::gd->setObjective(S("sidereal_f1c_b_open"), true);
	updateAll();
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->currentXY = Vector2(80.0f, 60.0f);
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setSimpleTarget(GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->currentXY);
	Invoke(S("walkDown"), 1.0f);
}

void LocationSiderealF1C_Waypoint_B::walkDown()
{
	Vector3 color = Npc3Controller::getColor();
	P<TextFieldController> component = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("cody_vent_open"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->setSimpleTarget(Vector2(80.0f, 30.0f));
}
