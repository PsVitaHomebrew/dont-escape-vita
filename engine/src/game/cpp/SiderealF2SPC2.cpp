#include "../game_all.h"

void SiderealF2SPC2::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_pc_off");
	actionType = Type::NormalAction;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("disc1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("disc2"), String::Empty, nullptr, String::Empty));
}

void SiderealF2SPC2::takeBack(String a)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->pyk);
}

void SiderealF2SPC2::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) == 50 && GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) == 10)
	{
		if (usedItem == S("disc1") || usedItem == S("disc2"))
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->disk);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hdd2);
			List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
			DialogueController::dc->initDialogue(list, S("sidereal_disk_comp"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GetComponent<TextFieldController>(), Vector3(1.0f, 0.0f, 0.0f));
			GetComponent<TextFieldController>()->setBGColor(0.5f, 0.0f, 0.0f, 0.5f);
			list[list.Count() - 1]->action = [this](String a) { takeBack(a); };
			for (int i = 0; i < list.Count(); i++)
			{
				Timeline::t->addDialogue(list[i]);
			}
		}
		else
		{
			PlayerController::pc->spawnName = S("SiderealPCExit");
			CurtainController::cc->fadeOut(S("SiderealPC1"), WalkController::Direction::S_);
		}
	}
	else
	{
		P<TimelineAction> timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_pc_off1"));
		timelineAction->actionWithText = false;
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_pc_off2"));
		timelineAction->actionWithText = false;
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>();
		timelineAction->textfield = PlayerController::pc->textField;
		timelineAction->text = GameStrings::getString(GameStrings::actions, S("sidereal_pc_off3"));
		timelineAction->actionWithText = false;
		Timeline::t->addAction(timelineAction);
	}
}

void SiderealF2SPC2::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) == 50 && GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) == 10)
	{
		characterAnimationName = S("stop");
		animationFlip = false;
		useCurrentDirection = true;
		range = 2.0f;
		objectName = S("sidereal_pc_on");
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 50.0f;
		objectName = S("sidereal_pc_off");
	}
}

void SiderealF2SPC2::clickAction2()
{
}

void SiderealF2SPC2::clickAction0()
{
}
