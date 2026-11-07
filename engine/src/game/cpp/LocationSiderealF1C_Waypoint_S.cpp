#include "../game_all.h"

void LocationSiderealF1C_Waypoint_S::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("pull2_w");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_pipe");
	range = 3.0f;
}

void LocationSiderealF1C_Waypoint_S::clickAction()
{
	if (GameDataController::gd->getObjective(S("sidereal_barry_pipe_moved")))
	{
		if (GameDataController::gd->getObjective(S("sidereal_f1c_s_open")))
		{
			PlayerController::pc->spawnName = S("LocationSiderealF1S_Waypoint_C");
			CurtainController::cc->fadeOut(S("SiderealF1S"), WalkController::Direction::W);
		}
		else
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_door_open);
			GameDataController::gd->setObjective(S("sidereal_f1c_s_open"), true);
			updateAll();
		}
	}
}

void LocationSiderealF1C_Waypoint_S::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) != 15 || GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) != 40)
	{
		setCollider(-1);
		return;
	}
	if (GameDataController::gd->getObjective(S("sidereal_barry_pipe_moved")))
	{
		actionMarker = actionMarker2;
		setCollider(1);
		if (GameDataController::gd->getObjective(S("sidereal_f1c_s_open")))
		{
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(open);
			characterAnimationName = S("stop");
			animationFlip = false;
			useCurrentDirection = true;
			objectName = S("sidereal_exit4");
			actionType = Type::Transition;
			trans_dir = WalkController::Direction::W;
		}
		else
		{
			characterAnimationName = S("open_door2");
			animationFlip = true;
			useCurrentDirection = false;
			objectName = S("sidereal_door2");
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(door);
			actionType = Type::NormalAction;
		}
	}
	else
	{
		characterAnimationName = S("pull2_w");
		animationFlip = false;
		useCurrentDirection = false;
		objectName = S("sidereal_pipe");
		actionType = Type::NormalAction;
		actionMarker = actionMarker1;
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(pipe);
		setCollider(0);
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void LocationSiderealF1C_Waypoint_S::clickAction2()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("sidereal_pipe_too_heavy")), true);
	GameDataController::gd->setObjective(S("sidereal_pipe_tried"), true);
}

void LocationSiderealF1C_Waypoint_S::clickAction0()
{
}

void LocationSiderealF1C_Waypoint_S::pushLittleCart()
{
	GameDataController::gd->setObjective(S("sidereal_barry_pipe_moved"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::SW, S("stand_se"), nullptr, true, [this]() { positionThem(); });
	pipeobs->set_enabled(false);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->metal_moan);
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void LocationSiderealF1C_Waypoint_S::positionThem()
{
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	PlayerController::pc->setBusy(false);
	GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->currentXY = Vector2(40.0f, 35.0f);
	GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->setSimpleTarget(GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->currentXY);
	GameObject::Find(S("Player"))->GetComponent<WalkController>()->currentXY = Vector2(55.0f, 45.0f);
	GameObject::Find(S("Player"))->GetComponent<WalkController>()->setSimpleTarget(GameObject::Find(S("Player"))->GetComponent<WalkController>()->currentXY);
}
