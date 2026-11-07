#include "../game_all.h"

void OutpostBarsButtonReset::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_bars_reset");
	teleport = true;
	range = 1000.0f;
	updateState();
}

void OutpostBarsButtonReset::Update()
{
}

void OutpostBarsButtonReset::clickAction()
{
	sr->set_sprite(sprite_on);
	PlayerController::pc->setBusy(true);
	Invoke(S("unlock"), 0.5f);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->mouse_click, 0.5f);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->denied);
	button_a->targetValue = 50;
	button_b->targetValue = 50;
	button_c->targetValue = 50;
	button_d->targetValue = 50;
	button_e->targetValue = 50;
	GameDataController::gd->setObjectiveDetail(S("outpost_bars_a"), button_a->targetValue);
	GameDataController::gd->setObjectiveDetail(S("outpost_bars_b"), button_b->targetValue);
	GameDataController::gd->setObjectiveDetail(S("outpost_bars_c"), button_c->targetValue);
	GameDataController::gd->setObjectiveDetail(S("outpost_bars_d"), button_d->targetValue);
	GameDataController::gd->setObjectiveDetail(S("outpost_bars_e"), button_e->targetValue);
	aS->PlayOneShot(SoundsManagerController::sm->power_down_small, 0.5f);
	aS->set_pitch(0.8f);
}

void OutpostBarsButtonReset::zrobCos(P<OutpostBarsButtonAdd> obiekt, String nazwa, int minus)
{
}

void OutpostBarsButtonReset::unlock()
{
	PlayerController::pc->setBusy(false);
	updateState();
}

void OutpostBarsButtonReset::updateState()
{
	if (button_a->targetValue == 50 && button_b->targetValue == 50 && button_c->targetValue == 50 && button_d->targetValue == 50 && button_e->targetValue == 50)
	{
		allowed = false;
	}
	else
	{
		allowed = true;
	}
	if (!allowed)
	{
		sr->set_sprite(sprite_disabled);
		setCollider(-1);
		label->viewText(GameStrings::getString(GameStrings::world_labels, S("generic_reset_small")), false, true, true, 50, 128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		label->keepAlive = true;
	}
	else
	{
		setCollider(0);
		sr->set_sprite(sprite_off);
		label->viewText(GameStrings::getString(GameStrings::world_labels, S("generic_reset_small")), false, true, true, 50, 35.0f / 255.0f, 1.0f / 3.0f, 115.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		label->keepAlive = true;
	}
}

void OutpostBarsButtonReset::clickAction2()
{
}

void OutpostBarsButtonReset::clickAction0()
{
}
