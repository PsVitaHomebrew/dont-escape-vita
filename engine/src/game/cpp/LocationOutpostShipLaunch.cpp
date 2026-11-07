#include "../game_all.h"

void LocationOutpostShipLaunch::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	objectName = S("ship_launch_console");
	range = 100.0f;
}

void LocationOutpostShipLaunch::clickAction()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (!GameDataController::gd->getObjective(S("outpost_hatch_open")))
	{
		DialogueController::dc->initDialogue(list, S("cant_launch_hatch"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	}
	else if (InventoryController::ic->getCurrentWeight() > 1.0f)
	{
		DialogueController::dc->initDialogue(list, S("cant_launch_weight"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	}
	else if (GameDataController::gd->getItemData(S("welder"))->droppedLocation == S("socket_ship_inside"))
	{
		DialogueController::dc->initDialogue(list, S("cant_launch_welder"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	}
	else
	{
		DialogueController::dc->initDialogue(list, S("can_launch"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		list[list.Count() - 1]->action = [this](String s) { showQuestion(s); };
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void LocationOutpostShipLaunch::showQuestion(String s)
{
	GameObject::Find(S("clock"))->GetComponent<ClockController>()->showEndDialogue(S("launch_ship"), S("equip_nothing2"));
}

void LocationOutpostShipLaunch::updateState()
{
}

void LocationOutpostShipLaunch::clickAction2()
{
}

void LocationOutpostShipLaunch::clickAction0()
{
}
