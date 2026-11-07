#include "../game_all.h"

void LocationSiderealPCStart::Start()
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
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->esc = GameObject::Find(S("SiderealPCExit"))->GetComponent<SiderealPCExit>();
	failsafe = false;
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_mystery);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->pc_noise, 1.0f);
	GameObject::Find(S("PC_mail"))->GetComponent<SiderealPCMail>()->updateState();
}

void LocationSiderealPCStart::resetMail()
{
	GameObject::Find(S("PC_mail"))->GetComponent<SiderealPCMail>()->updateAll();
}

void LocationSiderealPCStart::Update()
{
}
