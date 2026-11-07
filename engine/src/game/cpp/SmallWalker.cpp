#include "../game_all.h"

void SmallWalker::Start()
{
	skipit = 1;
	realPosition = Vector2(gameObject->transform->get_position().x, gameObject->transform->get_position().y);
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	colliderManager->setTarget(gameObject);
	animationFlip = true;
	characterAnimationName = S("action_stnd_e");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("intro_desert");
	range = 10000.0f;
	title->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	title2->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::E;
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->buttonEnabled = false;
	component->onClick = nullptr;
	component->workIfBusy = false;
	component->set_enabled(false);
	component->GetComponent<BoxCollider2D>()->set_enabled(false);
	component->set_enabled(false);
	component->buttonEnabled = false;
}

void SmallWalker::skipIt()
{
	GameDataController::gd->setObjective(S("intro_skipped"), true);
	titleAlpha = -200.0f;
	PlayerController::pc->spawnName = S("Waypoint_Crossroad_Base");
	CurtainController::cc->fadeOut(S("LocationCrossroad"), WalkController::Direction::N, nullptr, nullptr, false, nullptr, 0.1f);
}

void SmallWalker::Update()
{
	if (GameDataController::gd->getObjective(S("intro_desert_walked")))
	{
		realPosition.x += 0.08f * Time::get_deltaTime();
		if ((double)realPosition.x > 0.5 && titleAlpha < -100.0f)
		{
			title->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
			title2->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
		}
		else if (realPosition.x > 0.5f && titleAlpha > -100.0f)
		{
			titleAlpha = -200.0f;
			PlayerController::pc->spawnName = S("Waypoint_Crossroad_Base");
			CurtainController::cc->fadeOut(S("LocationCrossroad"), WalkController::Direction::N, nullptr, nullptr, false, nullptr, 0.005f);
		}
		else if (realPosition.x > 0.2f && titleAlpha > 0.0f && titleAlpha2 > 0.0f)
		{
			titleAlpha -= 0.01f;
			titleAlpha2 -= 0.01f;
			title->set_color(Color(1.0f, 1.0f, 1.0f, titleAlpha));
			title2->set_color(Color(1.0f, 1.0f, 1.0f, titleAlpha2));
		}
		else
		{
			if (realPosition.x > -0.6f && titleAlpha < 1.0f)
			{
				titleAlpha += 0.01f;
				title->set_color(Color(1.0f, 1.0f, 1.0f, titleAlpha));
			}
			if (realPosition.x > -0.2f && titleAlpha2 < 1.0f)
			{
				titleAlpha2 += 0.01f;
				title2->set_color(Color(1.0f, 1.0f, 1.0f, titleAlpha2));
			}
		}
	}
	else
	{
		gameObject->GetComponent<Animator>()->Play(S("small_stop"));
	}
	gameObject->transform->set_position(Vector3(realPosition.x, realPosition.y, gameObject->transform->get_position().z));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
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

void SmallWalker::showButton()
{
	P<Button> component = GameObject::Find(S("ContinueBtn"))->GetComponent<Button>();
	component->initButton(S("[") + GameStrings::getString(GameStrings::gui, S("skip")) + S("]"));
	component->workIfBusy = false;
	component->onClick = [this]() { skipIt(); };
	component->GetComponent<BoxCollider2D>()->set_enabled(true);
	component->buttonText->OPTIONAL_MARGIN = 6;
	component->set_enabled(true);
	component->buttonEnabled = true;
}

void SmallWalker::clickAction()
{
}

void SmallWalker::updateState()
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

void SmallWalker::whatOnClick()
{
	GameDataController::gd->setObjective(S("intro_desert_walked"), true);
	gameObject->GetComponent<Animator>()->Play(S("small_walk"));
	updateState();
}

void SmallWalker::clickAction2()
{
}

void SmallWalker::clickAction0()
{
}
