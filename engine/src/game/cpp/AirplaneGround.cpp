#include "../game_all.h"

void AirplaneGround::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airplane_ground");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("shovel"), String::Empty, nullptr, String::Empty));
}

void AirplaneGround::clickAction()
{
	if (usedItem == S("shovel"))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("plane_undig_shovel")), QuestionController::PopupType::QUESTION, [this]() { yesDig(); }, 80, 20);
	}
	else
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("plane_undig_no_shovel")), QuestionController::PopupType::QUESTION, [this]() { yesDig(); }, 120, 20);
	}
}

void AirplaneGround::yesDig()
{
	GameDataController::gd->setObjective(S("plane_undig"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::NULL_, nullptr, SoundsManagerController::sm->digger);
}

void AirplaneGround::updateState()
{
	colliderManager->setCollider(0);
	if (!GameDataController::gd->getObjective(S("plane_undig")))
	{
		ground->set_enabled(true);
		plane->set_enabled(false);
	}
	else
	{
		ground->set_enabled(false);
		plane->set_enabled(true);
		colliderManager->setCollider(-1);
	}
}

void AirplaneGround::clickAction2()
{
}

void AirplaneGround::clickAction0()
{
}

void AirplaneGround::whatOnClick0()
{
}

void AirplaneGround::whatOnClick()
{
}
