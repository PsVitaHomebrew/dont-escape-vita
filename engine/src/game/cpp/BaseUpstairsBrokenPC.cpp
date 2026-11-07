#include "../game_all.h"

void BaseUpstairsBrokenPC::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_stnd_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("base_broken_pc");
	range = 40.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("ext_cord"), GameStrings::getString(GameStrings::actions, S("pc_ext")), nullptr, String::Empty));
}

void BaseUpstairsBrokenPC::clickAction()
{
	PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("base_broken_pc")), true);
}

void BaseUpstairsBrokenPC::updateState()
{
}

void BaseUpstairsBrokenPC::clickAction2()
{
}

void BaseUpstairsBrokenPC::clickAction0()
{
}
