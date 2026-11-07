#include "../game_all.h"

void DreamMaggie::_cctor()
{
	color = Vector3(0.6f, 106.0f / 255.0f, 0.4f);
}

void DreamMaggie::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = true;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	actionType = Type::Talk;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_freezer");
	range = 30.0f;
	shadow = New<SpriteShadow>(sarge);
	shadow->fadeRateV = 0.002f;
	shadow->fadeRateH = 0.002f;
	shadow->skewFactor = 25.0f;
	shadow->skewFactor2 = 0.0f;
	shadow->startAlpha = 0.75f;
	shadow->source = 180.0f;
	shadow->scaleFactor = 0.75f;
	shadow->downwards = true;
	position = ScreenControler::roundToNearestFullPixel3(sarge->transform->get_position());
	sarge->transform->set_position(position);
	position2 = Vector2(210.0f, 45.0f);
	shadow->offsetY = 18;
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

void DreamMaggie::whatOnClick0()
{
	if (usedItem != String::Empty)
	{
		actionMarker = actionmarker2;
		range = 4.0f;
	}
	else
	{
		actionMarker = actionmarker1;
		range = 30.0f;
	}
}

void DreamMaggie::clickAction()
{
	if (usedItem == String::Empty)
	{
		initIntroDialogue();
	}
}

void DreamMaggie::initIntroDialogue()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (!GameDataController::gd->getObjective(S("r_steve_intro1")))
	{
		GameDataController::gd->setObjective(S("r_steve_intro1"), true);
		DialogueController::dc->initDialogue(list, S("r_steve_intro1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), sarge->GetComponent<TextFieldController>(), color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	}
	else
	{
		DialogueController::dc->initDialogue(list, S("r_steve_intro2"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), sarge->GetComponent<TextFieldController>(), color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	DialogueController::dc->callback = [this]() { dialogues(); };
	dialogues();
}

void DreamMaggie::takeDoc(int i)
{
	doc = DialogueController::dc->dialogueOptions[i]->GetComponent<DialogueOptionController>();
}

void DreamMaggie::dialogues()
{
	DialogueController::dc->reset();
	int num = 0;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_steve_come1_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/sarge_ship")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("r_steve_come1"));
	DialogueController::dc->initDialogue(doc->lines, S("r_steve_come1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	num++;
	String empty = String::Empty;
	empty = ((GameDataController::gd->getObjective(S("r_sarge_wounded_bandage")) && GameDataController::gd->getObjective(S("r_sarge_wounded_bandage"))) ? String::Empty : (GameDataController::gd->getObjective(S("r_sarge_wounded_alcohol")) ? S("r_steve_you4") : ((!GameDataController::gd->getObjective(S("r_sarge_wounded_bandage"))) ? S("r_steve_you2") : S("r_steve_you3"))));
	if (GameDataController::gd->getObjective(S("r_sarge_wounded_bandage")) && GameDataController::gd->getObjective(S("r_sarge_wounded_alcohol")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_steve_you1_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/wounded")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("r_steve_you1"));
		DialogueController::dc->initDialogue(doc->lines, S("r_steve_you5"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	}
	else
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("r_steve_you1_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/wounded")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("r_steve_you1"));
		DialogueController::dc->initDialogue(doc->lines, S("r_steve_you1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
		DialogueController::dc->initDialogue(doc->lines, empty, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	}
	num++;
	takeDoc(num);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("exit_caption"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/bye")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("r_steve_bye_1"));
	DialogueController::dc->initDialogue(doc->lines, S("r_steve_bye_1"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), textField, color, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor());
	doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalk(val); };
	num++;
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void DreamMaggie::endTalk(String val)
{
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	updateState();
}

void DreamMaggie::Update()
{
	shadow->update(position, position2, 20);
}

void DreamMaggie::updateState()
{
}

void DreamMaggie::clickAction2()
{
}

void DreamMaggie::clickAction0()
{
}
