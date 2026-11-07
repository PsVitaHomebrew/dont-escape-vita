#include "../game_all.h"

void OutpostBarsButtonAdd::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_bars_button");
	teleport = true;
	range = 1000.0f;
	aS = GetComponent<AudioSource>();
	allowed = true;
	currentValue = GameDataController::gd->getObjectiveDetail(S("outpost_bars_") + plus_1);
	targetValue = currentValue;
	updateState();
}

void OutpostBarsButtonAdd::Update()
{
	if (delay <= 0.0f)
	{
		if (currentValue < targetValue)
		{
			currentValue++;
		}
		else if (currentValue > targetValue)
		{
			currentValue--;
		}
		delay = 0.05f;
		updateState();
	}
	else
	{
		delay -= Time::get_deltaTime();
	}
}

void OutpostBarsButtonAdd::clickAction()
{
	if (allowed)
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->mouse_click, 0.5f);
		currentValue = GameDataController::gd->getObjectiveDetail(S("outpost_bars_") + plus_1);
		targetValue = currentValue + bigPlus;
		GameDataController::gd->setObjectiveDetail(S("outpost_bars_") + plus_1, targetValue);
		zrobCos(minus1Obj, minus_1, smallMinus);
		zrobCos(minus2Obj, minus_2, smallMinus);
		zrobCos(minus3Obj, minus_3, bigMinus);
		zrobCos(minus4Obj, minus_4, bigMinus);
		updateAll();
		aS->PlayOneShot(SoundsManagerController::sm->power_up_small, 0.5f);
		aS->set_pitch(0.8f + Random::Range(0.0f, 0.1f) + (float)caption_eff->score * 0.1f);
		sr->set_sprite(sprite_on);
		PlayerController::pc->setBusy(true);
		Invoke(S("unlock"), 0.5f);
	}
}

void OutpostBarsButtonAdd::zrobCos(P<OutpostBarsButtonAdd> obiekt, String nazwa, int minus)
{
	int objectiveDetail = GameDataController::gd->getObjectiveDetail(S("outpost_bars_") + nazwa);
	int detail = objectiveDetail - minus;
	obiekt->currentValue = obiekt->targetValue;
	GameDataController::gd->setObjectiveDetail(S("outpost_bars_") + nazwa, detail);
	obiekt->targetValue = detail;
}

void OutpostBarsButtonAdd::unlock()
{
	PlayerController::pc->setBusy(false);
	updateAll();
	if (caption_eff->score == 10)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_bars_perfect")));
	}
}

void OutpostBarsButtonAdd::updateState()
{
	coords(Vector2((float)xShift, (float)(yShift + currentValue)));
	if (!PlayerController::wc->busy)
	{
		allowed = true;
		setCollider(0);
		sr->set_sprite(sprite_off);
		if (targetValue + bigPlus > 100)
		{
			allowed = false;
		}
		if (minus1Obj->targetValue - smallMinus < 0)
		{
			allowed = false;
		}
		if (minus2Obj->targetValue - smallMinus < 0)
		{
			allowed = false;
		}
		if (minus3Obj->targetValue - bigMinus < 0)
		{
			allowed = false;
		}
		if (minus4Obj->targetValue - bigMinus < 0)
		{
			allowed = false;
		}
		if (!allowed)
		{
			sr->set_sprite(sprite_disabled);
			setCollider(-1);
		}
	}
	if (currentValue > perfect_start && currentValue <= perfect_end)
	{
		bar->GetComponent<SpriteRenderer>()->set_sprite(bar_green);
	}
	else if (currentValue > good_start && currentValue <= good_end)
	{
		bar->GetComponent<SpriteRenderer>()->set_sprite(bar_yellow);
	}
	else
	{
		bar->GetComponent<SpriteRenderer>()->set_sprite(bar_red);
	}
	if (targetValue > perfect_start && targetValue <= perfect_end)
	{
		GameDataController::gd->setObjectiveDetail(S("outpost_score_") + plus_1, 2);
	}
	else if (targetValue > good_start && targetValue <= good_end)
	{
		GameDataController::gd->setObjectiveDetail(S("outpost_score_") + plus_1, 1);
	}
	else
	{
		GameDataController::gd->setObjectiveDetail(S("outpost_score_") + plus_1, 0);
	}
	caption_eff->aktualizuj();
}

Vector3 OutpostBarsButtonAdd::coords(Vector2 source)
{
	Vector2 vectorToChange = Vector2();
	float z = gameObject->transform->get_position().z;
	vectorToChange.x = source.x + 120.0f;
	vectorToChange.y = source.y + 72.0f;
	vectorToChange = ScreenControler::gameToScreen(vectorToChange);
	Vector3 vector = Vector3(vectorToChange.x, vectorToChange.y, gameObject->transform->get_position().z);
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(vector);
	position.z = -0.256f;
	bar->transform->set_position(position);
	return vector;
}

void OutpostBarsButtonAdd::clickAction2()
{
}

void OutpostBarsButtonAdd::clickAction0()
{
}
