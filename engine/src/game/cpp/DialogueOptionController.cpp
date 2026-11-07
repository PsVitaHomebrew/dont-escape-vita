#include "../game_all.h"

void DialogueOptionController::Start()
{
	lines = List<P<DialogueLine>>::New();
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	alphaSet = false;
	cc = GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>();
	hide();
	background->transform->set_position(Vector3(gameObject->transform->get_position().x, gameObject->transform->get_position().y, background->transform->get_position().z));
	number *= 10;
	if (audioSource == nullptr)
	{
		if (GameObject::Find(S("static_dust"))->GetComponent<AudioSource>() == nullptr)
		{
			audioSource = GameObject::Find(S("static_dust"))->AddComponent<AudioSource>();
			audioSource->set_ignoreListenerPause(true);
			audioSource->set_ignoreListenerVolume(true);
		}
		else
		{
			audioSource = GameObject::Find(S("static_dust"))->GetComponent<AudioSource>();
		}
	}
}

void DialogueOptionController::Update()
{
	if (rend == nullptr)
	{
		rend = gameObject->GetComponent<SpriteRenderer>();
	}
	if (backgroundRend == nullptr)
	{
		backgroundRend = background->GetComponent<SpriteRenderer>();
	}
	if (localCooldown > 0.0f)
	{
		localCooldown -= 1.0f * Time::get_deltaTime() * 60.0f;
	}
	float num = (float)maxCooldown - localCooldown + (float)number;
	num /= (float)maxCooldown + (float)number;
	num *= num;
	rend->set_color(Color(num, num, num, num));
	backgroundRend->set_color(Color(num, num, num, num));
}

void DialogueOptionController::OnMouseEnter()
{
	Vector3 position = Vector3(gameObject->transform->get_position().x, gameObject->transform->get_position().y, DialogueController::dc->frame->transform->get_position().z);
	DialogueController::dc->frame->transform->set_position(position);
	if (PlayerController::pc->dialogue != PlayerController::DialogueState::NONE || DialogueController::dc->cooldown != 0.0f)
	{
		return;
	}
	if (cc == nullptr)
	{
		cc = GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>();
	}
	cc->showCursor(CursorController::PixelCursor::ACTIVE);
	DialogueController::dc->frame->GetComponent<SpriteRenderer>()->set_enabled(true);
	if (audioSource == nullptr)
	{
		if (GameObject::Find(S("static_dust"))->GetComponent<AudioSource>() == nullptr)
		{
			audioSource = GameObject::Find(S("static_dust"))->AddComponent<AudioSource>();
			audioSource->set_ignoreListenerPause(true);
			audioSource->set_ignoreListenerVolume(true);
		}
		else
		{
			audioSource = GameObject::Find(S("static_dust"))->GetComponent<AudioSource>();
		}
	}
	audioSource->set_volume((float)PlayerPrefs::GetInt(S("sound")) / 100.0f);
	audioSource->PlayOneShot(SoundsManagerController::sm->ui_hover);
	DialogueController::dc->bottomTextfield->viewText(caption, false, true, false, ObjectActionController::BOTTOM_TEXT_WIDTH);
}

void DialogueOptionController::OnMouseDown()
{
	PlayerController::pc->clickedSomething = true;
	if (PlayerController::pc->dialogue != PlayerController::DialogueState::NONE || DialogueController::dc->cooldown != 0.0f)
	{
		return;
	}
	for (int i = 0; i < lines.Count(); i++)
	{
		if (lines[i]->text.Length() > 0)
		{
			PlayerController::pc->setBusy(true);
			PlayerController::pc->dialogue = PlayerController::DialogueState::WAIT_TO_SPEED;
		}
		Timeline::t->addDialogue(lines[i]);
	}
	if (audioSource == nullptr)
	{
		if (GameObject::Find(S("static_dust"))->GetComponent<AudioSource>() == nullptr)
		{
			audioSource = GameObject::Find(S("static_dust"))->AddComponent<AudioSource>();
			audioSource->set_ignoreListenerPause(true);
			audioSource->set_ignoreListenerVolume(true);
		}
		else
		{
			audioSource = GameObject::Find(S("static_dust"))->GetComponent<AudioSource>();
		}
	}
	audioSource->set_volume((float)PlayerPrefs::GetInt(S("sound")) / 100.0f);
	audioSource->PlayOneShot(SoundsManagerController::sm->ui_click, 0.5f);
	DialogueController::dc->cooldown = DialogueController::dc->maxCooldown;
	if (objective.Length() > 0)
	{
		GameDataController::gd->setObjective(objective, true);
	}
	objective = String::Empty;
	DialogueController::dc->frame->GetComponent<SpriteRenderer>()->set_enabled(false);
}

void DialogueOptionController::OnMouseOver()
{
	if (PlayerController::pc->dialogue == PlayerController::DialogueState::NONE && DialogueController::dc->cooldown == 0.0f)
	{
		if (cc == nullptr)
		{
			cc = GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>();
		}
		cc->showCursor(CursorController::PixelCursor::ACTIVE);
		DialogueController::dc->frame->GetComponent<SpriteRenderer>()->set_enabled(true);
		if (DialogueController::dc->bottomTextfield->get_TypedText().Length() == 0)
		{
			DialogueController::dc->bottomTextfield->viewText(caption, false, true, false, ObjectActionController::BOTTOM_TEXT_WIDTH);
		}
	}
}

void DialogueOptionController::OnMouseExit()
{
	DialogueController::dc->frame->GetComponent<SpriteRenderer>()->set_enabled(false);
	GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController::PixelCursor::NORMAL);
	P<GameObject> gameObject = GameObject::Find(S("BottomText"));
	gameObject->GetComponent<TextFieldController>()->keepAlive = false;
	DialogueController::dc->bottomTextfield->dissmiss(true);
}

void DialogueOptionController::setObjective(String ob)
{
	objective = ob;
	if (objective != String::Empty && GameDataController::gd->getObjective(objective))
	{
		background->GetComponent<SpriteRenderer>()->set_sprite(DialogueController::dc->frameOld);
	}
	else
	{
		background->GetComponent<SpriteRenderer>()->set_sprite(DialogueController::dc->frameNew);
	}
}

void DialogueOptionController::show()
{
	rend->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
	backgroundRend->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
	localCooldown = maxCooldown + number;
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	gameObject->GetComponent<BoxCollider2D>()->set_enabled(true);
	background->GetComponent<SpriteRenderer>()->set_enabled(true);
	active = true;
}

void DialogueOptionController::hide()
{
	localCooldown = maxCooldown + number;
	active = false;
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	gameObject->GetComponent<BoxCollider2D>()->set_enabled(false);
	background->GetComponent<SpriteRenderer>()->set_enabled(false);
	background->GetComponent<SpriteRenderer>()->set_sprite(DialogueController::dc->frameNew);
}

void DialogueOptionController::initDialogue(List<P<DialogueLine>> dialogueLines, String prefix, P<TextFieldController> tf_a, Vector3 color_a, P<TextFieldController> tf_b, Vector3 color_b, P<TextFieldController> tf_c, Vector3 color_c)
{
	int num = 0;
	String text = GameStrings::getString(GameStrings::dialogues, prefix + num + S("_a"));
	String text2 = GameStrings::getString(GameStrings::dialogues, prefix + num + S("_b"));
	String t = String::Empty;
	P<TextFieldController> src = nullptr;
	Vector3 tC = Vector3(1.0f, 1.0f, 1.0f);
	if (text.IndexOf(S("_STRING_MISSING")) == -1)
	{
		t = text;
		src = tf_a;
		tC = color_a;
	}
	if (text2.IndexOf(S("_STRING_MISSING")) == -1)
	{
		t = text2;
		src = tf_b;
		tC = color_b;
	}
	dialogueLines.Add(New<DialogueLine>(src, tC, t, nullptr));
}
