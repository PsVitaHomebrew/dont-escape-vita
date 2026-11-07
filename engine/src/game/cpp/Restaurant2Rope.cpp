#include "../game_all.h"

void Restaurant2Rope::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_rope");
	range = 1.0f;
	teleport = false;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("restaurant_rope_pipe")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("knife"), GameStrings::getString(GameStrings::actions, S("restaurant_rope_knife")), nullptr, String::Empty));
}

void Restaurant2Rope::Update()
{
}

void Restaurant2Rope::whatOnClick()
{
}

void Restaurant2Rope::clickAction()
{
	if (GameDataController::gd->getObjective(S("restaurant_pipe_switched")))
	{
		GameDataController::gd->setObjective(S("restaurant_flag_lowered"), true);
		ItemsManager::im->updateItem(S("rope"), S("LocationRestaurant2"), 160, 30);
		ItemsManager::im->updateItem(S("flag"), S("LocationRestaurant2"), 180, 30);
		CurtainController::cc->fadeOut(S("none"), WalkController::Direction::S_, nullptr, nullptr, false, [this]() { lowerFlag(); });
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("restaurant_rope")), true, false, false, 150);
	}
}

void Restaurant2Rope::lowerFlag()
{
}

void Restaurant2Rope::drop(String name)
{
	P<Item> item = ItemsManager::im->getItem(name);
	Vector2 vector = ScreenControler::gameToScreen(Vector2((float)item->dataRef->locX, (float)(item->dataRef->locY + GroundItemController::yOffset)));
	Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
	vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
	item->dataRef->droppedLocation = SceneManager::GetActiveScene().get_name();
	P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion()).as<GameObject>();
	gameObject->GetComponent<GroundItemController>()->init(item);
}

void Restaurant2Rope::updateState()
{
	if (GameDataController::gd->getObjective(S("restaurant_flag_lowered")))
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		colliderManager->setCollider(-1);
	}
	else
	{
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		colliderManager->setCollider(0);
	}
}

void Restaurant2Rope::clickAction2()
{
}

void Restaurant2Rope::clickAction0()
{
}
