#include "../game_all.h"

void ResultsFrame::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	frame = gameObject->GetComponent<SpriteRenderer>();
	sr = gameObject->transform->Find(S("inside"))->GetComponent<SpriteRenderer>();
}

void ResultsFrame::move(float x, float y)
{
	gameObject->transform->set_position(Vector3(x, y, gameObject->transform->get_position().z));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
}

void ResultsFrame::Update()
{
	if (targetAlpha < alpha)
	{
		alpha -= 0.1f;
	}
	if (alpha < targetAlpha)
	{
		alpha += 0.1f;
	}
	if (Mathf::Abs(targetAlpha - alpha) < 0.1f)
	{
		alpha = targetAlpha;
	}
	if (alpha == 0.0f && nextSprite != nullptr)
	{
		sr->set_sprite(nextSprite);
		nextSprite = nullptr;
		targetAlpha = 1.0f;
	}
	sr->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	frame->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
}

void ResultsFrame::show(P<Sprite> sprite)
{
	MonoBehaviour::print(S("SHOWING: ") + str(sprite));
	nextSprite = sprite;
	targetAlpha = 0.0f;
}

void ResultsFrame::hide()
{
	nextSprite = nullptr;
	targetAlpha = 0.0f;
}
