#include "../game_all.h"

void CreditsStart::Start()
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
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->buttonEnabled = false;
	component->gameObject->GetComponent<TextFieldController>()->OPTIONAL_MARGIN = 6;
	GameObject::Find(S("LocationManager"))->GetComponent<Napisy>()->showNapisy2();
}

void CreditsStart::mainMenu()
{
	PlayerController::wc->fullStop();
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("MainMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
}

void CreditsStart::showButton()
{
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("back")) + S("]"));
	component->workIfBusy = true;
	component->onClick = [this]() { mainMenu(); };
	component->buttonText->OPTIONAL_MARGIN = 6;
	component->set_enabled(true);
	component->buttonEnabled = true;
}

void CreditsStart::Update()
{
	if (skipit == 2)
	{
		timer += Time::get_deltaTime();
		if (timer > 3.0f)
		{
			timer = 0.0f;
			skipit = 1;
			P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
			component->initButton(S(" "));
			component->workIfBusy = false;
			component->onClick = nullptr;
			component->buttonEnabled = false;
		}
	}
	if ((Input::GetMouseButtonDown(0) || Input::GetKeyDown(KeyCode::Escape)) && skipit == 1)
	{
		skipit = 2;
		showButton();
	}
}
