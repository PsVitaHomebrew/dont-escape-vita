#include "../game_all.h"

void FireplaceLight::Start()
{
}

void FireplaceLight::Update()
{
}

void FireplaceLight::newShadow()
{
	fireLight->set_color(Color(1.0f, 1.0f, 1.0f, Random::Range(0.85f, 1.0f)));
}
