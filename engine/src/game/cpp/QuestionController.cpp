#include "../game_all.h"

void QuestionController::Awake()
{
	if (qc == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		qc = this;
	}
	else if (qc != P<QuestionController>(this))
	{
		Object::Destroy(gameObject);
	}
}

void QuestionController::Start()
{
	darkness = gameObject->transform->Find(S("darkness"))->GetComponent<SpriteRenderer>();
	questionText = gameObject->GetComponent<TextFieldController>();
	yes = gameObject->transform->Find(S("yes"))->GetComponent<Button>();
	no = gameObject->transform->Find(S("no"))->GetComponent<Button>();
	questionText->transform->set_parent(gameObject->transform);
	questionText->container->transform->set_parent(gameObject->transform);
	questionText->transform->set_position(ScreenControler::roundToNearestFullPixel2(questionText->transform->get_position()));
	gameObject->SetActive(false);
	darkness->transform->set_localScale(Vector3(10.0f, 10.0f, 1.0f));
	yes->initButton(S(" "));
	no->initButton(S(" "));
	yes->transform->set_parent(gameObject->transform);
	yes->gameObject->transform->set_parent(gameObject->transform);
	yes->buttonText->transform->set_parent(gameObject->transform);
	yes->buttonText->container->transform->set_parent(gameObject->transform);
	no->transform->set_parent(gameObject->transform);
	no->gameObject->transform->set_parent(gameObject->transform);
	no->buttonText->transform->set_parent(gameObject->transform);
	no->buttonText->container->transform->set_parent(gameObject->transform);
	no->onClick = [this]() { hideQuestion(); };
	questionAsked = false;
}

void QuestionController::showQuestion(String label, QuestionController_PopupType type, Button_Delegate yesClick, int time, int timeSaver, Button_Delegate noClick, String customYesLabel, String customNoLabel, P<Sprite> image)
{
	questionAsked = true;
	if (cursorCont == nullptr)
	{
		initCursor();
	}
	cursorCont->showCursor(CursorController::PixelCursor::NORMAL);
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->keepAlive = false;
	antiDoubleClick = 0.6f;
	timeAdded = 0;
	float num = 0.0f;
	if (time != 0)
	{
		timeAdded = time;
		label += S(" ^^");
		String text;
		if (timeSaver > 0 && GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
		{
			label += GameStrings::getString(GameStrings::warnings, S("time_action_would_take"));
			text = label;
			label = text + S(" ") + time + S(" ") + GameStrings::getString(GameStrings::warnings, S("time_minutes")) + S(".");
			if (GameDataController::gd->getObjective(S("dialogue_ginger_intro")))
			{
				timeAdded -= timeSaver;
				text = label;
				label = text + S(" ^") + GameStrings::getString(GameStrings::warnings, S("time_help1")) + String::Empty + timeSaver + S(" ") + GameStrings::getString(GameStrings::warnings, S("time_minutes")) + String::Empty;
				num += 0.1f;
			}
			if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
			{
				int num2 = (int)((float)timeSaver * 1.5f);
				timeAdded -= num2;
				text = label;
				label = text + S(" ^") + GameStrings::getString(GameStrings::warnings, S("time_help2")) + String::Empty + num2 + S(" ") + GameStrings::getString(GameStrings::warnings, S("time_minutes")) + String::Empty;
				num += 0.1f;
			}
			if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
			{
				int num3 = (int)((float)timeSaver * 0.5f);
				timeAdded -= num3;
				text = label;
				label = text + S(" ^") + GameStrings::getString(GameStrings::warnings, S("time_help3")) + String::Empty + num3 + S(" ") + GameStrings::getString(GameStrings::warnings, S("time_minutes")) + String::Empty;
				num += 0.1f;
			}
			text = label;
			label = text + S(" ^") + GameStrings::getString(GameStrings::warnings, S("time_summary")) + S(" ") + timeAdded + S(" ") + GameStrings::getString(GameStrings::warnings, S("time_minutes")) + S(".");
			num += 0.1f;
		}
		else
		{
			label += GameStrings::getString(GameStrings::warnings, S("time_action_will_take"));
			text = label;
			label = text + S(" ") + time + S(" ") + GameStrings::getString(GameStrings::warnings, S("time_minutes")) + S(".");
		}
		String text2 = GameStrings::getString(GameStrings::gui, S("left_prefix"));
		if (text2.Length() > 0)
		{
			text2 += S(" ");
		}
		String text3 = GameStrings::getString(GameStrings::gui, S("left"));
		if (text3.Length() > 0)
		{
			text3 = S(" ") + text3;
		}
		text = label;
		label = text + S(" ^") + GameStrings::getString(GameStrings::gui, S("time_now")) + S(" ") + ClockController::getClockTime() + S(" (") + text2 + ClockController::getTimeLeft() + text3 + S(")");
		label = label + S(" ^") + GameStrings::getString(GameStrings::warnings, S("time_proceed"));
	}
	questionText->viewText(label, false, true, true, 230);
	questionText->keepAlive = true;
	num = questionText->getChars()[questionText->getChars().Count() - 1]->transform->get_position().y;
	switch (type)
	{
	case PopupType::QUESTION:
		if (customYesLabel != nullptr)
		{
			yes->initButton(customYesLabel);
		}
		else
		{
			yes->initButton(GameStrings::getString(GameStrings::gui, S("yes")).ToUpper());
		}
		if (customNoLabel != nullptr)
		{
			no->initButton(customNoLabel);
		}
		else
		{
			no->initButton(GameStrings::getString(GameStrings::gui, S("no")).ToUpper());
		}
		yes->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(-0.55f, -0.1f + num, yes->transform->get_position().z)));
		no->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(0.55f, -0.1f + num, yes->transform->get_position().z)));
		break;
	case PopupType::STATEMENT:
		if (customYesLabel != nullptr)
		{
			yes->initButton(customYesLabel);
		}
		else
		{
			yes->initButton(GameStrings::getString(GameStrings::gui, S("ok")).ToUpper());
		}
		yes->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(0.0f, -0.1f + num, yes->transform->get_position().z)));
		no->transform->set_position(ScreenControler::roundToNearestFullPixel2(Vector3(9999.0f, 9999.0f, yes->transform->get_position().z)));
		break;
	}
	yes->transform->set_parent(gameObject->transform);
	yes->gameObject->transform->set_parent(gameObject->transform);
	yes->buttonText->transform->set_parent(gameObject->transform);
	yes->buttonText->container->transform->set_parent(gameObject->transform);
	no->transform->set_parent(gameObject->transform);
	no->gameObject->transform->set_parent(gameObject->transform);
	no->buttonText->transform->set_parent(gameObject->transform);
	yes->buttonText->container->transform->set_parent(gameObject->transform);
	qc->gameObject->SetActive(true);
	PlayerController::pc->setBusy(true);
	yes->onClick = [this]() { timeAndHide(); };
	onYesClick = yesClick;
	if (noClick != nullptr)
	{
		no->onClick = [this]() { customNo(); };
		onNoClick = noClick;
	}
	else
	{
		no->onClick = [this]() { hideQuestion(); };
	}
	yes->workIfBusy = false;
	no->workIfBusy = false;
	if (image != nullptr)
	{
		gameObject->GetComponent<SpriteRenderer>()->set_sprite(image);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void QuestionController::timeAndHide()
{
	qc->hideQuestion();
	GameDataController::gd->autoSave();
	if (!ClockController::advanceTime(timeAdded))
	{
		yes->onClick = nullptr;
		onYesClick = nullptr;
	}
	else if (onYesClick != nullptr)
	{
		onYesClick();
	}
}

void QuestionController::customNo()
{
	qc->hideQuestion();
	onNoClick();
}

void QuestionController::initCursor()
{
	cursorCont = GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>();
}

void QuestionController::hideQuestion()
{
	questionAsked = false;
	qc->questionText->dissmiss();
	qc->no->buttonText->dissmiss();
	qc->yes->buttonText->dissmiss();
	qc->gameObject->SetActive(false);
	PlayerController::pc->clickedSomething = true;
	PlayerController::pc->setBusy(false);
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	if (cursorCont == nullptr)
	{
		initCursor();
	}
	cursorCont->showCursor(CursorController::PixelCursor::NORMAL);
	MonoBehaviour::print(S("QUESTION HIDDEN"));
}

void QuestionController::Update()
{
	if (questionAsked)
	{
		if (antiDoubleClick > 0.0f)
		{
			antiDoubleClick -= Time::get_deltaTime();
		}
		else
		{
			yes->workIfBusy = true;
			no->workIfBusy = true;
		}
		if (Input::GetKeyDown(KeyCode::Escape))
		{
			no->onClick();
		}
	}
}
