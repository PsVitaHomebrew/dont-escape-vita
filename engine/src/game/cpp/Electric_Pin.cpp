#include "../game_all.h"

void Electric_Pin::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("electric_pin");
	range = 10000.0f;
	teleport = true;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("puzzle_cable"), String::Empty, nullptr, String::Empty));
	sr = GetComponent<SpriteRenderer>();
}

void Electric_Pin::clickAction()
{
}

void Electric_Pin::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_") + pinLetter.ToLower() + pinNumber) == 0)
	{
		if ((bool)sr)
		{
			sr->set_enabled(false);
		}
	}
	else if ((bool)sr)
	{
		sr->set_enabled(true);
		if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_") + pinLetter.ToLower() + pinNumber) == 1)
		{
			sr->set_sprite(wire_1);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_") + pinLetter.ToLower() + pinNumber) == 2)
		{
			sr->set_sprite(wire_2);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_") + pinLetter.ToLower() + pinNumber) == 3)
		{
			sr->set_sprite(wire_3);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_") + pinLetter.ToLower() + pinNumber) == 4)
		{
			sr->set_sprite(wire_4);
		}
		else
		{
			sr->set_sprite(selector);
		}
	}
}

void Electric_Pin::clickAction2()
{
}

void Electric_Pin::clickAction0()
{
}

void Electric_Pin::whatOnClick0()
{
	if (output && usedItem != S("puzzle_cable"))
	{
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hose);
		CursorController::cc->selectItem(ItemsManager::im->getItem(S("puzzle_cable")));
		GameDataController::gd->setObjectiveDetail(S("sidereal_electric_pin_") + pinLetter.ToLower() + pinNumber, -1);
		updateAll();
		checkConnect(1, S("sidereal_electric_pin_A"));
		checkConnect(2, S("sidereal_electric_pin_B"));
	}
	if (usedItem == S("puzzle_cable") && input)
	{
		String text = String::Empty;
		for (int i = 0; i < 5; i++)
		{
			String text2 = S("sidereal_electric_pin_") + prevPin.ToLower() + i;
			if (GameDataController::gd->getObjective(text2) && GameDataController::gd->getObjectiveDetail(text2) == -1)
			{
				text = text2;
				break;
			}
		}
		if (text != String::Empty)
		{
			for (int j = 0; j < 5; j++)
			{
				String id = S("sidereal_electric_pin_") + prevPin.ToLower() + j;
				if (GameDataController::gd->getObjective(id) && GameDataController::gd->getObjectiveDetail(id) == pinNumber)
				{
					GameDataController::gd->setObjectiveDetail(id, 0);
				}
			}
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->pyk);
			GameDataController::gd->setObjectiveDetail(text, pinNumber);
			updateAll();
		}
		checkConnect(1, S("sidereal_electric_pin_A"));
		checkConnect(2, S("sidereal_electric_pin_B"));
	}
	butbut->showOrNot();
}

void Electric_Pin::whatOnClick()
{
}

void Electric_Pin::startWithCheck()
{
	checkConnect(1, S("sidereal_electric_pin_A"));
	checkConnect(2, S("sidereal_electric_pin_B"));
}

void Electric_Pin::checkConnect(int exit, String pinName)
{
	int num = exit;
	int num2 = 0;
	for (int num3 = 4; num3 >= 0; num3--)
	{
		String text = S("a");
		if (num3 == 0)
		{
			text = S("a");
		}
		if (num3 == 1)
		{
			text = S("b");
		}
		if (num3 == 2)
		{
			text = S("c");
		}
		if (num3 == 3)
		{
			text = S("d");
		}
		if (num3 == 4)
		{
			text = S("e");
		}
		bool flag = false;
		for (int i = 0; i < 5; i++)
		{
			if (GameDataController::gd->getObjective(S("sidereal_electric_pin_") + text + i) && GameDataController::gd->getObjectiveDetail(S("sidereal_electric_pin_") + text + i) == num)
			{
				num2 += GameObject::Find(S("Pin_") + text.ToUpper() + i)->GetComponent<Electric_Pin>()->electricValue;
				num = i;
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			GameDataController::gd->setObjective(pinName, false);
			GameDataController::gd->setObjectiveDetail(pinName, 0);
			GameObject::Find(pinName + S("Label"))->GetComponent<SiderealElectricPinA>()->display(S("-"));
			break;
		}
		if (num3 == 0)
		{
			GameDataController::gd->setObjective(pinName, true);
			GameDataController::gd->setObjectiveDetail(pinName, num2);
			GameObject::Find(pinName + S("Label"))->GetComponent<SiderealElectricPinA>()->display(num2 + String::Empty);
		}
	}
}
