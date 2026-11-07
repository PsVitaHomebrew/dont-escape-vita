#include "../game_all.h"

void RestaurantSolider1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	actionType = Type::Talk;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_solider_1");
	range = 30.0f;
	position = ScreenControler::roundToNearestFullPixel3(sarge->transform->get_position());
	sarge->transform->set_position(position);
	position2 = Vector2(74.0f, 30.0f);
	Vector2 vectorToChange = Vector2();
	float z = sarge->transform->get_position().z;
	vectorToChange.x = position2.x;
	vectorToChange.y = position2.y;
	vectorToChange = ScreenControler::gameToScreen(vectorToChange);
	position = Vector3(vectorToChange.x, vectorToChange.y, sarge->transform->get_position().z);
	Vector3 vector = Camera::get_main()->WorldToScreenPoint(sarge->transform->get_position());
	position.z = vector.z;
	sarge->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position));
	sarge->transform->set_position(Vector3(sarge->transform->get_position().x, sarge->transform->get_position().y, z));
	updateState();
}

void RestaurantSolider1::clickAction()
{
	initIntroDialogue();
}

void RestaurantSolider1::initIntroDialogue()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, S("r_josh_intro1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), sarge->GetComponent<TextFieldController>(), color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	DialogueController::dc->callback = [this]() { dialogues(); };
	dialogues();
}

void RestaurantSolider1::takeDoc(int i)
{
	doc = DialogueController::dc->dialogueOptions[i]->GetComponent<DialogueOptionController>();
}

void RestaurantSolider1::dialogues()
{
	DialogueController::dc->reset();
	int num = 0;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_josh_sarge1_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("r_josh_sarge1"));
	DialogueController::dc->initDialogue(doc->lines, S("r_josh_sarge1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_josh_come1_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge_ship")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("r_josh_come1"));
	DialogueController::dc->initDialogue(doc->lines, S("r_josh_come1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), textField, color);
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("exit_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("r_josh_bye1"));
	DialogueController::dc->initDialogue(doc->lines, S("r_josh_bye1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalk(val); };
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void RestaurantSolider1::giveCatchers(String val)
{
	GameDataController::gd->setObjective(S("r_paul_catchers_given"), true);
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("stormcatcher1")));
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("stormcatcher2")));
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("stormcatcher3")));
}

void RestaurantSolider1::endTalk(String val)
{
	if (GameDataController::gd->getObjective(S("r_sarge_wounded1")))
	{
		GameDataController::gd->setObjective(S("r_sarge_wounded2"), true);
	}
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	updateState();
}

void RestaurantSolider1::Update()
{
	if (enabledd)
	{
		shadow->offsetY = joshOffset;
		Vector2 currentXY = Vector2(position2.x, 10.0f);
		shadow->update(position, currentXY, 0);
	}
}

void RestaurantSolider1::updateState()
{
	if (GameDataController::gd->getCurrentDay() != 3 || GameDataController::gd->getObjectiveDetail(S("day_3_threat")) != 1 || !GameDataController::gd->getObjective(S("sidereal_base_located")))
	{
		sarge->GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(-1);
		enabledd = false;
		return;
	}
	enabledd = true;
	shadow = New<SpriteShadow>(sarge);
	shadow->fadeRateV = 0.0f;
	shadow->fadeRateH = 0.0f;
	shadow->skewFactor = 0.0f;
	shadow->skewFactor2 = 15.0f;
	shadow->startAlpha = 0.5f;
	shadow->source = 140.0f;
	shadow->offsetY = joshOffset;
	shadow->scaleFactor = 0.3f;
	shadow->downwards = true;
	sarge->GetComponent<SpriteRenderer>()->set_enabled(true);
	setCollider(0);
	if (GameDataController::gd->getObjective(S("restaurant_sarge_encountered")))
	{
		sarge->GetComponent<Animator>()->Play(S("solider1_guard_loop"));
	}
	else
	{
		sarge->GetComponent<Animator>()->Play(S("solider1_aim_start"));
	}
}

void RestaurantSolider1::clickAction2()
{
}

void RestaurantSolider1::clickAction0()
{
}

void RestaurantSolider1::_cctor()
{
	color = Vector3(178.0f / 255.0f, 1.0f, 201.0f / 255.0f);
}
