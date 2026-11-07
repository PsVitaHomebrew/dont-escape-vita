#include "../game_all.h"

void LocationOutpostShipCloset::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_s");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship_closet");
	range = 1.0f;
}

void LocationOutpostShipCloset::clickAction()
{
	if (GameDataController::gd->getObjective(S("outpost_cabinet_open")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("outpost_cabinet_open")));
		return;
	}
	GameDataController::gd->setObjective(S("outpost_cabinet_open"), true);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->cabinet_open);
	gameObject->GetComponent<Animator>()->Play(S("closet_open"));
	Vector3 color_b = Vector3(206.0f / 255.0f, 57.0f / 255.0f, 45.0f / 255.0f);
	P<TextFieldController> component = GameObject::Find(S("ExamineSprite"))->GetComponent<TextFieldController>();
	ExamineSprite::es->textField->shift.x = -40.0f;
	ExamineSprite::es->textField->shift.y = 70.0f;
	ExamineSprite::es->textField->center = true;
	ExamineSprite::es->textField->directionY = -1.0f;
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("ship_closet"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color_b);
	list[list.Count() - 1]->action = [this](String a) { upd(a); };
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void LocationOutpostShipCloset::upd(String a)
{
	updateState();
}

void LocationOutpostShipCloset::updateState()
{
	if (GameDataController::gd->getObjective(S("outpost_cabinet_open")))
	{
		colliderManager->setCollider(1);
		GetComponent<Animator>()->Play(S("closet_opened"));
		objectName = S("outpost_ship_closet_open");
		characterAnimationName = S("action_stnd_s");
		animationFlip = false;
		useCurrentDirection = false;
		range = 3.0f;
	}
	else
	{
		colliderManager->setCollider(0);
		GetComponent<Animator>()->Play(S("closet_closed"));
		objectName = S("outpost_ship_closet");
		characterAnimationName = S("kneel_s");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
	}
}

void LocationOutpostShipCloset::clickAction2()
{
}

void LocationOutpostShipCloset::clickAction0()
{
}

void LocationOutpostShipCloset::whatOnClick0()
{
}

void LocationOutpostShipCloset::whatOnClick()
{
}
