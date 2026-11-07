#include "../game_all.h"

void CS4Tarpaulin::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("kneel_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("tarpaulin");
	range = 1.0f;
}

void CS4Tarpaulin::clickAction()
{
	if (GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("cant_reach")));
	}
	else if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("tarpaulin"))))
	{
		GameDataController::gd->setObjective(S("cs_tarpaulin_taken"), true);
		updateState();
	}
}

void CS4Tarpaulin::updateState()
{
	if (GameDataController::gd->getObjective(S("cs_tarpaulin_taken")) || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		setCollider(-1);
		GetComponent<SpriteRenderer>()->set_enabled(false);
		return;
	}
	setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	if (!GameDataController::gd->getObjective(S("constructionsite_from_above")))
	{
		range = 1.0f;
		characterAnimationName = S("kneel_n");
		animationFlip = false;
		useCurrentDirection = false;
	}
	else
	{
		range = 100.0f;
		characterAnimationName = S("action_stnd_se");
		animationFlip = true;
		useCurrentDirection = false;
	}
}

void CS4Tarpaulin::clickAction2()
{
}

void CS4Tarpaulin::clickAction0()
{
}

void CS4Tarpaulin::whatOnClick0()
{
}

void CS4Tarpaulin::whatOnClick()
{
}
