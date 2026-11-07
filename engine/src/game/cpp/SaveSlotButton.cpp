#include "../game_all.h"

void SaveSlotButton::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::gui;
	objectName = S("blank");
	range = 9999.0f;
	teleport = true;
	allowAllItems = true;
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	bigSpriteRenderer->gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(bigSpriteRenderer->gameObject->transform->get_position()));
	thumbSpriteRenderer = GetComponent<SpriteRenderer>();
	Vector2 vector = ScreenControler::gameToScreen(gts);
	Vector3 vector2 = Vector3(vector.x, vector.y, -0.01f);
	bigSpriteRenderer->gameObject->transform->set_position(Camera::get_main()->ScreenToWorldPoint(vector2));
	bigSpriteRenderer->gameObject->transform->set_position(Vector3(bigSpriteRenderer->gameObject->transform->get_position().x, bigSpriteRenderer->gameObject->transform->get_position().y, -3.0f));
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

void SaveSlotButton::Update()
{
	Vector2 vector = ScreenControler::gameToScreen(position);
	Vector3 vector2 = Vector3(vector.x, vector.y, -0.01f);
	gameObject->transform->set_position(Camera::get_main()->ScreenToWorldPoint(vector2));
	gameObject->transform->set_position(Vector3(gameObject->transform->get_position().x, gameObject->transform->get_position().y, -3.0f));
	if (needUpdate)
	{
		updateState();
		needUpdate = false;
	}
}

void SaveSlotButton::OnMouseEnter()
{
	if (PlayerController::wc->busy)
	{
		return;
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
	audioSource->PlayOneShot(SoundsManagerController::sm->ui_hover);
}

void SaveSlotButton::mouseOver()
{
	if (PlayerController::wc->busy)
	{
		return;
	}
	if (GameDataController::gd->checkSave(slotName))
	{
		P<SaveData> savePreview = GameDataController::gd->getSavePreview(slotName);
		if (savePreview->gameDay < 5)
		{
			String src = GameStrings::getString(GameStrings::gui, S("day"));
			src = GameStrings::capitalise(src);
			labelSlotDay->viewText(src + S(" ") + savePreview->gameDay + S(" ") + ClockController::getClockTime(savePreview->gameTime), false, true, true, 200, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		}
		else
		{
			labelSlotDay->viewText(GameStrings::capitalise(GameStrings::getString(GameStrings::gui, S("epilogue"))) + S(" "), false, true, true, 200, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		}
		labelSlotDay->keepAlive = true;
		String text = String::Empty;
		if (savePreview->objectives.Find([](const P<Objective>& x) { return x->id.Contains(S("previous_disc_barry")); })->state || savePreview->objectives.Find([](const P<Objective>& x) { return x->id.Contains(S("previous_disc_cody")); })->state)
		{
			text = S("- ") + GameStrings::getString(GameStrings::gui, S("newGamePlus")) + S(" -");
		}
		labelSlotDate->directionY = 1.0f;
		labelSlotDate->viewText(text + S(" ^") + savePreview->dateTime.ToShortTimeString() + S(" ") + savePreview->dateTime.ToShortDateString(), false, true, true, 200, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		labelSlotDate->keepAlive = true;
	}
	String empty = String::Empty;
	empty = GameStrings::getString(GameStrings::gui, S("slot_name")) + S(" ");
	if (slotName == S("save1"))
	{
		empty += S("1");
	}
	if (slotName == S("save2"))
	{
		empty += S("2");
	}
	if (slotName == S("save3"))
	{
		empty += S("3");
	}
	if (slotName == S("save4"))
	{
		empty += S("4");
	}
	if (slotName == S("save5"))
	{
		empty += S("5");
	}
	if (slotName == S("save6"))
	{
		empty += S("6");
	}
	if (slotName == S("save7"))
	{
		empty += S("7");
	}
	if (slotName == S("save8"))
	{
		empty += S("8");
	}
	if (slotName == S("save9"))
	{
		empty += S("9");
	}
	if (slotName == S("save10"))
	{
		empty += S("10");
	}
	if (slotName == S("autosave0"))
	{
		empty = GameStrings::getString(GameStrings::gui, S("autosave_name"));
	}
	else if (slotName.IndexOf(S("autosave")) != -1)
	{
		empty = GameStrings::getString(GameStrings::gui, S("autosave_chapter_name1")) + S(" ");
		if (slotName == S("chapter_1_autosave"))
		{
			empty += S("1");
		}
		if (slotName == S("chapter_2_autosave"))
		{
			empty += S("2");
		}
		if (slotName == S("chapter_3_autosave"))
		{
			empty += S("3");
		}
		if (slotName == S("chapter_4_autosave"))
		{
			empty += S("4");
		}
		String text2 = empty;
		empty = text2 + S(" ") + GameStrings::getString(GameStrings::gui, S("autosave_chapter_name2")) + S(" - ") + GameStrings::getString(GameStrings::gui, S("autosave_name"));
	}
	labelSlotName->viewText(empty, false, true, true, 200, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	labelSlotName->keepAlive = true;
	if (GameDataController::gd->checkSave(slotName))
	{
		bigSpriteRenderer->set_enabled(true);
	}
	else
	{
		bigSpriteRenderer->set_enabled(false);
	}
	bigSpriteRenderer->set_sprite(bigThumb);
}

void SaveSlotButton::mouseOut()
{
	if (!PlayerController::wc->busy)
	{
		labelSlotName->keepAlive = false;
		labelSlotDate->keepAlive = false;
		labelSlotDay->keepAlive = false;
		bigSpriteRenderer->set_sprite(nullptr);
	}
}

void SaveSlotButton::clickAction()
{
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
	if (GameDataController::wantSave)
	{
		if (GameDataController::gd->checkSave(slotName))
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::gui, S("save_overwrite_warning")), QuestionController::PopupType::QUESTION, [this]() { overwriteSave(); }, 0, 0, [this]() { cancel(); });
			return;
		}
		ScreenShots::ss->saveShots(slotName);
		GameDataController::gd->Save(slotName);
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::gui, S("save_done")), QuestionController::PopupType::STATEMENT);
		updateState();
	}
	else if (GameDataController::gd->checkSave(slotName))
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::gui, S("load_warning")), QuestionController::PopupType::QUESTION, [this]() { loadSave(); }, 0, 0, [this]() { cancel(); });
	}
}

void SaveSlotButton::cancel()
{
	labelSlotName->keepAlive = false;
	labelSlotDate->keepAlive = false;
	labelSlotDay->keepAlive = false;
	bigSpriteRenderer->set_sprite(nullptr);
}

void SaveSlotButton::overwriteSave()
{
	ScreenShots::ss->saveShots(slotName);
	GameDataController::gd->Save(slotName);
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::gui, S("save_done")), QuestionController::PopupType::STATEMENT);
	updateState();
}

void SaveSlotButton::loadSave()
{
	GameDataController::gd->politeLoad(slotName);
}

void SaveSlotButton::updateState()
{
	if (slotName.IndexOf(S("autosave")) != -1)
	{
		if (GameDataController::wantSave)
		{
			gameObject->transform->Find(S("back"))->GetComponent<SpriteRenderer>()->set_enabled(false);
			thumbSpriteRenderer->set_enabled(false);
			GetComponent<BoxCollider2D>()->set_enabled(false);
			return;
		}
		thumbSpriteRenderer->set_enabled(true);
		GetComponent<BoxCollider2D>()->set_enabled(true);
		if (GameDataController::gd->checkSave(slotName))
		{
			gameObject->transform->Find(S("back"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else
		{
			gameObject->transform->Find(S("back"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
	if (GameDataController::wantSave || GameDataController::gd->checkSave(slotName))
	{
		GetComponent<BoxCollider2D>()->set_enabled(true);
		thumb = ScreenShots::ss->getSprite(slotName);
		bigThumb = ScreenShots::ss->getSprite(slotName, true);
		thumbSpriteRenderer->set_sprite(thumb);
	}
	else
	{
		GetComponent<BoxCollider2D>()->set_enabled(false);
	}
	if (GameDataController::gd->checkSave(slotName))
	{
		thumbSpriteRenderer->set_enabled(true);
	}
	else
	{
		thumbSpriteRenderer->set_enabled(false);
	}
}

void SaveSlotButton::clickAction2()
{
}

void SaveSlotButton::clickAction0()
{
}

void SaveSlotButton::whatOnClick0()
{
}

void SaveSlotButton::whatOnClick()
{
}
