#include "../game_all.h"

void WalkerNoBackpack::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = String::Empty;
	range = 8000.0f;
	teleport = false;
	updateState();
	actionType = Type::Secret;
}

void WalkerNoBackpack::Update()
{
}

void WalkerNoBackpack::whatOnClick()
{
}

void WalkerNoBackpack::clickAction()
{
	if (counter == 0)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("pick_up_backpack")), true, false, false, 150);
		counter++;
		return;
	}
	ExamineSprite::es->textField->shift.x = -10.0f;
	ExamineSprite::es->textField->shift.y = -40.0f;
	ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::gui, S("pick_up_backpack")) }), 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.25f);
	ExamineSprite::es->show(pointer);
}

void WalkerNoBackpack::updateState()
{
	if (!GameDataController::gd->getObjective(S("tent_awake")))
	{
		colliderManager->setCollider(-1);
	}
	else if (!GameDataController::gd->getObjective(S("tent_backpack_taken")))
	{
		colliderManager->setCollider(0);
	}
	else
	{
		colliderManager->setCollider(-1);
	}
}

void WalkerNoBackpack::clickAction2()
{
}

void WalkerNoBackpack::clickAction0()
{
}
