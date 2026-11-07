#include "../game_all.h"

void CurtainController::Awake()
{
	if (cc == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		cc = this;
		MonoBehaviour::print(S("Curtain controler initialized"));
	}
	else if (cc != P<CurtainController>(this))
	{
		Object::Destroy(gameObject);
	}
}

void CurtainController::Start()
{
	sr = gameObject->GetComponent<SpriteRenderer>();
	targetLocaiton = String::Empty;
	transform->set_position(Vector3(0.0f, 0.0f, -8.0f));
	fadeIn();
}

float CurtainController::getAlpha()
{
	return alpha;
}

bool CurtainController::okToGo()
{
	if (alpha < 0.5f && targetAlpha <= 0.0f)
	{
		return true;
	}
	return false;
}

void CurtainController::loadAfterWhile()
{
	GameDataController::gd->tryLoad(nextSceneStartAnimation, true);
	nextSceneStartAnimation = nullptr;
}

void CurtainController::updatePreviousLocation()
{
	String text = SceneManager::GetActiveScene().get_name();
	if (text != S("PauseMenu") && text != S("SaveMenu") && text != S("LoadMenu"))
	{
		GameDataController::gd->previousLocation = text;
	}
}

void CurtainController::Update()
{
	if (Mathf::Abs(alpha - targetAlpha) <= speed && alpha != targetAlpha)
	{
		alpha = targetAlpha;
	}
	else if (alpha == targetAlpha)
	{
		if (targetLocaiton == S("LOAD"))
		{
			targetLocaiton = String::Empty;
			Invoke(S("loadAfterWhile"), 0.1f);
		}
		else if (targetLocaiton != String::Empty)
		{
			if (targetLocaiton.Equals(S("none")))
			{
				Array<P<ObjectActionController>> array = Object::FindObjectsOfType<ObjectActionController>();
				array[0].cast<ObjectActionController>()->updateAll();
				fadeIn();
			}
			else
			{
				P<TextFieldController> component = GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>();
				component->transform->set_parent(nullptr);
				updatePreviousLocation();
				loadScene(targetLocaiton);
			}
		}
	}
	if (delayer > 0)
	{
		delayer--;
	}
	else
	{
		if (alpha > targetAlpha)
		{
			alpha -= speed * Time::get_deltaTime() * 60.0f;
		}
		if (alpha < targetAlpha)
		{
			alpha += speed * Time::get_deltaTime() * 60.0f;
		}
		timeout += Time::get_deltaTime();
		if (timeout > 7.0f)
		{
			alpha = targetAlpha;
			timeout = 0.0f;
		}
	}
	sr->set_color(Color(0.0f, 0.0f, 0.0f, alpha));
}

void CurtainController::loadScene(String name)
{
	targetLocaiton = name;
	SceneManager::LoadScene(targetLocaiton);
	targetLocaiton = String::Empty;
}

void CurtainController::OnLevelWasLoaded(int level)
{
	if (P<CurtainController>(this) == cc)
	{
		currentLocationManager = nullptr;
		MonoBehaviour::print(S("ON LEVEL WAS LOADED"));
		if (onSceneChange == nullptr && nextSceneStartAnimation == nullptr)
		{
			PlayerController::pc->setBusy(false);
		}
		PlayerController::wc->fullStop();
		PlayerController::wc->dir = targetWalkDir;
		fadeIn();
	}
}

void CurtainController::fadeOut(String target, WalkController_Direction targetDir, String animation, P<AudioClip> sound, bool flipX, CurtainController_Delegate actionAfterFade, float tSpeed)
{
	timeout = 0.0f;
	if (target == S("LocationMap"))
	{
		GameDataController::gd->autoSave();
	}
	speed = tSpeed;
	PlayerController::pc->setBusy(true);
	targetAlpha = 1.0f;
	onSceneChange = actionAfterFade;
	targetLocaiton = target;
	nextSceneStartAnimation = animation;
	nextSceneStartAnimatioFlip = flipX;
	nextSceneStartSound = sound;
	targetWalkDir = PlayerController::wc->dir;
	if (!(targetDir == WalkController::Direction::NULL_))
	{
		targetWalkDir = targetDir;
	}
	PlayerController::pc->setBusy(true);
}

void CurtainController::fixCameraRect()
{
	float num = 1.7777778f;
	float num2 = (float)Screen::get_width() / (float)Screen::get_height();
	float num3 = num2 / num;
	P<Camera> component = GameObject::Find(S("Main Camera"))->GetComponent<Camera>();
	P<GameObject> gameObject = GameObject::Find(S("Main Camera(Clone)"));
	P<Camera> camera = nullptr;
	if ((bool)gameObject)
	{
		camera = gameObject->GetComponent<Camera>();
	}
	if (num3 < 1.0f)
	{
		Rect rect = component->get_rect();
		rect.width = 1.0f;
		rect.height = num3;
		rect.x = 0.0f;
		rect.y = (1.0f - num3) / 2.0f;
		component->set_rect(rect);
		if ((bool)camera)
		{
			camera->set_rect(rect);
		}
		ScreenControler::ratioHeight = rect.height;
		ScreenControler::ratioWidth = rect.width;
		ScreenControler::shiftRatioX = rect.x * (float)Screen::get_width();
		ScreenControler::shiftRatioY = rect.y * (float)Screen::get_height();
		ScreenControler::shiftX = rect.x;
		ScreenControler::shiftY = rect.y;
		return;
	}
	float num4 = 1.0f / num3;
	Rect rect2 = component->get_rect();
	rect2.width = num4;
	rect2.height = 1.0f;
	rect2.x = (1.0f - num4) / 2.0f;
	rect2.y = 0.0f;
	component->set_rect(rect2);
	if ((bool)camera)
	{
		camera->set_rect(rect2);
	}
	ScreenControler::ratioHeight = rect2.height;
	ScreenControler::ratioWidth = rect2.width;
	ScreenControler::shiftRatioX = rect2.x * (float)Screen::get_width();
	ScreenControler::shiftRatioY = rect2.y * (float)Screen::get_height();
	ScreenControler::shiftX = rect2.x;
	ScreenControler::shiftY = rect2.y;
}

void CurtainController::fadeIn()
{
	InventoryButtonController::ibc->CancelInvoke();
	fixCameraRect();
	if (onSceneChange != nullptr)
	{
		onSceneChange();
	}
	PlayerController::pc->npcShouldAppearRightOnSpot = false;
	if (PlayerController::pc != nullptr && !targetLocaiton.Equals(S("none")) && !PlayerController::pc->spawnName.Equals(String::Empty))
	{
		delayer = 0;
		if (currentLocationManager == nullptr)
		{
			currentLocationManager = GameObject::Find(S("Location"))->GetComponent<LocationManager>();
		}
		if (!PlayerController::pc->spawnName.Equals(S("previous")) && !PlayerController::pc->spawnName.Equals(S("InfoExit")))
		{
			GameDataController::gd->usedSpawner = PlayerController::pc->spawnName;
		}
		MonoBehaviour::print(S("Placing player in ") + PlayerController::pc->spawnName);
		if (!PlayerController::pc->spawnName.Equals(S("previous")))
		{
			Vector2 vector = ScreenControler::roundToNearestFullPixel(GameObject::Find(PlayerController::pc->spawnName)->transform->Find(S("LocationTransitioner"))->transform->get_position());
			PlayerController::wc->shadow->clearLastFrame();
			PlayerController::wc->currentXY.x = vector.x;
			PlayerController::wc->currentXY.y = vector.y;
			PlayerController::wc->clearTarget();
			MonoBehaviour::print(S("SPAWNING PLAYER at ") + PlayerController::wc->currentXY.ToString() + S(" (") + GameObject::Find(PlayerController::pc->spawnName)->transform->Find(S("LocationTransitioner"))->transform->get_position().ToString() + S(" "));
		}
		else
		{
			PlayerController::pc->npcShouldAppearRightOnSpot = true;
			MonoBehaviour::print(S("which is  ") + GameDataController::gd->previousX + S(" ") + GameDataController::gd->previousY);
			PlayerController::wc->currentXY.x = GameDataController::gd->previousX;
			PlayerController::wc->currentXY.y = GameDataController::gd->previousY;
			PlayerController::wc->clearTarget();
		}
	}
	else
	{
		delayer = 30;
		if (SceneManager::GetActiveScene().get_name() != S("MainMenu") && SceneManager::GetActiveScene().get_name() != S("FontSelector") && SceneManager::GetActiveScene().get_name() != S("LoadingScene"))
		{
			for (int i = 0; i < ItemsManager::im->items.Count(); i++)
			{
				if (!ItemsManager::im->items[i]->dataRef->droppedLocation.Equals(SceneManager::GetActiveScene().get_name()))
				{
					continue;
				}
				Array<P<GroundItemController>> array = Object::FindObjectsOfType<GroundItemController>();
				if (array == nullptr)
				{
					continue;
				}
				for (int j = 0; j < array.Length(); j++)
				{
					if (array[j]->itemRef->dataRef->id == ItemsManager::im->items[i]->dataRef->id)
					{
						Vector2 vector2 = ScreenControler::gameToScreen(Vector2(ItemsManager::im->items[i]->dataRef->locX, ItemsManager::im->items[i]->dataRef->locY));
						Vector3 vector3 = Vector3(vector2.x, vector2.y, 0.0f);
						vector3 = Camera::get_main()->ScreenToWorldPoint(vector2);
						array[j]->gameObject->transform->set_position(vector3);
					}
				}
			}
		}
		if (GameObject::Find(S("dusk")) != nullptr)
		{
			GameObject::Find(S("dusk"))->GetComponent<DuskController>()->manualUpdate();
		}
	}
	alpha = 1.0f;
	targetAlpha = 0.0f;
	targetLocaiton = String::Empty;
	if (nextSceneStartAnimation != nullptr)
	{
		PlayerController::wc->forceAnimation(nextSceneStartAnimation, nextSceneStartAnimatioFlip);
		PlayerController::pc->gameObject->GetComponent<Animator>()->set_enabled(true);
		nextSceneStartAnimation = nullptr;
	}
	else
	{
		PlayerController::pc->setBusy(false);
	}
	if (nextSceneStartSound != nullptr)
	{
		PlayerController::pc->aS->PlayOneShot(nextSceneStartSound);
	}
	PlayerController::wc->shadow->clearLastFrame();
}
