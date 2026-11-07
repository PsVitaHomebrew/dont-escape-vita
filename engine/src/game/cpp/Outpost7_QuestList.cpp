#include "../game_all.h"

void Outpost7_QuestList::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_n");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("screen_quests");
	range = 1.0f;
}

List<String> Outpost7_QuestList::quests()
{
	List<String> list = List<String>::New();
	list.Add(GameStrings::getString(GameStrings::world_labels, S("quests_header")) + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_underline")));
	if (GameDataController::gd->getObjective(S("outpost_hatch_open")))
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_hatch_YES")));
	}
	else
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_hatch_NO")));
	}
	if ((GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 1 && GameDataController::gd->getObjective(S("outpost_hull_repaired_outside"))) || (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0 && GameDataController::gd->getObjective(S("outpost_hull_repaired_inside"))))
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_hull_integrity_YES")));
	}
	else
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_hull_integrity_NO")));
	}
	int num = 0;
	num += GameDataController::gd->getObjectiveDetail(S("outpost_score_a"));
	num += GameDataController::gd->getObjectiveDetail(S("outpost_score_b"));
	num += GameDataController::gd->getObjectiveDetail(S("outpost_score_c"));
	num += GameDataController::gd->getObjectiveDetail(S("outpost_score_d"));
	num += GameDataController::gd->getObjectiveDetail(S("outpost_score_e"));
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 0 || num != 0)
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_air_mixture_YES")));
	}
	else
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_air_mixture_NO")));
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 1 || num != 0)
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_fuel_mixture_YES")));
	}
	else
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_fuel_mixture_NO")));
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) != 1 || GameDataController::gd->getObjective(S("outpost_catalyst_used")))
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_catalyst_YES")));
	}
	else
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_catalyst_NO")));
	}
	if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_air_remember_NO")));
	}
	else
	{
		list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_air_remember_YES")));
	}
	list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_missing")));
	list.Add(list[list.Count() - 1] + S("^") + GameStrings::getString(GameStrings::world_labels, S("quests_underline")));
	return list;
}

void Outpost7_QuestList::clickAction()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->computer_click2);
	if (PlayerPrefs::GetString(S("lang")) == str(GameStrings::Language::DE))
	{
		ExamineSprite::es->textField->shift.x = -105.0f;
		ExamineSprite::es->textField->shift.y = 55.0f;
		ExamineSprite::es->readyText(quests(), 213, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		ExamineSprite::es->ac = SoundsManagerController::sm->computer_click1;
		ExamineSprite::es->audioVolume = 0.25f;
		ExamineSprite::es->show(paintingDE);
	}
	else
	{
		ExamineSprite::es->textField->shift.x = -52.0f;
		ExamineSprite::es->textField->shift.y = 55.0f;
		ExamineSprite::es->readyText(quests(), 170, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		ExamineSprite::es->ac = SoundsManagerController::sm->computer_click1;
		ExamineSprite::es->audioVolume = 0.25f;
		ExamineSprite::es->show(painting);
	}
}

void Outpost7_QuestList::updateState()
{
	colliderManager->setCollider(0);
}

void Outpost7_QuestList::clickAction2()
{
}

void Outpost7_QuestList::clickAction0()
{
}

void Outpost7_QuestList::whatOnClick0()
{
}

void Outpost7_QuestList::whatOnClick()
{
}
