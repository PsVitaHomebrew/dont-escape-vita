#include "../game_all.h"

void RestaurantLeaflet::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e_in");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_leaflet");
	range = 1.0f;
}

void RestaurantLeaflet::clickAction()
{
	ExamineSprite::es->textField->shift.x = -3.0f;
	ExamineSprite::es->textField->shift.y = 50.0f;
	ExamineSprite::es->readyText(List<String>::New({
		GameStrings::getString(GameStrings::world_labels, S("leaflet_1")),
		GameStrings::getString(GameStrings::world_labels, S("leaflet_2")),
		GameStrings::getString(GameStrings::world_labels, S("leaflet_3")),
		GameStrings::getString(GameStrings::world_labels, S("leaflet_4")),
		GameStrings::getString(GameStrings::world_labels, S("leaflet_5")),
		GameStrings::getString(GameStrings::world_labels, S("leaflet_6")),
		GameStrings::getString(GameStrings::world_labels, S("leaflet_7")),
		GameStrings::getString(GameStrings::world_labels, S("leaflet_8")),
		GameStrings::getString(GameStrings::world_labels, S("leaflet_9")),
		GameStrings::getString(GameStrings::world_labels, S("leaflet_10"))
	}), 120, 0.2f, 0.2f, 0.2f, 210.0f / 255.0f, 224.0f / 255.0f, 250.0f / 255.0f, 1.0f);
	if (GameDataController::gd->getCurrentDay() != 2)
	{
		ExamineSprite::es->closingAnimation = S("kneel_e_out");
	}
	else
	{
		ExamineSprite::es->closingAnimation = S("kneel_e_wait");
	}
	ExamineSprite::es->closingAnimationFlip = true;
	ExamineSprite::es->ac = SoundsManagerController::sm->page_turn_02;
	ExamineSprite::es->show(painting, nullptr, nullptr, nullptr, nullptr, [this]() { talkWithCate(); }, false);
}

void RestaurantLeaflet::talkWithCate()
{
	if (GameDataController::gd->getCurrentDay() == 2)
	{
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("cate_restaurant_leaflet"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		list[list.Count() - 1]->action = [this](String p) { getup(p); };
		list[list.Count() - 1]->actionWithText = false;
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		Timeline::t->doNotUnlock = true;
	}
}

void RestaurantLeaflet::getup(String p)
{
	Timeline::t->doNotUnlock = true;
	PlayerController::wc->forceAnimation(S("kneel_e_out"), true);
}

void RestaurantLeaflet::updateState()
{
	colliderManager->setCollider(0);
}

void RestaurantLeaflet::clickAction2()
{
}

void RestaurantLeaflet::clickAction0()
{
}

void RestaurantLeaflet::whatOnClick0()
{
}

void RestaurantLeaflet::whatOnClick()
{
}
