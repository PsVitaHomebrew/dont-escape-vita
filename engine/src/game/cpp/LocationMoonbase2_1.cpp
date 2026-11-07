#include "../game_all.h"

void LocationMoonbase2_1::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moonbase_passage");
	actionType = Type::Transition;
	trans_dir = WalkController::Direction::W;
	doubleClickCondition = S("moon_allow_fast_travel_now");
	if (GameDataController::gd->getObjective(S("moon_light_failed")))
	{
		GetComponent<AudioSource>()->set_clip(SoundsManagerController::sm->ambient_ship_crashed);
		GetComponent<AudioSource>()->gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::PaddedCell);
		GetComponent<AudioSource>()->set_volume(0.75f);
		GetComponent<AudioSource>()->set_loop(true);
		GetComponent<AudioSource>()->set_pitch(0.25f);
		GetComponent<AudioSource>()->set_time(GetComponent<AudioSource>()->get_clip()->get_length() * Random::Range(0.0f, 0.9f));
		GetComponent<AudioSource>()->Play();
	}
}

void LocationMoonbase2_1::jump()
{
	PlayerController::wc->setSimpleTargetV3(GameObject::Find(S("jump_here"))->transform->get_position());
}

void LocationMoonbase2_1::clickAction()
{
	PlayerController::pc->spawnName = S("LocationMoonbase1_2");
	if (GameDataController::gd->getObjective(S("moon_window_cracked")))
	{
		CurtainController::cc->fadeOut(S("LocationMoonbase1"), WalkController::Direction::W, S("jump_side"), SoundsManagerController::sm->break_glass_big, true);
	}
	else
	{
		CurtainController::cc->fadeOut(S("LocationMoonbase1"), WalkController::Direction::W);
	}
}

void LocationMoonbase2_1::updateState()
{
}

void LocationMoonbase2_1::clickAction2()
{
}

void LocationMoonbase2_1::clickAction0()
{
}
