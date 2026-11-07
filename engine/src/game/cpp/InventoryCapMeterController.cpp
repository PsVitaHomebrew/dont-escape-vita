#include "../game_all.h"

void InventoryCapMeterController::Awake()
{
	if (cm == nullptr)
	{
		cm = this;
		gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
		gameObject->transform->set_position(Vector3(gameObject->transform->get_position().x, gameObject->transform->get_position().y, gameObject->transform->get_position().z));
		tfc = gameObject->GetComponent<TextFieldController>();
		ic = gameObject->transform->get_parent()->gameObject->GetComponent<InventoryController>();
	}
	else if (cm != P<InventoryCapMeterController>(this))
	{
		Object::Destroy(gameObject);
	}
}

void InventoryCapMeterController::Start()
{
	tfc->viewText(S("/"), false, true);
	tfc->keepAlive = true;
	tfc->black->SetActive(false);
	tfc->container->transform->set_parent(gameObject->transform);
	tfc->zzz = gameObject->transform->get_position().z - 0.01f;
}

void InventoryCapMeterController::Update()
{
}

void InventoryCapMeterController::updateText()
{
	String text = str(Mathf::Round(ic->maxCapacity));
	String text2 = str(Mathf::Round(ic->getCurrentWeight() * 100.0f) / 100.0f);
	tfc->viewText(text2 + S("/") + text + GameStrings::getString(GameStrings::gui, S("kg")), false, true, true, 100, 0.58f, 0.58f, 0.58f);
	tfc->keepAlive = true;
	tfc->black->SetActive(false);
}

void InventoryCapMeterController::OnMouseEnter()
{
	if (!PlayerController::wc->busy)
	{
		String text = str(ic->maxCapacity);
		String text2 = str(ic->getCurrentWeight());
		P<GameObject> gameObject = GameObject::Find(S("BottomText"));
		gameObject->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::gui, S("capacity")) + S(": ") + text2 + S("/") + text + S(" ") + GameStrings::getString(GameStrings::gui, S("kg")), false, true, false, ObjectActionController::BOTTOM_TEXT_WIDTH);
	}
}

void InventoryCapMeterController::OnMouseExit()
{
	if (!GameObject::FindGameObjectWithTag(S("Player"))->GetComponent<WalkController>()->busy)
	{
		P<GameObject> gameObject = GameObject::Find(S("BottomText"));
		gameObject->GetComponent<TextFieldController>()->keepAlive = false;
	}
}

void InventoryCapMeterController::OnMouseDown()
{
	if (!GameObject::FindGameObjectWithTag(S("Player"))->GetComponent<WalkController>()->busy)
	{
		GameObject::FindGameObjectWithTag(S("Player"))->GetComponent<PlayerController>()->clickedSomething = true;
	}
}
