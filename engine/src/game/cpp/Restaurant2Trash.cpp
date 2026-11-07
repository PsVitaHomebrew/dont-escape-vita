#include "../game_all.h"

void Restaurant2Trash::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("pull2_w");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_trash");
	range = 3.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("restaurant_trash_crowbar")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rope"), GameStrings::getString(GameStrings::actions, S("restaurant_trash_crowbar")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("hook"), GameStrings::getString(GameStrings::actions, S("restaurant_trash_crowbar")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ropehook"), GameStrings::getString(GameStrings::actions, S("restaurant_trash_crowbar")), nullptr, String::Empty));
}

void Restaurant2Trash::clickAction()
{
}

void Restaurant2Trash::updateState()
{
	if (GameDataController::gd->getObjective(S("restaurant_trash_moved")))
	{
		trashCollider->transform->set_position(Vector3(0.485f, 0.031f, 100.0f));
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
	else
	{
		trashCollider->transform->set_position(Vector3(-0.019f, -0.06f, 100.0f));
		setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	ItemsManager::im->fixGroundItems(Vector2(95.0f, 35.0f), Vector2(20.0f, 10.0f));
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
	ItemsManager::im->initGroundAndInv();
}

void Restaurant2Trash::clickAction2()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_trash_heavy")), true);
	GameDataController::gd->setObjective(S("restaurant_trash_tried"), true);
}

void Restaurant2Trash::clickAction0()
{
}

void Restaurant2Trash::pushLittleCart_Barry()
{
	pushLittleCart();
	P<TextFieldController> component = GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("barry_pushed_trash"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, Npc2Controller::getColor());
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void Restaurant2Trash::pushLittleCart_Cate()
{
	pushLittleCart();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("ginger_pushed_trash"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor());
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void Restaurant2Trash::pushLittleCart()
{
	GameDataController::gd->setObjective(S("restaurant_trash_moved"), !GameDataController::gd->getObjective(S("restaurant_trash_moved")));
	if (GameDataController::gd->getObjective(S("restaurant_trash_moved")))
	{
		trashCollider->transform->set_position(Vector3(0.485f, 0.031f, 100.0f));
	}
	else
	{
		trashCollider->transform->set_position(Vector3(-0.019f, -0.06f, 100.0f));
	}
	ItemsManager::im->fixGroundItems(Vector2(95.0f, 35.0f), Vector2(20.0f, 10.0f));
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	updateState();
	CurtainController::cc->fadeOut(S("none"), WalkController::Direction::S_);
}
