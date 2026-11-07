#include "../game_all.h"

void Napisy::Start()
{
}

void Napisy::Update()
{
}

void Napisy::showNapisyS(String s)
{
	if (GameDataController::persistentData == nullptr)
	{
		GameDataController::persistentData = New<PersistentData>();
		GameDataController::gd->initPersistantAchieves();
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		GameDataController::persistentData->chapter1_locust = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		GameDataController::persistentData->chapter1_gas = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		GameDataController::persistentData->chapter1_spiders = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		GameDataController::persistentData->chapter2_hot = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
	{
		GameDataController::persistentData->chapter2_cold = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		GameDataController::persistentData->chapter3_bandits = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		GameDataController::persistentData->chapter3_thunderstorm = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
	{
		GameDataController::persistentData->chapter4_air = true;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1)
	{
		GameDataController::persistentData->chapter4_fuel = true;
	}
	if (GameDataController::gd->getObjective(S("moon_disc1_used")))
	{
		GameDataController::persistentData->disc_barry = true;
	}
	else
	{
		GameDataController::persistentData->disc_barry = false;
	}
	if (GameDataController::gd->getObjective(S("moon_disc2_used")))
	{
		GameDataController::persistentData->disc_cody = true;
	}
	else
	{
		GameDataController::persistentData->disc_cody = false;
	}
	GameDataController::gd->PersistentSave();
	Invoke(S("showNapisy1"), 3.0f);
}

void Napisy::showNapisy1()
{
	JukeboxAmbient::jb->changeAmbient(nullptr, 0.0f);
	GameObject::Find(S("credits1"))->GetComponent<EndCredits>()->showDontEscape();
	Invoke(S("showNapisy2"), 6.0f);
}

void Napisy::showNapisy2()
{
	GameObject::Find(S("credits1"))->GetComponent<EndCredits>()->showBlack();
	Invoke(S("showNapisy3"), 1.0f);
}

void Napisy::showNapisy3()
{
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("credits_1")), false, true, true, 240, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->setTime(6.0f);
	Invoke(S("showNapisy4"), 7.0f);
}

void Napisy::showNapisy4()
{
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("credits_2")), false, true, true, 240, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->setTime(6.0f);
	Invoke(S("showNapisy5"), 7.0f);
}

void Napisy::showNapisy5()
{
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("credits_3")), false, true, true, 240, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->setTime(6.0f);
	Invoke(S("showNapisy6"), 7.0f);
}

void Napisy::showNapisy6()
{
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("credits_4")), false, true, true, 240, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->setTime(6.0f);
	Invoke(S("showNapisy7"), 7.0f);
}

void Napisy::showNapisy7()
{
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("credits_5")), false, true, true, 240, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->setTime(11.0f);
	Invoke(S("showNapisy8"), 12.0f);
}

void Napisy::showNapisy8()
{
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("credits_6")), false, true, true, 240, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->setTime(11.0f);
	Invoke(S("showNapisy9"), 12.0f);
}

void Napisy::showNapisy9()
{
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("credits_7")), false, true, true, 240, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->setTime(11.0f);
	Invoke(S("showNapisy10"), 12.0f);
}

void Napisy::showNapisy10()
{
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("credits_8")), false, true, true, 240, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->setTime(7.0f);
	Invoke(S("showNapisy11"), 8.0f);
}

void Napisy::showNapisy11()
{
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("credits_9")), false, true, true, 240, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("credits2"))->GetComponent<TextFieldController>()->setTime(7.0f);
	Invoke(S("showNapisy12"), 8.0f);
}

void Napisy::showNapisy12()
{
	PlayerController::wc->fullStop();
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("MainMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
}
