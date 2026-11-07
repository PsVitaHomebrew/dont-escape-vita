#include "../game_all.h"

void MixerResults::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("source_good");
	range = 8000.0f;
	teleport = false;
	sr = gameObject->GetComponent<SpriteRenderer>();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("mixer_glass"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pill_half"), String::Empty, nullptr, String::Empty));
	updateState();
}

void MixerResults::Update()
{
}

void MixerResults::whatOnClick()
{
}

void MixerResults::clickAction()
{
	if (!GameDataController::gd->getObjective(S("sidereal_mixer_mixed")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_empty")));
	}
	else if (GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) == 0)
	{
		PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_junk1")));
		PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_junk2")));
		PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_junk3")));
		Timeline::t->actions[Timeline::t->actions.Count() - 1]->function = [this](String param) { resetMixer(param); };
		Timeline::t->actions[Timeline::t->actions.Count() - 1]->actionWithText = false;
	}
	else if (GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) == 1)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1)
		{
			PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_wrong")));
			PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_junk2")));
			PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_junk3")));
			Timeline::t->actions[Timeline::t->actions.Count() - 1]->function = [this](String param) { resetMixer(param); };
			Timeline::t->actions[Timeline::t->actions.Count() - 1]->actionWithText = false;
		}
		else if (usedItem == S("pill_half"))
		{
			if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("pills"))))
			{
				PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->sand_pour1);
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_pills2")));
				GameDataController::gd->setObjectiveDetail(S("sidereal_mixer_mixed"), 3);
				updateAll();
			}
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_pills1")));
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) == 2)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
		{
			PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_wrong")));
			PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_junk2")));
			PlayerController::pc->sayLine(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_junk3")));
			Timeline::t->actions[Timeline::t->actions.Count() - 1]->function = [this](String param) { resetMixer(param); };
			Timeline::t->actions[Timeline::t->actions.Count() - 1]->actionWithText = false;
		}
		else if (usedItem == S("mixer_glass"))
		{
			if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("catalyst"))))
			{
				PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->liquid_pour_small);
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_catalyst2")));
				GameDataController::gd->setObjectiveDetail(S("sidereal_mixer_mixed"), 3);
				updateAll();
			}
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_tray_catalyst1")));
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) == 3)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_button_already_done")));
	}
}

void MixerResults::resetMixer(String param)
{
	GameDataController::gd->setObjective(S("sidereal_mixer_mixed"), false);
	GameDataController::gd->setObjectiveDetail(S("sidereal_mixer_mixed"), 0);
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("LocationMixerExit");
	CurtainController::cc->fadeOut(S("SiderealMixer"), WalkController::Direction::N);
}

void MixerResults::updateState()
{
	setCollider(0);
	if (!GameDataController::gd->getObjective(S("sidereal_mixer_mixed")))
	{
		objectName = S("mixer_tray_empty");
		sr->set_enabled(false);
		return;
	}
	sr->set_enabled(true);
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) == 0)
	{
		sr->set_sprite(sprite_1);
		objectName = S("mixer_tray_junk");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) == 1)
	{
		sr->set_sprite(sprite_2);
		objectName = S("mixer_tray_pills");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) == 2)
	{
		sr->set_sprite(sprite_3);
		objectName = S("mixer_tray_catalyst");
	}
	else if (GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) == 3)
	{
		sr->set_enabled(false);
		objectName = S("mixer_tray_empty");
	}
}

void MixerResults::clickAction2()
{
}

void MixerResults::clickAction0()
{
}
