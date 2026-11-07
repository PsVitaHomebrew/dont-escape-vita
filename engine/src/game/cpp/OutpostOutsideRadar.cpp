#include "../game_all.h"

void OutpostOutsideRadar::Update()
{
	alpha += Random::Range(-1.0f, 1.0f) * Time::get_deltaTime();
	if (alpha > 1.0f)
	{
		alpha = 1.0f;
	}
	if ((double)alpha < 0.5)
	{
		alpha = 0.5f;
	}
	blysk->set_color(Color(1.0f, 1.0f, 1.0f, alpha));
	if (wstan && PlayerController::wc->currentXY.x >= 165.0f)
	{
		wstan = false;
		PlayerController::wc->forceDirection(WalkController::Direction::W);
		PlayerController::wc->forceAnimation(S("stand_e"), true, false, false);
		PlayerController::wc->forceDirection(WalkController::Direction::W);
		PlayerController::pc->setBusy(false);
		updateAll();
		PlayerController::wc->setSimpleTargetV3(walkHere2->transform->get_position());
	}
}

void OutpostOutsideRadar::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_e");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_radar_panel");
	range = 1.0f;
	wstan = false;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("screwdriver"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("duplexer"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("crowbar_too_brute")), nullptr, String::Empty));
	updateAll();
}

void OutpostOutsideRadar::clickAction()
{
	if (usedItem == S("screwdriver"))
	{
		if (!GameDataController::gd->getObjective(S("outpost_radar_open")))
		{
			ItemsManager::im->getItem(S("metal_slab"))->dataRef->droppedLocation = S("LocationOutpostOutside2");
			ItemsManager::im->getItem(S("metal_slab"))->dataRef->locX = 160;
			ItemsManager::im->getItem(S("metal_slab"))->dataRef->locY = 95;
			Vector2 vector = ScreenControler::gameToScreen(Vector2((float)ItemsManager::im->getItem(S("metal_slab"))->dataRef->locX, (float)(ItemsManager::im->getItem(S("metal_slab"))->dataRef->locY + GroundItemController::yOffset)));
			Vector3 vector2 = Vector3(vector.x, vector.y, 0.0f);
			vector2 = Camera::get_main()->ScreenToWorldPoint(vector);
			P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), vector2, Quaternion()).as<GameObject>();
			gameObject->GetComponent<GroundItemController>()->init(ItemsManager::im->getItem(S("metal_slab")));
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->screw);
			GameDataController::gd->setObjective(S("outpost_radar_open"), true);
			updateState();
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("generic_opened")));
		}
	}
	else if (usedItem == S("duplexer"))
	{
		if (!GameDataController::gd->getObjective(S("outpost_radar_open")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("radar_locked")));
			return;
		}
		wstan = true;
		InventoryController::ic->removeItem(S("duplexer"));
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->screw);
		GameDataController::gd->setObjective(S("outpost_radar_repaired"), true);
		PlayerController::wc->forceAnimation(S("kneel_e_out"), true);
	}
	else if (!GameDataController::gd->getObjective(S("outpost_radar_open")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("radar_locked")));
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("radar_broken")));
	}
}

void OutpostOutsideRadar::updateState()
{
	colliderManager->setCollider(0);
	blok->set_enabled(false);
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("screwdriver"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("duplexer"), String::Empty, nullptr, String::Empty));
	if (!GameDataController::gd->getObjective(S("outpost_radar_open")))
	{
		interactions.Add(New<ItemInteraction>(S("crowbar"), GameStrings::getString(GameStrings::actions, S("crowbar_too_brute")), nullptr, String::Empty));
		GetComponent<SpriteRenderer>()->set_sprite(closed);
		blysk->set_enabled(true);
	}
	else
	{
		blysk->set_enabled(false);
		GetComponent<SpriteRenderer>()->set_sprite(open);
	}
	if (GameDataController::gd->getObjective(S("outpost_radar_repaired")))
	{
		blok->set_enabled(true);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
		colliderManager->setCollider(-1);
	}
	else
	{
		blok->set_enabled(false);
		GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
		colliderManager->setCollider(0);
	}
}

void OutpostOutsideRadar::clickAction2()
{
	if (wstan)
	{
		PlayerController::wc->forceAnimation(S("walk_e"));
		PlayerController::wc->setSimpleTargetV3(walkHere->transform->get_position());
		PlayerController::pc->setBusy(true);
	}
}

void OutpostOutsideRadar::clickAction0()
{
}

void OutpostOutsideRadar::whatOnClick0()
{
}

void OutpostOutsideRadar::whatOnClick()
{
}
