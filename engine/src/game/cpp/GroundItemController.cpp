#include "../game_all.h"

void GroundItemController::Awake()
{
	spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
	interactions = List<P<ItemInteraction>>::New();
}

void GroundItemController::init(P<Item> item)
{
	itemRef = item;
	spriteRenderer->set_sprite(itemRef->groundSprite);
	frontView = gameObject->transform->Find(S("FrontView"))->GetComponent<SpriteRenderer>();
	frontView->set_sprite(itemRef->groundSprite);
	frontView->set_color(Color(0.0f, 1.0f, 0.0f, 1.0f));
	frontView->set_enabled(false);
	dkvs = GameStrings::items;
	objectName = item->id;
	delay = 0;
	frame = 0;
	allowAllItems = false;
	if (item->usableItemsGround != nullptr)
	{
		interactions = item->usableItemsGround;
	}
	if (item->usableItemsGround == nullptr && item->usableItemsInventory != nullptr)
	{
		allowAllItems = true;
	}
	P<Sprite> sprite = gameObject->GetComponent<SpriteRenderer>()->get_sprite();
	P<BoxCollider2D> component = gameObject->GetComponent<BoxCollider2D>();
	Vector2 vector = gameObject->GetComponent<SpriteRenderer>()->get_bounds().size;
	component->set_size(vector);
	MonoBehaviour::print(S("Item"));
	component->set_offset(Vector2((0.0f - vector.x) * (0.5f - sprite->get_pivot().x / sprite->get_rect().width), vector.y / 2.0f - vector.y * (sprite->get_pivot().y / sprite->get_rect().height)));
	if (itemRef->soundLoop != nullptr)
	{
		if (gameObject->GetComponent<AudioSource>() == nullptr)
		{
			gameObject->AddComponent<AudioSource>();
		}
		gameObject->GetComponent<AudioSource>()->set_clip(itemRef->soundLoop);
		gameObject->GetComponent<AudioSource>()->set_loop(true);
		gameObject->GetComponent<AudioSource>()->Play();
	}
	Vector3 localPosition = Vector3(0.0f, -0.0092592f * (float)yOffset, 0.0f);
	transform->Find(S("Action_Marker"))->transform->set_localPosition(localPosition);
	if (!canPickUp)
	{
		disablePickup();
	}
}

void GroundItemController::Update()
{
	if (itemRef->animationDelay <= 0)
	{
		return;
	}
	delay++;
	if (delay >= itemRef->animationDelay)
	{
		delay = 0;
		frame++;
		if (itemRef->groundSprite_1 != nullptr && frame == 1)
		{
			spriteRenderer->set_sprite(itemRef->groundSprite_1);
			return;
		}
		if (itemRef->groundSprite_2 != nullptr && frame == 2)
		{
			spriteRenderer->set_sprite(itemRef->groundSprite_2);
			return;
		}
		if (itemRef->groundSprite_3 != nullptr && frame == 3)
		{
			spriteRenderer->set_sprite(itemRef->groundSprite_3);
			return;
		}
		if (itemRef->groundSprite_4 != nullptr && frame == 4)
		{
			spriteRenderer->set_sprite(itemRef->groundSprite_4);
			return;
		}
		if (itemRef->groundSprite_5 != nullptr && frame == 5)
		{
			spriteRenderer->set_sprite(itemRef->groundSprite_5);
			return;
		}
		spriteRenderer->set_sprite(itemRef->groundSprite);
		frame = 0;
	}
}

void GroundItemController::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("kneel_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
}

void GroundItemController::disablePickup()
{
	canPickUp = false;
	P<BoxCollider2D> component = gameObject->GetComponent<BoxCollider2D>();
	if (component != nullptr)
	{
		component->set_enabled(false);
	}
	P<PolygonCollider2D> component2 = gameObject->GetComponent<PolygonCollider2D>();
	if (component2 != nullptr)
	{
		component2->set_enabled(false);
	}
}

void GroundItemController::enablePickup()
{
	canPickUp = true;
	P<BoxCollider2D> component = gameObject->GetComponent<BoxCollider2D>();
	if (component != nullptr)
	{
		component->set_enabled(true);
	}
	P<PolygonCollider2D> component2 = gameObject->GetComponent<PolygonCollider2D>();
	if (component2 != nullptr)
	{
		component2->set_enabled(true);
	}
}

void GroundItemController::whatOnClick()
{
	if (usedItem == String::Empty)
	{
		animationFlip = false;
		characterAnimationName = S("kneel_");
		useCurrentDirection = true;
		range = 2.0f;
	}
	else if (allowAllItems)
	{
		range = 200.0f;
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
	}
	else
	{
		range = usedItemInteraction->range;
		if (range < 2.0f)
		{
			range = 2.0f;
		}
		animationFlip = false;
		characterAnimationName = usedItemInteraction->animation;
		useCurrentDirection = false;
	}
	PlayerController::wc->range = (int)range;
}

void GroundItemController::clickAction()
{
	if (usedItem != String::Empty)
	{
		if (allowAllItems)
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("generic_pick_it_up")));
		}
		else if (interactions[0]->action != nullptr)
		{
			interactions[0]->action();
		}
		return;
	}
	if (itemRef->id == S("bear_trap_1b") || itemRef->id == S("bear_trap_2b"))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("bear_trap_b")));
		return;
	}
	P<InventoryItemController> inventoryItemController = InventoryController::ic->findFreeSpot();
	if (inventoryItemController == nullptr)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::gui, S("inventory_full")), true);
	}
	else if (InventoryController::ic->getCurrentWeight() + itemRef->weight > (float)InventoryController::ic->maxCapacity)
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::gui, S("capacity_full")), true);
		GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("capacity_1")) + S(" ") + itemRef->weight + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")) + S(" ") + GameStrings::getString(GameStrings::gui, S("capacity_2")) + S(" ") + InventoryController::getRoundedWeightLeft() + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")) + S(" ") + GameStrings::getString(GameStrings::gui, S("capacity_3")), false, true, false, BottomTextController::bottomTextWidth, 1.0f, 1.0f, 0.0f);
	}
	else
	{
		MonoBehaviour::print(S("im.updateItem"));
		ItemsManager::im->updateItem(itemRef->id, S("inventory"), inventoryItemController->lx, inventoryItemController->ly);
		MonoBehaviour::print(S("ic.loadItem"));
		InventoryController::ic->loadItem(itemRef);
		MonoBehaviour::print(S("Destroy ") + gameObject->ToString());
		Object::Destroy(gameObject);
		PlayerController::pc->aS->PlayOneShot(itemRef->sound);
	}
}

void GroundItemController::clickAction2()
{
}

void GroundItemController::updateState()
{
}

void GroundItemController::clickAction0()
{
}
