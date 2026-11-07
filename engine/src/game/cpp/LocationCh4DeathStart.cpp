#include "../game_all.h"

void LocationCh4DeathStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -5.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("none"));
	PlayerController::pc->copySettingsToNPCs();
	MonoBehaviour::print(S("............................. LOCATION INFO  .................................."));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	P<TimelineAction> timelineAction = New<TimelineAction>(Timeline::t->textField);
	if (GameDataController::gd->getObjective(S("ship_launched")))
	{
		timelineAction->textWidth = 200;
		Timeline::t->textField->shift.x = -100.0f;
		Timeline::t->textField->shift.y = 50.0f;
		Timeline::t->textField->directionY = 1.0f;
		if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_no_air_bad"));
			Timeline::t->addAction(timelineAction);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1)
		{
			timelineAction->text = GameStrings::getString(GameStrings::results, S("r_d4_no_fuel_bad"));
			Timeline::t->addAction(timelineAction);
		}
	}
	timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->function = [this](String param) { end(param); };
	timelineAction->actionWithText = false;
	timelineAction->param = S("0");
	timelineAction->text = GameStrings::getString(GameStrings::results, S("day4_death"));
	Timeline::t->addAction(timelineAction);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_game_over);
	JukeboxAmbient::jb->changeAmbient(nullptr, 0.0f);
	GameObject::Find(S("barry_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
	GameObject::Find(S("cody_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
	if (!GameDataController::gd->getObjective(S("ship_launched")))
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane03"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		return;
	}
	GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane03"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		if (GameDataController::gd->getObjective(S("npc2_alive")))
		{
			GameObject::Find(S("barry_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else
		{
			GameObject::Find(S("barry_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
		if (GameDataController::gd->getObjective(S("npc3_alive")))
		{
			GameObject::Find(S("cody_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else
		{
			GameObject::Find(S("cody_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1)
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane03"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void LocationCh4DeathStart::end(String param)
{
	GameDataController::gd->politeLoad(GameDataController::CHAPTER_4_COMPLETE_AUTOSAVE);
}

void LocationCh4DeathStart::Update()
{
}
