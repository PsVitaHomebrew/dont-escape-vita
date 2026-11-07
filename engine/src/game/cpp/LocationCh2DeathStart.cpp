#include "../game_all.h"

void LocationCh2DeathStart::Start()
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
	timelineAction->textWidth = 200;
	Timeline::t->textField->shift.x = -100.0f;
	Timeline::t->textField->shift.y = 50.0f;
	Timeline::t->textField->directionY = 1.0f;
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_heat_bad"));
		Timeline::t->addAction(timelineAction);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
	{
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_cold_bad"));
		Timeline::t->addAction(timelineAction);
	}
	timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->function = [this](String param) { end(param); };
	timelineAction->actionWithText = false;
	timelineAction->param = S("0");
	timelineAction->text = GameStrings::getString(GameStrings::results, S("day2_death"));
	Timeline::t->addAction(timelineAction);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_game_over);
	JukeboxAmbient::jb->changeAmbient(nullptr, 0.0f);
	if (GameDataController::gd->finishingLocation == S("Location1") || GameDataController::gd->finishingLocation == S("Location2") || GameDataController::gd->finishingLocation == S("LocationBaseUpstairs") || GameDataController::gd->finishingLocation == S("LocationAttic1") || GameDataController::gd->finishingLocation == S("LocationAttic2") || GameDataController::gd->finishingLocation == S("LocationBaseBathroom"))
	{
		GameObject::Find(S("Location"))->transform->Find(S("black"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(false);
			GameObject::Find(S("Location"))->transform->Find(S("plane_cave"))->GetComponent<SpriteRenderer>()->set_enabled(false);
			GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(true);
			GameObject::Find(S("Location"))->transform->Find(S("plane_random1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
			GameObject::Find(S("Location"))->transform->Find(S("plane_random2"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
		else
		{
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(true);
			GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(false);
			GameObject::Find(S("Location"))->transform->Find(S("plane_cave"))->GetComponent<SpriteRenderer>()->set_enabled(false);
			GameObject::Find(S("Location"))->transform->Find(S("plane_random1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
			GameObject::Find(S("Location"))->transform->Find(S("plane_random2"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
	else if (GameDataController::gd->finishingLocation == S("LocationCave"))
	{
		GameObject::Find(S("Location"))->transform->Find(S("black"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane_cave"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane_random1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane_random2"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		GameObject::Find(S("Location"))->transform->Find(S("black"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			GameObject::Find(S("Location"))->transform->Find(S("plane_random1"))->GetComponent<SpriteRenderer>()->set_enabled(false);
			GameObject::Find(S("Location"))->transform->Find(S("plane_random2"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			GameObject::Find(S("Location"))->transform->Find(S("plane_random1"))->GetComponent<SpriteRenderer>()->set_enabled(true);
			GameObject::Find(S("Location"))->transform->Find(S("plane_random2"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
		GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
	{
		GameObject::Find(S("player_cold_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjective(S("npc2_joined")))
		{
			GameObject::Find(S("barry_cold_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else
		{
			GameObject::Find(S("barry_cold_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")))
		{
			GameObject::Find(S("cody_cold_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else
		{
			GameObject::Find(S("cody_cold_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
	{
		GameObject::Find(S("player_hot_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjective(S("npc2_joined")))
		{
			GameObject::Find(S("barry_hot_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else
		{
			GameObject::Find(S("barry_hot_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
		if (GameDataController::gd->getObjective(S("npc3_joined")))
		{
			GameObject::Find(S("cody_hot_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else
		{
			GameObject::Find(S("cody_hot_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
}

void LocationCh2DeathStart::end(String param)
{
	GameDataController::gd->politeLoad(GameDataController::CHAPTER_2_COMPLETE_AUTOSAVE);
}

void LocationCh2DeathStart::Update()
{
}
