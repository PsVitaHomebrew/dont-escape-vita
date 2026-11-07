#include "../game_all.h"

void NPCActionController::Awake()
{
	interactions = List<P<ItemInteraction>>::New();
}

void NPCActionController::setFlippedL()
{
	gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
}

void NPCActionController::setFlippedR()
{
	gameObject->GetComponent<SpriteRenderer>()->set_flipX(false);
}

int NPCActionController::locationDialogue(int i, Vector3 color, String who)
{
	String text = String::Empty;
	String text2 = SceneManager::GetActiveScene().get_name();
	Vector3 color_b = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	if (GameDataController::gd->getObjective(S("barry_base_family")) && GameDataController::gd->getObjective(S("place_gas_station_barry")) && GameDataController::gd->getObjective(S("place_restaurant_barry")) && GameDataController::gd->getObjective(S("place_bhome_barry")) && GameDataController::gd->getObjective(S("place_road_barry")) && (GameDataController::gd->getObjective(S("place_bridge0_barry")) || GameDataController::gd->getObjective(S("place_bridge1_barry")) || GameDataController::gd->getObjective(S("place_bridge2_barry")) || GameDataController::gd->getObjective(S("place_bridge3_barry"))))
	{
		GameDataController::Achievement(S("S_TOUR"));
	}
	if (text2.IndexOf(S("Airplane")) != -1)
	{
		text = S("airplane");
	}
	if (text2.IndexOf(S("LocationBus")) != -1)
	{
		text = S("bus");
	}
	if (text2 == S("Location1") || text2 == S("Location2") || text2 == S("LocationAttic1") || text2 == S("LocationAttic2") || text2 == S("LocationBaseBathroom") || text2 == S("LocationBaseUpstairs"))
	{
		text = S("base");
	}
	if (text2 == S("LocationCrashsite1") || text2 == S("LocationCrossroad"))
	{
		text = S("road");
	}
	if (text2 == S("LocationBridge"))
	{
		text = S("bridge");
		text = (GameDataController::gd->getObjective(S("bridge_planks_used_2")) ? (text + S("2")) : ((!GameDataController::gd->getObjective(S("bridge_planks_used_1"))) ? (text + S("0")) : (text + S("1"))));
	}
	if (text2.IndexOf(S("LocationGasstation")) != -1)
	{
		text = S("gas_station");
	}
	if (text2.IndexOf(S("LocationRestaurant")) != -1)
	{
		text = S("restaurant");
	}
	if (text2.IndexOf(S("HuntersLodge")) != -1)
	{
		text = S("hunters");
	}
	if (text2.IndexOf(S("HuntersLodge")) != -1 && who == S("cody") && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2)
	{
		text = S("hunters2");
	}
	if (text2.IndexOf(S("LocationHouseB")) != -1)
	{
		text = S("bhome");
	}
	if (text2.IndexOf(S("SiderealOutside")) != -1)
	{
		text = S("sp_outside");
	}
	else if (text2.IndexOf(S("Sidereal")) != -1 && text2 != S("LocationSiderealRoof"))
	{
		text = S("sp_inside");
	}
	if (text2.IndexOf(S("LocationOutpostOutside")) != -1)
	{
		text = S("outpost1");
	}
	else if (text2.IndexOf(S("LocationOutpost")) != -1)
	{
		text = S("outpost2");
	}
	if (text2 == S("LocationRV"))
	{
		text = S("rv");
	}
	if (text2 == S("LocationRV2"))
	{
		text = S("rv2");
	}
	if (text2 == S("LocationCave"))
	{
		text = S("cave");
		if (who == S("cody"))
		{
			component = GameObject::Find(S("Echo"))->GetComponent<TextFieldController>();
			component->setAlpha(0.5f);
			color_b = color;
		}
	}
	if (text2 == S("MoonShip"))
	{
		text = S("moon0");
	}
	if (text2 == S("Moon1") || text2 == S("Moon2"))
	{
		text = S("moon1");
	}
	if (text2.IndexOf(S("LocationMoonbase")) != -1)
	{
		text = S("moon2");
	}
	if (text2 == S("CS1") && GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
	{
		text = S("construction2");
	}
	else
	{
		if (text2 == S("CS2") || text2 == S("CS3") || text2 == S("CS4") || text2 == S("CS5"))
		{
			text = S("construction1");
		}
	}
	if (text == String::Empty)
	{
		return i;
	}
	takeDoc(i);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("this_place"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/location")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(S("place_") + text + S("_") + who);
	DialogueController::dc->initDialogue(doc->lines, S("place_") + text + S("_") + who, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color_b, textField, color);
	i++;
	return i;
}

int NPCActionController::dayDialogue(int i, Vector3 color, String who)
{
	String text = S("d");
	text += str(GameDataController::gd->getCurrentDay());
	if (GameDataController::gd->getCurrentDay() > 4)
	{
		return i;
	}
	if (GameDataController::gd->getCurrentDay() < 2)
	{
		return i;
	}
	String text2 = String::Empty;
	if (GameDataController::gd->getCurrentDay() == 2)
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 0)
		{
			text2 = S("hot");
		}
		if (GameDataController::gd->getObjectiveDetail(S("day_2_threat")) == 1)
		{
			text2 = S("cold");
		}
	}
	if (GameDataController::gd->getCurrentDay() == 3)
	{
		if (GameDataController::gd->getObjective(S("dialogue_ginger_reunited")))
		{
			if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 0)
			{
				text2 = S("thugs");
			}
			if (GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1)
			{
				text2 = S("storm");
			}
		}
		else if (!GameDataController::gd->getObjective(S("sidereal_roof_collapsed")))
		{
			text2 = S("sidereal");
		}
	}
	if (GameDataController::gd->getCurrentDay() == 4)
	{
		text2 = S("ship");
	}
	if (text2 == String::Empty)
	{
		return i;
	}
	Vector3 color2 = GingerActionController::getColor();
	P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
	takeDoc(i);
	doc->caption = GameStrings::getString(GameStrings::dialogues, S("this_day"));
	doc->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Dialogues/day")));
	doc->lines = List<P<DialogueLine>>::New();
	doc->setObjective(text + S("_") + text2 + S("_") + who);
	DialogueController::dc->initDialogue(doc->lines, text + S("_") + text2 + S("_") + who, PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color2, textField, color);
	i++;
	return i;
}

void NPCActionController::decideRandomTopic()
{
	randomLines = List<P<DialogueLine>>::New();
	String text = String::Empty;
	if (SceneManager::GetActiveScene().get_name() == S("LocationSiderealRoof") && GameDataController::gd->getObjective(S("sidereal_roof_collapsed")) && GameDataController::gd->getObjective(S("sidereal_roof_wait_for_rescue")))
	{
		text = ((GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive"))) ? S("chitchat_help_barry_cody_01") : (((!GameDataController::gd->getObjective(S("npc3_joined")) || !GameDataController::gd->getObjective(S("npc3_alive"))) && GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive"))) ? S("chitchat_help_barry_01") : ((!GameDataController::gd->getObjective(S("npc3_joined")) || !GameDataController::gd->getObjective(S("npc3_alive")) || (GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")))) ? String::Empty : S("chitchat_help_cody_01"))));
	}
	else if (GameDataController::gd->getCurrentDay() < 5)
	{
		String text2 = S("chitchat");
		if (SceneManager::GetActiveScene().get_name() != S("LocationSiderealRoof") && (SceneManager::GetActiveScene().get_name() != S("LocationRestaurant5") || GameDataController::gd->getCurrentDay() > 2) && GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("barry_warned")) && !GameDataController::gd->getObjective(S("cody_warned")))
		{
			float num = Random::Range(0.0f, 1.0f);
			text2 = ((num < 0.2f) ? (text2 + S("_cate_cody")) : ((num < 0.4f) ? (text2 + S("_cate_barry")) : ((!(num < 0.6f)) ? (text2 + S("_cate_cody_barry")) : (text2 + S("_cate")))));
		}
		else if (SceneManager::GetActiveScene().get_name() != S("LocationSiderealRoof") && (SceneManager::GetActiveScene().get_name() != S("LocationRestaurant5") || GameDataController::gd->getCurrentDay() > 2) && GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("npc2_alive")))
		{
			float num2 = Random::Range(0.0f, 1.0f);
			text2 = ((num2 < 0.3f) ? (text2 + S("_cate_cody_deadbarry")) : ((!(num2 < 0.6f)) ? (text2 + S("_cate_cody")) : (text2 + S("_cate"))));
		}
		else if (SceneManager::GetActiveScene().get_name() != S("LocationSiderealRoof") && (SceneManager::GetActiveScene().get_name() != S("LocationRestaurant5") || GameDataController::gd->getCurrentDay() > 2) && GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc2_joined")) && !GameDataController::gd->getObjective(S("npc3_alive")) && GameDataController::gd->getObjective(S("npc2_alive")))
		{
			float num3 = Random::Range(0.0f, 1.0f);
			text2 = ((num3 < 0.3f) ? (text2 + S("_cate_barry_deadcody")) : ((!(num3 < 0.6f)) ? (text2 + S("_cate_barry")) : (text2 + S("_cate"))));
		}
		else if (SceneManager::GetActiveScene().get_name() != S("LocationSiderealRoof") && (SceneManager::GetActiveScene().get_name() != S("LocationRestaurant5") || GameDataController::gd->getCurrentDay() > 2) && GameDataController::gd->getObjective(S("npc3_joined")) && GameDataController::gd->getObjective(S("npc3_alive")) && !GameDataController::gd->getObjective(S("cody_warned")))
		{
			float num4 = Random::Range(0.0f, 1.0f);
			text2 = ((!(num4 < 0.5f)) ? (text2 + S("_cate_cody")) : (text2 + S("_cate")));
		}
		else if (SceneManager::GetActiveScene().get_name() != S("LocationSiderealRoof") && (SceneManager::GetActiveScene().get_name() != S("LocationRestaurant5") || GameDataController::gd->getCurrentDay() > 2) && GameDataController::gd->getObjective(S("npc2_joined")) && GameDataController::gd->getObjective(S("npc2_alive")) && !GameDataController::gd->getObjective(S("barry_warned")))
		{
			float num5 = Random::Range(0.0f, 1.0f);
			text2 = ((!(num5 < 0.5f)) ? (text2 + S("_cate_barry")) : (text2 + S("_cate")));
		}
		else
		{
			text2 += S("_cate");
		}
		String text3 = str(GameDataController::gd->getObjectiveDetail(text2)).Substring(0, 1);
		MonoBehaviour::print(S("WYBIERAM TEMAT..... ") + text2 + S(" ........... ") + text3);
		if (str(GameDataController::gd->getObjectiveDetail(text2)).Length() > 1)
		{
			String text4 = str(GameDataController::gd->getObjectiveDetail(text2)).Substring(1);
			text4 += text3;
			MonoBehaviour::print(S("NEW STRING TO ") + text4);
			GameDataController::gd->setObjectiveDetail(text2, int_Parse(text4));
		}
		text = text2 + text3;
		if (GameDataController::gd->getObjective(S("previous_disc_barry")) || GameDataController::gd->getObjective(S("previous_disc_cody")))
		{
			if (text == S("chitchat_cate_cody4"))
			{
				text = S("chitchat_2_cate_cody4");
			}
			if (text == S("chitchat_cate_cody_barry5"))
			{
				text = S("chitchat_2_cate_cody_barry5");
			}
			if (text == S("chitchat_cate_cody_barry4"))
			{
				text = S("chitchat_2_cate_cody_barry4");
			}
			if (text == S("chitchat_cate_cody1"))
			{
				text = S("chitchat_2_cate_cody1");
			}
		}
	}
	if (!(text == String::Empty))
	{
		DialogueController::dc->initDialogue(randomLines, text, GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>(), GingerActionController::getColor(), GameObject::Find(S("Npc2"))->GetComponent<TextFieldController>(), Npc2Controller::getColor(), GameObject::Find(S("Npc3"))->GetComponent<TextFieldController>(), Npc3Controller::getColor());
	}
}

void NPCActionController::randomLinesTalkOrNot(bool force)
{
	if (PlayerController::wc->busy || CursorController::cc->getCurrentState() == CursorController::PixelCursor::OK)
	{
		return;
	}
	if (!force && (SceneManager::GetActiveScene().get_name() == S("LocationSiderealRoof") || SceneManager::GetActiveScene().get_name() == S("LocationOutpostOutside2") || PlayerController::wc->busy || GameObject::Find(S("Ginger"))->GetComponent<NPCActionController>()->busyTalkingRandomly || GameObject::Find(S("Npc2"))->GetComponent<NPCActionController>()->busyTalkingRandomly || GameObject::Find(S("Npc3"))->GetComponent<NPCActionController>()->busyTalkingRandomly || !gameObject->GetComponent<NPCWalkController>()->spawned))
	{
		MonoBehaviour::print(S("RANDOM LINES force == false && busyTalkingRandomly"));
	}
	else
	{
		if (InventoryButtonController::ibc->isItOpen() || busyTalkingRandomly)
		{
			return;
		}
		randomLinesProbab = (float)GameDataController::gd->getObjectiveDetail(S("chitchat")) / 100.0f;
		GameDataController::gd->setObjectiveDetail(S("chitchat"), GameDataController::gd->getObjectiveDetail(S("chitchat")) + 2);
		MonoBehaviour::print(S("randomLinesProbab = ") + randomLinesProbab);
		if (busyTalkingRandomly || (!force && !(Random::Range(0.0f, 1.0f) <= randomLinesProbab)))
		{
			return;
		}
		GameDataController::gd->setObjectiveDetail(S("chitchat"), -25);
		busyTalkingRandomly = true;
		decideRandomTopic();
		MonoBehaviour::print(S("TALK  ") + randomLines.Count());
		if (randomLines != nullptr && randomLines.Count() > 0)
		{
			randomLines[randomLines.Count() - 1]->action = [this](String v) { makeNotBusy(v); };
			for (int i = 0; i < randomLines.Count(); i++)
			{
				randomLines[i]->time = Random::Range(0.1f, 1.5f);
				Timeline::t->addDialogue(randomLines[i], 1.0f + (float)randomLines[i]->text.Length() * 0.075f);
			}
		}
	}
}

void NPCActionController::makeNotBusy(String v)
{
	busyTalkingRandomly = false;
}

void NPCActionController::init(P<Item> item)
{
	updateState();
}

void NPCActionController::Update()
{
	if (needUpdate)
	{
		needUpdate = false;
		updateState();
	}
}

void NPCActionController::takeDoc(int i)
{
	doc = DialogueController::dc->dialogueOptions[i]->GetComponent<DialogueOptionController>();
}

void NPCActionController::OnEnable()
{
	needUpdate = true;
}

void NPCActionController::Start()
{
	textField = gameObject->GetComponent<TextFieldController>();
	colliderManager->setTarget(gameObject);
	dkvs = GameStrings::objects;
	animationFlip = false;
	characterAnimationName = S("action_stnd_");
	if (GameDataController::gd->getObjective(S("moon_suited_up")))
	{
		characterAnimationName = S("suit_action_stnd_");
	}
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	P<Sprite> sprite = gameObject->GetComponent<SpriteRenderer>()->get_sprite();
	P<BoxCollider2D> component = gameObject->GetComponent<BoxCollider2D>();
	Vector2 vector = gameObject->GetComponent<SpriteRenderer>()->get_bounds().size;
	component->set_offset(Vector2((0.0f - vector.x) * (0.5f - sprite->get_pivot().x / sprite->get_rect().width), vector.y / 2.0f - vector.y * (sprite->get_pivot().y / sprite->get_rect().height)));
	continueStart();
}

void NPCActionController::whatOnClick()
{
}

void NPCActionController::clickAction()
{
	Timeline::t->stopChitChat();
	if (GameObject::Find(S("Ginger")) != nullptr)
	{
		GameObject::Find(S("Ginger"))->GetComponent<NPCActionController>()->busyTalkingRandomly = false;
	}
	if (rotateToSpeaker)
	{
		if (PlayerController::wc->currentXY.x >= gameObject->GetComponent<NPCWalkController>()->currentXY.x)
		{
			if (PlayerController::wc->currentXY.y >= gameObject->GetComponent<NPCWalkController>()->currentXY.y)
			{
				gameObject->GetComponent<NPCWalkController>()->dir = NPCWalkController::Direction::SE;
			}
			else
			{
				gameObject->GetComponent<NPCWalkController>()->dir = NPCWalkController::Direction::NE;
			}
			gameObject->GetComponent<SpriteRenderer>()->set_flipX(false);
		}
		else
		{
			if (PlayerController::wc->currentXY.y >= gameObject->GetComponent<NPCWalkController>()->currentXY.y)
			{
				gameObject->GetComponent<NPCWalkController>()->dir = NPCWalkController::Direction::SW;
			}
			else
			{
				gameObject->GetComponent<NPCWalkController>()->dir = NPCWalkController::Direction::NW;
			}
			gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
		}
	}
	String text = S("stand_");
	if (PlayerController::wc->suit)
	{
		text = S("suit_") + text;
	}
	if (PlayerController::wc->currentXY.x <= gameObject->GetComponent<NPCWalkController>()->currentXY.x)
	{
		if (PlayerController::wc->currentXY.y >= gameObject->GetComponent<NPCWalkController>()->currentXY.y)
		{
			PlayerController::wc->dir = WalkController::Direction::SE;
			text += S("se");
		}
		else
		{
			PlayerController::wc->dir = WalkController::Direction::NE;
			text += S("ne");
		}
		PlayerController::wc->gameObject->GetComponent<SpriteRenderer>()->set_flipX(false);
	}
	else
	{
		if (PlayerController::wc->currentXY.y >= gameObject->GetComponent<NPCWalkController>()->currentXY.y)
		{
			PlayerController::wc->dir = WalkController::Direction::SW;
			text += S("se");
		}
		else
		{
			PlayerController::wc->dir = WalkController::Direction::NW;
			text += S("ne");
		}
		PlayerController::wc->gameObject->GetComponent<SpriteRenderer>()->set_flipX(true);
	}
	MonoBehaviour::print(S("ROTATING TO SPEAKER: ") + text);
	PlayerController::wc->forceAnimation(text, PlayerController::wc->gameObject->GetComponent<SpriteRenderer>()->get_flipX());
	npcClickAction(usedItem);
}

void NPCActionController::endTalk(String val)
{
	DialogueController::dc->talking = false;
	DialogueController::dc->hide();
	updateState();
}

void NPCActionController::npcClickAction(String item)
{
}

void NPCActionController::continueStart()
{
}

void NPCActionController::clickAction2()
{
}

void NPCActionController::updateState()
{
}

void NPCActionController::clickAction0()
{
}
