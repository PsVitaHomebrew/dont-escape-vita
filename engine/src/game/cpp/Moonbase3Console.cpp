#include "../game_all.h"

void Moonbase3Console::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("screen_quests");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("disc1"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("disc2"), String::Empty, nullptr, String::Empty));
}

List<String> Moonbase3Console::quests()
{
	List<String> list = List<String>::New();
	ExamineSprite::es->lookAction = [this]() { ohNo(); };
	list.Add(String::Empty + GameStrings::getString(GameStrings::world_labels, S("pod_caption_stats_a")));
	if (!GameDataController::gd->getObjective(S("moon_disc1_used")))
	{
		list.Add(list[list.Count() - 1] + S(" ^^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_fd1_a")));
	}
	else
	{
		list.Add(list[list.Count() - 1] + S(" ^^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_fd1_b")));
	}
	if (!GameDataController::gd->getObjective(S("moon_disc2_used")))
	{
		list.Add(list[list.Count() - 1] + S(" ^^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_fd2_a")));
	}
	else
	{
		list.Add(list[list.Count() - 1] + S(" ^^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_fd2_b")));
	}
	if (!GameDataController::gd->getObjective(S("moon_console_unlocked")))
	{
		list.Add(list[list.Count() - 1] + S(" ^^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_3a")));
	}
	else
	{
		String text = GameStrings::getString(GameStrings::world_labels, S("pod_caption_2a"));
		int num = 52;
		if (GameDataController::gd->getObjective(S("moon_cate_sleeps")))
		{
			num++;
		}
		if (GameDataController::gd->getObjective(S("moon_cody_sleeps")))
		{
			num++;
		}
		if (GameDataController::gd->getObjective(S("moon_barry_sleeps")))
		{
			num++;
		}
		String text2 = text;
		text = text2 + S(" ") + num + String::Empty + GameStrings::getString(GameStrings::world_labels, S("pod_caption_2b"));
		list.Add(list[list.Count() - 1] + S(" ^^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_3c")));
		list.Add(String::Empty + GameStrings::getString(GameStrings::world_labels, S("pod_caption_0")));
		list.Add(list[list.Count() - 1] + S(" ^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_1")));
		list.Add(list[list.Count() - 1] + S(" ^") + text);
		list.Add(list[list.Count() - 1] + S(" ^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_4")));
		list.Add(list[list.Count() - 1] + S(" ^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_5")));
		list.Add(list[list.Count() - 1] + S(" ^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_6")));
		list.Add(list[list.Count() - 1] + S(" ^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_7")));
		if (GameDataController::gd->getObjective(S("moon_disc1_used")))
		{
			list.Add(list[list.Count() - 1] + S(" ^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_A")));
		}
		if (GameDataController::gd->getObjective(S("moon_disc2_used")))
		{
			list.Add(list[list.Count() - 1] + S(" ^") + GameStrings::getString(GameStrings::world_labels, S("pod_caption_B")));
		}
	}
	list.Add(list[list.Count() - 1] + S(" ^") + GameStrings::getString(GameStrings::world_labels, S("quests_underline")));
	return list;
}

void Moonbase3Console::failsound(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fail1);
}

void Moonbase3Console::examine(String val)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
	ExamineSprite::es->textField->shift.x = -110.0f;
	ExamineSprite::es->textField->shift.y = 55.0f;
	ExamineSprite::es->readyText(quests(), 210, 0.5f, 0.75f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	ExamineSprite::es->ac = SoundsManagerController::sm->computer_click1;
	ExamineSprite::es->audioVolume = 0.25f;
	ExamineSprite::es->show(painting);
	ExamineSprite::es->actionOnShow = false;
	if (val == S("yes"))
	{
		if (GameDataController::gd->getObjective(S("moon_disc1_used")) && GameDataController::gd->getObjective(S("moon_disc2_used")))
		{
			ExamineSprite::es->lookAction = [this]() { say1(); };
		}
		else
		{
			ExamineSprite::es->lookAction = [this]() { say2(); };
		}
		ExamineSprite::es->actionOnShow = false;
	}
}

void Moonbase3Console::say1()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moon_console_disks_inserted")));
}

void Moonbase3Console::say2()
{
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moon_console_disk_inserted")));
}

void Moonbase3Console::clickAction()
{
	if (usedItem != String::Empty)
	{
		if (GameDataController::gd->getObjective(S("moon_light_failed")) && !GameDataController::gd->getObjective(S("moon_light_restored")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moon_console_disk_no_power")));
			return;
		}
		if (!GameDataController::gd->getObjective(S("moon_console_unlocked")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moon_console_disk_locked")));
			return;
		}
		if (!GameDataController::gd->getObjective(S("moon_pods_unlocked")))
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moon_console_disk_checked")));
			return;
		}
		if (usedItem == S("disc1"))
		{
			GameDataController::gd->setObjective(S("moon_disc1_used"), true);
			P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("moon_console_disk1_inserted"));
			timelineAction->textColor = Vector3(1.0f, 1.0f, 1.0f);
			timelineAction->function = [this](String val) { examine(val); };
			timelineAction->param = S("yes");
			timelineAction->actionWithText = false;
			Timeline::t->addAction(timelineAction);
		}
		else if (usedItem == S("disc2"))
		{
			GameDataController::gd->setObjective(S("moon_disc2_used"), true);
			P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("moon_console_disk2_inserted"));
			timelineAction->textColor = Vector3(1.0f, 1.0f, 1.0f);
			timelineAction->function = [this](String val) { examine(val); };
			timelineAction->param = S("yes");
			timelineAction->actionWithText = false;
			Timeline::t->addAction(timelineAction);
		}
		InventoryController::ic->removeItem(usedItem);
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->disk);
		return;
	}
	if (GameDataController::gd->getObjective(S("moon_light_failed")) && !GameDataController::gd->getObjective(S("moon_light_restored")))
	{
		gameObject->transform->Find(S("TextField"))->transform->set_position(ScreenControler::roundToNearestFullPixel3(gameObject->transform->Find(S("TextField"))->transform->get_position()));
		P<TimelineAction> timelineAction2 = New<TimelineAction>();
		timelineAction2 = New<TimelineAction>();
		timelineAction2->textfield = gameObject->transform->Find(S("TextField"))->GetComponent<TextFieldController>();
		timelineAction2->textColor = Vector3(1.0f, 0.0f, 0.0f);
		timelineAction2->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
		timelineAction2->text = GameStrings::getString(GameStrings::actions, S("moon_power_failure_2"));
		timelineAction2->actionWithText = true;
		timelineAction2->function = [this](String s) { failsound(s); };
		Timeline::t->addAction(timelineAction2);
		return;
	}
	examine(String::Empty);
	if (GameDataController::gd->getObjective(S("moon_console_unlocked")))
	{
		if (GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("dialogue_pods_intro")))
		{
			ExamineSprite::es->lookAction = [this]() { ohNo(); };
		}
		else if (!GameDataController::gd->getObjective(S("npc1_alive")) && !GameDataController::gd->getObjective(S("moon_pods_unlocked")))
		{
			ExamineSprite::es->lookAction = [this]() { opennocate(); };
		}
	}
	GameDataController::gd->setObjective(S("pods_cosnole_inspected"), true);
}

void Moonbase3Console::ohNo()
{
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	String prefix = S("ginger_moon_pods_emergency_intro_cate");
	if (!GameDataController::gd->getObjective(S("npc1_alive")))
	{
		prefix = S("ginger_moon_pods_emergency_intro_no_cate");
	}
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	DialogueController::dc->initDialogue(list, prefix, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, GingerActionController::getColor());
	if (GameDataController::gd->getObjective(S("npc1_alive")))
	{
		list[list.Count() - 1]->action = [this](String s) { startDialogue2(s); };
	}
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
	GameDataController::gd->setObjective(S("dialogue_pods_intro"), true);
}

void Moonbase3Console::opennocate()
{
	GameDataController::gd->setObjective(S("moon_pods_unlocked"), true);
	GameObject::Find(S("Moonbase3Pad1"))->GetComponent<Moonbase3Pod>()->openIfNeeded();
	GameObject::Find(S("Moonbase3Pad2"))->GetComponent<Moonbase3Pod>()->openIfNeeded();
	GameObject::Find(S("Moonbase3Pad3"))->GetComponent<Moonbase3Pod>()->openIfNeeded();
	GameObject::Find(S("Moonbase3Pad4"))->GetComponent<Moonbase3Pod>()->openIfNeeded();
}

void Moonbase3Console::updateState()
{
	colliderManager->setCollider(0);
}

void Moonbase3Console::startDialogue2(String str_)
{
	GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>()->npcClickAction(String::Empty);
}

void Moonbase3Console::clickAction2()
{
}

void Moonbase3Console::clickAction0()
{
}

void Moonbase3Console::whatOnClick0()
{
}

void Moonbase3Console::whatOnClick()
{
}
