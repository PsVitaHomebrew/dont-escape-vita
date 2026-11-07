#include "../game_all.h"

void LocationCh3DeathStart::Start()
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
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_thugs_bad"));
	}
	else
	{
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day3_storm_bad"));
	}
	Timeline::t->addAction(timelineAction);
	timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->function = [this](String param) { end(param); };
	timelineAction->actionWithText = false;
	timelineAction->param = S("0");
	Timeline::t->addAction(timelineAction);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_game_over);
	JukeboxAmbient::jb->changeAmbient(nullptr, 0.0f);
	GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	GameObject::Find(S("Location"))->transform->Find(S("plane01b"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	GameObject::Find(S("Location"))->transform->Find(S("plane02b"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		if (GameDataController::gd->finishingLocation == S("Location1") || GameDataController::gd->finishingLocation == S("Location2") || GameDataController::gd->finishingLocation == S("LocationBaseUpstairs") || GameDataController::gd->finishingLocation == S("LocationBaseBathroom") || GameDataController::gd->finishingLocation == S("LocationAttic1") || GameDataController::gd->finishingLocation == S("LocationAttic2") || GameDataController::gd->finishingLocation == S("LocationRoof1") || GameDataController::gd->finishingLocation == S("LocationRoof2"))
		{
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(false);
			GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		else
		{
			GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(true);
			GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
	else if (GameDataController::gd->finishingLocation == S("Location1") || GameDataController::gd->finishingLocation == S("Location2") || GameDataController::gd->finishingLocation == S("LocationBaseUpstairs") || GameDataController::gd->finishingLocation == S("LocationAttic1") || GameDataController::gd->finishingLocation == S("LocationAttic2") || GameDataController::gd->finishingLocation == S("LocationBaseBathroom"))
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane01b"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane02b"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GameObject::Find(S("Location"))->transform->Find(S("plane01b"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane02b"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		GameObject::Find(S("player_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2 || GameDataController::gd->getObjective(S("npc2_alive")))
		{
			GameObject::Find(S("barry_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2 || GameDataController::gd->getObjective(S("npc3_alive")))
		{
			GameObject::Find(S("cody_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
	{
		GameObject::Find(S("player_dead_body_b"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		if (GameDataController::gd->getObjectiveDetail(S("npc2_alive")) == 2 || GameDataController::gd->getObjective(S("npc2_alive")))
		{
			GameObject::Find(S("barry_dead_body_b"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
		if (GameDataController::gd->getObjectiveDetail(S("npc3_alive")) == 2 || GameDataController::gd->getObjective(S("npc3_alive")))
		{
			GameObject::Find(S("cody_dead_body_b"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		}
	}
}

void LocationCh3DeathStart::end(String param)
{
	GameDataController::gd->politeLoad(GameDataController::CHAPTER_3_COMPLETE_AUTOSAVE);
}

void LocationCh3DeathStart::Update()
{
}
