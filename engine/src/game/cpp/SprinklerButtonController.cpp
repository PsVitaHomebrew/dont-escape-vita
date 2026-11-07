#include "../game_all.h"

void SprinklerButtonController::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("barn_console_sprinkler");
	teleport = true;
	transform->set_position(ScreenControler::roundToNearestFullPixel2(transform->get_position()));
}

void SprinklerButtonController::changeState()
{
	GameDataController::gd->setObjective(dataRef, !GameDataController::gd->getObjective(dataRef));
}

void SprinklerButtonController::clickAction()
{
	if (GameDataController::gd->getObjective(S("barn_sprinklers_enabled")))
	{
		arrow->fastUpdate = false;
		changeState();
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->button_click);
		if (connected1 != nullptr)
		{
			connected1->changeState();
			int num = Random::Range(1, 6);
			MonoBehaviour::print(S("RANDOM ") + num);
			connected1->GetComponent<Animator>()->Play(S("b1_flicker") + num, 0);
		}
		if (connected2 != nullptr)
		{
			connected2->changeState();
			int num2 = Random::Range(1, 6);
			MonoBehaviour::print(S("RANDOM ") + num2);
			connected2->GetComponent<Animator>()->Play(S("b1_flicker") + num2, 0);
		}
		if (connected3 != nullptr)
		{
			connected3->changeState();
			int num3 = Random::Range(1, 6);
			MonoBehaviour::print(S("RANDOM ") + num3);
			connected3->GetComponent<Animator>()->Play(S("b1_flicker") + num3, 0);
		}
		if (connected4 != nullptr)
		{
			connected4->changeState();
			int num4 = Random::Range(1, 6);
			MonoBehaviour::print(S("RANDOM ") + num4);
			connected4->GetComponent<Animator>()->Play(S("b1_flicker") + num4, 0);
		}
		if (!GameDataController::gd->getObjective(dataRef))
		{
			GetComponent<Animator>()->Play(S("b1_on_off"), 0);
		}
		else
		{
			GetComponent<Animator>()->Play(S("b1_off_on"), 0);
		}
	}
}

void SprinklerButtonController::updateAfterAnimation()
{
	updateState();
}

void SprinklerButtonController::updateState()
{
	if (GameDataController::gd->getObjective(dataRef))
	{
		GetComponent<Animator>()->Play(S("b1_on"), 0);
	}
	else
	{
		GetComponent<Animator>()->Play(S("b1_off"), 0);
	}
}

void SprinklerButtonController::clickAction2()
{
}

void SprinklerButtonController::clickAction0()
{
}
