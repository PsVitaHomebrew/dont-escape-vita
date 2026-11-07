#include "../game_all.h"

void DreamWraith::_cctor()
{
	colorTiger = Vector3(0.6f, 106.0f / 255.0f, 0.4f);
	colorMaggie = Vector3(0.6f, 106.0f / 255.0f, 0.4f);
}

void DreamWraith::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = true;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	actionType = Type::Talk;
	dkvs = GameStrings::objects;
	objectName = S("???");
	range = 30.0f;
	position = ScreenControler::roundToNearestFullPixel3(sarge->transform->get_position());
	sarge->transform->set_position(position);
	position2 = Vector2(-1.0f, 40.0f);
	setCollider(-1);
	playeremiter->started = false;
	updateState();
}

void DreamWraith::whatOnClick0()
{
}

void DreamWraith::clickAction()
{
}

void DreamWraith::shadowpep(String val)
{
}

void DreamWraith::reset()
{
	playeremiter->started = false;
	position2 = Vector2(-1.0f, 40.0f);
	ld3bs->reset();
}

void DreamWraith::reset1()
{
	PlayerController::wc->forceAnimation(S("sit_strugle"), true);
	PlayerController::pc->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 0.5f));
	playeremiter->started = true;
}

void DreamWraith::reset2()
{
	PlayerController::pc->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 0.25f));
}

void DreamWraith::reset3()
{
	PlayerController::pc->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 0.1f));
}

void DreamWraith::reset4()
{
	PlayerController::pc->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	playeremiter->started = false;
}

void DreamWraith::reset0()
{
	GameDataController::gd->setObjective(S("dream_day_3b_started"), false);
	PlayerController::pc->spawnName = S("DreamStairs");
	CurtainController::cc->fadeOut(S("Dream3B"));
	Invoke(S("reset"), 1.0f);
}

void DreamWraith::Update()
{
	if (gogogo || gogogo2)
	{
		position2.x += Time::get_deltaTime() * 12.0f;
		position2.y = PlayerController::wc->currentXY.y + 17.0f;
		if (position2.x > 20.0f)
		{
			gogogo = false;
		}
		if (position2.x >= PlayerController::wc->currentXY.x - 15.0f)
		{
			position2.x = PlayerController::wc->currentXY.x - 15.0f;
			gogogo2 = false;
			PlayerController::pc->setBusy(true);
			PlayerController::wc->forceAnimation(S("sit_fall"), true);
			GameObject::Find(S("DreamStairs"))->GetComponent<DreamStairsUpper>()->setCollider(-1);
			GameObject::Find(S("tiger"))->GetComponent<DreamTiger>()->setCollider(-1);
			Invoke(S("reset1"), 1.0f);
			Invoke(S("reset2"), 5.0f);
			Invoke(S("reset3"), 7.0f);
			Invoke(S("reset4"), 9.0f);
			Invoke(S("reset0"), 12.0f);
		}
	}
	Vector2 vectorToChange = Vector2();
	float z = sarge->transform->get_position().z;
	vectorToChange.x = position2.x;
	vectorToChange.y = position2.y;
	vectorToChange = ScreenControler::gameToScreen(vectorToChange);
	position = Vector3(vectorToChange.x, vectorToChange.y, sarge->transform->get_position().z);
	Vector3 vector = Camera::get_main()->WorldToScreenPoint(sarge->transform->get_position());
	position.z = vector.z;
	sarge->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position));
	sarge->transform->set_position(Vector3(sarge->transform->get_position().x, sarge->transform->get_position().y, z));
}

void DreamWraith::updateState()
{
}

void DreamWraith::clickAction2()
{
}

void DreamWraith::clickAction0()
{
}
