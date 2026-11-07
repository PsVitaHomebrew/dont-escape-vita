#include "../game_all.h"

void RVWaypoint::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("crashsite_tracks");
	doubleClickCondition = S("visited_rv");
	actionType = Type::NormalAction;
	trans_dir = WalkController::Direction::N;
}

void RVWaypoint::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("map_rv_revealed")) == TravelAgency::LOCATION_STATUS_UNDISCOVERED)
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("crashsite_tracks"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		GameDataController::gd->setObjectiveDetail(S("map_rv_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
		updateState();
	}
	else
	{
		PlayerController::pc->setBusy(true);
		PlayerController::pc->spawnName = S("InfoExit");
		CurtainController::cc->fadeOut(S("LocationMap"), WalkController::Direction::E);
	}
}

void RVWaypoint::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("map_rv_revealed")) == TravelAgency::LOCATION_STATUS_UNDISCOVERED)
	{
		range = 40.0f;
		characterAnimationName = S("action_stnd_");
		actionType = Type::NormalAction;
	}
	else
	{
		range = 10.0f;
		characterAnimationName = S("stop");
		actionType = Type::Transition;
	}
	if (GameDataController::gd->getCurrentDay() > 1)
	{
		setCollider(0);
	}
	else
	{
		setCollider(-1);
	}
}

void RVWaypoint::clickAction2()
{
}

void RVWaypoint::clickAction0()
{
}
