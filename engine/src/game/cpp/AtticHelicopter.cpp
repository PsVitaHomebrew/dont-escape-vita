#include "../game_all.h"

void AtticHelicopter::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	useCurrentDirection = true;
	characterAnimationName = S("action_stnd_");
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("helicopter");
	range = 50.0f;
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("tarpaulin"), GameStrings::getString(GameStrings::actions, S("heli_wrong_side")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("ducttape"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("flag"), GameStrings::getString(GameStrings::actions, S("cover_too_small")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanket"), GameStrings::getString(GameStrings::actions, S("cover_too_small")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("blanketb"), GameStrings::getString(GameStrings::actions, S("cover_too_small")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("therm"), GameStrings::getString(GameStrings::actions, S("cover_too_small")), nullptr, String::Empty));
}

void AtticHelicopter::clickAction()
{
	if (usedItem == S("ducttape"))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("heli_cant_fix_tape")));
	}
	else
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("helicopter")), true);
	}
}

void AtticHelicopter::whatOnClick()
{
}

void AtticHelicopter::updateState()
{
	if (GameDataController::gd->getObjective(S("helicopter_covered")))
	{
		GetComponent<SpriteRenderer>()->set_enabled(true);
	}
	else
	{
		GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void AtticHelicopter::clickAction2()
{
}

void AtticHelicopter::clickAction0()
{
}
