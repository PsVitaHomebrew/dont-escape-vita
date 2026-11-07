#include "../game_all.h"

void CraneThing::Start()
{
}

void CraneThing::updateState()
{
	if (GameDataController::gd->getObjective(S("cs_pack_lifted")))
	{
		targetX = 160.0f;
		targetY = 30.0f;
	}
	else
	{
		if (GameDataController::gd->getObjective(S("cs_crane_left")))
		{
			targetX = 160.0f;
		}
		else
		{
			targetX = 220.0f;
		}
		if (GameDataController::gd->getObjective(S("cs_crane_down")))
		{
			targetY = 5.0f;
		}
		else
		{
			targetY = 80.0f;
		}
	}
	if (GameDataController::gd->getObjective(S("cs_crane_closed")))
	{
		GetComponent<SpriteRenderer>()->set_sprite(closed);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_sprite(open);
	}
}

void CraneThing::Update()
{
	float num = 30.0f;
	if (targetY == 30.0f)
	{
		num = 10.0f;
	}
	if (targetX - currentX < 1.0f)
	{
		currentX -= Time::get_deltaTime() * 20.0f;
	}
	if (currentX - targetX < 1.0f)
	{
		currentX += Time::get_deltaTime() * 20.0f;
	}
	if (Mathf::Abs(targetX - currentX) < 1.0f)
	{
		currentX = targetX;
	}
	if (targetY - currentY < 1.0f)
	{
		currentY -= Time::get_deltaTime() * num;
	}
	if (currentY - targetY < 1.0f)
	{
		currentY += Time::get_deltaTime() * num;
	}
	if (Mathf::Abs(targetY - currentY) < 1.0f)
	{
		currentY = targetY;
	}
	Vector2 vectorToChange = Vector2();
	Vector2 vectorToChange2 = Vector2();
	float z = gameObject->transform->get_position().z;
	vectorToChange.x = currentX;
	vectorToChange.y = currentY;
	vectorToChange = ScreenControler::gameToScreen(vectorToChange);
	vectorToChange2.x = currentX;
	vectorToChange2.y = yyy;
	vectorToChange2 = ScreenControler::gameToScreen(vectorToChange2);
	Vector3 position = Vector3(vectorToChange.x, vectorToChange.y, gameObject->transform->get_position().z);
	Vector3 position2 = Vector3(vectorToChange2.x, vectorToChange2.y, metal->transform->get_position().z);
	Vector3 vector = Camera::get_main()->WorldToScreenPoint(gameObject->transform->get_position());
	Vector3 vector2 = Camera::get_main()->WorldToScreenPoint(metal->transform->get_position());
	position.z = vector.z;
	position2.z = vector2.z;
	gameObject->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position));
	metal->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position2));
}
