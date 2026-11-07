#include "../game_all.h"

void LanguageSelectorButton::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = String::Empty;
	range = 999.0f;
	updateState();
}

void LanguageSelectorButton::takeDoc(int i)
{
	doc = DialogueController::dc->dialogueOptions[i]->GetComponent<DialogueOptionController>();
}

void LanguageSelectorButton::clickAction()
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2(23.0f, 21.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	GameObject::Find(S("BottomText"))->transform->set_position(position);
	languageSelectorCaption->hideText();
	DialogueController::dc->callback = nullptr;
	takeDoc(0);
	MonoBehaviour::print(S("PICKING LANGUAGE"));
	DialogueController::dc->reset();
	int num = 0;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::languages, str(GameStrings_Language::EN));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/l_eng")));
	doc->lines = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->setObjective(String::Empty);
	doc->lines[doc->lines.Count() - 1]->action = [this](String lang) { changeLanguage(lang); };
	doc->lines[doc->lines.Count() - 1]->actionParam = str(GameStrings_Language::EN);
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::languages, str(GameStrings_Language::PL));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/l_pl")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String lang) { changeLanguage(lang); };
	doc->lines[doc->lines.Count() - 1]->actionParam = str(GameStrings_Language::PL);
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::languages, str(GameStrings_Language::DE));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/l_de")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String lang) { changeLanguage(lang); };
	doc->lines[doc->lines.Count() - 1]->actionParam = str(GameStrings_Language::DE);
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::gui, S("cancel"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(String::Empty);
	DialogueController::dc->initDialogue(doc->lines, String::Empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
	doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalk(val); };
	doc->lines[doc->lines.Count() - 1]->actionWithText = true;
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void LanguageSelectorButton::changeLanguage(String lang)
{
	PlayerPrefs::SetString(S("lang"), lang);
	PlayerPrefs::Save();
	GameStrings::readStrings(lang);
	ItemsManager::im->reloadAfterLanguageChange();
	endTalk(String::Empty);
	GameObject::Find(S("Caption"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("font_pick0")), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	GameObject::Find(S("Caption2"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("font_pick3")), false, true, true, 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	P<Button> component = GameObject::Find(S("PixelBtn"))->GetComponent<Button>();
	component->buttonText->viewText(S("[") + GameStrings::getString(GameStrings::gui, S("font_pick1")) + S("]"), false, true, true, 200);
	component->buttonText->keepAlive = true;
	component->buttonText->setTextColor(1.0f, 0.73f, 0.0f);
	component->buttonText->black->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
	P<Button> component2 = GameObject::Find(S("SmoothBtn"))->GetComponent<Button>();
	component2->buttonText->viewText(S("[") + GameStrings::getString(GameStrings::gui, S("font_pick2")) + S("]"), false, true, true, 200);
	component2->buttonText->keepAlive = true;
	component2->buttonText->setTextColor(1.0f, 0.73f, 0.0f);
	component2->buttonText->black->GetComponent<SpriteRenderer>()->set_color(Color(0.0f, 0.0f, 0.0f, 0.0f));
}

void LanguageSelectorButton::endTalk(String val)
{
	languageSelectorCaption->updateText();
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	updateState();
}

void LanguageSelectorButton::updateState()
{
	languageSelectorCaption->updateText();
	if (PlayerPrefs::GetString(S("lang"), str(GameStrings_Language::EN)) == str(GameStrings_Language::EN))
	{
		flag->set_sprite(flag_en);
	}
	if (PlayerPrefs::GetString(S("lang"), str(GameStrings_Language::EN)) == str(GameStrings_Language::PL))
	{
		flag->set_sprite(flag_pl);
	}
	if (PlayerPrefs::GetString(S("lang"), str(GameStrings_Language::DE)) == str(GameStrings_Language::DE))
	{
		flag->set_sprite(flag_de);
	}
}

void LanguageSelectorButton::clickAction2()
{
}

void LanguageSelectorButton::clickAction0()
{
}

void LanguageSelectorButton::whatOnClick0()
{
}

void LanguageSelectorButton::whatOnClick()
{
}
