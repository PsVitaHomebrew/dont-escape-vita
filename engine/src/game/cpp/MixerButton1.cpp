#include "../game_all.h"

void MixerButton1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("mixer_button_small");
	range = 8000.0f;
	teleport = false;
	sr = gameObject->GetComponent<SpriteRenderer>();
	updateState();
}

void MixerButton1::Update()
{
}

void MixerButton1::whatOnClick()
{
}

void MixerButton1::clickAction()
{
	countThem();
	if (GameDataController::gd->getObjective(S("sidereal_mixer_") + thisNumber))
	{
		GameDataController::gd->setObjective(S("sidereal_mixer_") + thisNumber, false);
		updateAll();
	}
	else if (((thisNumber == S("b1") || thisNumber == S("b2") || thisNumber == S("b3")) && GameDataController::gd->getObjective(S("sidereal_components_1"))) || ((thisNumber == S("b4") || thisNumber == S("b5") || thisNumber == S("b6")) && GameDataController::gd->getObjective(S("sidereal_components_2"))))
	{
		if (liczba < 3)
		{
			GameDataController::gd->setObjective(S("sidereal_mixer_") + thisNumber, true);
			updateAll();
		}
		else
		{
			sr->set_sprite(sprite_wr);
			setCollider(-1);
			Invoke(S("updateAll"), 0.1f);
		}
	}
	else
	{
		sr->set_sprite(sprite_wr);
		setCollider(-1);
		Invoke(S("updateAll"), 0.1f);
	}
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
}

void MixerButton1::countThem()
{
	liczba = 0;
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b1")))
	{
		liczba++;
	}
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b2")))
	{
		liczba++;
	}
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b3")))
	{
		liczba++;
	}
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b4")))
	{
		liczba++;
	}
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b5")))
	{
		liczba++;
	}
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b6")))
	{
		liczba++;
	}
}

void MixerButton1::updateState()
{
	setCollider(0);
	if (GameDataController::gd->getObjective(S("sidereal_mixer_") + thisNumber))
	{
		sr->set_sprite(sprite_on);
	}
	else
	{
		sr->set_sprite(sprite_off);
	}
}

void MixerButton1::clickAction2()
{
}

void MixerButton1::clickAction0()
{
}
