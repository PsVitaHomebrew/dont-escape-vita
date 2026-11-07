#include "../game_all.h"

SpriteShadow::SpriteShadow()
{
}

SpriteShadow::SpriteShadow(P<GameObject> t)
{
	gameObject = t;
	shadow_mask = Resources::Load<Sprite>(S("Bitmaps/misc/shadow_mask"));
	shadows = Array<P<SpriteShadowSlice>>::New((int)gameObject->GetComponent<SpriteRenderer>()->get_sprite()->get_rect().height);
	for (int i = 0; i < shadows.Length(); i++)
	{
		newShadowPiece(i);
	}
	if (gameObject->GetComponent<WalkController>() != nullptr)
	{
		offsetY = gameObject->GetComponent<WalkController>()->offsetY;
	}
	else if (gameObject->GetComponent<NPCWalkController>() != nullptr)
	{
		offsetY = gameObject->GetComponent<NPCWalkController>()->offsetY;
	}
	else
	{
		offsetY = 0;
	}
	offsetY2 = 2;
	lastFrame = String::Empty;
}

void SpriteShadow::clearLastFrame()
{
	lastFrame = String::Empty;
}

void SpriteShadow::newShadowPiece(int i)
{
	shadows[i] = New<SpriteShadowSlice>();
	shadows[i]->shadowHolder = New<GameObject>();
	shadows[i]->shadowHolder->transform->set_parent(this->gameObject->transform);
	shadows[i]->shadowHolder->set_name(this->gameObject->get_name() + S("_shadowHolder_") + i);
	shadows[i]->shadowHolder->AddComponent<SortingGroup>();
	P<GameObject> gameObject = New<GameObject>();
	gameObject->transform->set_parent(shadows[i]->shadowHolder->transform);
	shadows[i]->shadow = gameObject->AddComponent<SpriteRenderer>();
	shadows[i]->shadow->set_name(S("shadow_sprite_") + i);
	shadows[i]->shadow->set_maskInteraction(SpriteMaskInteraction::VisibleInsideMask);
	P<GameObject> gameObject2 = New<GameObject>();
	gameObject2->transform->set_parent(shadows[i]->shadowHolder->transform);
	shadows[i]->mask = gameObject2->AddComponent<SpriteMask>();
	shadows[i]->mask->set_name(S("shadow_mask_") + i);
	shadows[i]->mask->set_sprite(shadow_mask);
}

void SpriteShadow::update(Vector3 postion, Vector2 currentXY, int offset)
{
	shadowOffsetY = offset;
	if (shadowOffsetY <= -7)
	{
		shadowOffsetY -= 3;
	}
	else if (shadowOffsetY == -6)
	{
		shadowOffsetY = -3;
	}
	else if (shadowOffsetY == -5)
	{
		shadowOffsetY = -2;
	}
	else if (shadowOffsetY == -4)
	{
		shadowOffsetY = -1;
	}
	else if (shadowOffsetY == -3)
	{
		shadowOffsetY = 0;
	}
	else if (shadowOffsetY == -2)
	{
		shadowOffsetY = 0;
	}
	else if (shadowOffsetY == -1)
	{
		shadowOffsetY = 0;
	}
	else
	{
		shadowOffsetY = 0;
	}
	if (gameObject->GetComponent<SpriteRenderer>()->get_sprite()->get_name() != lastFrame || alphaMod != 1.0f)
	{
		for (int i = 0; i < shadows.Length(); i++)
		{
			if ((float)i >= (float)shadows.Length() * scaleFactor)
			{
				shadows[i]->shadow->set_enabled(false);
				shadows[i]->mask->set_enabled(false);
			}
			else
			{
				shadows[i]->shadow->set_enabled(true);
				shadows[i]->mask->set_enabled(true);
			}
			int num = (int)((float)i * (1.0f / scaleFactor - 1.0f));
			if (num > shadows.Length() - 1)
			{
				num = shadows.Length() - 1;
			}
			shadows[i]->shadow->set_sprite(gameObject->GetComponent<SpriteRenderer>()->get_sprite());
			shadows[i]->shadow->set_flipY(downwards);
			shadows[i]->shadow->set_flipX(gameObject->GetComponent<SpriteRenderer>()->get_flipX());
			float num2 = startAlpha - fadeRateV * (float)i;
			float num3 = Mathf::Abs(currentXY.x - source);
			num2 -= fadeRateH * num3;
			if (num2 < 0.0f)
			{
				num2 = 0.0f;
			}
			shadows[i]->shadow->set_color(Color(0.0f, 0.0f, 0.0f, num2 * alphaMod));
			float num4 = 0.0f - source + currentXY.x;
			num4 *= skewFactor / 1000.0f;
			num4 -= skewFactor2 / 10.0f;
			float num5 = 1.0f;
			num5 = ((!downwards) ? (-1.0f) : 1.0f);
			Vector3 position = Vector3(0.0f, 0.0f, -0.055f);
			position = Camera::get_main()->WorldToScreenPoint(position);
			Vector2 tmp;
			tmp.x = currentXY.x + num4 * (float)i;
			tmp.y = currentXY.y;
			Vector2 vector = ScreenControler::gameToScreen(tmp);
			Vector3 position2 = Vector3(vector.x, vector.y, position.z);
			shadows[i]->shadowHolder->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position2));
			Vector2 tmp2;
			tmp2.x = currentXY.x + num4 * (float)i;
			tmp2.y = currentXY.y - (float)(offsetY + offsetY2 - num - shadowOffsetY) * num5;
			Vector2 vector2 = ScreenControler::gameToScreen(tmp2);
			Vector3 position3 = Vector3(vector2.x, vector2.y, position.z);
			shadows[i]->shadow->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position3));
			Vector2 vectorToChange = Vector3();
			vectorToChange.x = currentXY.x + num4 * (float)i;
			vectorToChange.y = currentXY.y - (float)i * num5;
			vectorToChange = ScreenControler::gameToScreen(vectorToChange);
			Vector3 position4 = Vector3(vectorToChange.x, vectorToChange.y, position.z);
			shadows[i]->mask->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position4));
		}
	}
	lastFrame = gameObject->GetComponent<SpriteRenderer>()->get_sprite()->get_name();
}
