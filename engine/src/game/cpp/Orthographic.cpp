#include "../game_all.h"

void Orthographic::Start()
{
	if (SystemInfo::get_graphicsDeviceVersion().ToLower().StartsWith(S("direct3d 9")))
	{
		offset = 0.5f;
	}
	GetComponent<Camera>()->set_orthographic(true);
}

void Orthographic::Update()
{
	GetComponent<Camera>()->set_orthographicSize((float)(Screen::get_height() / 2));
	GetComponent<Camera>()->transform->set_position(Vector3((float)(Screen::get_width() / 2) - offset, (float)(Screen::get_height() / 2) - offset, -1.0f));
}
