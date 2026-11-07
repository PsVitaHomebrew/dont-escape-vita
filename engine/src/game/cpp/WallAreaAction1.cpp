#include "../game_all.h"

void WallAreaAction1::runrunrun()
{
	if (running)
	{
		GameDataController::gd->setObjective(S("run_hint"), true);
		running = true;
		GameObject::Find(S("run_hint"))->GetComponent<TextFieldController>()->setTime(2.0f);
		GameObject::Find(S("run_hint"))->GetComponent<TextFieldController>()->keepAlive = false;
	}
}

void WallAreaAction1::Action(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
	if (!running && wc != nullptr)
	{
		running = true;
		GameObject::Find(S("run_hint"))->GetComponent<TextFieldController>()->viewText(S("[") + GameStrings::getString(GameStrings::gui, S("run_hint")) + S("]"), false, true, false, 150);
		GameObject::Find(S("run_hint"))->GetComponent<TextFieldController>()->keepAlive = true;
	}
}

void WallAreaAction1::Action2(P<WalkController> wc, P<NPCWalkController> npcwc, P<GroundItemController> gic)
{
}
