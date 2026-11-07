#include "../game_all.h"

void ResultsChapterShipFuel::changeMusic(String s)
{
	rf->move(-0.63f, -0.25f);
	show_launch = 1.0f;
	Timeline::t->textField->directionY = -1.0f;
	Timeline::defaultTwidth = 140;
	Timeline::t->textField->shift = Vector2(-35.0f, -60.0f);
	changeDanger(s);
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->needShake = 5.0f;
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_attack2, true, 0.0f, 1.0f);
	GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_sprite(launch_sprite);
	GameObject::Find(S("ProgressBar"))->GetComponent<SpriteRenderer>()->set_sprite(launch_spriteF);
}

void ResultsChapterShipFuel::changeView(String s)
{
	Timeline::t->textField->directionY = -1.0f;
	Timeline::defaultTwidth = 140;
	Timeline::t->textField->shift = Vector2(-35.0f, -60.0f);
	changeDanger(s);
	show_flight = true;
}

void ResultsChapterShipFuel::Update()
{
	if (sr == nullptr)
	{
		return;
	}
	sr2->set_color(Color(1.0f, 1.0f, 1.0f, 1.0f - show_launch));
	if (show_launch > 0.0f)
	{
		show_launch -= Time::get_deltaTime();
	}
	if (show_launch < 0.0f)
	{
		show_launch = 0.0f;
	}
	if (show_flight)
	{
		time += Time::get_deltaTime() * 2.0f;
		if (time > 0.75f)
		{
			sr->set_sprite(fly_sprite_1);
		}
		else if (time > 0.5f)
		{
			sr->set_sprite(fly_sprite_2);
		}
		else if (time > 0.25f)
		{
			sr->set_sprite(fly_sprite_3);
		}
		else
		{
			sr->set_sprite(fly_sprite_4);
		}
		if (time > 0.75f)
		{
			sr2->set_sprite(fly_sprite_1F);
		}
		else if (time > 0.5f)
		{
			sr2->set_sprite(fly_sprite_2F);
		}
		else if (time > 0.25f)
		{
			sr2->set_sprite(fly_sprite_3F);
		}
		else
		{
			sr2->set_sprite(fly_sprite_4F);
		}
		if (time > 1.0f)
		{
			time = 0.0f;
		}
	}
}

void ResultsChapterShipFuel::chapterResult()
{
	Timeline::t->textField->shift = Vector2(-25.0f, 20.0f);
	sr = GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>();
	sr2 = GameObject::Find(S("ProgressBar"))->GetComponent<SpriteRenderer>();
	launch_sprite = Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/rocket_start"));
	fly_sprite_1 = Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/end_flight0"));
	fly_sprite_2 = Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/end_flight1"));
	fly_sprite_3 = Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/end_flight2"));
	fly_sprite_4 = Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/end_flight3"));
	launch_spriteF = Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/rocket_start_f"));
	fly_sprite_1F = Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/end_flight0_f"));
	fly_sprite_2F = Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/end_flight1_f"));
	fly_sprite_3F = Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/end_flight2_f"));
	fly_sprite_4F = Resources::Load<Sprite>(S("Bitmaps/Locations/LocationResults/end_flight3_f"));
	show_flight = false;
	time = 0.0f;
	surviavbleDanger = 20;
	danger = 0;
	removeDanger = 0;
	pbc->total = 100;
	changeDanger(str(pbc->total));
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_0"));
	Timeline::t->addAction(timelineAction);
	if (GameDataController::gd->getObjective(S("ship_launched")))
	{
		analytics_launched = S("true");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_launched"));
		Timeline::t->addAction(timelineAction);
		check(0, S("r_d4_cate"), S("c_ship_cate"));
		check(0, S("r_d4_hatch1"), S("c_ship_hatch"));
		check(0, S("r_d4_hatch2"), String::Empty);
		check(0, S("r_d4_hatch3"), String::Empty);
		check(0, S("r_d4_hatch4"), String::Empty);
		check(0, S("r_d4_hatch5"), String::Empty);
		check(0, S("r_d4_cate2"), S("c_ship_cate"));
		check(0, S("r_d4_cate3"), String::Empty);
		check(0, S("r_d4_cate4"), String::Empty);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { changeMusic(v); };
		timelineAction->actionWithText = true;
		timelineAction->param = S("-") + 0 + S("|hide");
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_1"));
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc2_alive")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_seat_cody_barry");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_cody_barry"));
			Timeline::t->addAction(timelineAction);
		}
		else if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_seat_cody");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_cody"));
			Timeline::t->addAction(timelineAction);
			if (GameDataController::gd->getObjective(S("npc2_joined")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_barry_dead"));
				Timeline::t->addAction(timelineAction);
			}
		}
		else if (GameDataController::gd->getObjective(S("npc2_alive")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_seat_barry");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_barry"));
			Timeline::t->addAction(timelineAction);
			if (GameDataController::gd->getObjective(S("npc3_joined")))
			{
				timelineAction = New<TimelineAction>(Timeline::t->textField);
				timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
				timelineAction->actionWithText = true;
				timelineAction->param = S("-") + 0;
				timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_cody_dead"));
				Timeline::t->addAction(timelineAction);
			}
		}
		else
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_seat_nobody");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_nobody"));
			Timeline::t->addAction(timelineAction);
		}
		int num = 0;
		num += GameDataController::gd->getObjectiveDetail(S("outpost_score_a"));
		num += GameDataController::gd->getObjectiveDetail(S("outpost_score_b"));
		num += GameDataController::gd->getObjectiveDetail(S("outpost_score_c"));
		num += GameDataController::gd->getObjectiveDetail(S("outpost_score_d"));
		num += GameDataController::gd->getObjectiveDetail(S("outpost_score_e"));
		analytics_mixture = num + S("/10");
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { changeView(v); };
		timelineAction->actionWithText = true;
		timelineAction->param = S("-") + 0 + S("|hide");
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_fuel_mixture1"));
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && !GameDataController::gd->getObjective(S("thug_killed_bathroom")))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_ship_razor");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_razor1"));
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + String::Empty;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_razor2"));
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + String::Empty;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_razor3"));
			Timeline::t->addAction(timelineAction);
		}
		if ((GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getObjective(S("gasstation_sarge_convinced")) && !GameDataController::gd->getObjective(S("cs_food_poisioned"))) || (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && GameDataController::gd->getObjective(S("restaurant_sarge_encountered"))))
		{
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/c_ship_sarge");
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_sarge1"));
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + String::Empty;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_sarge2"));
			Timeline::t->addAction(timelineAction);
			timelineAction = New<TimelineAction>(Timeline::t->textField);
			timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
			timelineAction->actionWithText = true;
			timelineAction->param = S("-") + 0 + String::Empty;
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_sarge3"));
			Timeline::t->addAction(timelineAction);
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->actionWithText = true;
		timelineAction->param = S("-") + 0 + S("|hide");
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_fuel_mixture2"));
		Timeline::t->addAction(timelineAction);
		String key = String::Empty;
		String text = String::Empty;
		if (num == 0)
		{
			key = S("r_d4_fuel_mixture_0");
		}
		if (num > 0 && num <= 3)
		{
			key = S("r_d4_fuel_mixture_1");
		}
		if (num > 3 && num <= 6)
		{
			key = S("r_d4_fuel_mixture_2");
		}
		if (num > 6 && num <= 9)
		{
			key = S("r_d4_fuel_mixture_3");
		}
		if (num == 10)
		{
			key = S("r_d4_fuel_mixture_4");
		}
		if (num == 0)
		{
			text = S("c_mix_1");
		}
		if (num > 0 && num <= 3)
		{
			text = S("c_mix_2");
		}
		if (num > 3 && num <= 6)
		{
			text = S("c_mix_3");
		}
		if (num > 6 && num <= 9)
		{
			text = S("c_mix_4");
		}
		if (num == 10)
		{
			text = S("c_mix_5");
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->actionWithText = true;
		timelineAction->param = S("-") + 0 + S("|Bitmaps/Locations/LocationResults/") + text;
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_fuel_mixture3"));
		Timeline::t->addAction(timelineAction);
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::changeDanger(v); };
		timelineAction->actionWithText = false;
		timelineAction->param = S("-") + num * 2;
		removeDanger += num * 2;
		timelineAction->text = GameStrings::getString(GameStrings::results, key);
		Timeline::t->addAction(timelineAction);
		if (GameDataController::gd->getObjective(S("outpost_navigation_chip_inserted")))
		{
			analytics_nav = S("true");
			check(0, S("r_d4_nav_inserted"), S("c_nav_inserted"));
			check(20, S("r_d4_nav_inserted2"), String::Empty);
		}
		else
		{
			check(0, S("r_d4_nav_missing"), S("c_nav_missing"));
			check(0, S("r_d4_nav_missing2"), String::Empty);
		}
		if (GameDataController::gd->getObjective(S("outpost_calibrator_inserted")))
		{
			analytics_calib = S("true");
			check(0, S("r_d4_calibrator_inserted"), S("c_calibrator_inserted"));
			check(20, S("r_d4_calibrator_inserted2"), String::Empty);
		}
		else
		{
			check(0, S("r_d4_calibrator_missing"), S("c_calibrator_missing"));
			check(0, S("r_d4_calibrator_missing2"), String::Empty);
		}
		if (GameDataController::gd->getObjective(S("outpost_hull_repaired_outside")))
		{
			analytics_hull = S("true");
			check(0, S("r_d4_hull_outside_fixed"), S("c_hull_outside_fixed"));
			check(20, S("r_d4_hull_outside_fixed2"), String::Empty);
		}
		else
		{
			check(0, S("r_d4_hull_outside_broken"), S("c_hull_outside_broken"));
			check(0, S("r_d4_hull_outside_broken2"), String::Empty);
		}
		if (GameDataController::gd->getObjective(S("outpost_catalyst_used")))
		{
			analytics_catalyst = S("true");
			check(0, S("r_d4_catalyst_inserted"), S("c_ship_catalyst"));
			check(20, S("r_d4_catalyst_inserted2"), String::Empty);
		}
		else
		{
			check(0, S("r_d4_catalyst_missing"), S("c_ship_catalyst"));
			check(0, S("r_d4_catalyst_missing2"), String::Empty);
		}
		if (danger - removeDanger <= surviavbleDanger)
		{
			check(0, S("r_d4_no_fuel1"), S("c_ship_cate"));
			check(0, S("r_d4_no_fuel2"), S("hide"));
			check(0, S("r_d4_no_fuel3"), String::Empty);
			check(0, S("r_d4_no_fuel4"), String::Empty);
			check(0, S("r_d4_no_fuel5"), String::Empty);
			check(0, S("r_d4_no_fuel6"), String::Empty);
		}
		else
		{
			check(0, S("r_d4_no_fuel_dead1"), String::Empty);
			check(0, S("r_d4_no_fuel_dead2"), String::Empty);
			check(0, S("r_d4_no_fuel_dead3"), String::Empty);
		}
		if (danger - removeDanger <= 0)
		{
			winQuality = 3;
		}
		else
		{
			winQuality = 2;
		}
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->function = [this](String v) { ResultsController::liveOrDie(v); };
		timelineAction->actionWithText = true;
		timelineAction->param = S("0");
		timelineAction->text = String::Empty;
		Timeline::t->addAction(timelineAction);
	}
	else
	{
		timelineAction = New<TimelineAction>(Timeline::t->textField);
		timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_no_launch"));
		timelineAction->function = [this](String v) { ResultsController::liveOrDie(v); };
		Timeline::t->addAction(timelineAction);
	}
}
