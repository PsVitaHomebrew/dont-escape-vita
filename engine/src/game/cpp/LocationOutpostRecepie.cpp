#include "../game_all.h"

void LocationOutpostRecepie::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("outpost_recepie");
	range = 0.0f;
	teleport = false;
	updateState();
	actionType = Type::NormalAction;
}

void LocationOutpostRecepie::Update()
{
}

void LocationOutpostRecepie::whatOnClick()
{
}

void LocationOutpostRecepie::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1)
	{
		if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("mixer_catalyst_note"))))
		{
			GameDataController::gd->setObjective(S("mixer_note_taken"), true);
			updateState();
		}
	}
	else if (InventoryController::ic->pickUpItem(ItemsManager::im->getItem(S("mixer_pills_note"))))
	{
		GameDataController::gd->setObjective(S("mixer_note_taken"), true);
		updateState();
	}
}

void LocationOutpostRecepie::updateState()
{
	if (!GameDataController::gd->getObjective(S("mixer_note_taken")))
	{
		characterAnimationName = S("action_n");
		animationFlip = false;
		useCurrentDirection = false;
		range = 1.0f;
		setCollider(0);
		sr->set_sprite(present);
	}
	else
	{
		setCollider(-1);
		sr->set_sprite(gone);
	}
}

void LocationOutpostRecepie::clickAction2()
{
}

void LocationOutpostRecepie::clickAction0()
{
}
