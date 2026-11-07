#include "../game_all.h"

void Button::Start()
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

void Button::Update()
{
	if (buttonEnabled)
	{
		if (bcol == nullptr)
		{
			bcol = gameObject->GetComponent<BoxCollider2D>();
		}
		bcol->set_enabled(true);
		if (buttonText == nullptr)
		{
			buttonText = gameObject->GetComponent<TextFieldController>();
		}
		Vector2 size = buttonText->black->GetComponent<SpriteRenderer>()->get_bounds().size;
		bcol->set_size(size);
		bcol->set_offset(Vector2(buttonText->black->GetComponent<SpriteRenderer>()->get_bounds().center.x - gameObject->transform->get_position().x, buttonText->black->GetComponent<SpriteRenderer>()->get_bounds().center.y - gameObject->transform->get_position().y));
	}
	else
	{
		if (bcol == nullptr)
		{
			bcol = gameObject->GetComponent<BoxCollider2D>();
		}
		bcol->set_enabled(false);
	}
}

void Button::OnMouseDown()
{
	if (onClick == nullptr || (!workIfBusy && PlayerController::wc->busy))
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
	audioSource->PlayOneShot(SoundsManagerController::sm->ui_click, 0.5f);
	onClick();
}

void Button::initButton(String label)
{
	initCursor();
	buttonText = gameObject->GetComponent<TextFieldController>();
	bcol = gameObject->GetComponent<BoxCollider2D>();
	buttonText->viewText(label, false, true, true, 200);
	buttonText->keepAlive = true;
	onHover = nullptr;
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	if (buttonText == nullptr)
	{
		buttonText = gameObject->GetComponent<TextFieldController>();
	}
	buttonText->setTextColor(color1.x, color1.y, color1.z);
	buttonText->black->GetComponent<SpriteRenderer>()->set_color(Color(background1.x, background1.y, background1.z, alpha1));
}

void Button::initCursor()
{
	cursorCont = GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>();
}

void Button::OnMouseOver()
{
	if (workIfBusy || !PlayerController::wc->busy)
	{
		if (cursorCont == nullptr)
		{
			initCursor();
		}
		cursorCont->showCursor(CursorController::PixelCursor::ACTIVE);
		if (onHover != nullptr)
		{
			onHover();
		}
		if (buttonText == nullptr)
		{
			buttonText = gameObject->GetComponent<TextFieldController>();
		}
		buttonText->setTextColor(color2.x, color2.y, color2.z);
		buttonText->black->GetComponent<SpriteRenderer>()->set_color(Color(background2.x, background2.y, background2.z, alpha2));
	}
}

void Button::OnMouseEnter()
{
	if (cursorCont == nullptr)
	{
		initCursor();
	}
	if (!workIfBusy && PlayerController::wc->busy)
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

void Button::OnMouseExit()
{
	if (cursorCont == nullptr)
	{
		initCursor();
	}
	cursorCont->showCursor(CursorController::PixelCursor::NORMAL);
	if (buttonText == nullptr)
	{
		buttonText = gameObject->GetComponent<TextFieldController>();
	}
	buttonText->setTextColor(color1.x, color1.y, color1.z);
	buttonText->black->GetComponent<SpriteRenderer>()->set_color(Color(background1.x, background1.y, background1.z, alpha1));
}
