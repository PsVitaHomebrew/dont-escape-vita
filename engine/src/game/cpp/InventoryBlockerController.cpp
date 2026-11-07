#include "../game_all.h"

void InventoryBlockerController::Start()
{
}

void InventoryBlockerController::Update()
{
}

void InventoryBlockerController::OnMouseEnter()
{
	InventoryButtonController::ibc->GetComponent<InventoryButtonController>()->spaceWasPressed = false;
}

void InventoryBlockerController::OnMouseDown()
{
	if (!PlayerController::pc->gameObject->GetComponent<WalkController>()->busy)
	{
		PlayerController::pc->clickedSomething = true;
	}
}
