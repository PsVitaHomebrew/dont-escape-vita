#include "../game_all.h"

void LocationAirlockStart::Start()
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
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->esc = GameObject::Find(S("MoonAirlockExit"))->GetComponent<MoonAirlockExit>();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->suit_breathing, 1.0f);
	audioSouruce->set_loop(true);
	audioSouruce->set_clip(SoundsManagerController::sm->moon);
	audioSouruce->set_volume(1.0f);
	audioSouruce->Play();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->suit_breathing, 0.75f, AudioReverbPreset::Underwater);
	PlayerController::ssg->setStepType2(StepSoundGenerator::MOON, AudioReverbPreset::Underwater);
}

void LocationAirlockStart::Update()
{
	time -= Time::get_deltaTime();
	if (time <= 0.0f)
	{
		time = Random::Range(1.0f, 10.0f);
		float num = Random::Range(0.2f, 3.0f);
		if (num < 1.0f)
		{
			rumbler->PlayOneShot(SoundsManagerController::sm->rumble_2s);
		}
		else
		{
			rumbler->PlayOneShot(SoundsManagerController::sm->rumble_4s);
		}
		rumbler->set_pitch(Random::Range(0.9f, 1.1f));
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->needShake = num;
	}
}
