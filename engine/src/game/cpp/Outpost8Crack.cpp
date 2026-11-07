#include "../game_all.h"

void Outpost8Crack::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_ne");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_ship_crack_out");
	range = 0.0f;
}

void Outpost8Crack::yesWeld()
{
	InventoryController::ic->removeItem(S("metal_slab"));
	GameDataController::gd->setObjective(S("outpost_hull_repaired_outside"), true);
	CurtainController::cc->fadeOut();
}

void Outpost8Crack::clickAction()
{
	if (GameDataController::gd->getObjective(S("outpost_hull_repaired_outside")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("crack_outside_fixed")));
		return;
	}
	if (GameDataController::gd->getItemData(S("welder"))->droppedLocation == S("socket_ship_outside"))
	{
		if (usedItem != String::Empty)
		{
			QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("weld_ship_outside")), QuestionController_PopupType::QUESTION, [this]() { yesWeld(); }, 30);
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("welder_material_needed")));
		}
		return;
	}
	if (usedItem != String::Empty)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("welder_needed")));
		return;
	}
	Vector3 color_b = Vector3(206.0f / 255.0f, 57.0f / 255.0f, 45.0f / 255.0f);
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("outpost_ship_crack_out"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color_b);
	list[3]->action = [this](String var) { gingerwalk(var); };
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void Outpost8Crack::gingerwalk(String var)
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->setTargetV3(GameObject::Find(S("GingerWalk"))->transform->get_position());
}

void Outpost8Crack::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 1)
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(-1);
		return;
	}
	GetComponent<SpriteRenderer>()->set_enabled(true);
	setCollider(0);
	if (GameDataController::gd->getObjective(S("outpost_hull_repaired_outside")))
	{
		objectName = S("outpost_ship_crack_out_welded");
		GetComponent<SpriteRenderer>()->set_sprite(spaw);
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("nails1"), GameStrings::getString(GameStrings::actions, S("welder_no_need")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("nails2"), GameStrings::getString(GameStrings::actions, S("welder_no_need")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("nails3"), GameStrings::getString(GameStrings::actions, S("welder_no_need")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("nails4"), GameStrings::getString(GameStrings::actions, S("welder_no_need")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("nails5"), GameStrings::getString(GameStrings::actions, S("welder_no_need")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("welder_no_need")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("ducttape"), GameStrings::getString(GameStrings::actions, S("welder_no_need")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("gluegun"), GameStrings::getString(GameStrings::actions, S("welder_no_need")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("gluegun_powered"), GameStrings::getString(GameStrings::actions, S("welder_no_need")), nullptr, String::Empty));
	}
	else
	{
		objectName = S("outpost_ship_crack_out");
		GetComponent<SpriteRenderer>()->set_sprite(crack);
		interactions = List<P<ItemInteraction>>::New();
		interactions.Add(New<ItemInteraction>(S("metal_slab"), String::Empty, nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("nails1"), GameStrings::getString(GameStrings::actions, S("welder_wrong_item")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("nails2"), GameStrings::getString(GameStrings::actions, S("welder_wrong_item")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("nails3"), GameStrings::getString(GameStrings::actions, S("welder_wrong_item")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("nails4"), GameStrings::getString(GameStrings::actions, S("welder_wrong_item")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("nails5"), GameStrings::getString(GameStrings::actions, S("welder_wrong_item")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("welder_wrong_item")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("ducttape"), GameStrings::getString(GameStrings::actions, S("welder_wrong_item")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("welder"), GameStrings::getString(GameStrings::actions, S("welder_plug_it")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("gluegun"), GameStrings::getString(GameStrings::actions, S("welder_wrong_item2")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("gluegun_powered"), GameStrings::getString(GameStrings::actions, S("welder_wrong_item2")), nullptr, String::Empty));
	}
}

void Outpost8Crack::clickAction2()
{
}

void Outpost8Crack::clickAction0()
{
}

void Outpost8Crack::whatOnClick0()
{
}

void Outpost8Crack::whatOnClick()
{
}
