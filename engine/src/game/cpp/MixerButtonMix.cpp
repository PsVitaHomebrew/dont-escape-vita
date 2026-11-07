#include "../game_all.h"

void MixerButtonMix::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("mixer_button_big");
	range = 8000.0f;
	teleport = false;
	sr = gameObject->GetComponent<SpriteRenderer>();
	updateState();
}

void MixerButtonMix::Update()
{
}

void MixerButtonMix::whatOnClick()
{
}

void MixerButtonMix::clickAction()
{
	countThem();
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
	if (GameDataController::gd->getObjective(S("sidereal_mixer_mixed")) && GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) > 0)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_button_already_done")));
	}
	else if (GameDataController::gd->getObjective(S("sidereal_mixer_mixed")) && GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) == 0)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_full")));
	}
	else if (liczba < 3)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_button_not_complete")));
	}
	else
	{
		QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("mixer")), QuestionController::PopupType::QUESTION, [this]() { yesMix(); }, 15);
	}
}

void MixerButtonMix::yesMix()
{
	GameDataController::gd->setObjective(S("sidereal_mixer_mixed"), true);
	int num = 0;
	int num2 = 0;
	int num3 = 0;
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b1")))
	{
		num += 2;
		num2++;
		num3 = num3;
	}
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b2")))
	{
		num++;
		num2 += 2;
		num3 = num3;
	}
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b3")))
	{
		num++;
		num2 = num2;
		num3 += 2;
	}
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b4")))
	{
		num = num;
		num2++;
		num3 += 2;
	}
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b5")))
	{
		num = num;
		num2 += 2;
		num3++;
	}
	if (GameDataController::gd->getObjective(S("sidereal_mixer_b6")))
	{
		num += 2;
		num2 = num2;
		num3++;
	}
	if (num == 2 && num2 == 4 && num3 == 3)
	{
		GameDataController::gd->setObjectiveDetail(S("sidereal_mixer_mixed"), 1);
	}
	else if (num == 4 && num2 == 2 && num3 == 3)
	{
		GameDataController::gd->setObjectiveDetail(S("sidereal_mixer_mixed"), 2);
	}
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->mixer);
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("LocationMixerExit");
	CurtainController::cc->fadeOut(S("SiderealMixer"), WalkController::Direction::N, nullptr, nullptr, false, [this]() { doneMixing(); });
}

void MixerButtonMix::doneMixing()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_complete")));
}

void MixerButtonMix::countThem()
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

void MixerButtonMix::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_components_1")))
	{
		comps1->set_enabled(true);
	}
	else
	{
		comps1->set_enabled(false);
	}
	if (GameDataController::gd->getObjective(S("sidereal_components_2")))
	{
		comps2->set_enabled(true);
	}
	else
	{
		comps2->set_enabled(false);
	}
	setCollider(0);
	countThem();
	if (liczba == 0)
	{
		sr->set_enabled(false);
		return;
	}
	sr->set_enabled(true);
	if (liczba == 1)
	{
		sr->set_sprite(sprite_1);
	}
	if (liczba == 2)
	{
		sr->set_sprite(sprite_2);
	}
	if (liczba == 3)
	{
		sr->set_sprite(sprite_3);
	}
}

void MixerButtonMix::clickAction2()
{
}

void MixerButtonMix::clickAction0()
{
}
