#include "../game_all.h"

void HuntersLodgeSolar::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("lodge_solar1");
	range = 20.0f;
	actionType = Type::NormalAction;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("broom"), String::Empty, nullptr, String::Empty));
	updateState();
}

void HuntersLodgeSolar::Update()
{
}

void HuntersLodgeSolar::clickAction()
{
	if (GameDataController::gd->getObjective(S("lodge_roof_cleaned")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("lodge_roof_clean")));
	}
	else if (usedItem == String::Empty)
	{
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("lodge_roof"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor());
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
		{
			Vector3 color = Npc3Controller::getColor();
			P<TextFieldController> component2 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
			DialogueController::dc->initDialogue(list, S("lodge_roof_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color, component2, color);
		}
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
	else
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("lodge_swipe_roof")), QuestionController::PopupType::QUESTION, [this]() { swiper(); }, 70, 10);
	}
}

void HuntersLodgeSolar::swiper()
{
	GameDataController::gd->setObjective(S("lodge_roof_cleaned"), true);
	CurtainController::cc->fadeOut();
}

void HuntersLodgeSolar::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 1)
	{
		colliderManager->setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
		blik->set_enabled(false);
		leaves->set_enabled(false);
		return;
	}
	colliderManager->setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	blik->set_enabled(true);
	if (GameDataController::gd->getObjective(S("lodge_roof_cleaned")))
	{
		leaves->set_enabled(false);
		objectName = S("lodge_solar2");
	}
	else
	{
		objectName = S("lodge_solar1");
		leaves->set_enabled(true);
	}
}

void HuntersLodgeSolar::clickAction2()
{
}

void HuntersLodgeSolar::clickAction0()
{
}

void HuntersLodgeSolar::whatOnClick0()
{
}

void HuntersLodgeSolar::whatOnClick()
{
}
