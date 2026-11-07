#include "../game_all.h"

void LocationBugDeathStart::Start()
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
	timelineAction->param = S("0");
	timelineAction->textWidth = 190;
	Timeline::t->textField->shift.x = -80.0f;
	Timeline::t->textField->shift.y = 50.0f;
	Timeline::t->textField->directionY = 1.0f;
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_spiders_bad1")) + S(" ") + -GameDataController::gd->getObjectiveDetail(S("day1_complete")) + S(" ") + GameStrings::getString(GameStrings::results, S("day1_spiders_bad2"));
		Timeline::t->addAction(timelineAction);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_bugs_bad1")) + S(" ") + -GameDataController::gd->getObjectiveDetail(S("day1_complete")) + S(" ") + GameStrings::getString(GameStrings::results, S("day1_bugs_bad2"));
		Timeline::t->addAction(timelineAction);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_gas_bad1")) + S(" ") + -GameDataController::gd->getObjectiveDetail(S("day1_complete")) + S(" ") + GameStrings::getString(GameStrings::results, S("day1_gas_bad2"));
		Timeline::t->addAction(timelineAction);
	}
	timelineAction = New<TimelineAction>(Timeline::t->textField);
	timelineAction->function = [this](String param) { end(param); };
	timelineAction->actionWithText = false;
	timelineAction->param = S("0");
	Timeline::t->textField->directionY = 1.0f;
	timelineAction->textWidth = 190;
	Timeline::t->textField->shift.x = -80.0f;
	Timeline::t->textField->shift.y = 50.0f;
	timelineAction->text = GameStrings::getString(GameStrings::results, S("day1_death"));
	Timeline::t->addAction(timelineAction);
	GameObject::Find(S("Spider (1)"))->get_gameObject()->transform->set_position(ScreenControler::roundToNearestFullPixel2(GameObject::Find(S("Spider (1)"))->get_gameObject()->transform->get_position()));
	GameObject::Find(S("Spider (2)"))->get_gameObject()->transform->set_position(ScreenControler::roundToNearestFullPixel2(GameObject::Find(S("Spider (2)"))->get_gameObject()->transform->get_position()));
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_game_over);
	JukeboxAmbient::jb->changeAmbient(nullptr, 0.0f);
	if (GameDataController::gd->finishingLocation == S("Location1") || GameDataController::gd->finishingLocation == S("Location2") || GameDataController::gd->finishingLocation == S("LocationBaseUpstairs") || GameDataController::gd->finishingLocation == S("LocationBaseBathroom"))
	{
		GameObject::Find(S("Location"))->transform->Find(S("black"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		GameObject::Find(S("Location"))->transform->Find(S("black"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("plane01"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("plane02"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		GameObject::Find(S("player_gas_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("player_bugs_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("bugs_feast_1"))->transform->set_position(ScreenControler::roundToNearestFullPixel2(GameObject::Find(S("bugs_feast_1"))->transform->get_position()));
		GameObject::Find(S("bugs_feast_1"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Gas (1)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Gas (2)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Gas (3)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Gas (4)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Gas (5)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Gas"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Spider (1)"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Spider (2)"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		GameObject::Find(S("player_gas_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("player_bugs_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("bugs_feast_1"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Gas (1)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = true;
		GameObject::Find(S("Gas (2)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = true;
		GameObject::Find(S("Gas (3)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = true;
		GameObject::Find(S("Gas (4)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = true;
		GameObject::Find(S("Gas (5)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = true;
		GameObject::Find(S("Gas"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = true;
		GameObject::Find(S("Spider (1)"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Spider (2)"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		GameObject::Find(S("player_gas_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("player_bugs_dead_body"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("bugs_feast_1"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Gas (1)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Gas (2)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Gas (3)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Gas (4)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Gas (5)"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Gas"))->get_gameObject()->GetComponent<ParticleGenerator>()->started = false;
		GameObject::Find(S("Spider (1)"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Spider (2)"))->get_gameObject()->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Spider (1)"))->get_gameObject()->GetComponent<Animator>()->Play(S("eat_fast"));
		GameObject::Find(S("Spider (2)"))->get_gameObject()->GetComponent<Animator>()->Play(S("eat_fast"));
	}
}

void LocationBugDeathStart::end(String param)
{
	GameDataController::gd->politeLoad(GameDataController::CHAPTER_1_COMPLETE_AUTOSAVE);
}

void LocationBugDeathStart::Update()
{
}
