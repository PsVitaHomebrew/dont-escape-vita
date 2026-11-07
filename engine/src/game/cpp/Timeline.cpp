#include "../game_all.h"

void Timeline::Awake()
{
	if (t == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		t = P<Timeline>(this);
	}
	else if (t != P<Timeline>(this))
	{
		Object::Destroy(gameObject);
	}
}

void Timeline::stopChitChat()
{
	MonoBehaviour::print(S("STOP CHIT CHAT!"));
	if (GameObject::Find(S("Ginger")) != nullptr)
	{
		GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->busyTalkingRandomly = false;
	}
	if (actions == nullptr || actions.Count() <= 0)
	{
		return;
	}
	for (int i = 0; i < actions.Count(); i++)
	{
		if (!actions[0]->blockG)
		{
			actions[0]->textfield->keepAlive = false;
			actions[0]->textTime = 0.0f;
			actions[0]->time = 0.0f;
			actions.RemoveAt(0);
			i--;
		}
	}
}

bool Timeline::isSafeToChangeBusy()
{
	if (actions != nullptr && actions.Count() > 0)
	{
		bool result = true;
		for (int i = 0; i < actions.Count(); i++)
		{
			if (actions[0]->blockG)
			{
				result = false;
			}
		}
		return result;
	}
	return t->actions == nullptr || t->actions.Count() == 0;
}

void Timeline::addAction(P<TimelineAction> action)
{
	if (actions == nullptr)
	{
		actions = List<P<TimelineAction>>::New();
	}
	actions.Add(action);
}

void Timeline::addDialogueLines(List<P<DialogueLine>> dl)
{
	for (int i = 0; i < dl.Count(); i++)
	{
		addDialogue(dl[i]);
	}
}

void Timeline::addDialogue(P<DialogueLine> dl, float tTime)
{
	if (PlayerPrefs::GetString(S("lang")) == str(GameStrings::Language::DE))
	{
		defaultTwidth = 130;
	}
	else
	{
		defaultTwidth = 100;
	}
	P<TimelineAction> timelineAction = New<TimelineAction>(dl->source);
	timelineAction->textColor = dl->textColor;
	timelineAction->text = dl->text;
	timelineAction->fast = false;
	timelineAction->blockG = true;
	if (tTime > 0.0f)
	{
		timelineAction->fast = true;
		timelineAction->instant = true;
		timelineAction->blockG = false;
		timelineAction->textTime = tTime;
	}
	else
	{
		t->stopChitChat();
	}
	timelineAction->time = dl->time;
	timelineAction->function = dl->action;
	timelineAction->actionWithText = dl->actionWithText;
	timelineAction->param = dl->actionParam;
	timelineAction->backgroundAlpha = 0.75f;
	addAction(timelineAction);
}

void Timeline::initTextfield()
{
	if (textField == nullptr)
	{
		textField = gameObject->AddComponent<TextFieldController>();
		textField = gameObject->GetComponent<TextFieldController>();
		textField->transform->set_parent(gameObject->transform);
		textField->container->transform->set_parent(gameObject->transform);
		textField->transform->set_position(ScreenControler::roundToNearestFullPixel2(textField->transform->get_position()));
	}
}

void Timeline::Start()
{
	initTextfield();
}

void Timeline::Update()
{
	if (actions == nullptr || actions.Count() <= 0 || !(actions[0]->time >= 0.0f))
	{
		return;
	}
	actions[0]->time -= Time::get_deltaTime();
	if (!(actions[0]->time <= 0.0f))
	{
		return;
	}
	actions[0]->time = 0.0f;
	if (actions[0]->textfield != nullptr && !actions[0]->textDisplayed)
	{
		if (actions[0]->textWidth == -1)
		{
			actions[0]->textWidth = defaultTwidth;
		}
		PlayerController::pc->clickedSomething = false;
		actions[0]->textDisplayed = true;
		if (actions[0] != nullptr && actions[0]->text != nullptr && actions[0]->text.Length() > 0)
		{
			actions[0]->textfield->viewText(actions[0]->text, actions[0]->blockG, actions[0]->fast, actions[0]->instant, actions[0]->textWidth, actions[0]->textColor.x, actions[0]->textColor.y, actions[0]->textColor.z, actions[0]->backgroundColor.x, actions[0]->backgroundColor.y, actions[0]->backgroundColor.z, actions[0]->backgroundAlpha);
			if (actions[0]->blockG || actions[0]->textTime > 0.0f)
			{
				actions[0]->textfield->keepAlive = true;
			}
		}
	}
	if (!actions[0]->blockG && actions[0]->textTime > 0.0f)
	{
		actions[0]->textTime -= Time::get_deltaTime();
	}
	else if (!actions[0]->blockG && actions[0]->textTime <= 0.0f)
	{
		actions[0]->textfield->keepAlive = false;
	}
	if (actions[0]->actionWithText)
	{
		functionLaunch();
	}
	if (actions[0]->textfield == nullptr || (actions[0]->textfield != nullptr && !actions[0]->textfield->keepAlive))
	{
		proceedWithPurpose();
	}
}

void Timeline::functionLaunch()
{
	if (actions[0]->function != nullptr)
	{
		actions[0]->function(actions[0]->param);
		actions[0]->function = nullptr;
	}
}

void Timeline::proceedWithPurpose()
{
	functionLaunch();
	actions.RemoveAt(0);
	int num = GameDataController::gd->getObjectiveDetail(S("chitchat"));
	if (num > -5)
	{
		num = -5;
	}
	GameDataController::gd->setObjectiveDetail(S("chitchat"), num);
	if (!doNotUnlock)
	{
		PlayerController::pc->setBusy(false);
	}
	doNotUnlock = false;
}

void Timeline::killText()
{
	actions[0]->textfield->terminate();
}
