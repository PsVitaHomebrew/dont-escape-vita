#include "../game_all.h"

void NPCWalkController::Start()
{
	path = List<Vector2>::New();
	Camera::get_main()->set_orthographicSize(0.625f);
	targetXY = Vector2(currentXY.x, currentXY.y);
	actionTargetXY = Vector2(currentXY.x, currentXY.y);
	currentXY_screen_rounded = Vector3(0.0f, 0.0f, 0.0f);
	currentSpeed = Vector2(0.0f, 0.0f);
	shadow = New<SpriteShadow>(gameObject);
	shadow->startAlpha = 0.5f;
	shadow->fadeRateV = 0.009f;
	shadow->fadeRateH = 0.004f;
	shadowOffsetY = 0;
	previousXY = Vector2();
	previous2XY = Vector2();
	spawned = false;
}

Vector2 NPCWalkController::getTargetXY()
{
	return targetXY;
}

void NPCWalkController::setFlipped(bool f)
{
	gameObject->GetComponent<SpriteRenderer>()->set_flipX(f);
}

bool NPCWalkController::flipped()
{
	return gameObject->GetComponent<SpriteRenderer>()->get_flipX();
}

String NPCWalkController::getCurrentAnimClip()
{
	return currentAnimClip;
}

void NPCWalkController::setTargetV3(Vector3 targetPosition)
{
	P<LocationManager> component = GameObject::Find(S("Location"))->GetComponent<LocationManager>();
	List<Vector2> list = component->Search2(component->findNearestClearNode(component->getNodeLocation(currentXY)), component->findNearestClearNode(component->getNodeLocation(ScreenControler::roundToNearestFullPixel(targetPosition))));
	list.Insert(0, currentXY);
	setTarget(list);
}

void NPCWalkController::setTarget(List<Vector2> newTarget)
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

void NPCWalkController::setTextFieldY(int y)
{
	if (textfield == nullptr)
	{
		textfield = gameObject->GetComponent<TextFieldController>();
	}
	textfield->shift.y = y;
}

void NPCWalkController::playSound(P<AudioClip> ac)
{
	gameObject->GetComponent<AudioSource>()->PlayOneShot(ac);
}

void NPCWalkController::setSimpleTargetV3(Vector3 newTarget)
{
	setSimpleTarget(ScreenControler::roundToNearestFullPixel(newTarget));
}

void NPCWalkController::setSimpleTarget(Vector2 newTarget)
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

void NPCWalkController::clearTarget()
{
	path = List<Vector2>::New();
	currentXY.x = Mathf::Round(currentXY.x);
	currentXY.y = Mathf::Round(currentXY.y);
	targetXY.x = currentXY.x;
	targetXY.y = currentXY.y;
	range = 1;
	waitedOneFrameBeforeAction = false;
}

void NPCWalkController::animationStartAction()
{
	if (onFinishWalking != nullptr)
	{
		onFinishWalking->clickAction0();
	}
}

void NPCWalkController::animationAction()
{
	if (onFinishWalking != nullptr)
	{
		onFinishWalking->clickAction();
	}
	onFinishWalking = nullptr;
}

void NPCWalkController::otherAnimationAction()
{
	if (onFinishWalking2 != nullptr)
	{
		onFinishWalking2->clickAction2();
	}
	onFinishWalking2 = nullptr;
}

void NPCWalkController::setBusy(bool b)
{
	busy = b;
}

void NPCWalkController::animationEnd()
{
	setBusy(false);
	shadowOffsetY = 0;
	if (currentAnimClip == S("action_stnd_n") || currentAnimClip == S("kneel_n"))
	{
		dir = Direction::N;
		gameObject->GetComponent<Animator>()->Play(S("stand_n"), 0);
	}
	if (currentAnimClip == S("action_stnd_ne") || currentAnimClip == S("kneel_ne"))
	{
		dir = Direction::NE;
		if (gameObject->GetComponent<SpriteRenderer>()->get_flipX())
		{
			dir = Direction::NW;
		}
		gameObject->GetComponent<Animator>()->Play(S("stand_ne"), 0);
	}
	if (currentAnimClip == S("action_stnd_e") || currentAnimClip == S("kneel_e"))
	{
		dir = Direction::E;
		if (gameObject->GetComponent<SpriteRenderer>()->get_flipX())
		{
			dir = Direction::W;
		}
		gameObject->GetComponent<Animator>()->Play(S("stand_e"), 0);
	}
	if (currentAnimClip == S("action_stnd_se") || currentAnimClip == S("kneel_se"))
	{
		dir = Direction::SE;
		if (gameObject->GetComponent<SpriteRenderer>()->get_flipX())
		{
			dir = Direction::SW;
		}
		gameObject->GetComponent<Animator>()->Play(S("stand_se"), 0);
		if (dir == Direction::SW)
		{
			gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
		}
		else
		{
			gameObject->GetComponent<SpriteRenderer>()->set_flipX(false);
		}
	}
	if (currentAnimClip == S("action_stnd_s") || currentAnimClip == S("kneel_s"))
	{
		dir = Direction::S_;
		gameObject->GetComponent<Animator>()->Play(S("stand_s"), 0);
	}
}

void NPCWalkController::setShadowOffset(int off)
{
	shadowOffsetY = off;
}

void NPCWalkController::forceAnimationForAnimationEvent(String name)
{
	forceAnimation(name, gameObject->GetComponent<SpriteRenderer>()->get_flipX());
}

void NPCWalkController::forceAnimationForAnimationEvent2(String name, bool flip)
{
	forceAnimation(name, flip);
}

void NPCWalkController::forceAnimation(String name, bool flip, bool useCurrentDir, bool makeBusy)
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
	if (makeBusy)
	{
		setBusy(true);
	}
	gameObject->GetComponent<Animator>()->Play(name, 0);
	gameObject->GetComponent<SpriteRenderer>()->set_flipX(flip);
}

void NPCWalkController::Update()
{
	if (currentXY.y < 0.0f)
	{
		PlayerController::pc->aS->set_volume(1.0f + currentXY.y / 100.0f);
	}
	else
	{
		PlayerController::pc->aS->set_volume(1.0f);
	}
	currentSpeed.x = 0.0f;
	currentSpeed.y = 0.0f;
	if ((false || (targetXY.x == currentXY.x && targetXY.y == currentXY.y)) && path.Count() > 0)
	{
		targetXY = path[0];
		path.RemoveAt(0);
	}
	float num = 0.001f;
	float num2 = Time::get_deltaTime();
	if (num2 > 0.03f)
	{
		num2 = 0.03f;
	}
	if (Mathf::Abs(currentXY.x - targetXY.x) > speed * num2 * num || Mathf::Abs(currentXY.y - targetXY.y) > speed * num2 * num)
	{
		if (currentXY.x - speed * num2 * num >= targetXY.x)
		{
			currentSpeed.x = 0.0f - speed;
		}
		if (currentXY.x + speed * num2 * num <= targetXY.x)
		{
			currentSpeed.x = speed;
		}
		if (currentXY.y - speed * num2 * num >= targetXY.y)
		{
			currentSpeed.y = 0.0f - speed;
		}
		if (currentXY.y + speed * num2 * num <= targetXY.y)
		{
			currentSpeed.y = speed;
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
	if (bc2d == nullptr)
	{
		bc2d = gameObject->GetComponent<BoxCollider2D>();
	}
	if (!clickable || currentSpeed.x != 0.0f || currentSpeed.y != 0.0f)
	{
		bc2d->set_enabled(false);
	}
	else if (spawned)
	{
		bc2d->set_enabled(true);
	}
	if (!busy)
	{
		String text = S("stand_s");
		bool flipX = gameObject->GetComponent<SpriteRenderer>()->get_flipX();
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
		if ((currentSpeed.x != 0.0f || currentSpeed.y != 0.0f) && waitOneFrameBeforeWalking)
		{
			text = S("walk_");
			walkedBefore = true;
		}
		else if ((currentSpeed.x != 0.0f || currentSpeed.y != 0.0f) && !waitOneFrameBeforeWalking)
		{
			waitOneFrameBeforeWalking = true;
			text = S("stand_");
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
			text = S("walk_");
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
		if (text == S("stand_"))
		{
			if (dir == Direction::N || dir == Direction::W || dir == Direction::SW || dir == Direction::NW)
			{
				dir = Direction::SW;
			}
			else
			{
				dir = Direction::SE;
			}
		}
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
		if (path != nullptr && path.Count() > 0 && LocationManager::dist(currentXY, path[path.Count() - 1]) < (float)range)
		{
			path = List<Vector2>::New();
			fullStop();
		}
		if (path.Count() == 0 && currentSpeed.x == 0.0f && currentSpeed.y == 0.0f && targetXY.x == currentXY.x && targetXY.y == currentXY.y && (onFinishWalking != nullptr || onFinishWalking0 != nullptr) && !busy)
		{
			if (!waitedOneFrameBeforeAction)
			{
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
		}
		if (currentAnimClip != text && speed > 0.01f && text != currentAnimClip && (!busy || letOneMoreAnimationBeforeBusy > 0))
		{
			gameObject->GetComponent<Animator>()->set_enabled(true);
			bool flag = false;
			if (currentAnimClip.IndexOf(S("walk")) == -1 || currentAnimClip.IndexOf(S("stand")) == -1)
			{
				flag = true;
			}
			currentAnimClip = text;
			float num3 = gameObject->GetComponent<Animator>()->GetCurrentAnimatorStateInfo(0).get_normalizedTime();
			if (flag)
			{
				num3 = 0.0f;
			}
			MonoBehaviour::print(S("Attempting to play: ") + text + S(" from ") + num3);
			gameObject->GetComponent<Animator>()->Play(text, 0, num3);
		}
		gameObject->GetComponent<SpriteRenderer>()->set_flipX(flipX);
	}
	float num4 = num2 * 10.0f;
	if (num4 > speed)
	{
		num4 = speed;
	}
	currentXY.x += currentSpeed.x * num4;
	currentXY.y += currentSpeed.y * num4;
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
	shadow->update(currentXY_screen_rounded, currentXY, shadowOffsetY);
	if (Mathf::Abs(currentXY.x - targetXY.x) < 1.0f)
	{
		currentXY.x = targetXY.x;
	}
	if (Mathf::Abs(currentXY.y - targetXY.y) < 1.0f)
	{
		currentXY.y = targetXY.y;
	}
}

void NPCWalkController::updateStateAfterAnimation()
{
	gameObject->GetComponent<NPCActionController>()->updateState();
}

void NPCWalkController::setAnimationTargetXY(String coords)
{
	Array<String> array = coords.Split(u';');
	targetXY.x = int_Parse(array[0]);
	targetXY.y = int_Parse(array[1]);
}

void NPCWalkController::forceDirection(NPCWalkController_Direction d)
{
	dir = d;
	previousDir = d;
	dirChangeDelay = 9999;
}

void NPCWalkController::fullStop(bool abortTargetAction)
{
	MonoBehaviour::print(S("FULL STOP"));
	if (abortTargetAction)
	{
		MonoBehaviour::print(S("ABORTING ACTION"));
		onFinishWalking = nullptr;
	}
	currentSpeed.x = 0.0f;
	currentXY.x = Mathf::Floor(currentXY.x);
	targetXY.x = currentXY.x;
	currentSpeed.y = 0.0f;
	currentXY.y = Mathf::Floor(currentXY.y);
	targetXY.y = currentXY.y;
	previousXY.x = 9999.0f;
	previousXY.y = 9999.0f;
	previous2XY.x = 9999.0f;
	previous2XY.y = 9999.0f;
}

void NPCWalkController::playIdleAnimation(String animationName)
{
	float num = 0.0f;
	float num2 = 0.0f;
	float num3 = 0.0f;
	float num4 = 0.0f;
	if (animationName == S("barry_stand_se"))
	{
		num = 3.0f;
		num2 = 7.0f;
		num3 = 11.0f;
		animationName = S("stand_se");
	}
	else if (animationName == S("barry_mourn"))
	{
		num = 1.0f;
		num2 = 3.0f;
		num3 = 5.0f;
		animationName = S("npc2_mourn");
	}
	else if (animationName == S("cody_stand_se"))
	{
		num = 2.0f;
		num2 = 5.0f;
		num3 = 10.0f;
		animationName = S("stand_se");
	}
	else if (animationName == S("ginger_stand_se"))
	{
		gameObject->GetComponent<GingerActionController>()->randomLinesTalkOrNot();
		num = 2.0f;
		num2 = 12.0f;
		num3 = 0.0f;
		animationName = S("stand_se");
	}
	float num5 = Random::Range(0.0f, 1.0f);
	num4 = ((num5 > 0.75f) ? num : ((num5 > 0.5f) ? num2 : ((!(num5 > 0.25f)) ? 0.0f : num3)));
	if (lastIdle == num4 || PlayerController::pc->dialogue != PlayerController::DialogueState::NONE)
	{
		lastIdle = -1.0f;
		num4 = 0.0f;
	}
	else
	{
		lastIdle = num4;
	}
	gameObject->GetComponent<Animator>()->Play(animationName, 0, num4 / gameObject->GetComponent<Animator>()->GetCurrentAnimatorStateInfo(0).get_length());
}
