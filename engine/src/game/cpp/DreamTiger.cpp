#include "../game_all.h"

void DreamTiger::_cctor()
{
	colorTiger = Vector3(134.0f / 255.0f, 121.0f / 255.0f, 91.0f / 255.0f);
	colorMaggie = Vector3(175.0f / 255.0f, 98.0f / 255.0f, 124.0f / 255.0f);
}

void DreamTiger::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_ne");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	actionType = Type::Talk;
	dkvs = GameStrings::objects;
	objectName = S("dream_tiger");
	range = 1.0f;
	shadow = New<SpriteShadow>(tiger);
	shadow2 = New<SpriteShadow>(maggie);
	shadow->fadeRateV = 0.002f;
	shadow->fadeRateH = 0.002f;
	shadow->skewFactor = 25.0f;
	shadow->skewFactor2 = 0.0f;
	shadow->startAlpha = 0.75f;
	shadow->source = 180.0f;
	shadow->scaleFactor = 0.5f;
	shadow->downwards = true;
	shadow2->fadeRateV = 0.002f;
	shadow2->fadeRateH = 0.002f;
	shadow2->skewFactor = 25.0f;
	shadow2->skewFactor2 = 0.0f;
	shadow2->startAlpha = 0.75f;
	shadow2->source = 180.0f;
	shadow2->scaleFactor = 0.5f;
	shadow2->downwards = true;
	position = ScreenControler::roundToNearestFullPixel3(tiger->transform->get_position());
	tiger->transform->set_position(position);
	position2 = Vector2(195.0f, 65.0f);
	position2_b = Vector2(210.0f, 45.0f);
	shadow->offsetY = -1;
	shadow2->offsetY = -1;
	Vector2 vectorToChange = Vector2();
	float z = tiger->transform->get_position().z;
	vectorToChange.x = position2.x;
	vectorToChange.y = position2.y;
	vectorToChange = ScreenControler::gameToScreen(vectorToChange);
	position = Vector3(vectorToChange.x, vectorToChange.y, tiger->transform->get_position().z);
	Vector3 vector = Camera::get_main()->WorldToScreenPoint(tiger->transform->get_position());
	position.z = vector.z;
	tiger->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position));
	tiger->transform->set_position(Vector3(tiger->transform->get_position().x, tiger->transform->get_position().y, z));
	z = maggie->transform->get_position().z;
	vectorToChange.x = position2_b.x;
	vectorToChange.y = position2_b.y;
	vectorToChange = ScreenControler::gameToScreen(vectorToChange);
	position_b = Vector3(vectorToChange.x, vectorToChange.y, maggie->transform->get_position().z);
	vector = Camera::get_main()->WorldToScreenPoint(maggie->transform->get_position());
	position_b.z = vector.z;
	maggie->transform->set_position(Camera::get_main()->ScreenToWorldPoint(position_b));
	maggie->transform->set_position(Vector3(maggie->transform->get_position().x, maggie->transform->get_position().y, z));
	updateState();
}

void DreamTiger::whatOnClick0()
{
}

void DreamTiger::clickAction()
{
	if (usedItem == String::Empty)
	{
		if (!GameDataController::gd->getObjective(S("dream_tiger_future")) && !GameDataController::gd->getObjective(S("dream_maggie_future")))
		{
			initIntroDialogue();
		}
		else if (GameDataController::gd->getObjective(S("previous_disc_barry")) && GameDataController::gd->getObjective(S("previous_disc_cody")))
		{
			tiger->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::actions, S("tiger_run")), false, true, false, 100, colorTiger.x, colorTiger.y, colorTiger.z);
		}
		else if (GameDataController::gd->getObjective(S("previous_disc_barry")))
		{
			tiger->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::actions, S("tiger_run")), false, true, false, 100, colorTiger.x, colorTiger.y, colorTiger.z);
		}
		else if (GameDataController::gd->getObjective(S("previous_disc_cody")))
		{
			maggie->GetComponent<TextFieldController>()->viewText(GameStrings::getString(GameStrings::actions, S("maggie_run")), false, true, false, 100, colorMaggie.x, colorMaggie.y, colorMaggie.z);
		}
	}
}

void DreamTiger::initIntroDialogue()
{
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	if (GameDataController::gd->getObjective(S("previous_disc_cody")) && GameDataController::gd->getObjective(S("previous_disc_barry")))
	{
		GameDataController::gd->setObjective(S("dream_maggie_intro"), true);
		DialogueController::dc->initDialogue(list, S("dream_maggie_tiger_intro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tiger->GetComponent<TextFieldController>(), colorTiger, GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
	}
	else if (GameDataController::gd->getObjective(S("previous_disc_barry")))
	{
		GameDataController::gd->setObjective(S("dream_tiger_intro"), true);
		DialogueController::dc->initDialogue(list, S("dream_tiger_intro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tiger->GetComponent<TextFieldController>(), colorTiger, GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
	}
	else if (GameDataController::gd->getObjective(S("previous_disc_cody")))
	{
		GameDataController::gd->setObjective(S("dream_maggie_intro"), true);
		DialogueController::dc->initDialogue(list, S("dream_maggie_intro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	DialogueController::dc->callback = [this]() { dialogues(); };
	dialogues();
}

void DreamTiger::takeDoc(int i)
{
	doc = DialogueController::dc->dialogueOptions[i]->GetComponent<DialogueOptionController>();
}

void DreamTiger::dialogues()
{
	DialogueController::dc->reset();
	int num = 0;
	if (GameDataController::gd->getObjective(S("previous_disc_barry")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("dream_tiger_who_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/tiger")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dream_tiger_who"));
		DialogueController::dc->initDialogue(doc->lines, S("dream_tiger_who"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tiger->GetComponent<TextFieldController>(), colorTiger, GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
		num++;
	}
	if (GameDataController::gd->getObjective(S("previous_disc_barry")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("dream_tiger_remember_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/dream")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dream_tiger_remember"));
		DialogueController::dc->initDialogue(doc->lines, S("dream_tiger_remember"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tiger->GetComponent<TextFieldController>(), colorTiger, GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
		num++;
	}
	if (GameDataController::gd->getObjective(S("previous_disc_cody")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("dream_maggie_who_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/dead_wife")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dream_maggie_who"));
		DialogueController::dc->initDialogue(doc->lines, S("dream_maggie_who"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
		num++;
	}
	if (GameDataController::gd->getObjective(S("previous_disc_cody")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("dream_maggie_remember_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/dream")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dream_maggie_remember"));
		DialogueController::dc->initDialogue(doc->lines, S("dream_maggie_remember"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
		num++;
	}
	if (GameDataController::gd->getObjective(S("previous_disc_barry")) && !GameDataController::gd->getObjective(S("previous_disc_cody")))
	{
		if (GameDataController::gd->getObjective(S("dream_tiger_remember")) && GameDataController::gd->getObjective(S("dream_tiger_who")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dream_tiger_cody_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/cody")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dream_tiger_cody"));
			DialogueController::dc->initDialogue(doc->lines, S("dream_tiger_cody"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tiger->GetComponent<TextFieldController>(), colorTiger, GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
			num++;
		}
		if (GameDataController::gd->getObjective(S("dream_tiger_cody")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dream_tiger_future_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/where_go")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dream_tiger_future"));
			DialogueController::dc->initDialogue(doc->lines, S("dream_tiger_future"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), tiger->GetComponent<TextFieldController>(), colorTiger, GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
			doc->lines[doc->lines.Count() - 6]->action = [this](String val) { shadowpep(val); };
			doc->lines[doc->lines.Count() - 4]->action = [this](String val) { shadowpep2(val); };
			doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalk(val); };
			num++;
		}
	}
	if (GameDataController::gd->getObjective(S("previous_disc_cody")) && !GameDataController::gd->getObjective(S("previous_disc_barry")))
	{
		if (GameDataController::gd->getObjective(S("dream_maggie_remember")) && GameDataController::gd->getObjective(S("dream_maggie_who")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dream_maggie_barry_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/barry")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dream_maggie_barry"));
			DialogueController::dc->initDialogue(doc->lines, S("dream_maggie_barry"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
			num++;
		}
		if (GameDataController::gd->getObjective(S("dream_maggie_barry")))
		{
			takeDoc(num);
			doc->caption = GameStrings::getString(GameStrings::dialogues, S("dream_maggie_future_caption"));
			doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/where_go")));
			doc->lines = List<P<DialogueLine>>::New();
			doc->setObjective(S("dream_maggie_future"));
			DialogueController::dc->initDialogue(doc->lines, S("dream_maggie_future"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie);
			doc->lines[doc->lines.Count() - 8]->action = [this](String val) { shadowpep(val); };
			doc->lines[doc->lines.Count() - 6]->action = [this](String val) { shadowpep2(val); };
			doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalk(val); };
			num++;
		}
	}
	if (GameDataController::gd->getObjective(S("previous_disc_cody")) && GameDataController::gd->getObjective(S("previous_disc_barry")) && GameDataController::gd->getObjective(S("dream_maggie_remember")) && GameDataController::gd->getObjective(S("dream_maggie_who")) && GameDataController::gd->getObjective(S("dream_tiger_remember")) && GameDataController::gd->getObjective(S("dream_tiger_who")))
	{
		takeDoc(num);
		doc->caption = GameStrings::getString(GameStrings::dialogues, S("dream_maggie_tiger_future_caption"));
		doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/where_go")));
		doc->lines = List<P<DialogueLine>>::New();
		doc->setObjective(S("dream_maggie_future"));
		DialogueController::dc->initDialogue(doc->lines, S("dream_maggie_tiger_future"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), GameObject::Find(S("maggie_sprite"))->GetComponent<TextFieldController>(), colorMaggie, tiger->GetComponent<TextFieldController>(), colorTiger);
		doc->lines[doc->lines.Count() - 8]->action = [this](String val) { shadowpep(val); };
		doc->lines[doc->lines.Count() - 6]->action = [this](String val) { shadowpep2(val); };
		doc->lines[doc->lines.Count() - 1]->action = [this](String val) { endTalk(val); };
		num++;
		GameDataController::gd->setObjective(S("dream_tiger_future"), true);
	}
	takeDoc(0);
	if (doc->caption != String::Empty)
	{
		DialogueController::dc->talking = true;
	}
}

void DreamTiger::endTalk(String val)
{
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	updateState();
	dw->gogogo2 = true;
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_scare);
}

void DreamTiger::shadowpep(String val)
{
	dw->gogogo = true;
}

void DreamTiger::shadowpep2(String val)
{
	PlayerController::wc->forceAnimation(S("stand_e"), true);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->dumdumdum, 1.0f);
}

void DreamTiger::Update()
{
	if (tiger->GetComponent<SpriteRenderer>()->get_enabled())
	{
		shadow->update(position, position2, 20);
	}
	if (maggie->GetComponent<SpriteRenderer>()->get_enabled())
	{
		shadow2->update(position_b, position2_b, 20);
	}
}

void DreamTiger::updateState()
{
	if (GameDataController::gd->getObjective(S("previous_disc_barry")) && GameDataController::gd->getObjective(S("previous_disc_cody")))
	{
		tiger->GetComponent<SpriteRenderer>()->set_enabled(true);
		maggie->GetComponent<SpriteRenderer>()->set_enabled(true);
		setCollider(2);
		objectName = S("dream_tiger_maggie");
	}
	else if (GameDataController::gd->getObjective(S("previous_disc_barry")) && !GameDataController::gd->getObjective(S("previous_disc_cody")))
	{
		tiger->GetComponent<SpriteRenderer>()->set_enabled(true);
		maggie->GetComponent<SpriteRenderer>()->set_enabled(false);
		maggie->transform->set_position(Vector3(-100.0f, -100.0f, -100.0f));
		setCollider(0);
		objectName = S("dream_tiger");
	}
	else if (GameDataController::gd->getObjective(S("previous_disc_cody")) && !GameDataController::gd->getObjective(S("previous_disc_barry")))
	{
		maggie->GetComponent<SpriteRenderer>()->set_enabled(true);
		tiger->GetComponent<SpriteRenderer>()->set_enabled(false);
		tiger->transform->set_position(Vector3(-100.0f, -100.0f, -100.0f));
		setCollider(1);
		objectName = S("dream_maggie");
	}
	else
	{
		tiger->GetComponent<SpriteRenderer>()->set_enabled(false);
		maggie->GetComponent<SpriteRenderer>()->set_enabled(false);
		setCollider(-1);
		maggie->transform->set_position(Vector3(-100.0f, -100.0f, -100.0f));
		tiger->transform->set_position(Vector3(-100.0f, -100.0f, -100.0f));
	}
}

void DreamTiger::clickAction2()
{
}

void DreamTiger::clickAction0()
{
}
