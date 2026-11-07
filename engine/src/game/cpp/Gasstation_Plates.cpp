#include "../game_all.h"

void Gasstation_Plates::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_s");
	animationFlip = false;
	useCurrentDirection = false;
	range = 1.0f;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("gasstation_plates");
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("rock"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("hammer"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("plates_throw")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("plates_throw")), nullptr, String::Empty));
	updateState();
}

void Gasstation_Plates::clickAction()
{
	if (usedItem != String::Empty)
	{
		if (GameDataController::gd->getObjective(S("gasstation_spider_discovered")) && GameDataController::gd->getCurrentDay() == 1)
		{
			GameObject::Find(S("fly_object"))->GetComponent<GasstationFlyObjectController>()->fly(ItemsManager::im->getItem(usedItem));
			InventoryController::ic->removeItem(usedItem);
			Invoke(S("play_animation"), 0.3f);
			Invoke(S("hiss"), 0.5f);
			Invoke(S("run_like_hell"), 1.5f);
		}
		else
		{
			PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_plates_no_need")), true);
		}
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("gasstation_plates_noise")), true);
	}
}

void Gasstation_Plates::stopAnimation()
{
	GetComponent<Animator>()->Play(S("plates_still"));
	setCollider(-1);
	GetComponent<SpriteRenderer>()->set_enabled(false);
}

void Gasstation_Plates::hiss()
{
	GameObject::Find(S("Spider"))->GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->hiss);
}

void Gasstation_Plates::play_animation()
{
	GetComponent<Animator>()->Play(S("plates_crash"));
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->plates_break);
	GameDataController::gd->setObjective(S("gasstation_spider_baited"), true);
	P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/GroundItem")), Vector3(-0.277f, -0.3843064f, 0.0f), Quaternion()).as<GameObject>();
	gameObject->GetComponent<GroundItemController>()->init(ItemsManager::im->getItem(usedItem));
	ItemsManager::im->getItem(usedItem)->dataRef->locX = 90;
	ItemsManager::im->getItem(usedItem)->dataRef->locY = 26;
	ItemsManager::im->getItem(usedItem)->dataRef->droppedLocation = SceneManager::GetActiveScene().get_name();
}

void Gasstation_Plates::run_like_hell()
{
	PlayerController::wc->forceAnimation(S("stand_ne"));
	PlayerController::pc->spawnName = S("Waypoint_Gasstation1_GasstationRoom2");
	CurtainController::cc->fadeOut(S("LocationGasstation1"), WalkController::Direction::S_);
}

void Gasstation_Plates::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		setCollider(0);
		GetComponent<SpriteRenderer>()->set_enabled(true);
		if (!GameDataController::gd->getObjective(S("gasstation_spider_baited")))
		{
			GetComponent<Animator>()->Play(S("plates_still"));
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_enabled(false);
		}
	}
	else
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void Gasstation_Plates::clickAction2()
{
}

void Gasstation_Plates::clickAction0()
{
}

void Gasstation_Plates::whatOnClick0()
{
	if (usedItem != String::Empty && GameDataController::gd->getObjective(S("gasstation_spider_discovered")) && GameDataController::gd->getCurrentDay() == 1)
	{
		characterAnimationName = S("throw_s");
		range = 1.0f;
	}
	else
	{
		characterAnimationName = S("action_stnd_s");
		range = 100.0f;
	}
}
