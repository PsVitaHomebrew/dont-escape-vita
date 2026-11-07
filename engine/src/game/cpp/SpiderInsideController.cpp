#include "../game_all.h"

void SpiderInsideController::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("stop");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("nasty_spider");
	teleport = true;
	updateState();
	gameObject->GetComponent<Animator>()->Play(S("walk"));
	setCollider(0);
}

void SpiderInsideController::Update()
{
	gameObject->transform->set_position(Vector3(realX, gameObject->transform->get_position().y, gameObject->transform->get_position().z));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")))
	{
		realX += 0.004f * Time::get_deltaTime() * 60.0f;
		if (realX > -0.256f)
		{
			realX = -0.256f;
			gameObject->GetComponent<Animator>()->Play(S("tease"));
		}
		else
		{
			gameObject->GetComponent<Animator>()->Play(S("walk"));
		}
		gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
}

void SpiderInsideController::clickAction()
{
}

void SpiderInsideController::whatOnClick()
{
}

void SpiderInsideController::updateState()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjective(S("gasstation_spider_baited")) && !GameDataController::gd->getObjective(S("gasstation_spider_shot")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void SpiderInsideController::clickAction2()
{
}

void SpiderInsideController::clickAction0()
{
}
