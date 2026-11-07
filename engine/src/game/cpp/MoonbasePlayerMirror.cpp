#include "../game_all.h"

void MoonbasePlayerMirror::Start()
{
	doIEvenCare = true;
	if (objectName == S("Ginger"))
	{
		if (GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("moon_cate_sleeps")))
		{
			doIEvenCare = true;
		}
		else
		{
			doIEvenCare = false;
		}
	}
	if (objectName == S("Npc2"))
	{
		if (GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("moon_barry_sleeps")))
		{
			doIEvenCare = true;
		}
		else
		{
			doIEvenCare = false;
		}
	}
	if (objectName == S("Npc3"))
	{
		if (GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("moon_cody_sleeps")))
		{
			doIEvenCare = true;
		}
		else
		{
			doIEvenCare = false;
		}
	}
	spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
}

void MoonbasePlayerMirror::Update()
{
	if (!doIEvenCare)
	{
		spriteRenderer->set_enabled(false);
	}
	else
	{
		spriteRenderer->set_enabled(true);
	}
	if (playerSprite == nullptr)
	{
		playerSprite = GameObject::Find(objectName)->GetComponent<SpriteRenderer>();
	}
	spriteRenderer->set_sprite(playerSprite->get_sprite());
	spriteRenderer->set_flipX(playerSprite->get_flipX());
	spriteRenderer->set_flipY(true);
	gameObject->transform->set_position(Vector3(playerSprite->gameObject->transform->get_position().x, playerSprite->gameObject->transform->get_position().y - 0.385f, gameObject->transform->get_position().z));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
}
