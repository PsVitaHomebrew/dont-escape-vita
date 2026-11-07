#include "../game_all.h"

void LocationSiderealClimbStart::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->scaleFactor = 0.4f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.5f;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 240.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Off);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_3, 1.0f);
	PlayerController::pc->allowDrop = false;
	InventoryButtonController::ibc->hide();
	GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->hide();
	PlayerController::pc->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 0.0f, 0.0f));
	npc1->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 0.0f, 0.0f));
	npc2->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 0.0f, 0.0f));
	npc3->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 0.0f, 0.0f));
	npc1->currentXY = PlayerController::wc->currentXY;
	npc2->currentXY = PlayerController::wc->currentXY;
	npc3->currentXY = PlayerController::wc->currentXY;
	if (GameDataController::gd->gameTime < 510 || GameDataController::gd->gameTime >= 1050)
	{
		moong->set_enabled(true);
	}
	else
	{
		moong->set_enabled(false);
	}
	npc1->pathRestricted = false;
	npc2->pathRestricted = false;
	npc3->pathRestricted = false;
	npc1->gameObject->GetComponent<NPCActionController>()->setCollider(-1);
	npc2->gameObject->GetComponent<NPCActionController>()->setCollider(-1);
	npc3->gameObject->GetComponent<NPCActionController>()->setCollider(-1);
	npc1->currentXY = PlayerController::wc->currentXY;
	npc2->currentXY = PlayerController::wc->currentXY;
	npc3->currentXY = PlayerController::wc->currentXY;
	npc1->setSimpleTarget(PlayerController::wc->currentXY);
	npc2->setSimpleTarget(PlayerController::wc->currentXY);
	npc3->setSimpleTarget(PlayerController::wc->currentXY);
}

void LocationSiderealClimbStart::suwsuw(P<NPCWalkController> npc, int dist)
{
	Vector2 currentXY = PlayerController::wc->currentXY;
	currentXY.x += dist;
	currentXY.y += (float)dist * 0.55f;
	npc->currentXY = currentXY;
	npc->clearTarget();
	if (PlayerController::wc->currentSpeed.x > 0.0f)
	{
		npc->forceAnimation(S("walk_e"));
	}
	else if (PlayerController::wc->currentSpeed.x < 0.0f)
	{
		npc->forceAnimation(S("walk_e"), true);
	}
	else
	{
		npc->forceAnimation(S("stand_se"));
	}
}

void LocationSiderealClimbStart::Update()
{
	przesuw(tlo1, 0.2f, 0.0f);
	przesuw(tlo2, -0.04f, 7.0f);
	przesuw(tlo3, -0.03f, 7.0f);
	przesuw(tlo4, -0.02f, 7.0f);
	suwsuw(npc1, -20);
	suwsuw(npc2, -40);
	suwsuw(npc3, -60);
}

bool LocationSiderealClimbStart::nawig(P<NPCWalkController> npc, P<GameObject> nav)
{
	if (PlayerController::pc->gameObject->transform->get_position().x > nav->transform->get_position().x)
	{
		npc->setTargetV3(nav->transform->get_position());
		return true;
	}
	return false;
}

void LocationSiderealClimbStart::przesuw(P<GameObject> go, float skala, float bonbon)
{
	Vector2 vector = Vector2();
	float z = go->transform->get_position().z;
	vector.x = PlayerController::wc->currentXY.x;
	vector.y = PlayerController::wc->currentXY.y;
	Vector3 vector2 = Vector3(vector.x, (float)shift - vector.x * skala * 1.0f + bonbon, go->transform->get_position().z);
	vector2.z = Camera::get_main()->WorldToScreenPoint(go->transform->get_position()).z;
	go->transform->set_position(Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(vector2)));
	go->transform->set_position(Vector3(0.0f, go->transform->get_position().y, z));
}
