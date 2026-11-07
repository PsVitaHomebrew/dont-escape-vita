#include "../game_all.h"

void StaticControler::Start()
{
	pos = Vector3(0.0f, 0.0f, -1.0f);
	sprite = gameObject->GetComponent<SpriteRenderer>()->get_sprite();
	spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
	spriteRenderer->set_color(Color(0.0f, 0.0f, 0.0f, 0.3f * (float)PlayerPrefs::GetInt(S("stati")) / 100.0f));
	time = 0.0f;
	static_power = PlayerPrefs::GetInt(S("stati"));
}

void StaticControler::Update()
{
	time += Time::get_deltaTime();
	if ((double)time >= 0.02)
	{
		time = 0.0f;
		spriteRenderer->set_color(Color(0.0f, 0.0f, 0.0f, Random::Range(0.2f, 0.3f) * (float)static_power / 100.0f));
		int width = sprite->get_texture()->get_width();
		int height = sprite->get_texture()->get_height();
		width = Random::Range(-240, 480);
		height = Random::Range(-144, 270);
		vvv = Vector2((float)width, (float)height);
		Vector2 vector = ScreenControler::gameToScreen(vvv);
		pos.x = vector.x;
		pos.y = vector.y;
		pos = Camera::get_main()->ScreenToWorldPoint(pos);
		pos.z = -6.25f;
		gameObject->transform->set_position(pos);
	}
}
