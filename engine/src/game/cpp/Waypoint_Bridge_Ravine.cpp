#include "../game_all.h"

void Waypoint_Bridge_Ravine::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("bridge_ravine");
	range = 70.0f;
}

void Waypoint_Bridge_Ravine::clickAction()
{
	String text = GameStrings::getString(GameStrings::warnings, S("bridge_ravine1"));
	if (InventoryController::ic->getCurrentWeight() > 10.0f)
	{
		text += S("^");
		String text2 = text;
		text = text2 + GameStrings::getString(GameStrings::warnings, S("bridge_ravine2")) + S(" ") + InventoryController::ic->getCurrentWeight() + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")) + S(" ") + GameStrings::getString(GameStrings::warnings, S("bridge_ravine3"));
	}
	int num = 2;
	num += (int)(2.0f * (InventoryController::ic->getCurrentWeight() / 5.0f));
	QuestionController::qc->showQuestion(text, QuestionController::PopupType::QUESTION, [this]() { yesClicked(); }, num);
}

void Waypoint_Bridge_Ravine::yesClicked()
{
	PlayerController::pc->setBusy(true);
	if (!GameDataController::gd->getObjective(S("bridge_westside")))
	{
		GameDataController::gd->setObjective(S("bridge_westside"), true);
		PlayerController::pc->spawnName = S("Waypoint_Ravine_West");
		CurtainController::cc->fadeOut(S("LocationBridge"), WalkController::Direction::W);
		updateState();
	}
	else
	{
		GameDataController::gd->setObjective(S("bridge_westside"), false);
		PlayerController::pc->spawnName = S("Waypoint_Ravine_East");
		CurtainController::cc->fadeOut(S("LocationBridge"), WalkController::Direction::E);
		updateState();
	}
}

void Waypoint_Bridge_Ravine::updateState()
{
	MonoBehaviour::print(S("UPDATING RAVINE"));
	if (GameDataController::gd->getObjective(S("bridge_planks_used_1")))
	{
		colliderManager->setCollider(-1);
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		GameObject::Find(S("LocationEast"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("LocationWest"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("bridge_area_collider"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		if (GameDataController::gd->getObjective(S("bridge_planks_used_2")))
		{
			GameObject::Find(S("LocationMoreBridge"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
		}
		else
		{
			GameObject::Find(S("LocationMoreBridge"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		}
	}
	else
	{
		MonoBehaviour::print(S("BRIDGE IS NOT FIXED, SO..."));
		GameObject::Find(S("Location"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		GameObject::Find(S("LocationMoreBridge"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		if (GameDataController::gd->getObjective(S("bridge_westside")))
		{
			actionType = Type::Transition;
			trans_dir = WalkController::Direction::E;
			MonoBehaviour::print(S("ENABLING WEST SIDE"));
			colliderManager->setCollider(1);
			GameObject::Find(S("LocationEast"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
			GameObject::Find(S("LocationWest"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
			GameObject::Find(S("bridge_area_collider"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		}
		else
		{
			MonoBehaviour::print(S("ENABLING EAST SIDE"));
			actionType = Type::Transition;
			trans_dir = WalkController::Direction::W;
			colliderManager->setCollider(0);
			GameObject::Find(S("LocationEast"))->GetComponent<PolygonCollider2D>()->set_enabled(true);
			GameObject::Find(S("LocationWest"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
			GameObject::Find(S("bridge_area_collider"))->GetComponent<PolygonCollider2D>()->set_enabled(false);
		}
	}
	GameObject::Find(S("Location"))->GetComponent<LocationManager>()->initNodes();
}

void Waypoint_Bridge_Ravine::clickAction2()
{
}

void Waypoint_Bridge_Ravine::clickAction0()
{
}
