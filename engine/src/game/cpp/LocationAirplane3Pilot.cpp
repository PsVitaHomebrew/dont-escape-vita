#include "../game_all.h"

void LocationAirplane3Pilot::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n_busy2");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("airplane_pilot");
	range = 1.0f;
}

void LocationAirplane3Pilot::clickAction()
{
	if (!GameDataController::gd->getObjective(S("plane_pilot_searched")))
	{
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			Vector3 color = GingerActionController::getColor();
			P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
			Vector3 color2 = Npc3Controller::getColor();
			P<TextFieldController> component2 = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
			List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
			if (GameDataController::gd->getObjectiveDetail(S("plane_pilot_searched")) == 0)
			{
				DialogueController::dc->initDialogue(list, S("airplane_cody_a"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color, component2, color2);
				for (int i = 0; i < list.Count() - 1; i++)
				{
					Timeline::t->addDialogue(list[i]);
				}
				Timeline::t->addDialogue(list[list.Count() - 1]);
				GameDataController::gd->setObjectiveDetail(S("plane_pilot_searched"), 1);
			}
			else if (GameDataController::gd->getObjectiveDetail(S("plane_pilot_searched")) == 1)
			{
				DialogueController::dc->initDialogue(list, S("airplane_cody_b"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color, component2, color2);
				for (int j = 0; j < list.Count() - 1; j++)
				{
					Timeline::t->addDialogue(list[j]);
				}
				Timeline::t->addDialogue(list[list.Count() - 1]);
				GameDataController::gd->setObjectiveDetail(S("plane_pilot_searched"), 2);
			}
			else if (GameDataController::gd->getObjectiveDetail(S("plane_pilot_searched")) == 2)
			{
				DialogueController::dc->initDialogue(list, S("airplane_cody_c"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color, component2, color2);
				list[1]->action = [this](String a) { rotate(a); };
				list[1]->actionWithText = true;
				for (int k = 0; k < list.Count() - 1; k++)
				{
					Timeline::t->addDialogue(list[k]);
				}
				Timeline::t->addDialogue(list[list.Count() - 1]);
				GameDataController::gd->setObjectiveDetail(S("plane_pilot_searched"), 3);
			}
			else
			{
				QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("search_body_plane")), QuestionController_PopupType::QUESTION, [this]() { pickItUp1(); }, 0, 0, nullptr, nullptr, GameStrings::getString(GameStrings::warnings, S("search_body_plane_no")));
			}
		}
		else
		{
			pickItUp();
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("airplane_pilot_dead")));
	}
	updateState();
}

void LocationAirplane3Pilot::rotate(String a)
{
	PlayerController::wc->forceAnimation(S("stand_se"), true);
}

void LocationAirplane3Pilot::pickItUp()
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("manifest"))))
	{
		GameDataController::gd->setObjective(S("plane_pilot_searched"), true);
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("airplane_manifest_picked")));
	}
}

void LocationAirplane3Pilot::pickItUp1()
{
	PlayerController::wc->forceAnimation(S("action_n"));
	pickItUp();
}

void LocationAirplane3Pilot::updateState()
{
	if (!GameDataController::gd->getObjective(S("plane_pilot_searched")))
	{
		characterAnimationName = S("action_n_busy2");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
	}
	if (!GameDataController::gd->getObjective(S("plane_pilot_searched")))
	{
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			if (GameDataController::gd->getObjectiveDetail(S("plane_pilot_searched")) == 0)
			{
				characterAnimationName = S("action_stnd_");
				animationFlip = false;
				useCurrentDirection = true;
				range = 15.0f;
			}
			else if (GameDataController::gd->getObjectiveDetail(S("plane_pilot_searched")) == 1)
			{
				characterAnimationName = S("action_stnd_");
				animationFlip = false;
				useCurrentDirection = true;
				range = 5.0f;
			}
			else if (GameDataController::gd->getObjectiveDetail(S("plane_pilot_searched")) == 2)
			{
				characterAnimationName = S("action_n_busy2");
				animationFlip = false;
				useCurrentDirection = false;
				range = 1.0f;
			}
			else
			{
				characterAnimationName = S("action_stnd_n");
				animationFlip = false;
				useCurrentDirection = false;
				range = 1.0f;
			}
		}
		else
		{
			characterAnimationName = S("action_n");
			animationFlip = false;
			useCurrentDirection = false;
			range = 1.0f;
		}
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 100.0f;
	}
}

void LocationAirplane3Pilot::clickAction2()
{
}

void LocationAirplane3Pilot::clickAction0()
{
}

void LocationAirplane3Pilot::whatOnClick0()
{
}

void LocationAirplane3Pilot::whatOnClick()
{
}
