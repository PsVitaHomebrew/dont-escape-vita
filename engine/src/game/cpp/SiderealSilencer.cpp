#include "../game_all.h"

void SiderealSilencer::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = true;
	characterAnimationName = S("kneel_");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_silencer");
	range = 2.0f;
	updateState();
}

void SiderealSilencer::clickAction()
{
	pickItUp(nullptr);
}

void SiderealSilencer::pickItUp(String param)
{
	if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("silencer"))))
	{
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("sidereal_silencer"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>());
		if (GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")))
		{
			Vector3 color = GingerActionController::getColor();
			Vector3 color2 = Npc3Controller::getColor();
			P<TextFieldController> component = GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>();
			DialogueController::dc->initDialogue(list, S("sidereal_silencer_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color, component, color2);
		}
		if (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))
		{
			Vector3 color3 = GingerActionController::getColor();
			Vector3 color4 = Npc2Controller::getColor();
			P<TextFieldController> component2 = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
			DialogueController::dc->initDialogue(list, S("sidereal_silencer_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), color3, component2, color4);
		}
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		GameDataController::gd->setObjective(S("sidereal_silencer"), true);
		updateAll();
	}
}

void SiderealSilencer::whatOnClick()
{
}

void SiderealSilencer::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_silencer")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		blik->set_enabled(false);
		colliderManager->setCollider(-1);
		return;
	}
	colliderManager->setCollider(0);
	gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_A")) == 50 && GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_B")) == 10)
	{
		blik->set_enabled(true);
	}
	else
	{
		blik->set_enabled(false);
	}
}

void SiderealSilencer::clickAction2()
{
}

void SiderealSilencer::clickAction0()
{
}
