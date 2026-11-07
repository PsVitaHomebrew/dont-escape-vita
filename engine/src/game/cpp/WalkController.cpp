#include "../game_all.h"

Vector2 WalkController::getFinalTarget()
{
	if (path != nullptr && path.Count() > 0)
	{
		return path[path.Count() - 1];
	}
	return Vector2();
}

void WalkController::Start()
{
	Camera::get_main()->set_orthographicSize(0.625f);
	path = List<Vector2>::New();
	targetXY = Vector2(currentXY.x, currentXY.y);
	currentXY_screen_rounded = Vector3(0.0f, 0.0f, 0.0f);
	currentSpeed = Vector2(0.0f, 0.0f);
	shadow = New<SpriteShadow>(gameObject);
	shadow->startAlpha = 0.5f;
	shadow->fadeRateV = 0.009f;
	shadow->fadeRateH = 0.004f;
	shadowOffsetY = 0;
	animator = gameObject->GetComponent<Animator>();
	dustPart = gameObject->GetComponent<ParticleGenerator>();
	sr = gameObject->GetComponent<SpriteRenderer>();
}

void WalkController::setTextFieldY(int y)
{
	PlayerController::pc->textField->shift.y = (float)y;
}

String WalkController::getCurrentAnimClip()
{
	return currentAnimClip;
}

void WalkController::setCurrentAnimClip(String anim)
{
	currentAnimClip = anim;
}

void WalkController::setTarget(List<Vector2> newTarget)
{
	path = List<Vector2>::New();
	if (newTarget != nullptr)
	{
		while (newTarget.Count() > 0)
		{
			path.Add(newTarget[0]);
			newTarget.RemoveAt(0);
		}
	}
	if (path.Count() > 1)
	{
		path.RemoveAt(0);
	}
	currentXY.x = Mathf::Round(currentXY.x);
	currentXY.y = Mathf::Round(currentXY.y);
	range = 1;
	waitedOneFrameBeforeAction = false;
}

void WalkController::setSimpleTargetV3(Vector3 targetPosition)
{
	setSimpleTarget(ScreenControler::roundToNearestFullPixel(targetPosition));
}

void WalkController::setSimpleTarget(Vector2 newTarget)
{
	path = List<Vector2>::New();
	targetXY = Vector2();
	targetXY.x = newTarget.x;
	targetXY.y = newTarget.y;
	currentXY.x = Mathf::Round(currentXY.x);
	currentXY.y = Mathf::Round(currentXY.y);
	range = 1;
	waitedOneFrameBeforeAction = false;
}

void WalkController::clearTarget()
{
	path = List<Vector2>::New();
	currentXY.x = Mathf::Round(currentXY.x);
	currentXY.y = Mathf::Round(currentXY.y);
	targetXY.x = currentXY.x;
	targetXY.y = currentXY.y;
	range = 1;
	waitedOneFrameBeforeAction = false;
}

void WalkController::animationStartAction()
{
	if (onFinishWalking != nullptr)
	{
		Timeline::t->stopChitChat();
		speedMultip = 1.0f;
		onFinishWalking->clickAction0();
	}
}

void WalkController::animationAction()
{
	if (onFinishWalking != nullptr)
	{
		Timeline::t->stopChitChat();
		speedMultip = 1.0f;
		P<GameObject> gameObject = GameObject::Find(S("BottomText"));
		if (gameObject != nullptr)
		{
			gameObject->GetComponent<TextFieldController>()->dissmiss(true);
		}
		onFinishWalking->clickAction();
	}
	onFinishWalking = nullptr;
}

void WalkController::otherAnimationAction()
{
	if (onFinishWalking2 != nullptr)
	{
		Timeline::t->stopChitChat();
		speedMultip = 1.0f;
		onFinishWalking2->clickAction2();
	}
	onFinishWalking2 = nullptr;
}

void WalkController::animationEnd()
{
	PlayerController::pc->setBusy(false);
	shadowOffsetY = 0;
	if (shadow->scaleFactor >= 0.75f)
	{
		shadowOffsetY = 0;
	}
	else if (shadow->scaleFactor >= 0.65f)
	{
		shadowOffsetY = -1;
	}
	else if (shadow->scaleFactor >= 0.55f)
	{
		shadowOffsetY = -2;
	}
	else if (shadow->scaleFactor >= 0.45f)
	{
		shadowOffsetY = -3;
	}
	else if (shadow->scaleFactor >= 0.35f)
	{
		shadowOffsetY = -4;
	}
	else if (shadow->scaleFactor >= 0.25f)
	{
		shadowOffsetY = -5;
	}
	else if (shadow->scaleFactor >= 0.15f)
	{
		shadowOffsetY = -6;
	}
	else
	{
		shadowOffsetY = -7;
	}
	if (currentAnimClip == S("suit_action_stnd_n") || currentAnimClip == S("action_stnd_n") || currentAnimClip == S("kneel_n"))
	{
		dir = Direction::N;
		MonoBehaviour::print(S("stand_n"));
		if (!suit)
		{
			gameObject->GetComponent<Animator>()->Play(S("stand_n"), 0);
		}
		else
		{
			gameObject->GetComponent<Animator>()->Play(S("suit_stand_n"), 0);
		}
	}
	if (currentAnimClip == S("suit_action_stnd_ne") || currentAnimClip == S("action_stnd_ne") || currentAnimClip == S("kneel_ne"))
	{
		dir = Direction::NE;
		MonoBehaviour::print(S("stand_ne"));
		if (sr->get_flipX())
		{
			dir = Direction::NW;
		}
		if (!suit)
		{
			gameObject->GetComponent<Animator>()->Play(S("stand_ne"), 0);
		}
		else
		{
			gameObject->GetComponent<Animator>()->Play(S("suit_stand_ne"), 0);
		}
	}
	if (currentAnimClip == S("suit_action_stnd_e") || currentAnimClip == S("action_stnd_e") || currentAnimClip == S("kneel_e"))
	{
		dir = Direction::E;
		MonoBehaviour::print(S("stand_e"));
		if (sr->get_flipX())
		{
			dir = Direction::W;
		}
		if (!suit)
		{
			gameObject->GetComponent<Animator>()->Play(S("stand_e"), 0);
		}
		else
		{
			gameObject->GetComponent<Animator>()->Play(S("suit_stand_e"), 0);
		}
	}
	if (currentAnimClip == S("suit_action_stnd_se") || currentAnimClip == S("action_stnd_se") || currentAnimClip == S("kneel_se"))
	{
		dir = Direction::SE;
		MonoBehaviour::print(S("stand_se"));
		if (sr->get_flipX())
		{
			dir = Direction::SW;
		}
		if (!suit)
		{
			gameObject->GetComponent<Animator>()->Play(S("stand_se"), 0);
		}
		else
		{
			gameObject->GetComponent<Animator>()->Play(S("suit_stand_se"), 0);
		}
		if (dir == Direction::SW)
		{
			sr->set_flipX(true);
		}
		else
		{
			sr->set_flipX(false);
		}
	}
	if (currentAnimClip == S("suit_action_stnd_s") || currentAnimClip == S("action_stnd_s") || currentAnimClip == S("kneel_s"))
	{
		dir = Direction::S_;
		MonoBehaviour::print(S("stand_s"));
		if (!suit)
		{
			animator->Play(S("stand_s"), 0);
		}
		else
		{
			animator->Play(S("suit_stand_s"), 0);
		}
	}
}

void WalkController::setShadowOffset(int off)
{
	shadowOffsetY = off;
}

void WalkController::forceAnimationForAnimationEvent(String name)
{
	forceAnimation(name);
}

void WalkController::forceAnimationForAnimationEventFlipped(String name)
{
	forceAnimation(name, true);
}

void WalkController::forceAnimation(String name, bool flip, bool useCurrentDir, bool makeBusy)
{
	currentAnimClip = S("none");
	if (useCurrentDir)
	{
		String text = String::Empty;
		if (dir == Direction::N)
		{
			text += S("n");
			flip = false;
		}
		else if (dir == Direction::NE)
		{
			text += S("ne");
			flip = false;
		}
		else if (dir == Direction::E)
		{
			text += S("e");
			flip = false;
		}
		else if (dir == Direction::SE)
		{
			text += S("se");
			flip = false;
		}
		else if (dir == Direction::S_)
		{
			text += S("s");
			flip = false;
		}
		else if (dir == Direction::SW)
		{
			text += S("se");
			flip = true;
		}
		else if (dir == Direction::W)
		{
			text += S("e");
			flip = true;
		}
		else if (dir == Direction::NW)
		{
			text += S("ne");
			flip = true;
		}
		name += text;
	}
	if (suit)
	{
		name = S("suit_") + name;
	}
	MonoBehaviour::print(S("FORCING ANIMATION ") + name);
	if (makeBusy)
	{
		PlayerController::pc->setBusy(true);
	}
	animator->Play(name, 0);
	sr->set_flipX(flip);
}

void WalkController::playSound(P<AudioClip> ac)
{
	PlayerController::pc->aS->PlayOneShot(ac);
}

void WalkController::Update()
{
	dustPart->started = false;
	float num = Time::get_deltaTime();
	if (num > 0.03f)
	{
		num = 0.03f;
	}
	if (CurtainController::cc->targetAlpha == 1.0f)
	{
		busy = true;
	}
	if (currentXY.y < 0.0f)
	{
		PlayerController::pc->aS->set_volume(1.0f + currentXY.y / 100.0f);
	}
	else
	{
		PlayerController::pc->aS->set_volume(1.0f);
	}
	if (currentXY.x < -5.0f)
	{
		PlayerController::pc->aS->set_panStereo(0.0f);
		SoundsManagerController::sm->auxASPlayer->set_panStereo(0.0f);
	}
	else
	{
		PlayerController::pc->aS->set_panStereo((0.0f - (120.0f - currentXY.x)) / 120.0f);
		SoundsManagerController::sm->auxASPlayer->set_panStereo((0.0f - (120.0f - currentXY.x)) / 120.0f);
	}
	currentSpeed.x = 0.0f;
	currentSpeed.y = 0.0f;
	if ((false || (targetXY.x == currentXY.x && targetXY.y == currentXY.y)) && path.Count() > 0)
	{
		targetXY = path[0];
		path.RemoveAt(0);
	}
	float num2 = 0.001f;
	if (Mathf::Abs(currentXY.x - targetXY.x) > speed * num * num2 * speedMultip || Mathf::Abs(currentXY.y - targetXY.y) > speed * num * num2 * speedMultip)
	{
		if (currentXY.x - speed * num * num2 * speedMultip >= targetXY.x)
		{
			currentSpeed.x = (0.0f - speed) * speedMultip;
		}
		if (currentXY.x + speed * num * num2 * speedMultip <= targetXY.x)
		{
			currentSpeed.x = speed * speedMultip;
		}
		if (currentXY.y - speed * num * num2 * speedMultip >= targetXY.y)
		{
			currentSpeed.y = (0.0f - speed) * speedMultip;
		}
		if (currentXY.y + speed * num * num2 * speedMultip <= targetXY.y)
		{
			currentSpeed.y = speed * speedMultip;
		}
		if (currentSpeed.x != 0.0f && currentSpeed.y != 0.0f)
		{
			currentSpeed.x /= 1.2f;
			currentSpeed.y /= 1.2f;
		}
	}
	if (currentSpeed.x == 0.0f)
	{
		currentXY.x = Mathf::Floor(currentXY.x);
		targetXY.x = currentXY.x;
	}
	if (currentSpeed.y == 0.0f)
	{
		currentXY.y = Mathf::Floor(currentXY.y);
		targetXY.y = currentXY.y;
	}
	if (currentSpeed.x == 0.0f && currentSpeed.y == 0.0f)
	{
		PlayerController::wc->speedMultip = 1.0f;
	}
	if (autoAction != nullptr || !busy || (letOneMoreAnimationBeforeBusy > 0 && currentAnimClip.IndexOf(S("stand")) != -1))
	{
		String text = S("stand_s");
		if (suit)
		{
			text = S("suit_") + text;
		}
		bool flipX = sr->get_flipX();
		if (letOneMoreAnimationBeforeBusy > 0)
		{
			letOneMoreAnimationBeforeBusy--;
		}
		if (currentSpeed.x == 0.0f && currentSpeed.y > 0.0f)
		{
			dir = Direction::N;
		}
		else if (currentSpeed.x > 0.0f && currentSpeed.y > 0.0f)
		{
			dir = Direction::NE;
		}
		else if (currentSpeed.x > 0.0f && currentSpeed.y == 0.0f)
		{
			dir = Direction::E;
		}
		else if (currentSpeed.x > 0.0f && currentSpeed.y < 0.0f)
		{
			dir = Direction::SE;
		}
		else if (currentSpeed.x == 0.0f && currentSpeed.y < 0.0f)
		{
			dir = Direction::S_;
		}
		else if (currentSpeed.x < 0.0f && currentSpeed.y < 0.0f)
		{
			dir = Direction::SW;
		}
		else if (currentSpeed.x < 0.0f && currentSpeed.y == 0.0f)
		{
			dir = Direction::W;
		}
		else if (currentSpeed.x < 0.0f && currentSpeed.y > 0.0f)
		{
			dir = Direction::NW;
		}
		if ((dir == Direction::N && (previousDir == Direction::NE || previousDir == Direction::NW)) || (dir == Direction::NE && (previousDir == Direction::N || previousDir == Direction::E)) || (dir == Direction::E && (previousDir == Direction::NE || previousDir == Direction::SE)) || (dir == Direction::SE && (previousDir == Direction::E || previousDir == Direction::S_)) || (dir == Direction::S_ && (previousDir == Direction::SE || previousDir == Direction::SW)) || (dir == Direction::SW && (previousDir == Direction::W || previousDir == Direction::S_)) || (dir == Direction::W && (previousDir == Direction::NW || previousDir == Direction::SW)) || (dir == Direction::NW && (previousDir == Direction::N || previousDir == Direction::W)))
		{
			if (dirChangeDelay >= 10)
			{
				dirChangeDelay = 0;
			}
			else
			{
				dir = previousDir;
			}
		}
		if (dirChangeDelay < 15)
		{
			dirChangeDelay++;
		}
		if (dir != previousDir)
		{
			dirChangeDelay = 0;
		}
		previousDir = dir;
		dustPart->started = false;
		if ((currentSpeed.x != 0.0f || currentSpeed.y != 0.0f) && waitOneFrameBeforeWalking)
		{
			text = S("walk_");
			if (suit)
			{
				text = S("suit_") + text;
			}
			walkedBefore = true;
			if (speed != MAX_SPEED)
			{
				speedMultip = 1.0f;
			}
			if (speedMultip > 1.0f && speed == MAX_SPEED)
			{
				text = S("run_");
				dustPart->started = true;
			}
		}
		else if ((currentSpeed.x != 0.0f || currentSpeed.y != 0.0f) && !waitOneFrameBeforeWalking)
		{
			waitOneFrameBeforeWalking = true;
			text = S("stand_");
			if (suit)
			{
				text = S("suit_") + text;
			}
			if (dir == Direction::E)
			{
				dir = Direction::SE;
			}
			if (dir == Direction::W)
			{
				dir = Direction::SW;
			}
		}
		else if (walkedBefore)
		{
			walkedBefore = false;
			text = S("stand_");
			if (suit)
			{
				text = S("suit_") + text;
			}
			if (dir == Direction::E)
			{
				dir = Direction::SE;
			}
			if (dir == Direction::W)
			{
				dir = Direction::SW;
			}
		}
		else
		{
			waitOneFrameBeforeWalking = false;
			walkedBefore = false;
			text = S("stand_");
			if (suit)
			{
				text = S("suit_") + text;
			}
			if (dir == Direction::E)
			{
				dir = Direction::SE;
			}
			if (dir == Direction::W)
			{
				dir = Direction::SW;
			}
		}
		String text2 = String::Empty;
		if (dir == Direction::N)
		{
			text2 += S("n");
			flipX = false;
		}
		else if (dir == Direction::NE)
		{
			text2 += S("ne");
			flipX = false;
		}
		else if (dir == Direction::E)
		{
			text2 += S("e");
			flipX = false;
		}
		else if (dir == Direction::SE)
		{
			text2 += S("se");
			flipX = false;
		}
		else if (dir == Direction::S_)
		{
			text2 += S("s");
			flipX = false;
		}
		else if (dir == Direction::SW)
		{
			text2 += S("se");
			flipX = true;
		}
		else if (dir == Direction::W)
		{
			text2 += S("e");
			flipX = true;
		}
		else if (dir == Direction::NW)
		{
			text2 += S("ne");
			flipX = true;
		}
		text += text2;
		if (path != nullptr && ((path.Count() > 0 && LocationManager::dist(currentXY, path[path.Count() - 1]) < (float)range) || (path.Count() == 0 && LocationManager::dist(currentXY, targetXY) < (float)range)))
		{
			path = List<Vector2>::New();
			fullStop();
			text = S("stand_") + text2;
			if (suit)
			{
				text = S("suit_") + text;
			}
		}
		if (path.Count() == 0 && currentSpeed.x == 0.0f && currentSpeed.y == 0.0f && targetXY.x == currentXY.x && targetXY.y == currentXY.y && (((onFinishWalking != nullptr || onFinishWalking0 != nullptr) && !busy) || autoAction != nullptr))
		{
			if (!waitedOneFrameBeforeAction)
			{
				letOneMoreAnimationBeforeBusy = 1;
				waitedOneFrameBeforeAction = true;
			}
			else if (onFinishWalking0 != nullptr)
			{
				onFinishWalking0->clickAction0();
				onFinishWalking0 = nullptr;
			}
			else if (onFinishWalking != nullptr)
			{
				MonoBehaviour::print(S("COMMENCING ACTION!"));
				busy = true;
				if (!onFinishWalking->characterAnimationName.Equals(String::Empty) && !onFinishWalking->characterAnimationName.Equals(S("stop")))
				{
					String text3 = onFinishWalking->characterAnimationName;
					if (onFinishWalking->useCurrentDirection)
					{
						text3 += text2;
					}
					currentAnimClip = text3;
					MonoBehaviour::print(S("!Attempting to play: ") + text3);
					gameObject->GetComponent<Animator>()->Play(text3, 0);
					if (!onFinishWalking->useCurrentDirection)
					{
						flipX = onFinishWalking->animationFlip;
					}
				}
				else
				{
					if (!onFinishWalking->characterAnimationName.Equals(S("stop")))
					{
						animationEnd();
					}
					if (!onFinishWalking->useCurrentDirection)
					{
						flipX = onFinishWalking->animationFlip;
					}
					gameObject->GetComponent<Animator>()->set_enabled(false);
					currentAnimClip = S("none");
					onFinishWalking->clickAction();
					onFinishWalking = nullptr;
				}
			}
			else if (autoAction != nullptr)
			{
				fullStop();
				autoAction();
				autoAction = nullptr;
			}
		}
		if (currentAnimClip != text && speed * speedMultip > 0.01f && text != currentAnimClip && (!busy || letOneMoreAnimationBeforeBusy > 0))
		{
			gameObject->GetComponent<Animator>()->set_enabled(true);
			bool flag = false;
			if (currentAnimClip.IndexOf(S("walk")) == -1 || currentAnimClip.IndexOf(S("stand")) == -1)
			{
				flag = true;
			}
			currentAnimClip = text;
			float normalizedTime = gameObject->GetComponent<Animator>()->GetCurrentAnimatorStateInfo(0).get_normalizedTime();
			if (flag)
			{
				normalizedTime = 0.0f;
			}
			gameObject->GetComponent<Animator>()->Play(text, 0, normalizedTime);
		}
		sr->set_flipX(flipX);
	}
	float num3 = num * 10.0f;
	currentXY.x += currentSpeed.x * num3;
	currentXY.y += currentSpeed.y * num3;
	Vector2 vectorToChange = Vector2();
	float z = gameObject->transform->get_position().z;
	vectorToChange.x = currentXY.x;
	vectorToChange.y = currentXY.y + (float)offsetY;
	vectorToChange = ScreenControler::gameToScreen(vectorToChange);
	currentXY_screen_rounded = Vector3(vectorToChange.x, vectorToChange.y, gameObject->transform->get_position().z);
	Vector3 vector = Camera::get_main()->WorldToScreenPoint(gameObject->transform->get_position());
	currentXY_screen_rounded.z = vector.z;
	gameObject->transform->set_position(Camera::get_main()->ScreenToWorldPoint(currentXY_screen_rounded));
	gameObject->transform->set_position(Vector3(gameObject->transform->get_position().x, gameObject->transform->get_position().y, z));
	if (Mathf::Abs(currentXY.x - targetXY.x) < 1.0f)
	{
		currentXY.x = targetXY.x;
	}
	if (Mathf::Abs(currentXY.y - targetXY.y) < 1.0f)
	{
		currentXY.y = targetXY.y;
	}
	shadow->update(currentXY_screen_rounded, currentXY, shadowOffsetY);
}

void WalkController::forceDirection(WalkController_Direction d)
{
	dir = d;
	previousDir = d;
	dirChangeDelay = 9999;
}

void WalkController::fullStop(bool abortTargetAction, bool playStandAnimation, bool forceStandAnimation)
{
	if (abortTargetAction)
	{
		MonoBehaviour::print(S("ABORTING ACTION"));
		onFinishWalking = nullptr;
		onFinishWalking0 = nullptr;
		onFinishWalking2 = nullptr;
	}
	currentSpeed.x = 0.0f;
	currentXY.x = Mathf::Floor(currentXY.x);
	targetXY.x = currentXY.x;
	currentSpeed.y = 0.0f;
	currentXY.y = Mathf::Floor(currentXY.y);
	targetXY.y = currentXY.y;
	if (forceStandAnimation || ((currentAnimClip.IndexOf(S("walk_")) != -1 || currentAnimClip.IndexOf(S("run_")) != -1) && playStandAnimation))
	{
		forceAnimation(S("stand_"), false, true, false);
	}
	path = List<Vector2>::New();
}

void WalkController::playIdleAnimation(String animationName)
{
	float num = 0.0f;
	float num2 = 0.0f;
	float num3 = 0.0f;
	float num4 = 0.0f;
	if (animationName == S("stand_se"))
	{
		num = 3.0f;
		num2 = 8.0f;
		num3 = 14.0f;
	}
	float num5 = Random::Range(0.0f, 1.0f);
	num4 = ((num5 > 0.82f) ? num : ((num5 > 0.66f) ? num2 : ((!(num5 > 0.5f)) ? 0.0f : num3)));
	if (lastIdle == num4 || busy || PlayerController::pc->dialogue != PlayerController::DialogueState::NONE)
	{
		lastIdle = -1.0f;
		num4 = 0.0f;
	}
	else
	{
		lastIdle = num4;
	}
	if (!busy && !suit)
	{
		gameObject->GetComponent<Animator>()->Play(animationName, 0, num4 / gameObject->GetComponent<Animator>()->GetCurrentAnimatorStateInfo(0).get_length());
	}
	else if (suit)
	{
		gameObject->GetComponent<Animator>()->Play(S("suit_stand_se"));
	}
}
