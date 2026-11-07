#include "../game_all.h"

void HouseBRubble::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("house_b_inside_rubble");
	range = 1000.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("shovel"), GameStrings::getString(GameStrings::actions, S("barry_house_shovel")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("barry_house_shovel")), nullptr, String::Empty));
}

void HouseBRubble::clickAction()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("house_b_inside_rubble"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void HouseBRubble::updateState()
{
}

void HouseBRubble::clickAction2()
{
}

void HouseBRubble::clickAction0()
{
}
