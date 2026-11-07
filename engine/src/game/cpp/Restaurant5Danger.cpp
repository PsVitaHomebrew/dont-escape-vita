#include "../game_all.h"

void Restaurant5Danger::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_s");
	animationFlip = false;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("restaurant_threat_bugs");
	actionType = Type::NormalAction;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("flamethrower"), GameStrings::getString(GameStrings::actions, S("restaurant_block_flamethrower")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chemsuit_dmg_dmg"), GameStrings::getString(GameStrings::actions, S("restaurant_block_chemsuit")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chemsuit_rep_dmg"), GameStrings::getString(GameStrings::actions, S("restaurant_block_chemsuit")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chemsuit_dmg_rep"), GameStrings::getString(GameStrings::actions, S("restaurant_block_chemsuit")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("chemsuit_rep_rep"), GameStrings::getString(GameStrings::actions, S("restaurant_block_chemsuit")), nullptr, String::Empty));
	range = 210.0f;
}

void Restaurant5Danger::clickAction()
{
	Vector3 color = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
	String text = ((GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0) ? S("bugs") : ((GameDataController::gd->getObjectiveDetail(S("day_1_threat")) != 1) ? S("spiders") : S("gas")));
	DialogueController::dc->initDialogue(list, S("restaurant_blocked_") + text, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
	for (int i = 0; i < list.Count(); i++)
	{
		Timeline::t->addDialogue(list[i]);
	}
}

void Restaurant5Danger::updateState()
{
	colliderManager->setCollider(0);
	GetComponent<SpriteRenderer>()->set_enabled(true);
	if (GameDataController::gd->getCurrentDay() > 2)
	{
		colliderManager->setCollider(-1);
		GetComponent<Animator>()->set_enabled(false);
		if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
		{
			GetComponent<SpriteRenderer>()->set_sprite(bugs_dead);
		}
		else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
		{
			GetComponent<SpriteRenderer>()->set_sprite(webs_dead);
			GetComponent<SpriteRenderer>()->set_enabled(false);
		}
		else
		{
			GetComponent<SpriteRenderer>()->set_sprite(webs_dead);
		}
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 0)
	{
		GetComponent<Animator>()->set_enabled(true);
		GetComponent<Animator>()->Play(S("bugs"));
		for (int i = 0; i < flies.Count(); i++)
		{
			flies[i]->startFly(0);
		}
		objectName = S("restaurant_threat_bugs");
		interactions.Add(New<ItemInteraction>(S("rifle_so_6"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_so_5"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_so_4"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_so_3"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_so_2"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_so_1"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_so_0"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_6"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_5"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_4"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_3"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_2"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_1"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_s_0"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_6"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_5"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_4"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_3"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_2"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_1"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_o_0"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_6"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_5"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_4"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_3"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_2"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_1"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
		interactions.Add(New<ItemInteraction>(S("rifle_0"), GameStrings::getString(GameStrings::actions, S("restaurant_block_rifle")), nullptr, String::Empty));
	}
	else if (GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 1)
	{
		GetComponent<Animator>()->set_enabled(true);
		GetComponent<Animator>()->Play(S("gas"));
		objectName = S("restaurant_threat_gas");
	}
	else
	{
		GetComponent<Animator>()->set_enabled(false);
		GetComponent<SpriteRenderer>()->set_sprite(webs);
		objectName = S("restaurant_threat_spiders");
	}
	if (GameDataController::gd->getCurrentDay() > 2)
	{
		zmarker->transform->set_position(Vector3(zmarker->transform->get_position().x, 0.4f, zmarker->transform->get_position().z));
	}
	else
	{
		zmarker->transform->set_position(Vector3(zmarker->transform->get_position().x, -0.692f, zmarker->transform->get_position().z));
	}
}

void Restaurant5Danger::clickAction2()
{
}

void Restaurant5Danger::clickAction0()
{
}
