#include "../game_all.h"

void SiderealTheList::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_list");
	range = 1.0f;
}

void SiderealTheList::clickAction()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->page_turn_01);
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("cate_lab_list"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void SiderealTheList::updateState()
{
}

void SiderealTheList::clickAction2()
{
}

void SiderealTheList::clickAction0()
{
}

void SiderealTheList::whatOnClick0()
{
}

void SiderealTheList::whatOnClick()
{
}
