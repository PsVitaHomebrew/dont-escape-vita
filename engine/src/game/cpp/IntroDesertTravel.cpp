#include "../game_all.h"

void IntroDesertTravel::Start()
{
	realPosition = Vector2(gameObject->transform->get_position().x, gameObject->transform->get_position().y);
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	colliderManager->setTarget(gameObject);
	animationFlip = true;
	characterAnimationName = S("action_stnd_e");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("intro_desert");
	teleport = true;
	range = 10000.0f;
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->buttonEnabled = false;
	component->onClick = nullptr;
	component->workIfBusy = false;
	component->set_enabled(false);
	component->GetComponent<BoxCollider2D>()->set_enabled(false);
	component->GetComponent<Button>()->set_enabled(false);
}

void IntroDesertTravel::Update()
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
			component->GetComponent<BoxCollider2D>()->set_enabled(false);
			component->set_enabled(false);
			component->buttonEnabled = false;
		}
	}
	if ((Input::GetMouseButtonDown(0) || Input::GetKeyDown(KeyCode::Escape)) && skipit == 1)
	{
		skipit = 2;
		showButton();
	}
}

void IntroDesertTravel::clickAction()
{
}

void IntroDesertTravel::gogo()
{
	GameDataController::gd->setObjective(S("intro_desert_walked"), true);
	GameObject::Find(S("FakePlayer"))->GetComponent<Animator>()->Play(S("FakePlayerWalk"));
	updateState();
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_main, false);
	Invoke(S("showIntro1"), 5.0f);
	Invoke(S("showIntro1b"), 10.0f);
	Invoke(S("showIntro2"), 14.0f);
	Invoke(S("showIntro1b"), 20.0f);
	Invoke(S("allowSkip"), 6.0f);
}

void IntroDesertTravel::updateState()
{
	if (GameDataController::gd->getObjective(S("intro_desert_walked")))
	{
		setCollider(-1);
	}
	else
	{
		setCollider(0);
	}
}

void IntroDesertTravel::allowSkip()
{
	skipit = 1;
}

void IntroDesertTravel::whatOnClick()
{
	QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("intro_travel")), QuestionController::PopupType::QUESTION, [this]() { gogo(); }, 50);
}

void IntroDesertTravel::showSkip()
{
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->GetComponent<BoxCollider2D>()->set_enabled(true);
	component->GetComponent<Button>()->set_enabled(true);
	component->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("skip")) + S("]"));
	component->onClick = [this]() { skipIt(); };
	component->GetComponent<BoxCollider2D>()->set_enabled(false);
	component->buttonText->OPTIONAL_MARGIN = 6;
	component->workIfBusy = false;
}

void IntroDesertTravel::skipIt()
{
	GameDataController::gd->setObjective(S("intro_skipped"), true);
	GameObject::Find(S("LocationManager"))->GetComponent<LocationSkyStart>()->transition = true;
	PlayerController::pc->spawnName = S("Waypoint_Crossroad_Base");
	CurtainController::cc->fadeOut(S("LocationCrossroad"), WalkController::Direction::N, nullptr, nullptr, false, nullptr, 0.1f);
}

void IntroDesertTravel::showButton()
{
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("skip")) + S("]"));
	component->workIfBusy = false;
	component->onClick = [this]() { skipIt(); };
	component->GetComponent<BoxCollider2D>()->set_enabled(false);
	component->buttonText->OPTIONAL_MARGIN = 6;
	component->set_enabled(true);
	component->buttonEnabled = true;
}

void IntroDesertTravel::showIntro1()
{
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("intro_1")), false, true, true, 180, 0.43f, 0.43f, 0.43f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void IntroDesertTravel::showIntro1b()
{
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->viewText(S(" "), false, true, true, 180, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void IntroDesertTravel::showIntro2()
{
	GameObject::Find(S("TitleText"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("intro_2")), false, true, true, 200, 0.43f, 0.43f, 0.43f, 0.0f, 0.0f, 0.0f, 0.0f);
}

void IntroDesertTravel::clickAction2()
{
}

void IntroDesertTravel::clickAction0()
{
}
