#include "../game_all.h"

void DemoStartController::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 0;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = -5.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->source = 10.0f;
	PlayerController::ssg->setStepType(S("none"));
	MonoBehaviour::print(S("............................. LOCATION INFO  .................................."));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(-999.0f, -999.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	GameObject::Find(S("inventory_button"))->GetComponent<InventoryButtonController>()->hide();
	GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->hide();
	Invoke(S("launch"), 1.0f);
}

void DemoStartController::launch()
{
	QuestionController::qc->showQuestion(S("^Don't Escape: 4 Days in a Wasteland ^^ARMOR GAMES DEMO. ^^This demo contains chapters 1 and 2."), QuestionController::PopupType::QUESTION, [this]() { yesClick(); }, 0, 0, [this]() { noClick(); }, S("Start Game / Continue"), S("Options"));
}

void DemoStartController::yesClick()
{
}

void DemoStartController::newGame(String param)
{
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("LocationDreamBugs"), WalkController::Direction::N);
}

void DemoStartController::noClick()
{
	PlayerController::wc->fullStop(true);
	if (PlayerController::wc->speed != 0.0f)
	{
		PlayerController::wc->forceAnimation(S("stand_"), false, true);
	}
	PlayerController::pc->spawnName = S("InfoExit");
	GameDataController::gd->previousLocation = SceneManager::GetActiveScene().get_name();
	GameDataController::gd->previousX = (int)PlayerController::wc->currentXY.x;
	GameDataController::gd->previousY = (int)PlayerController::wc->currentXY.y;
	CurtainController::cc->fadeOut(S("PauseMenu"), WalkController::Direction::NULL_, nullptr, nullptr, false, nullptr, 1.0f);
	AudioListener::set_pause(true);
}

void DemoStartController::Update()
{
}
