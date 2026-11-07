#include "../game_all.h"

void SaveMenuStart::Start()
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
	String text = S("-");
	if (GameDataController::wantSave)
	{
		text = GameStrings::getString(GameStrings::gui, S("save_select"));
		GameObject::Find(S("Location"))->transform->Find(S("save_back"))->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameObject::Find(S("Location"))->transform->Find(S("load_back"))->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		text = GameStrings::getString(GameStrings::gui, S("load_select"));
		GameObject::Find(S("Location"))->transform->Find(S("save_back"))->GetComponent<SpriteRenderer>()->set_enabled(false);
		GameObject::Find(S("Location"))->transform->Find(S("load_back"))->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	GameObject::Find(S("Caption_MenuName"))->transform->set_position(ScreenControler::roundToNearestFullPixel2(GameObject::Find(S("Caption_MenuName"))->transform->get_position()));
	GameObject::Find(S("Caption_SlotName"))->transform->set_position(ScreenControler::roundToNearestFullPixel2(GameObject::Find(S("Caption_SlotName"))->transform->get_position()));
	GameObject::Find(S("Caption_SlotDay"))->transform->set_position(ScreenControler::roundToNearestFullPixel2(GameObject::Find(S("Caption_SlotDay"))->transform->get_position()));
	GameObject::Find(S("Caption_SlotDate"))->transform->set_position(ScreenControler::roundToNearestFullPixel2(GameObject::Find(S("Caption_SlotDate"))->transform->get_position()));
	GameObject::Find(S("Caption_MenuName"))->GetComponent<TextFieldController>()->viewText(text, false, true, true, 200, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("Caption_MenuName"))->GetComponent<TextFieldController>()->keepAlive = true;
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("back")) + S("]"));
	component->buttonText->OPTIONAL_MARGIN = 6;
	component->workIfBusy = false;
	component->onClick = [this]() { continueGame(); };
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->escButton = component;
	if (PlayerPrefs::GetString(S("lang"), str(GameStrings::Language::EN)) == str(GameStrings::Language::PL))
	{
		ENGINE_TODO("Thread.CurrentThread.CurrentCulture = new CultureInfo(\"de-DE\")");
	}
	else
	{
		ENGINE_TODO("Thread.CurrentThread.CurrentCulture = new CultureInfo(\"en-US\")");
	}
}

void SaveMenuStart::continueGame()
{
	PlayerController::pc->spawnName = S("InfoExit");
	PlayerController::wc->fullStop();
	if (GameDataController::gd->previousLocation == S("MainMenu"))
	{
		CurtainController::cc->fadeOut(S("MainMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
	}
	else
	{
		CurtainController::cc->fadeOut(S("PauseMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
	}
}

void SaveMenuStart::Update()
{
}
