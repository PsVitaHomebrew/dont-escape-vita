#include "../game_all.h"

void DialogueController::Awake()
{
	if (dc == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		dc = this;
	}
	else if (dc != P<DialogueController>(this))
	{
		Object::Destroy(gameObject);
	}
}

void DialogueController::ShowText(String text)
{
	upperTextfield->center = true;
	upperTextfield->shift = Vector2(0.0f, 0.0f);
	upperTextfield->viewText(text, false, true, true, 230);
	upperTextfield->keepAlive = true;
}

void DialogueController::HideText()
{
	upperTextfield->dissmiss();
}

void DialogueController::Start()
{
	talking = false;
	hidden = true;
	frame->GetComponent<SpriteRenderer>()->set_enabled(false);
	cooldown = maxCooldown;
	bottomTextfield = GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>();
	darkness = gameObject->transform->Find(S("darkness"))->GetComponent<SpriteRenderer>();
	darkness->set_color(Color(0.0f, 0.0f, 0.0f, darknessAlpha));
	transform->set_position(Vector3(0.0f, 0.0f, -4.5f));
	darkness->transform->set_position(Vector3(0.0f, 0.0f, -4.2f));
	if (upperTextfield == nullptr)
	{
		upperTextGameObject = New<GameObject>();
		upperTextfield = upperTextGameObject->AddComponent<TextFieldController>();
		upperTextGameObject->transform->set_parent(gameObject->transform);
		upperTextfield->container->transform->set_parent(upperTextGameObject->transform);
		upperTextGameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(upperTextGameObject->transform->get_position()));
	}
}

void DialogueController::quickDialogue(Vector3 color, P<NPCActionController> who, String what)
{
	P<TextFieldController> component = who->gameObject->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	dc->initDialogue(list, what, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void DialogueController::Update()
{
	if (bottomTextfield == nullptr)
	{
		bottomTextfield = GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>();
	}
	if (!hidden && (PlayerController::pc->dialogue != PlayerController::DialogueState::NONE || (Timeline::t->actions != nullptr && Timeline::t->actions.Count() > 0)))
	{
		hide();
	}
	else if (!hidden && !talking)
	{
		hide();
	}
	else if (hidden && talking && PlayerController::pc->dialogue == PlayerController::DialogueState::NONE && (Timeline::t->actions == nullptr || Timeline::t->actions.Count() == 0))
	{
		show();
	}
	if (!hidden)
	{
		if (darknessAlpha < targetAlpha)
		{
			darknessAlpha += 0.75f * Time::get_deltaTime() * 1.5f;
		}
		if (darknessAlpha > targetAlpha)
		{
			darknessAlpha = targetAlpha;
		}
		PlayerController::pc->setBusy(true);
		if (cooldown > 0.0f)
		{
			cooldown -= 1.0f * Time::get_deltaTime() * 60.0f;
			if (cooldown < 0.0f)
			{
				cooldown = 0.0f;
			}
		}
	}
	else
	{
		if (darknessAlpha > 0.0f)
		{
			darknessAlpha -= 1.5f * Time::get_deltaTime() * 1.5f;
		}
		if (darknessAlpha < 0.0f)
		{
			darknessAlpha = 0.0f;
		}
	}
	if (lastDarknessAlpha != darknessAlpha)
	{
		darkness->set_color(Color(targetColor, targetColor, targetColor, darknessAlpha));
		lastDarknessAlpha = darknessAlpha;
	}
}

void DialogueController::show()
{
	if (bottomTextfield == nullptr)
	{
		bottomTextfield = GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>();
	}
	if (callback != nullptr)
	{
		callback();
	}
	hidden = false;
	for (int i = 0; i < dialogueOptions.Length(); i++)
	{
		if (dialogueOptions[i]->GetComponent<DialogueOptionController>()->caption != String::Empty)
		{
			dialogueOptions[i]->GetComponent<DialogueOptionController>()->show();
		}
	}
	cooldown = maxCooldown;
	if (GameObject::Find(S("Location"))->GetComponent<LocationManager>()->showInventory)
	{
		InventoryButtonController::ibc->hide();
	}
	if (GameObject::Find(S("journal")) != nullptr)
	{
		GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->hide();
	}
}

void DialogueController::hide()
{
	hidden = true;
	HideText();
	for (int i = 0; i < dialogueOptions.Length(); i++)
	{
		dialogueOptions[i]->GetComponent<DialogueOptionController>()->hide();
	}
	if (!talking)
	{
		if (GameObject::Find(S("Location"))->GetComponent<LocationManager>()->showInventory)
		{
			InventoryButtonController::ibc->showFinal();
		}
		if (GameObject::Find(S("journal")) != nullptr)
		{
			GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->showFinal();
		}
	}
}

void DialogueController::reset()
{
	MonoBehaviour::print(S("RESETTING DIALOGUE OPTIONS... All ") + dialogueOptions.Length() + S(" of them."));
	for (int i = 0; i < dialogueOptions.Length(); i++)
	{
		dialogueOptions[i]->GetComponent<DialogueOptionController>()->caption = String::Empty;
	}
}

void DialogueController::initDialogue(List<P<DialogueLine>> dialogueLines, String prefix, P<TextFieldController> tf_a, Vector3 color_a, P<TextFieldController> tf_b, Vector3 color_b, P<TextFieldController> tf_c, Vector3 color_c, P<Sprite> background)
{
	if (background != nullptr)
	{
		darkness->set_color(Color(1.0f, 1.0f, 1.0f, darknessAlpha));
		transform->set_position(Vector3(0.0f, 0.0f, -4.5f));
		darkness->transform->set_position(Vector3(0.0f, 0.0f, -4.2f));
		darkness->GetComponent<SpriteRenderer>()->set_sprite(background);
		darkness->gameObject->transform->set_localScale(Vector3(1.0f, 1.0f, 1.0f));
		targetAlpha = 1.0f;
		targetColor = 1.0f;
	}
	else
	{
		targetColor = 0.0f;
		targetAlpha = 0.5f;
		darkness->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Misc/black")));
		darkness->gameObject->transform->set_localScale(Vector3(10.0f, 10.0f, 1.0f));
		darkness->set_color(Color(0.0f, 0.0f, 0.0f, darknessAlpha));
	}
	bool flag = false;
	int num = 1;
	if (prefix == String::Empty)
	{
		dialogueLines.Add(New<DialogueLine>(tf_a, color_a, String::Empty, nullptr));
		dialogueLines[dialogueLines.Count() - 1]->displayText = false;
		return;
	}
	do
	{
		String text = GameStrings::getString(GameStrings::dialogues, prefix + S("_") + num + S("_a"));
		String text2 = GameStrings::getString(GameStrings::dialogues, prefix + S("_") + num + S("_b"));
		String text3 = GameStrings::getString(GameStrings::dialogues, prefix + S("_") + num + S("_c"));
		String empty = String::Empty;
		P<TextFieldController> textFieldController = nullptr;
		Vector3 vector = Vector3(1.0f, 1.0f, 1.0f);
		if (text.IndexOf(S("_STRING_MISSING")) == -1)
		{
			empty = text;
			textFieldController = tf_a;
			vector = color_a;
			dialogueLines.Add(New<DialogueLine>(textFieldController, vector, empty, nullptr));
		}
		else if (text2.IndexOf(S("_STRING_MISSING")) == -1)
		{
			empty = text2;
			textFieldController = tf_b;
			vector = color_b;
			dialogueLines.Add(New<DialogueLine>(textFieldController, vector, empty, nullptr));
		}
		else if (text3.IndexOf(S("_STRING_MISSING")) == -1)
		{
			empty = text3;
			textFieldController = tf_c;
			vector = color_c;
			dialogueLines.Add(New<DialogueLine>(textFieldController, vector, empty, nullptr));
		}
		else
		{
			flag = true;
		}
		num++;
	}
	while (!flag);
}
