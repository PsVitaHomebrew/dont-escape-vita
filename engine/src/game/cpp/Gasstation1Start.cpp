#include "../game_all.h"

void Gasstation1Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.004f;
	PlayerController::wc->shadow->fadeRateH = 0.004f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 5.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 260.0f;
	PlayerController::ssg->setStepType(S("road"));
	GameDataController::gd->setObjective(S("visited_gasstation1"), true);
	GameDataController::gd->setObjective(S("bridge_westside"), true);
	PlayerController::pc->copySettingsToNPCs();
	if (GameDataController::gd->getObjectiveDetail(S("map_restaurant_revealed")) == TravelAgency::LOCATION_STATUS_UNREACHABLE)
	{
		GameDataController::gd->setObjectiveDetail(S("map_restaurant_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	}
	if (GameDataController::gd->getObjectiveDetail(S("map_houseb_revealed")) == TravelAgency::LOCATION_STATUS_UNREACHABLE)
	{
		GameDataController::gd->setObjectiveDetail(S("map_houseb_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	}
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 1.0f);
	if (GameDataController::gd->getCurrentDay() < 3 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		GameObject::Find(S("Column1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Column2"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Column3"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane00"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Column1_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Column2_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Column3_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane00_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getCurrentDay() == 1)
		{
			GameObject::Find(S("Location"))->transform->Find(S("plane00_spiders"))->GetComponent<SpriteRenderer>()->set_sprite(spiders1);
		}
		else
		{
			GameObject::Find(S("Location"))->transform->Find(S("plane00_spiders"))->GetComponent<SpriteRenderer>()->set_sprite(spiders2);
		}
	}
	else
	{
		GameObject::Find(S("Column1"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Column2"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Column3"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane00"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Column1_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Column2_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Column3_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane00_spiders"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			sr->set_enabled(true);
			if (GameDataController::gd->gameTime < 600)
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (GameDataController::gd->gameTime < 650)
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.8f));
			}
			else if (GameDataController::gd->gameTime < 700)
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.6f));
			}
			else if (GameDataController::gd->gameTime < 750)
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.4f));
			}
			else if (GameDataController::gd->gameTime < 800)
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.2f));
			}
			else
			{
				sr->set_color(Color(1.0f, 1.0f, 1.0f, 0.1f));
			}
		}
		else
		{
			sr->set_enabled(false);
		}
	}
	else
	{
		sr->set_enabled(false);
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->canPickUpItems();
	GameObject::Find(S("clock"))->GetComponent<ClockController>()->showFinal();
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_player_fallen")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && ItemsManager::im->getItem(S("rifle_6"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
	{
		GameObject::Find(S("clock"))->GetComponent<ClockController>()->hide();
		PlayerController::pc->allowDrop = false;
		Invoke(S("spiderAttack2"), 1.0f);
		GameDataController::gd->setObjective(S("gasstation_spider_player_fallen"), true);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->cantPickupItems();
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_scare, true, 0.0f, 0.0f);
	}
	else if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_player_fallen")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && ItemsManager::im->getItem(S("rifle_6"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
	{
		GameObject::Find(S("clock"))->GetComponent<ClockController>()->hide();
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->cantPickupItems();
		PlayerController::pc->allowDrop = false;
		spiderAttack2b();
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_scare, true, 0.0f, 0.0f);
	}
	else if (GameDataController::gd->getCurrentDay() == 1 && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a, true, 1.0f, 3.0f);
	}
	else if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getObjective(S("sidereal_base_located")) && !GameDataController::gd->getObjective(S("gasstation_sarge_reason")))
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	}
	else if (GameDataController::gd->getObjective(S("gasstation_sarge_shot")))
	{
		JukeboxMusic::jb->changeMusic(nullptr);
	}
	else
	{
		JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_3a);
	}
	if (GameDataController::gd->getCurrentDay() != 3 || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 0 || !GameDataController::gd->getObjective(S("sidereal_base_located")) || GameDataController::gd->getObjective(S("thugs_gasstation_talk")))
	{
		return;
	}
	GameDataController::gd->setObjectiveDetail(S("thugs_gasstation_talk"), Random::Range(0, 7));
	Invoke(S("thugTalk"), 1.0f);
	GameDataController::gd->setObjective(S("gasstation_map_warned"), true);
	if (!GameDataController::gd->getObjective(S("thugs_gasstation_spotted")))
	{
		GameDataController::gd->setObjective(S("thugs_gasstation_spotted"), true);
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		Vector3 color_b = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		DialogueController::dc->initDialogue(list, S("gasstation_hear_thugs1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color_b);
		if (GameDataController::gd->getObjective(S("npc2_alive")) || GameDataController::gd->getObjective(S("npc3_alive")))
		{
			list[1]->text = GameStrings::getString(GameStrings::dialogues, S("gasstation_hear_thugs2_2_b"));
		}
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
	}
}

void Gasstation1Start::thugTalk()
{
	if (tf != nullptr)
	{
		tf->dissmiss();
	}
	if (GameDataController::gd->getObjectiveDetail(S("thugs_gasstation_talk")) == 0 || GameDataController::gd->getObjectiveDetail(S("thugs_gasstation_talk")) == 2 || GameDataController::gd->getObjectiveDetail(S("thugs_gasstation_talk")) == 4 || GameDataController::gd->getObjectiveDetail(S("thugs_gasstation_talk")) == 6)
	{
		tf = tf1;
		color = color1;
	}
	else
	{
		tf = tf2;
		color = color2;
	}
	String text = GameStrings::getString(GameStrings::dialogues, S("thugs_gasstation_talk_") + GameDataController::gd->getObjectiveDetail(S("thugs_gasstation_talk")));
	float alpha = Random::Range(0.2f, 0.4f);
	tf->setAlpha(alpha);
	tf->viewText(text, false, true, true, 100, color.x, color.y, color.z, 0.0f, 0.0f, 0.0f, 0.25f, false, true);
	tf->setAlpha(alpha);
	Invoke(S("thugTalk"), (float)text.Length() * 0.25f + Random::Range(1.0f, 2.0f));
	if (GameDataController::gd->getObjectiveDetail(S("thugs_gasstation_talk")) + 1 > 7)
	{
		GameDataController::gd->setObjectiveDetail(S("thugs_gasstation_talk"), 0);
	}
	else
	{
		GameDataController::gd->setObjectiveDetail(S("thugs_gasstation_talk"), GameDataController::gd->getObjectiveDetail(S("thugs_gasstation_talk")) + 1);
	}
}

void Gasstation1Start::spiderAttack()
{
	MonoBehaviour::print(S("SIADAJ FRED"));
	PlayerController::pc->setBusy(true);
	PlayerController::wc->speed = 0.0f;
	PlayerController::wc->dir = WalkController::Direction::W;
	PlayerController::wc->forceAnimation(S("sit_fall"), true);
	Invoke(S("spiderAttack2"), 0.5f);
	GameObject::Find(S("clock"))->GetComponent<ClockController>()->hide();
}

void Gasstation1Start::spiderAttack2()
{
	PlayerController::wc->dir = WalkController::Direction::W;
	PlayerController::pc->gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
	PlayerController::wc->forceAnimation(S("sit_strugle"), true);
	PlayerController::pc->setBusy(false);
	PlayerController::pc->gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
	PlayerController::wc->setCurrentAnimClip(S("sit_strugle"));
	PlayerController::wc->speed = 0.0f;
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->cantPickupItems();
	GameObject::Find(S("clock"))->GetComponent<ClockController>()->hide();
}

void Gasstation1Start::spiderAttack2b()
{
	PlayerController::wc->dir = WalkController::Direction::W;
	PlayerController::pc->gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
	PlayerController::wc->forceAnimation(S("sit_strugle"), true);
	PlayerController::pc->setBusy(true);
	PlayerController::pc->gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
	PlayerController::wc->setCurrentAnimClip(S("sit_strugle"));
	PlayerController::wc->speed = 0.0f;
	Invoke(S("spiderAttack2"), 0.5f);
	GameObject::Find(S("clock"))->GetComponent<ClockController>()->hide();
}

void Gasstation1Start::Update()
{
}
