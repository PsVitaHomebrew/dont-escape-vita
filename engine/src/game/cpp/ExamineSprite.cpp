#include "../game_all.h"

bool ExamineSprite::get_Active()
{
	return active;
}

void ExamineSprite::Awake()
{
	if (es == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		es = this;
		MonoBehaviour::print(S("Inventory controler initialized"));
	}
	else if (es != P<ExamineSprite>(this))
	{
		Object::Destroy(gameObject);
	}
}

void ExamineSprite::Start()
{
	closingAnimation = nullptr;
	spriteRenderer = gameObject->transform->Find(S("sprite0"))->GetComponent<SpriteRenderer>();
	spriteRenderer1 = gameObject->transform->Find(S("sprite1"))->GetComponent<SpriteRenderer>();
	spriteRenderer2 = gameObject->transform->Find(S("sprite2"))->GetComponent<SpriteRenderer>();
	spriteRenderer3 = gameObject->transform->Find(S("sprite3"))->GetComponent<SpriteRenderer>();
	spriteRenderer4 = gameObject->transform->Find(S("sprite4"))->GetComponent<SpriteRenderer>();
	initTextfield();
}

void ExamineSprite::initTextfield()
{
	if (textField == nullptr)
	{
		textField = gameObject->AddComponent<TextFieldController>();
		textField = gameObject->GetComponent<TextFieldController>();
		textField->transform->set_parent(gameObject->transform);
		textField->container->transform->set_parent(gameObject->transform);
		Vector2 vector = ScreenControler::gameToScreen(Vector2(120.0f, 67.0f));
		Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
		position.z = -3.0f;
		gameObject->transform->set_position(position);
		position.y = 2.0f * position.y;
		spriteRenderer->gameObject->transform->set_position(position);
		position.z -= 0.1f;
		spriteRenderer1->gameObject->transform->set_position(position);
		position.z -= 0.1f;
		spriteRenderer2->gameObject->transform->set_position(position);
		position.z -= 0.1f;
		spriteRenderer3->gameObject->transform->set_position(position);
		position.z -= 0.1f;
		spriteRenderer4->gameObject->transform->set_position(position);
	}
}

void ExamineSprite::Update()
{
	if (targetAlpha < alpha)
	{
		alpha -= 0.1f;
	}
	else if (targetAlpha > alpha)
	{
		alpha += 0.1f;
	}
	if (Mathf::Abs(targetAlpha - alpha) < 0.1f)
	{
		alpha = targetAlpha;
	}
	spriteRenderer->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	float a = (cycleSprites ? 0.0f : alpha);
	spriteRenderer1->set_color(Color(1.0f, 1.0f, 1.0f, a));
	spriteRenderer2->set_color(Color(1.0f, 1.0f, 1.0f, a));
	spriteRenderer3->set_color(Color(1.0f, 1.0f, 1.0f, a));
	spriteRenderer4->set_color(Color(1.0f, 1.0f, 1.0f, a));
}

void ExamineSprite::show(P<Sprite> sprite, P<Sprite> sprite1, P<Sprite> sprite2, P<Sprite> sprite3, P<Sprite> sprite4, ExamineSprite_Delegate act, bool actionOnOpen)
{
	textField->center = false;
	gameObject->transform->set_position(Vector3(0.0f, 0.0f, -5.0f));
	targetAlpha = 1.0f;
	alpha = 0.0f;
	active = true;
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->queued = String::Empty;
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss();
	lookAction = act;
	actionOnShow = actionOnOpen;
	PlayerController::wc->fullStop(true);
	PlayerController::pc->setBusy(true);
	CursorController::cc->showCursor(CursorController::PixelCursor::OK);
	spriteRenderer->set_sprite(sprite);
	spriteRenderer1->set_sprite(sprite1);
	spriteRenderer2->set_sprite(sprite2);
	spriteRenderer3->set_sprite(sprite3);
	spriteRenderer4->set_sprite(sprite4);
	if (lookAction != nullptr && actionOnShow)
	{
		lookAction();
		lookAction = nullptr;
	}
	showPage();
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
}

bool ExamineSprite::showPage()
{
	if (ac != nullptr)
	{
		PlayerController::pc->aS->PlayOneShot(ac, audioVolume);
	}
	GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->dissmiss(true);
	if (pages != nullptr && pages.Count() > 0)
	{
		if (cycleSprites)
		{
			if (spriteRenderer1->get_sprite() != nullptr)
			{
				spriteRenderer->set_sprite(spriteRenderer1->get_sprite());
				spriteRenderer1->set_sprite(nullptr);
			}
			else if (spriteRenderer2->get_sprite() != nullptr)
			{
				spriteRenderer->set_sprite(spriteRenderer2->get_sprite());
				spriteRenderer2->set_sprite(nullptr);
			}
			else if (spriteRenderer3->get_sprite() != nullptr)
			{
				spriteRenderer->set_sprite(spriteRenderer3->get_sprite());
				spriteRenderer3->set_sprite(nullptr);
			}
			else if (spriteRenderer4->get_sprite() != nullptr)
			{
				spriteRenderer->set_sprite(spriteRenderer4->get_sprite());
				spriteRenderer4->set_sprite(nullptr);
			}
		}
		initTextfield();
		textField->keepAlive = true;
		textField->directionY = 1.0f;
		textField->viewText(pages[0], false, quick, quick, twidth, colors1.x, colors1.y, colors1.z, colors2.x, colors2.y, colors2.z, talpha);
		pages.RemoveAt(0);
		return true;
	}
	return false;
}

void ExamineSprite::readyText(List<String> _pages, int w, float r1, float g1, float b1, float r2, float g2, float b2, float _talpha)
{
	quick = true;
	MonoBehaviour::print(S("READU TEXT"));
	for (int i = 0; i < _pages.Count(); i++)
	{
		if (_pages[i].Equals(String::Empty) || _pages[i].Equals(S(" ")))
		{
			_pages.RemoveAt(i);
			i--;
		}
	}
	if (_pages.Count() > 0)
	{
		MonoBehaviour::print(_pages[0]);
	}
	pages = _pages;
	cycleSprites = false;
	twidth = w;
	colors1 = Vector3(r1, g1, b1);
	colors2 = Vector3(r2, g2, b2);
	talpha = _talpha;
}

void ExamineSprite::hide()
{
	if (!showPage())
	{
		ac = nullptr;
		audioVolume = 1.0f;
		active = false;
		pages = nullptr;
		targetAlpha = 0.0f;
		MonoBehaviour::print(S("HIDE EXAMINE SPRITE ") + (closingAnimation == nullptr));
		MonoBehaviour::print(S("IS THERE AN ACTION TO DO? ") + ENGINE_TODO_V("lookAction (delegate ToString in string concat)", String::Empty));
		CursorController::cc->showCursor(CursorController::PixelCursor::NORMAL);
		CursorController::cc->clearOverride();
		initTextfield();
		if (!quick)
		{
			textField->dissmiss();
		}
		textField->keepAlive = false;
		if (closingAnimation != nullptr)
		{
			PlayerController::wc->forceAnimation(closingAnimation, closingAnimationFlip);
			closingAnimationFlip = false;
			closingAnimation = nullptr;
		}
		else
		{
			PlayerController::pc->setBusy(false);
		}
		if (lookAction != nullptr && !actionOnShow)
		{
			lookAction();
			lookAction = nullptr;
		}
	}
}
