#include "../game_all.h"

void SiderealPCMail::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_mail_app");
	range = 8000.0f;
	teleport = true;
	updateState();
	buttonLeft->workIfBusy = false;
	buttonLeft->onClick = [this]() { prevPage(); };
	buttonRight->workIfBusy = false;
	buttonRight->onClick = [this]() { nextPage(); };
	buttonAtt->workIfBusy = false;
	buttonAtt->onClick = [this]() { showAtt(); };
}

void SiderealPCMail::Update()
{
}

void SiderealPCMail::showAtt()
{
	PlayerController::pc->clickedSomething = true;
	beeper->beep();
	PlayerController::pc->setBusy(true);
	Invoke(S("makeItAtt1"), Random::Range(0.1f, 0.3f));
}

void SiderealPCMail::makeItAtt1()
{
	PlayerController::pc->setBusy(false);
	ExamineSprite::es->textField->shift.x = -20.0f;
	ExamineSprite::es->textField->shift.y = 20.0f;
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_email_displayed")) == 3)
	{
		ExamineSprite::es->textField->shift.x = -9.0f;
		ExamineSprite::es->textField->shift.y = -23.0f;
		ExamineSprite::es->readyText(List<String>::New({
			GameStrings::getString(GameStrings::actions, S("sidereal_lodge_discover_1")),
			GameStrings::getString(GameStrings::actions, S("sidereal_lodge_discover_2"))
		}), 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f);
		ExamineSprite::es->show(mapLodge);
		pageNumber->hide();
		ExamineSprite::es->lookAction = [this]() { seenLodge(); };
		ExamineSprite::es->actionOnShow = false;
	}
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_email_displayed")) == 9)
	{
		ExamineSprite::es->textField->shift.x = -9.0f;
		ExamineSprite::es->textField->shift.y = 0.0f;
		ExamineSprite::es->readyText(List<String>::New({
			GameStrings::getString(GameStrings::actions, S("sidereal_base_discover_1")),
			GameStrings::getString(GameStrings::actions, S("sidereal_base_discover_2")),
			GameStrings::getString(GameStrings::actions, S("sidereal_base_discover_3"))
		}), 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f);
		ExamineSprite::es->show(mapBase);
		pageNumber->hide();
		ExamineSprite::es->lookAction = [this]() { seenBase(); };
		ExamineSprite::es->actionOnShow = false;
	}
	if (GameDataController::gd->getObjectiveDetail(S("sidereal_email_displayed")) == 5)
	{
		ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("sidereal_pc_email_5_b_examine")) }), 100, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f);
		ExamineSprite::es->show(errorImg);
	}
}

void SiderealPCMail::seenLodge()
{
	GameDataController::gd->setObjectiveDetail(S("map_hunters_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	updateAll();
}

void SiderealPCMail::seenBase()
{
	GameDataController::gd->setObjective(S("sidereal_base_located"), true);
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		GameDataController::gd->setObjectiveDetail(S("map_outpost_revealed"), TravelAgency::LOCATION_STATUS_UNREACHABLE);
	}
	else
	{
		GameDataController::gd->setObjectiveDetail(S("map_outpost_revealed"), TravelAgency::LOCATION_STATUS_REACHABLE);
	}
	updateAll();
}

void SiderealPCMail::nextPage()
{
	int objectiveDetail = GameDataController::gd->getObjectiveDetail(S("sidereal_email_page"));
	objectiveDetail++;
	if (objectiveDetail > 10)
	{
		objectiveDetail = 10;
	}
	GameDataController::gd->setObjectiveDetail(S("sidereal_email_page"), objectiveDetail);
	updateState();
	if (objectiveDetail == 3 && GameDataController::gd->getObjectiveDetail(S("sidereal_email_displayed")) == 2 && !GameDataController::gd->getObjective(S("sidereal_read_cate_mail")))
	{
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("cate_emial"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f));
		for (int i = 0; i < list.Count(); i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		GameDataController::gd->setObjective(S("sidereal_read_cate_mail"), true);
	}
}

void SiderealPCMail::makeItNext()
{
	PlayerController::pc->setBusy(false);
}

void SiderealPCMail::prevPage()
{
	int objectiveDetail = GameDataController::gd->getObjectiveDetail(S("sidereal_email_page"));
	objectiveDetail--;
	if (objectiveDetail < 1)
	{
		objectiveDetail = 1;
	}
	GameDataController::gd->setObjectiveDetail(S("sidereal_email_page"), objectiveDetail);
	updateState();
}

void SiderealPCMail::makeItPrev()
{
	PlayerController::pc->setBusy(false);
}

void SiderealPCMail::whatOnClick()
{
}

void SiderealPCMail::clickAction()
{
	beeper->beep();
	if (!GameDataController::gd->getObjective(S("sidereal_email_displayed")))
	{
		PlayerController::pc->setBusy(true);
		Invoke(S("makeItSo"), Random::Range(0.25f, 1.0f));
	}
	else
	{
		Invoke(S("makeItSo2"), Random::Range(0.15f, 0.25f));
	}
}

void SiderealPCMail::makeItSo2()
{
	GameDataController::gd->setObjective(S("sidereal_email_displayed"), false);
	PlayerController::pc->setBusy(false);
	updateAll();
}

void SiderealPCMail::makeItSo()
{
	PlayerController::pc->setBusy(false);
	GameDataController::gd->setObjective(S("sidereal_email_displayed"), true);
	GameDataController::gd->setObjectiveDetail(S("sidereal_email_displayed"), 1);
	GameDataController::gd->setObjectiveDetail(S("sidereal_email_page"), 1);
	updateAll();
}

void SiderealPCMail::updateState()
{
	if (!GameDataController::gd->getObjective(S("sidereal_email_displayed")))
	{
		mailCaption->hide();
		spriter->set_sprite(icon);
		setCollider(1);
		mail->hide();
		iconCaption->manualUpdate();
		buttonAtt->buttonEnabled = false;
		buttonLeft->buttonEnabled = false;
		buttonRight->buttonEnabled = false;
		if (buttonAtt->buttonText != nullptr)
		{
			buttonAtt->buttonText->dissmiss(true);
		}
		if (buttonLeft->buttonText != nullptr)
		{
			buttonLeft->buttonText->dissmiss(true);
		}
		if (buttonRight->buttonText != nullptr)
		{
			buttonRight->buttonText->dissmiss(true);
		}
		pageNumber->hide();
		objectName = S("sidereal_mail_app");
		return;
	}
	mailCaption->manualUpdate();
	objectName = S("sidereal_x_app");
	if (GameDataController::gd->getObjective(S("sidereal_read_last_mail")))
	{
		spriter->set_sprite(mailRead);
	}
	else
	{
		spriter->set_sprite(mailNorml);
	}
	setCollider(0);
	mail->manualUpdate();
	iconCaption->hide();
	int num = GameDataController::gd->getObjectiveDetail(S("sidereal_email_page"));
	int num2 = 0;
	for (int i = 1; i <= 10; i++)
	{
		if (GameStrings::getString(GameStrings::world_labels, S("sidereal_pc_email_") + GameDataController::gd->getObjectiveDetail(S("sidereal_email_displayed")) + S("_b_") + i).Length() > 1)
		{
			num2 = i;
		}
	}
	if (num > num2)
	{
		num = num2;
		GameDataController::gd->setObjectiveDetail(S("sidereal_email_page"), num);
	}
	buttonLeft->initButton(S("<|"));
	buttonRight->initButton(S("|>"));
	String text = GameStrings::getString(GameStrings::world_labels, S("sidereal_pc_email_") + GameDataController::gd->getObjectiveDetail(S("sidereal_email_displayed")) + S("_b_attachment"));
	if (text.Length() > 1)
	{
		buttonAtt->initButton(text);
		buttonAtt->buttonEnabled = true;
	}
	else
	{
		buttonAtt->initButton(String::Empty);
		buttonAtt->buttonEnabled = false;
	}
	buttonRight->color1 = Vector3(0.25f, 0.25f, 0.25f);
	buttonRight->color2 = Vector3(1.0f, 1.0f, 1.0f);
	buttonLeft->color1 = Vector3(0.25f, 0.25f, 0.25f);
	buttonLeft->color2 = Vector3(1.0f, 1.0f, 1.0f);
	buttonLeft->initButton(S("<|"));
	buttonRight->initButton(S("|>"));
	if (num == 10 || num >= num2)
	{
		buttonRight->color1 = Vector3(0.45f, 0.45f, 0.45f);
		buttonRight->color2 = Vector3(0.45f, 0.45f, 0.45f);
		buttonRight->initButton(S("|>"));
		buttonRight->buttonEnabled = false;
	}
	else
	{
		buttonRight->buttonEnabled = true;
	}
	if (num == 1)
	{
		buttonLeft->color1 = Vector3(0.45f, 0.45f, 0.45f);
		buttonLeft->color2 = Vector3(0.45f, 0.45f, 0.45f);
		buttonLeft->initButton(S("<|"));
		buttonLeft->buttonEnabled = false;
	}
	else
	{
		buttonLeft->buttonEnabled = true;
	}
	mail->nameToDisplay = S("sidereal_pc_email_") + GameDataController::gd->getObjectiveDetail(S("sidereal_email_displayed")) + S("_b_") + GameDataController::gd->getObjectiveDetail(S("sidereal_email_page"));
	mail->manualUpdate();
	pageNumber->overrideString = num + S("/") + num2;
	pageNumber->manualUpdate();
	pageNumber->gameObject->transform->set_position(Vector3(pageNumber->gameObject->transform->get_position().x, pageNumber->gameObject->transform->get_position().y, -0.1f));
}

void SiderealPCMail::clickAction2()
{
}

void SiderealPCMail::clickAction0()
{
}
