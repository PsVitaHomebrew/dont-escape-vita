#include "../game_all.h"

void HunterLodgeTree_Outside::Start()
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
	trans_dir = WalkController::Direction::S_;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ext_cord_place"), String::Empty, nullptr, String::Empty));
	updateState();
}

void HunterLodgeTree_Outside::Update()
{
}

void HunterLodgeTree_Outside::clickAction()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("climb_tree_down")), QuestionController::PopupType::QUESTION, [this]() { climbTree(); });
}

void HunterLodgeTree_Outside::climbTree()
{
	PlayerController::wc->forceAnimation(S("kneel_in_n"));
	Invoke(S("climbTree3"), 0.5f);
}

void HunterLodgeTree_Outside::climbTree3()
{
	PlayerController::pc->spawnName = S("HunterLodgeTree");
	CurtainController::cc->fadeOut(S("HuntersLodgeOutside2"), WalkController::Direction::S_, S("window_jump"));
}

void HunterLodgeTree_Outside::updateState()
{
}

void HunterLodgeTree_Outside::clickAction2()
{
}

void HunterLodgeTree_Outside::clickAction0()
{
}

void HunterLodgeTree_Outside::whatOnClick0()
{
}

void HunterLodgeTree_Outside::whatOnClick()
{
}
