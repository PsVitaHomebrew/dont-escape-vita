#include "../game_all.h"

void SpiderOutsideController::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("sit_shoot");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("nasty_spider");
	teleport = true;
	setCollider(0);
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("rifle_1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_2"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_3"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_4"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_5"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rifle_6"), String::Empty, nullptr, String::Empty));
	gameObject->GetComponent<Animator>()->Play(S("walk"));
	peopleShottingAtUs = false;
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && ItemsManager::im->getItem(S("rifle_6"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
	{
		PlayerController::pc->allowDrop = false;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		setCollider(0);
	}
	else
	{
		PlayerController::pc->allowDrop = true;
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(-1);
	}
}

void SpiderOutsideController::Update()
{
	if (!GetComponent<SpriteRenderer>()->get_enabled())
	{
		return;
	}
	gameObject->transform->set_position(Vector3(realX, gameObject->transform->get_position().y, gameObject->transform->get_position().z));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	actionMarker->transform->set_position(Vector3(PlayerController::pc->gameObject->transform->get_position().x, -0.318f, actionMarker->transform->get_position().z));
	if (!peopleShottingAtUs)
	{
		realX += 0.0005f * Time::get_deltaTime() * 60.0f;
		if (realX > 0.38f)
		{
			realX = 0.38f;
			gameObject->GetComponent<Animator>()->Play(S("tease"));
		}
		else if (realX > 0.3f)
		{
			realX -= 0.0003f * Time::get_deltaTime() * 60.0f;
		}
		else
		{
			gameObject->GetComponent<Animator>()->Play(S("walk_slow"));
		}
		gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
	}
	if (runLikeHell)
	{
		realX -= 0.02f * Time::get_deltaTime() * 60.0f;
		if (realX < -1.8f)
		{
			realX = -1.8f;
		}
		gameObject->GetComponent<Animator>()->Play(S("walk_fast"));
		gameObject->GetComponent<SpriteRenderer>()->set_flipX(false);
	}
}

void SpiderOutsideController::clickAction()
{
	if (usedItem.IndexOf(S("rifle_")) != -1)
	{
		peopleShottingAtUs = true;
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
		PlayerController::wc->dir = WalkController::Direction::W;
		gameObject->GetComponent<Animator>()->Play(S("attack"));
		GameDataController::gd->setObjective(S("gasstation_spider_shot"), true);
		PlayerController::pc->allowDrop = true;
		ItemsManager::im->rifleShot(usedItem, false);
		Invoke(S("showClock"), 3.0f);
	}
}

void SpiderOutsideController::showClock()
{
	GameObject::Find(S("clock"))->GetComponent<ClockController>()->showFinal();
}

void SpiderOutsideController::whatOnClick()
{
	if (usedItem.IndexOf(S("rifle_")) != -1)
	{
		characterAnimationName = S("sit_shoot");
		animationFlip = true;
		useCurrentDirection = false;
		PlayerController::wc->speed = 0.0f;
		PlayerController::pc->textField->dissmiss();
		setCollider(-1);
	}
	else
	{
		PlayerController::wc->setCurrentAnimClip(S("sit_strugle"));
		PlayerController::wc->fullStop(true);
	}
}

void SpiderOutsideController::whatOnClick0()
{
	if (usedItem.IndexOf(S("rifle_")) == -1)
	{
		range = 1.0f;
		teleport = false;
		PlayerController::wc->setCurrentAnimClip(S("sit_strugle"));
		PlayerController::wc->fullStop(true);
	}
	else
	{
		range = 1000.0f;
		teleport = true;
		characterAnimationName = S("sit_shoot");
	}
}

void SpiderOutsideController::updateState()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")) && ItemsManager::im->getItem(S("rifle_6"))->dataRef->droppedLocation.ToLower().IndexOf(S("inventory")) != -1)
	{
		setCollider(0);
	}
	else
	{
		setCollider(-1);
	}
}

void SpiderOutsideController::clickAction2()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rifle_shoot);
}

void SpiderOutsideController::clickAction0()
{
}

void SpiderOutsideController::hitAndRun()
{
	runLikeHell = true;
	realX -= 0.4f;
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_2a);
}

void SpiderOutsideController::hiss()
{
	gameObject->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->hiss);
	updateAll();
}
