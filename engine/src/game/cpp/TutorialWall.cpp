#include "../game_all.h"

void TutorialWall::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("break_wall");
	animationFlip = true;
	useCurrentDirection = false;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	actionType = Type::NormalAction;
	objectName = S("tutorial_wall1");
	range = 1.0f;
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("sledgehammer"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("sledge_handle"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("sledge_head"), GameStrings::getString(GameStrings::actions, S("tutorial_wall_head")), nullptr, String::Empty));
}

void TutorialWall::creak1()
{
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->door_creak_1);
}

void TutorialWall::creak2()
{
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->door_creak_2);
}

void TutorialWall::creak3()
{
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->door_creak_3);
}

void TutorialWall::clickAction()
{
	if (usedItem == S("sledgehammer"))
	{
		if (!GameDataController::gd->getObjective(S("tutorial_wall_smashed")))
		{
			smash1->started = true;
			Invoke(S("stopSmash1"), 0.3f);
			Invoke(S("ssmash2"), 2.0f);
			Invoke(S("ssmash3"), 4.0f);
			aS->PlayOneShot(SoundsManagerController::sm->rock_hit_1);
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rock_rumble_1);
			GameDataController::gd->setObjective(S("tutorial_wall_smashed"), true);
		}
		else
		{
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("tutorial_wall_already_smashed")));
		}
	}
	else if (usedItem == S("sledge_handle"))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("tutorial_wall_fail")));
	}
	else if (!GameDataController::gd->getObjective(S("tutorial_wall_smashed")))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("tutorial_wall")));
	}
	else
	{
		PlayerController::pc->spawnName = S("Fence3Waypoint1");
		CurtainController::cc->fadeOut(S("LocationDesertFence3"), WalkController::Direction::E, S("window_jump"));
	}
}

void TutorialWall::ssmash2()
{
	smash2->started = true;
	Invoke(S("stopSmash2"), 0.3f);
	aS->PlayOneShot(SoundsManagerController::sm->rock_hit_2);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rock_rumble_2);
}

void TutorialWall::ssmash3()
{
	smash3->started = true;
	Invoke(S("stopSmash3"), 0.4f);
	aS->PlayOneShot(SoundsManagerController::sm->rock_hit_3);
	objectName = S("tutorial_wall2");
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->rock_rumble_3);
}

void TutorialWall::stopSmash1()
{
	smash1->started = false;
	sr->set_enabled(true);
	sr->set_sprite(s1);
}

void TutorialWall::stopSmash2()
{
	smash2->started = false;
	sr->set_enabled(true);
	sr->set_sprite(s2);
}

void TutorialWall::stopSmash3()
{
	smash3->started = false;
	sr->set_enabled(true);
	sr->set_sprite(s3);
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::N;
}

void TutorialWall::updateState()
{
	if (GameDataController::gd->getObjective(S("tutorial_wall_smashed")))
	{
		sr->set_enabled(true);
		sr->set_sprite(s3);
		objectName = S("tutorial_wall2");
		actionType = Type::Transition;
		trans_dir = WalkController::Direction::N;
	}
	else
	{
		objectName = S("tutorial_wall1");
		actionType = Type::NormalAction;
		trans_dir = WalkController::Direction::N;
		sr->set_enabled(false);
	}
}

void TutorialWall::clickAction2()
{
	PlayerController::pc->GetComponent<Animator>()->set_speed(1.0f);
}

void TutorialWall::clickAction0()
{
}

void TutorialWall::whatOnClick0()
{
	if (usedItem == S("sledgehammer") && !GameDataController::gd->getObjective(S("tutorial_wall_smashed")))
	{
		characterAnimationName = S("break_wall");
		animationFlip = true;
		useCurrentDirection = false;
		range = 1.0f;
	}
	else if (usedItem == S("sledge_handle") && !GameDataController::gd->getObjective(S("tutorial_wall_smashed")))
	{
		characterAnimationName = S("break_wall_fail");
		animationFlip = true;
		useCurrentDirection = false;
		range = 1.0f;
	}
	else if (GameDataController::gd->getObjective(S("tutorial_wall_smashed")))
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 2.0f;
	}
	else
	{
		characterAnimationName = S("action_stnd_");
		animationFlip = false;
		useCurrentDirection = true;
		range = 50.0f;
	}
}

void TutorialWall::whatOnClick()
{
}
