#include "../game_all.h"

void InfoPrev::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = String::Empty;
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("information_prev");
	teleport = true;
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
}

void InfoPrev::clickAction()
{
	GameObject::Find(S("TextLeft"))->GetComponent<TextRightScript>()->gotoPrevPage();
	int num = Random::Range(1, 5);
	if (prevSound == num)
	{
		num++;
		if (num > 4)
		{
			num = 1;
		}
	}
	prevSound = num;
	P<AudioClip> clip;
	switch (num)
	{
	case 1:
		clip = SoundsManagerController::sm->page_turn_01;
		break;
	case 2:
		clip = SoundsManagerController::sm->page_turn_02;
		break;
	case 3:
		clip = SoundsManagerController::sm->page_turn_03;
		break;
	default:
		clip = SoundsManagerController::sm->page_turn_04;
		break;
	}
	PlayerController::pc->aS->PlayOneShot(clip, 0.5f);
}

void InfoPrev::updateState()
{
}

void InfoPrev::clickAction2()
{
}

void InfoPrev::clickAction0()
{
}
