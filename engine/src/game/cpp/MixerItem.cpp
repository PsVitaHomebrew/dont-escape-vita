#include "../game_all.h"

void MixerItem::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("pill_half");
	range = 8000.0f;
	teleport = false;
	sr = gameObject->GetComponent<SpriteRenderer>();
	interactions = List<P<ItemInteraction>>::New();
	updateState();
}

void MixerItem::Update()
{
}

void MixerItem::whatOnClick()
{
}

void MixerItem::clickAction()
{
	if (!GameDataController::gd->getObjective(S("sidereal_mixer_mixed")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_item_no_use")));
	}
	else if (GameDataController::gd->getObjectiveDetail(S("sidereal_mixer_mixed")) == 3)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("sidereal_mixer_button_already_done")));
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
	{
		CursorController::cc->selectItem(ItemsManager::im->getItem(S("pill_half")));
	}
	else
	{
		CursorController::cc->selectItem(ItemsManager::im->getItem(S("mixer_glass")));
	}
}

void MixerItem::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
	{
		setCollider(0);
		objectName = S("pill_half");
		sr->set_sprite(sprite_1);
	}
	else
	{
		setCollider(1);
		sr->set_sprite(sprite_2);
		objectName = S("mixer_glass");
	}
}

void MixerItem::clickAction2()
{
}

void MixerItem::clickAction0()
{
}
