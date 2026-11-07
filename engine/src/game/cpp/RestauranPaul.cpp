#include "../game_all.h"

void RestauranPaul::_cctor()
{
	color = Vector3(253.0f / 255.0f, 106.0f / 255.0f, 2.0f / 255.0f);
}

void RestauranPaul::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_se");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	actionType = Type::Talk;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_solider_4");
	range = 10.0f;
	position = ScreenControler::roundToNearestFullPixel3(sarge->transform->get_position());
	sarge->transform->set_position(position);
	position2 = Vector2(115.0f, 65.0f);
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

void RestauranPaul::clickAction()
{
	initIntroDialogue();
}

void RestauranPaul::initIntroDialogue()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (!GameDataController::gd->getObjective(S("r_paul_intro1")))
	{
		GameDataController::gd->setObjective(S("r_paul_intro1"), true);
		DialogueController::dc->initDialogue(list, S("r_paul_intro1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), sarge->GetComponent<TextFieldController>(), color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	}
	else
	{
		DialogueController::dc->initDialogue(list, S("r_paul_intro2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), sarge->GetComponent<TextFieldController>(), color);
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	DialogueController::dc->callback = [this]() { dialogues(); };
	dialogues();
}

void RestauranPaul::takeDoc(int i)
{
	doc = DialogueController::dc->dialogueOptions[i]->GetComponent<DialogueOptionController>();
}

void RestauranPaul::gingerTurn(String a)
{
	GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->forceAnimation(S("stand_ne"));
}

void RestauranPaul::dialogues()
{
	DialogueController::dc->reset();
	int num = 0;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_paul_catchers1_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/storm")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("r_paul_catchers1"));
	DialogueController::dc->initDialogue(doc->lines, S("r_paul_catchers1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	doc->lines[0]->action = [this](String s) { gingerTurn(s); };
	num++;
	if (GameDataController::gd->getObjective(S("r_paul_catchers1")) && !GameDataController::gd->getObjective(S("r_paul_catchers_given")))
	{
		if (!GameDataController::gd->getObjective(S("r_paul_catchers2")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_paul_catchers2_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/storm2")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("r_paul_catchers2"));
			DialogueController::dc->initDialogue(doc->lines, S("r_paul_catchers2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
			doc->lines[0]->action = [this](String s) { gingerTurn(s); };
		}
		else
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_paul_catchers4_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/storm2")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("r_paul_catchers4"));
			DialogueController::dc->initDialogue(doc->lines, S("r_paul_catchers4"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
			doc->lines[0]->action = [this](String s) { gingerTurn(s); };
		}
		if (!GameDataController::gd->getObjective(S("r_sarge_wounded_bandage")) || !GameDataController::gd->getObjective(S("r_sarge_wounded_alcohol")))
		{
			String empty = String::Empty;
			empty = (GameDataController::gd->getObjective(S("r_paul_catchers2")) ? S("r_paul_catchers5") : S("r_paul_catchers3"));
			DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
			doc->lines[0]->action = [this](String s) { gingerTurn(s); };
		}
		else
		{
			doc->setObjective(S("r_paul_catchers6"));
			DialogueController::dc->initDialogue(doc->lines, S("r_paul_catchers6"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
			doc->lines[0]->action = [this](String s) { gingerTurn(s); };
			doc->lines[doc->lines.Count() - 1]->action = [this](String s) { giveCatchers(s); };
		}
		num++;
	}
	if (GameDataController::gd->getObjective(S("r_paul_catchers_given")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_paul_catchers7_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/storm_catcher")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("r_paul_catchers7"));
		DialogueController::dc->initDialogue(doc->lines, S("r_paul_catchers7"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		doc->lines[0]->action = [this](String s) { gingerTurn(s); };
		num++;
	}
	if (GameDataController::gd->getObjective(S("r_paul_catchers_given")) && GameDataController::gd->getObjective(S("r_paul_mount1")) && GameDataController::gd->getObjective(S("r_sarge_gun")) && GameDataController::gd->getObjective(S("r_sarge_ammo")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_paul_mount2_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pylon2")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("r_paul_mount2"));
		DialogueController::dc->initDialogue(doc->lines, S("r_paul_mount2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		doc->lines[0]->action = [this](String s) { gingerTurn(s); };
		num++;
	}
	else if (GameDataController::gd->getObjective(S("r_paul_catchers7")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_paul_mount1_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/pylon")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("r_paul_mount1"));
		DialogueController::dc->initDialogue(doc->lines, S("r_paul_mount1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		doc->lines[0]->action = [this](String s) { gingerTurn(s); };
		num++;
	}
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_paul_come1_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge_ship")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("r_paul_come1"));
	DialogueController::dc->initDialogue(doc->lines, S("r_paul_come1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	doc->lines[0]->action = [this](String s) { gingerTurn(s); };
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("exit_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("r_paul_bye1"));
	DialogueController::dc->initDialogue(doc->lines, S("r_paul_bye1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color);
	doc->lines[doc->lines.Count() - 1]->action = [this](String s) { endTalk(s); };
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void RestauranPaul::giveCatchers(String val)
{
	GameDataController::gd->setObjective(S("r_paul_catchers_given"), true);
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("stormcatcher1")));
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("stormcatcher2")));
	InventoryController::ic->pickOrDropItem(ItemsManager::im->getItem(S("stormcatcher3")));
}

void RestauranPaul::endTalk(String val)
{
	if (GameDataController::gd->getObjective(S("r_sarge_wounded1")))
	{
		GameDataController::gd->setObjective(S("r_sarge_wounded2"), true);
	}
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	updateState();
}

void RestauranPaul::Update()
{
	if (sarge->GetComponent<SpriteRenderer>()->get_enabled() && last != sarge->GetComponent<SpriteRenderer>()->get_sprite())
	{
		Vector2 currentXY = Vector2(position2.x, 45.0f);
		shadow->update(position, currentXY, 0);
		last = sarge->GetComponent<SpriteRenderer>()->get_sprite();
	}
}

void RestauranPaul::updateState()
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
	shadow->scaleFactor = 0.3f;
	shadow->downwards = true;
	shadow->offsetY = 20;
	sarge->GetComponent<SpriteRenderer>()->set_enabled(true);
	setCollider(0);
	if (GameDataController::gd->getObjective(S("restaurant_sarge_encountered")))
	{
		sarge->GetComponent<Animator>()->Play(S("solider4_guard_loop"));
	}
	else
	{
		sarge->GetComponent<Animator>()->Play(S("solider4_aim"));
	}
}

void RestauranPaul::clickAction2()
{
}

void RestauranPaul::clickAction0()
{
}
