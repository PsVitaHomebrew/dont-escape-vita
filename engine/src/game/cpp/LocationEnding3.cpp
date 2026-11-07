#include "../game_all.h"

void LocationEnding3::Start()
{
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_3, 0.75f);
	GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->hide();
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0015f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 8.0f;
	PlayerController::wc->shadow->startAlpha = 0.25f;
	PlayerController::wc->shadow->source = 200.0f;
	PlayerController::ssg->setStepType(S("dirt"));
	PlayerController::wc->shadow->scaleFactor = 0.3f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->speed = 0.0f;
	PlayerController::wc->dir = WalkController::Direction::SE;
	PlayerController::wc->currentXY = Vector2(-51.0f, -28.0f);
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	PlayerController::wc->busy = true;
	Invoke(S("nextScene"), 5.0f);
}

void LocationEnding3::nextScene()
{
	PlayerController::pc->setBusy(true);
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("Ending5"), WalkController::Direction::S_, nullptr, nullptr, false, nullptr, 1.0f);
}

void LocationEnding3::Update()
{
}
