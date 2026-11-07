#include "../game_all.h"

void FontSelectorStart::Start()
{
	PlayerPrefs::SetString(S("lang"), str(GameStrings::Language::EN));
	PlayerPrefs::Save();
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
	caption = GameObject::Find(S("Caption"))->GetComponent<TextFieldController>();
	caption->force_pixel_font = true;
	caption->viewText(GameStrings::getString(GameStrings::gui, S("font_pick0")), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	caption->keepAlive = true;
	caption->transform->set_position(ScreenControler::roundToNearestFullPixel2(caption->transform->get_position()));
	caption2 = GameObject::Find(S("Caption2"))->GetComponent<TextFieldController>();
	caption2->force_pixel_font = true;
	caption2->viewText(GameStrings::getString(GameStrings::gui, S("font_pick3")), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	caption2->keepAlive = true;
	caption2->transform->set_position(ScreenControler::roundToNearestFullPixel2(caption->transform->get_position()));
	bottom = GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>();
	bottom->force_pixel_font = true;
	languageCaption = GameObject::Find(S("LanguageIcon"))->GetComponent<TextFieldController>();
	languageCaption->force_pixel_font = true;
	languageIcon = GameObject::Find(S("LanguageIcon"))->GetComponent<LanguageSelectorCaption>();
	P<Button> component = GameObject::Find(S("PixelBtn"))->GetComponent<Button>();
	component->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("font_pick1")) + S("]"));
	component->buttonText->force_pixel_font = true;
	component->buttonText->force_smooth_font = false;
	component->buttonText->updateFont();
	component->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("font_pick1")) + S("]"));
	component->workIfBusy = false;
	component->onClick = [this]() { selectPixel(); };
	component->onHover = [this]() { previewPixel(); };
	P<Button> component2 = GameObject::Find(S("SmoothBtn"))->GetComponent<Button>();
	component2->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("font_pick2")) + S("]"));
	component2->buttonText->force_smooth_font = true;
	component2->buttonText->force_pixel_font = false;
	component2->buttonText->updateFont();
	component2->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("font_pick2")) + S("]"));
	component2->workIfBusy = false;
	component2->onClick = [this]() { selectSmooth(); };
	component2->onHover = [this]() { previewSmooth(); };
	if ((bool)PlayerController::wc)
	{
		PlayerController::wc->currentXY.x = 1000.0f;
		PlayerController::wc->currentXY.y = 1000.0f;
		PlayerController::wc->clearTarget();
	}
}

void FontSelectorStart::selectPixel()
{
	PlayerPrefs::SetString(S("font"), S("pixel"));
	PlayerPrefs::Save();
	pickFont();
}

void FontSelectorStart::previewPixel()
{
	MonoBehaviour::print(S("PREVIEW PIXEL FONT"));
	caption->force_smooth_font = false;
	caption->force_pixel_font = true;
	caption->updateFont();
	caption->viewText(GameStrings::getString(GameStrings::gui, S("font_pick0")), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	caption2->force_smooth_font = false;
	caption2->force_pixel_font = true;
	caption2->updateFont();
	caption2->viewText(GameStrings::getString(GameStrings::gui, S("font_pick3")), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	languageCaption = GameObject::Find(S("LanguageIcon"))->GetComponent<TextFieldController>();
	languageCaption->force_smooth_font = false;
	languageCaption->force_pixel_font = true;
	languageCaption->updateFont();
	languageIcon->updateText();
	bottom->force_smooth_font = false;
	bottom->force_pixel_font = true;
	bottom->updateFont();
}

void FontSelectorStart::selectSmooth()
{
	PlayerPrefs::SetString(S("font"), S("smooth"));
	PlayerPrefs::Save();
	pickFont();
}

void FontSelectorStart::previewSmooth()
{
	MonoBehaviour::print(S("PREVIEW SMOOTH FONT"));
	caption->force_smooth_font = true;
	caption->force_pixel_font = false;
	caption->updateFont();
	caption->viewText(GameStrings::getString(GameStrings::gui, S("font_pick0")), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	caption2->force_smooth_font = true;
	caption2->force_pixel_font = false;
	caption2->updateFont();
	caption2->viewText(GameStrings::getString(GameStrings::gui, S("font_pick3")), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	languageCaption = GameObject::Find(S("LanguageIcon"))->GetComponent<TextFieldController>();
	languageCaption->force_smooth_font = true;
	languageCaption->force_pixel_font = false;
	languageCaption->updateFont();
	languageIcon->updateText();
	bottom->force_smooth_font = true;
	bottom->force_pixel_font = false;
	bottom->updateFont();
}

void FontSelectorStart::pickFont()
{
	PlayerPrefs::Save();
	Array<P<TextFieldController>> array = Resources::FindObjectsOfTypeAll<TextFieldController>();
	for (int i = 0; i < array.Length(); i++)
	{
		array[i].cast<TextFieldController>()->updateFont();
	}
	PlayerController::wc->fullStop();
	PlayerController::pc->spawnName = S("InfoExit");
	CurtainController::cc->fadeOut(S("MainMenu"), WalkController::Direction::S_, S("action_stnd_s"), nullptr, false, nullptr, CurtainController::MENU_CURTAIN_SPEED);
}

void FontSelectorStart::Update()
{
}
