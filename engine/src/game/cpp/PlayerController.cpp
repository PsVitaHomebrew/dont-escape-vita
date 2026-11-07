#include "../game_all.h"

void PlayerController::Awake()
{
	if (pc == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		pc = this;
		wc = gameObject->GetComponent<WalkController>();
		ssg = gameObject->GetComponent<StepSoundGenerator>();
		MonoBehaviour::print(S("INITIALIZING PLAYER "));
	}
	else if (pc != P<PlayerController>(this))
	{
		Object::Destroy(gameObject);
	}
}

void PlayerController::Start()
{
	GameStrings::readStrings(PlayerPrefs::GetString(S("lang"), str(GameStrings::Language::EN)));
	npcShouldAppearRightOnSpot = false;
	textField = gameObject->GetComponent<TextFieldController>();
	textField->transform->set_parent(gameObject->transform);
	textField->container->transform->set_parent(pc->gameObject->transform);
	aS = gameObject->GetComponent<AudioSource>();
	currentLocationManager = nullptr;
	sr = GetComponent<SpriteRenderer>();
}

void PlayerController::say(String txt)
{
	textField->viewText(txt, true, false, false, 150);
}

void PlayerController::sayLine(String txt)
{
	P<TimelineAction> timelineAction = New<TimelineAction>();
	timelineAction->textfield = pc->textField;
	timelineAction->text = txt;
	timelineAction->actionWithText = false;
	Timeline::t->addAction(timelineAction);
}

void PlayerController::copySettingsToNPCs()
{
	Array<P<NPCWalkController>> array = Object::FindObjectsOfType<NPCWalkController>();
	for (int i = 0; i < array.Length(); i++)
	{
		array[i]->shadow->fadeRateV = wc->shadow->fadeRateV;
		array[i]->shadow->fadeRateH = wc->shadow->fadeRateH;
		array[i]->shadow->skewFactor = wc->shadow->skewFactor;
		array[i]->shadow->skewFactor2 = wc->shadow->skewFactor2;
		array[i]->shadow->startAlpha = wc->shadow->startAlpha;
		array[i]->shadow->source = wc->shadow->source;
		array[i]->shadow->scaleFactor = wc->shadow->scaleFactor;
		array[i]->shadowOffsetY = wc->shadowOffsetY;
		array[i]->shadow->downwards = wc->shadow->downwards;
		array[i]->gameObject->GetComponent<StepSoundGenerator>()->setStepType2(ssg->selectedStepsType, pc->GetComponent<AudioReverbFilter>()->get_reverbPreset());
	}
}

void PlayerController::setDialogue(P<GameObject> target)
{
	currentDialogue = target;
	dialogue = DialogueState::WAIT_TO_SPEED;
	setBusy(true);
}

void PlayerController::setBusy(bool busy)
{
	if ((busy || !QuestionController::qc->gameObject->get_activeSelf()) && ((!busy && Timeline::t->isSafeToChangeBusy() && !ExamineSprite::es->get_Active()) || busy))
	{
		if (!busy)
		{
			GameDataController::gd->saveIfOK(String::Empty);
		}
		gameObject->GetComponent<WalkController>()->busy = busy;
	}
}

void PlayerController::forceAnimation(String name)
{
	pc->setBusy(false);
	wc->shadowOffsetY = 0;
	wc->forceAnimation(name);
}

void PlayerController::haltSoftLockProbe()
{
	antiSoftLock = false;
}

void PlayerController::resumeSoftLockProbe()
{
	antiSoftLock = true;
}

void PlayerController::Update()
{
	if (antiSoftLock)
	{
		softlockTimer += Time::get_deltaTime();
		if (softlockTimer > 2.0f)
		{
			softlockTimer = 0.0f;
			if (wc->busy)
			{
				if (wc->currentXY.x >= 0.0f && wc->currentXY.x <= 240.0f && wc->currentXY.y >= 0.0f && wc->currentXY.y <= 135.0f)
				{
					Array<AnimatorClipInfo> currentAnimatorClipInfo = wc->animator->GetCurrentAnimatorClipInfo(0);
					if ((currentAnimatorClipInfo[0].get_clip()->get_name().IndexOf(S("stand")) != -1 || sr->get_sprite()->get_name().IndexOf(S("stand")) != -1) && dialogue == DialogueState::NONE && (Timeline::t->actions == nullptr || (Timeline::t->actions != nullptr && Timeline::t->actions.Count() == 0)) && CurtainController::cc->targetAlpha == CurtainController::cc->getAlpha() && DialogueController::dc->hidden && !ExamineSprite::es->get_Active() && (GameObject::Find(S("Ginger")) == nullptr || (GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->currentXY.x == GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->getTargetXY()
						.x && GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->currentXY.y == GameObject::Find(S("Ginger"))->GetComponent<NPCWalkController>()->getTargetXY()
						.y)) && (GameObject::Find(S("Npc2")) == nullptr || (GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->currentXY.x == GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->getTargetXY()
						.x && GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->currentXY.y == GameObject::Find(S("Npc2"))->GetComponent<NPCWalkController>()->getTargetXY()
						.y)) && (GameObject::Find(S("Npc3")) == nullptr || (GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->currentXY.x == GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->getTargetXY()
						.x && GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->currentXY.y == GameObject::Find(S("Npc3"))->GetComponent<NPCWalkController>()->getTargetXY()
						.y)))
					{
						if (softlockProbe == 0)
						{
							MonoBehaviour::print(S("Softlock| softlockProbe = 1"));
							softlockProbe = 1;
						}
						else
						{
							Debug::LogWarning(S("Softlock| PROBABLE SOFTLOCK DETECTED - SETTING BUSY TO FALSE"));
							softlockProbe = 0;
							setBusy(false);
						}
					}
				}
			}
			else
			{
				softlockProbe = 0;
			}
		}
	}
	Vector2 vectorToChange = Input::get_mousePosition();
	clickedAlreadyForSomething = false;
	if (!DialogueController::dc->hidden)
	{
		return;
	}
	if (Input::GetMouseButtonDown(0))
	{
		if (currentLocationManager == nullptr)
		{
			currentLocationManager = GameObject::Find(S("Location"))->GetComponent<LocationManager>();
			MonoBehaviour::print(S("LOADED LOCATION MANAGER: ") + str(currentLocationManager));
		}
		clickedAlreadyForSomething = true;
		if (dialogue == DialogueState::WAIT_TO_SPEED && !clickedSomething && CurtainController::cc->okToGo())
		{
			dialogue = DialogueState::WAIT_TO_DISMISS;
			currentDialogue->GetComponent<TextFieldController>()->speedUp();
			setBusy(true);
		}
		else if (dialogue == DialogueState::WAIT_TO_DISMISS && !clickedSomething && CurtainController::cc->okToGo())
		{
			dialogue = DialogueState::NONE;
			currentDialogue->GetComponent<TextFieldController>()->terminate();
			setBusy(false);
			GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->clearOverride();
		}
		else if (!clickedSomething && ExamineSprite::es->get_Active() && CurtainController::cc->okToGo())
		{
			ExamineSprite::es->hide();
			clickedSomething = true;
		}
		else if (!clickedSomething && !gameObject->GetComponent<WalkController>()->busy && CurtainController::cc->okToGo())
		{
			GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->deselectItem();
			InventoryButtonController::ibc->close();
			Vector2 vector = ScreenControler::roundToNearestFullPixelOld(ScreenControler::screenToGame(vectorToChange));
			wc->setTarget(currentLocationManager->Search2(currentLocationManager->getNodeLocation(wc->currentXY), currentLocationManager->findNearestClearNode(currentLocationManager->getNodeLocation(vector))));
			gameObject->GetComponent<WalkController>()->onFinishWalking = nullptr;
			gameObject->GetComponent<WalkController>()->onFinishWalking0 = nullptr;
			gameObject->GetComponent<WalkController>()->onFinishWalking2 = nullptr;
			if (wc->speedMultip > 1.0f || ((wc->currentSpeed.x != 0.0f || wc->currentSpeed.y != 0.0f) && ScreenControler::distance(vector, prevTargetClick) < 10.0f))
			{
				wc->speedMultip = 2.0f;
			}
			else
			{
				wc->speedMultip = 1.0f;
			}
			prevTargetClick = vector;
			runTimeout = 1.0f;
		}
		clickedSomething = false;
	}
	else if (runTimeout > 0.0f)
	{
		runTimeout -= Time::get_deltaTime();
		if (runTimeout <= 0.0f)
		{
			prevTargetClick = Vector2();
		}
	}
	if (Input::GetMouseButtonDown(1))
	{
		GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->deselectItem();
	}
}

void PlayerController::interruptDialogueProbablyToKillPlayer()
{
	pc->textField->dissmiss(true);
	pc->dialogue = DialogueState::NONE;
	GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->deselectItem();
	GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->clearOverride();
	InventoryButtonController::ibc->close();
}
