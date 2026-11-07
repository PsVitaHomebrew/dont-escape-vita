#include "../game_all.h"

void RestaurantConspiracy::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e_in");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_conspiracy");
	range = 1.0f;
}

void RestaurantConspiracy::clickAction()
{
	ExamineSprite::es->textField->shift.x = -3.0f;
	ExamineSprite::es->textField->shift.y = 50.0f;
	ExamineSprite::es->readyText(List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("conspiracy1_1")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy1_2")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy1_3")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy1_4")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy1_5")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy1_6")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy1_7")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy1_8")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy1_9")),
		GameStrings::getString(GameStrings::world_labels, S("conspiracy1_10"))
	}), 120, 0.2f, 0.2f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f);
	ExamineSprite::es->closingAnimation = S("kneel_e_out");
	ExamineSprite::es->closingAnimationFlip = true;
	ExamineSprite::es->ac = SoundsManagerController::sm->page_turn_03;
	ExamineSprite::es->show(painting, nullptr, nullptr, nullptr, nullptr, nullptr, false);
}

void RestaurantConspiracy::updateState()
{
	if (!GameDataController::gd->getObjective(S("restaurant_chem_walked")))
	{
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void RestaurantConspiracy::clickAction2()
{
}

void RestaurantConspiracy::clickAction0()
{
}

void RestaurantConspiracy::whatOnClick0()
{
}

void RestaurantConspiracy::whatOnClick()
{
}
