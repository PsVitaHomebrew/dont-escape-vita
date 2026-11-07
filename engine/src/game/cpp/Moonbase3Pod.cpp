#include "../game_all.h"

void Moonbase3Pod::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("moonbase_pod_empty");
	range = 10.0f;
}

bool Moonbase3Pod::waitForOthers()
{
	bool flag = true;
	bool flag2 = true;
	bool flag3 = true;
	if (!GameDataController::gd->getObjective(S("npc1_alive")) || GameDataController::gd->getObjective(S("moon_cate_sleeps")))
	{
		flag = false;
	}
	if (!GameDataController::gd->getObjective(S("npc2_alive")) || GameDataController::gd->getObjective(S("moon_barry_sleeps")))
	{
		flag3 = false;
	}
	if (!GameDataController::gd->getObjective(S("npc3_alive")) || GameDataController::gd->getObjective(S("moon_cody_sleeps")))
	{
		flag2 = false;
	}
	if (flag && (flag2 || flag3))
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_wait_others")));
		return true;
	}
	if (flag)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_wait_cate")));
		return true;
	}
	if (flag2 && flag3)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_wait_others")));
		return true;
	}
	if (flag2)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_wait_cody")));
		return true;
	}
	if (flag3)
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_wait_barry")));
		return true;
	}
	return false;
}

void Moonbase3Pod::makeSound()
{
	GetComponent<AudioSource>()->PlayOneShot(SoundsManagerController::sm->pods);
}

void Moonbase3Pod::failsound(String s)
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->fail1);
}

void Moonbase3Pod::clickAction()
{
	if (GameDataController::gd->getObjective(S("moon_pods_unlocked")))
	{
		if (whose == S("david"))
		{
			if (!GameDataController::gd->getObjective(S("moon_david_sleeps")) && !waitForOthers())
			{
				QuestionController::qc->showQuestion(GameStrings::getString(GameStrings::warnings, S("moon_use_pod")), QuestionController::PopupType::QUESTION, [this]() { enterPod(); });
			}
		}
		else if (whose == S("cate"))
		{
			if (GameDataController::gd->getObjective(S("npc1_alive")))
			{
				if (GameDataController::gd->getObjective(S("moon_cate_sleeps")))
				{
					PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_cate")));
				}
				else
				{
					waitForOthers();
				}
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_closed")));
			}
		}
		else if (whose == S("barry"))
		{
			if (GameDataController::gd->getObjective(S("npc2_alive")))
			{
				if (GameDataController::gd->getObjective(S("moon_barry_sleeps")))
				{
					PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_barry")));
				}
				else
				{
					waitForOthers();
				}
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_closed")));
			}
		}
		else
		{
			if (!(whose == S("cody")))
			{
				return;
			}
			if (GameDataController::gd->getObjective(S("npc3_alive")))
			{
				if (GameDataController::gd->getObjective(S("moon_cody_sleeps")))
				{
					PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_cody")));
				}
				else
				{
					waitForOthers();
				}
			}
			else
			{
				PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_closed")));
			}
		}
	}
	else
	{
		PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moonbase_pod_closed")));
	}
}

void Moonbase3Pod::enterPod()
{
	if (!GameDataController::gd->getObjective(S("moon_light_restored")))
	{
		if (!GameDataController::gd->getObjective(S("moon_light_failed")))
		{
			PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->power_down_big, 0.75f);
			GameDataController::gd->setObjective(S("moon_light_failed"), true);
			GameObject::Find(S("LocationManager"))->GetComponent<LocationMoonbase3Start>()->updateMLF();
			PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("moon_power_failure_1")));
			audioSouruce2->set_clip(SoundsManagerController::sm->ambient_ship_crashed);
			audioSouruce2->gameObject->GetComponent<AudioReverbFilter>()->set_reverbPreset(AudioReverbPreset::PaddedCell);
			audioSouruce2->set_volume(0.75f);
			audioSouruce2->set_loop(true);
			audioSouruce2->set_pitch(0.25f);
			audioSouruce2->Play();
		}
		else
		{
			gameObject->transform->Find(S("TextField"))->transform->set_position(ScreenControler::roundToNearestFullPixel3(gameObject->transform->Find(S("TextField"))->transform->get_position()));
			P<TimelineAction> timelineAction = New<TimelineAction>();
			timelineAction = New<TimelineAction>();
			timelineAction->textfield = gameObject->transform->Find(S("TextField"))->GetComponent<TextFieldController>();
			timelineAction->textColor = Vector3(1.0f, 0.0f, 0.0f);
			timelineAction->backgroundColor = Vector3(0.5f, 0.0f, 0.0f);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("moon_power_failure_2"));
			timelineAction->actionWithText = true;
			timelineAction->function = [this](String s) { failsound(s); };
			Timeline::t->addAction(timelineAction);
		}
	}
	else
	{
		PlayerController::pc->forceAnimation(S("stop"));
		PlayerController::pc->setBusy(true);
		PlayerController::pc->spawnName = S("david_pod");
		Timeline::t->doNotUnlock = true;
		GameDataController::gd->setObjective(S("moon_david_sleeps"), true);
		CurtainController::cc->fadeOut(S("LocationMoonbase3"), WalkController::Direction::NW, S("stand_ne"), nullptr, true);
	}
}

void Moonbase3Pod::openIfNeeded(bool close)
{
	String text = S("open");
	if (close)
	{
		text = S("close");
	}
	if (whose == S("david"))
	{
		GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_") + text);
	}
	else if (whose == S("cate"))
	{
		if (GameDataController::gd->getObjective(S("npc1_alive")))
		{
			GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_") + text);
		}
	}
	else if (whose == S("barry"))
	{
		if (GameDataController::gd->getObjective(S("npc2_alive")))
		{
			GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_") + text);
		}
	}
	else if (whose == S("cody") && GameDataController::gd->getObjective(S("npc3_alive")))
	{
		GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_") + text);
	}
}

void Moonbase3Pod::updateState()
{
	if (GameDataController::gd->getObjective(S("moon_pods_unlocked")))
	{
		objectName = S("moonbase_pod_empty");
		if (whose == S("david"))
		{
			if (GameDataController::gd->getObjective(S("moon_david_sleeps")))
			{
				objectName = S("moonbase_pod_david");
				if (GameDataController::gd->getObjectiveDetail(S("moon_david_sleeps")) == 1)
				{
					GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_closed"));
				}
				else
				{
					GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_opened"));
				}
				person->GetComponent<SpriteRenderer>()->set_enabled(true);
			}
			else
			{
				GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_opened"));
				person->GetComponent<SpriteRenderer>()->set_enabled(false);
			}
		}
		else if (whose == S("cate"))
		{
			if (GameDataController::gd->getObjective(S("npc1_alive")))
			{
				if (GameDataController::gd->getObjective(S("moon_cate_sleeps")))
				{
					objectName = S("moonbase_pod_cate");
					if (GameDataController::gd->getObjectiveDetail(S("moon_cate_sleeps")) == 1)
					{
						GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_closed"));
					}
					else
					{
						GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_opened"));
					}
					person->GetComponent<SpriteRenderer>()->set_enabled(true);
				}
				else
				{
					GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_opened"));
					person->GetComponent<SpriteRenderer>()->set_enabled(false);
				}
			}
			else
			{
				GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_closed"));
				person->GetComponent<SpriteRenderer>()->set_enabled(false);
			}
		}
		else if (whose == S("barry"))
		{
			if (GameDataController::gd->getObjective(S("npc2_alive")))
			{
				if (GameDataController::gd->getObjective(S("moon_barry_sleeps")))
				{
					objectName = S("moonbase_pod_barry");
					if (GameDataController::gd->getObjectiveDetail(S("moon_barry_sleeps")) == 1)
					{
						GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_closed"));
					}
					else
					{
						GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_opened"));
					}
					person->GetComponent<SpriteRenderer>()->set_enabled(true);
				}
				else
				{
					GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_opened"));
					person->GetComponent<SpriteRenderer>()->set_enabled(false);
				}
			}
			else
			{
				GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_closed"));
				person->GetComponent<SpriteRenderer>()->set_enabled(false);
			}
		}
		else
		{
			if (!(whose == S("cody")))
			{
				return;
			}
			if (GameDataController::gd->getObjective(S("npc3_alive")))
			{
				if (GameDataController::gd->getObjective(S("moon_cody_sleeps")))
				{
					objectName = S("moonbase_pod_cody");
					if (GameDataController::gd->getObjectiveDetail(S("moon_cody_sleeps")) == 1)
					{
						GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_closed"));
					}
					else
					{
						GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_opened"));
					}
					person->GetComponent<SpriteRenderer>()->set_enabled(true);
				}
				else
				{
					GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_opened"));
					person->GetComponent<SpriteRenderer>()->set_enabled(false);
				}
			}
			else
			{
				GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_closed"));
				person->GetComponent<SpriteRenderer>()->set_enabled(false);
			}
		}
	}
	else
	{
		objectName = S("moonbase_pod_empty");
		GetComponent<Animator>()->Play(S("moon_pod") + numerek + S("_closed"));
		person->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void Moonbase3Pod::clickAction2()
{
}

void Moonbase3Pod::clickAction0()
{
}

void Moonbase3Pod::whatOnClick0()
{
}

void Moonbase3Pod::whatOnClick()
{
}
