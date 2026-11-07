#include "../game_all.h"

void RestaurantDeadCody::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("dead_cody");
	range = 50.0f;
	teleport = false;
	updateState();
}

void RestaurantDeadCody::Update()
{
}

void RestaurantDeadCody::whatOnClick()
{
}

void RestaurantDeadCody::clickAction()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	String prefix = ((!GameDataController::gd->getObjective(S("dialogue_cody_intro"))) ? S("restaurant_dead_cody_unknown") : S("restaurant_dead_cody_known"));
	DialogueController::dc->initDialogue(list, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	GameDataController::gd->setObjective(S("restaurant_dead_cody_commented"), true);
}

void RestaurantDeadCody::updateState()
{
	setCollider(-1);
	GetComponent<SpriteRenderer>()->set_enabled(false);
}

void RestaurantDeadCody::clickAction2()
{
}

void RestaurantDeadCody::clickAction0()
{
}
