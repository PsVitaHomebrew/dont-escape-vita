#include "../game_all.h"

void CS1_Waypoint_4::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("construction_site_entrance");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
	range = 10.0f;
}

void CS1_Waypoint_4::clickAction()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 3)
	{
		DialogueController::dc->quickDialogue(GingerActionController::getColor(), GameObject::Find(S("Ginger"))->GetComponent<GingerActionController>(), S("cs_park_gate"));
		return;
	}
	PlayerController::pc->spawnName = S("Waypoint_CS4_CS1");
	CurtainController::cc->fadeOut(S("CS4"), WalkController::Direction::E);
}

void CS1_Waypoint_4::updateState()
{
	if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0 && GameDataController::gd->getCurrentDay() == 3)
	{
		if (!GameDataController::gd->getObjective(S("cs_thug_shot")))
		{
			interactions = List<P<ItemInteraction>>::New();
			interactions.Add(New<ItemInteraction>(S("rifle_so_6"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_5"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_4"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_3"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_2"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_1"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_0"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_6"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_5"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_4"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_3"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_2"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_1"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_0"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_6"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_5"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_4"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_3"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_2"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_1"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_0"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_6"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_5"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_4"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_3"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_2"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_1"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_0"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_1"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_2"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_3"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_4"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_5"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_6"), GameStrings::getString(GameStrings::actions, S("cs_sharpshooter")), nullptr, String::Empty));
		}
		else
		{
			interactions = List<P<ItemInteraction>>::New();
			interactions.Add(New<ItemInteraction>(S("rifle_so_6"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_5"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_4"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_3"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_2"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_1"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_so_0"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_6"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_5"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_4"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_3"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_2"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_1"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_s_0"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_6"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_5"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_4"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_3"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_2"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_1"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_o_0"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_6"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_5"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_4"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_3"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_2"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("rifle_1"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_0"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_1"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_2"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_3"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_4"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_5"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
			interactions.Add(New<ItemInteraction>(S("revolver_6"), GameStrings::getString(GameStrings::actions, S("cs_nomore")), nullptr, String::Empty));
		}
	}
	else
	{
		interactions = List<P<ItemInteraction>>::New();
	}
}

void CS1_Waypoint_4::clickAction2()
{
}

void CS1_Waypoint_4::clickAction0()
{
}
