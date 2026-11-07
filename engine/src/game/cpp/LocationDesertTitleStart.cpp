#include "../game_all.h"

void LocationDesertTitleStart::Start()
{
	GameDataController::gd->setObjective(S("intro_desert_walked"), false);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_1, 0.25f);
	GameObject::Find(S("inventory_button"))->GetComponent<InventoryButtonController>()->hide();
	GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->hide();
	GameObject::Find(S("SmallPlayer"))->GetComponent<SmallWalker>()->fakeClick();
}

void LocationDesertTitleStart::Update()
{
	PlayerController::pc->gameObject->transform->set_position(Vector3(-11.0f, 0.5f, -2.5f));
	GameObject::Find(S("journal"))->get_gameObject()->transform->set_position(Vector3(-11.0f, 0.5f, -2.5f));
}
