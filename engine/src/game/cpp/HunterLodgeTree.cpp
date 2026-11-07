#include "../game_all.h"

void HunterLodgeTree::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_tree");
	range = 1.0f;
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ext_cord_place"), String::Empty, nullptr, String::Empty));
	updateState();
}

void HunterLodgeTree::Update()
{
}

void HunterLodgeTree::clickAction()
{
	if (usedItem == String::Empty)
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("climb_tree")), QuestionController::PopupType::QUESTION, [this]() { climbTree(); }, 5);
	}
	else
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("climb_tree_cord")), QuestionController::PopupType::QUESTION, [this]() { climbTree2(); }, 10);
	}
}

void HunterLodgeTree::climbTree()
{
	PlayerController::wc->forceAnimation(S("climb_se"));
	Invoke(S("climbTree3"), 0.5f);
}

void HunterLodgeTree::climbTree3()
{
	PlayerController::pc->spawnName = S("HunterLodgeTree_Outside");
	CurtainController::cc->fadeOut(S("HuntersLodgeTree"), WalkController::Direction::S_, S("kneel_out_n"));
}

void HunterLodgeTree::climbTree2()
{
	GameDataController::gd->setObjective(S("lodge_cord_climbed"), true);
	climbTree();
}

void HunterLodgeTree::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 1)
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
		blocker->set_enabled(false);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	}
	else
	{
		colliderManager->setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		blocker->set_enabled(true);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	}
}

void HunterLodgeTree::clickAction2()
{
}

void HunterLodgeTree::clickAction0()
{
}

void HunterLodgeTree::whatOnClick0()
{
}

void HunterLodgeTree::whatOnClick()
{
}
