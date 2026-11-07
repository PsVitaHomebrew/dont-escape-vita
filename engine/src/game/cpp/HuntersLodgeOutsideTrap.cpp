#include "../game_all.h"

void HuntersLodgeOutsideTrap::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = false;
	characterAnimationName = S("kneel_n");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_papers");
	range = 2.0f;
	updateState();
}

void HuntersLodgeOutsideTrap::clickAction()
{
	if (!GameDataController::gd->getObjective(S("hunters_lodge_trap_cleared")))
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("lodge_back_corpse"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		for (int i = 0; i < list.Count() - 1; i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
		{
			P<DialogueLine> dl = New<DialogueLine>(GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor(), GameStrings::getString(GameStrings::dialogues, S("lodge_back_corpse_barry_1_C")), nullptr);
			Timeline::t->addDialogue(dl);
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
		{
			P<DialogueLine> dl2 = New<DialogueLine>(GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor(), GameStrings::getString(GameStrings::dialogues, S("lodge_back_corpse_cody_1_C")), nullptr);
			Timeline::t->addDialogue(dl2);
		}
		MonoBehaviour::print(String::Concat(ENGINE_TODO_V("list.ToString()", S("System.Collections.Generic.List`1[DialogueLine]")), S(" "), str(list.Count())));
		list[list.Count() - 1]->action = [this](String param) { clearIt(param); };
		Timeline::t->addDialogue(list[list.Count() - 1]);
	}
	else
	{
		pickItUp(String::Empty);
	}
}

void HuntersLodgeOutsideTrap::clearIt(String param)
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("lodge_back_corpse_clear")), QuestionController::PopupType::QUESTION, [this]() { yesClearIt(); }, 30, 5, [this]() { noCliear(); });
}

void HuntersLodgeOutsideTrap::yesClearIt()
{
	PlayerController::pc->setBusy(true);
	GameDataController::gd->setObjective(S("hunters_lodge_trap_cleared"), true);
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::N, S("stop"), nullptr, true, [this]() { doneClearing(); });
}

void HuntersLodgeOutsideTrap::noCliear()
{
	standup(String::Empty);
}

void HuntersLodgeOutsideTrap::doneClearing()
{
	P<DialogueLine> dialogueLine = New<DialogueLine>(PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameStrings::getString(GameStrings::actions, S("lodge_back_corspe_cleared")), [this](String param) { standup(param); });
	dialogueLine->actionWithText = false;
	Timeline::t->addDialogue(dialogueLine);
	Timeline::t->doNotUnlock = true;
}

void HuntersLodgeOutsideTrap::standup(String param)
{
	PlayerController::pc->setBusy(true);
	PlayerController::wc->forceAnimation(S("kneel_out_n"));
}

void HuntersLodgeOutsideTrap::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("bear_trap_3"))))
	{
		GameDataController::gd->setObjective(S("hunters_lodge_trap_picked"), true);
		updateAll();
	}
}

void HuntersLodgeOutsideTrap::whatOnClick()
{
}

void HuntersLodgeOutsideTrap::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 0)
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		corpse->set_enabled(false);
		colliderManager->setCollider(-1);
		characterAnimationName = S("kneel_n");
		pg->started = false;
	}
	else if (!GameDataController::gd->getObjective(S("hunters_lodge_trap_cleared")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		corpse->set_enabled(true);
		colliderManager->setCollider(1);
		characterAnimationName = S("kneel_in_n");
		objectName = S("lodge_back_corpse");
		pg->started = true;
	}
	else if (!GameDataController::gd->getObjective(S("hunters_lodge_trap_picked")))
	{
		actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		corpse->set_enabled(false);
		colliderManager->setCollider(0);
		characterAnimationName = S("kneel_n");
		objectName = S("lodge_back_trap");
		pg->started = false;
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		corpse->set_enabled(false);
		colliderManager->setCollider(-1);
		characterAnimationName = S("kneel_n");
		pg->started = false;
	}
}

void HuntersLodgeOutsideTrap::clickAction2()
{
}

void HuntersLodgeOutsideTrap::clickAction0()
{
}
