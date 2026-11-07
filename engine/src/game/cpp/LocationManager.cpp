#include "../game_all.h"

void LocationManager::canPickUpItems()
{
	Array<P<GroundItemController>> array = Object::FindObjectsOfType<GroundItemController>();
	for (int i = 0; i < array.Length(); i++)
	{
		array[i]->enablePickup();
	}
}

void LocationManager::cantPickupItems()
{
	Array<P<GroundItemController>> array = Object::FindObjectsOfType<GroundItemController>();
	for (int i = 0; i < array.Length(); i++)
	{
		array[i]->disablePickup();
	}
}

void LocationManager::Start()
{
	if (GameDataController::gd->getObjective(S("moon_suited_up")))
	{
		suit = true;
	}
	else
	{
		suit = false;
	}
	PlayerController::wc->suit = suit;
	cameraMoved = Vector3(0.0f, 0.01f, -20.0f);
	MonoBehaviour::print(S("======== HELLO WORLD ============================================================================="));
	pathLayer = LayerMask::GetMask(S("hitTest"));
	blockingLayer = LayerMask::GetMask(S("obstacleLayer"));
	ItemsManager::im->initGroundAndInv();
	PlayerController::pc->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(14.0f, 15.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	InventoryButtonController::ibc->gameObject->transform->set_position(position);
	Cursor::set_visible(false);
	CursorController::cc->showCursor(CursorController::PixelCursor::NORMAL);
	GameObject::Find(S("Main Camera"))->GetComponent<Camera>()->set_backgroundColor(Color(0.0f, 0.0f, 0.0f));
	MainCamera = GameObject::Find(S("Main Camera"));
	MainCamera->GetComponent<Camera>()->set_depth(0.0f);
	MainCameraC = MainCamera->GetComponent<Camera>();
	if (needSpecialCamera)
	{
		UICamera = Object::Instantiate(MainCamera, Vector3(0.0f, 0.0f, -15.0f), Quaternion::get_identity());
		UICamera->GetComponent<Camera>()->set_depth(1.0f);
		UICamera->GetComponent<Camera>()->set_cullingMask(1 << LayerMask::NameToLayer(S("UI")));
		UICamera->GetComponent<Camera>()->set_cullingMask(UICamera->GetComponent<Camera>()->get_cullingMask() | (1 << LayerMask::NameToLayer(S("cursor"))));
		UICamera->GetComponent<Camera>()->set_cullingMask(UICamera->GetComponent<Camera>()->get_cullingMask() | (1 << LayerMask::NameToLayer(S("gui"))));
		UICamera->GetComponent<Camera>()->set_cullingMask(UICamera->GetComponent<Camera>()->get_cullingMask() | (1 << LayerMask::NameToLayer(S("text"))));
		UICamera->GetComponent<Camera>()->set_cullingMask(UICamera->GetComponent<Camera>()->get_cullingMask() | (1 << LayerMask::NameToLayer(S("static"))));
		MainCamera->GetComponent<Camera>()->set_cullingMask(MainCamera->GetComponent<Camera>()->get_cullingMask() & ~(1 << LayerMask::NameToLayer(S("UI"))));
		MainCamera->GetComponent<Camera>()->set_cullingMask(MainCamera->GetComponent<Camera>()->get_cullingMask() & ~(1 << LayerMask::NameToLayer(S("cursor"))));
		MainCamera->GetComponent<Camera>()->set_cullingMask(MainCamera->GetComponent<Camera>()->get_cullingMask() & ~(1 << LayerMask::NameToLayer(S("gui"))));
		MainCamera->GetComponent<Camera>()->set_cullingMask(MainCamera->GetComponent<Camera>()->get_cullingMask() & ~(1 << LayerMask::NameToLayer(S("text"))));
		MainCamera->GetComponent<Camera>()->set_cullingMask(MainCamera->GetComponent<Camera>()->get_cullingMask() & ~(1 << LayerMask::NameToLayer(S("static"))));
		UICamera->GetComponent<AudioListener>()->set_enabled(false);
		MainCamera->GetComponent<Camera>()->set_clearFlags(CameraClearFlags::Color);
		MainCamera->GetComponent<Camera>()->set_backgroundColor(Color(0.0f, 0.0f, 0.0f));
		UICamera->GetComponent<Camera>()->set_clearFlags(CameraClearFlags::Nothing);
		MainCamera->set_tag(S("OriginalCamera"));
	}
	CurtainController::fixCameraRect();
	previousCameraRect = Rect(MainCameraC->get_rect().x, MainCameraC->get_rect().y, MainCameraC->get_rect().width, MainCameraC->get_rect().height);
	Invoke(S("checkResolution"), 1.0f);
	PlayerController::pc->allowDrop = true;
	initNodes();
	if (SceneManager::GetActiveScene().get_name() != S("PauseMenu") && SceneManager::GetActiveScene().get_name() != S("SaveMenu"))
	{
		AudioListener::set_pause(false);
	}
	Invoke(S("resetShadow"), 0.25f);
	if (showInventory)
	{
		if (InventoryButtonController::ibc != nullptr)
		{
			if (GameDataController::gd->getObjective(S("tent_backpack_taken")))
			{
				InventoryButtonController::ibc->showFinal();
			}
			else
			{
				InventoryButtonController::ibc->hide();
			}
		}
		if (GameObject::Find(S("journal")) != nullptr)
		{
			if (GameDataController::gd->getObjective(S("tent_distance_checked")))
			{
				GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->showFinal();
				Invoke(S("blinkMaybe"), 0.5f);
			}
			else
			{
				GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->hide();
			}
		}
		if (GameObject::Find(S("clock")) != nullptr)
		{
			if (GameDataController::gd->getObjective(S("base_discovered")))
			{
				GameObject::Find(S("clock"))->GetComponent<ClockController>()->showFinal();
			}
			else
			{
				GameObject::Find(S("clock"))->GetComponent<ClockController>()->hide();
			}
		}
	}
	else
	{
		if (InventoryButtonController::ibc != nullptr)
		{
			InventoryButtonController::ibc->hide();
		}
		if (GameObject::Find(S("journal")) != nullptr)
		{
			GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->hide();
		}
		if (GameObject::Find(S("clock")) != nullptr)
		{
			GameObject::Find(S("clock"))->GetComponent<ClockController>()->hide();
		}
	}
	InventoryController::ic->maxCapacity = 30;
	if (GameDataController::gd->getObjectiveDetail(S("day1_complete")) == 1)
	{
		InventoryController::ic->maxCapacity += 5;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day2_complete")) == 1)
	{
		InventoryController::ic->maxCapacity += 5;
	}
	if (GameDataController::gd->getObjectiveDetail(S("day3_complete")) == 1)
	{
		InventoryController::ic->maxCapacity += 5;
	}
	if (GameDataController::gd->getCurrentDay() == 3 && GameDataController::gd->getObjectiveDetail(S("day_3_threat")) == 1 && GameDataController::gd->isOKtoSave(S("autosave")) && GameObject::Find(S("thunderstorm_generator")) == nullptr)
	{
		P<GameObject> gameObject = Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/thunderstorm_generator")), Vector3(0.0f, 0.0f, -4.5f), Quaternion()).as<GameObject>();
		gameObject->set_name(S("thunderstorm_generator"));
		gameObject->GetComponent<lightingblast>()->initthis();
	}
	if (SceneManager::GetActiveScene().get_name() != S("LocationMap"))
	{
		GameDataController::gd->setObjective(S("car_travel"), false);
	}
	Timeline::t->stopChitChat();
}

void LocationManager::checkResolution()
{
	if (Screen::get_fullScreen() && Screen::get_currentResolution().width != PlayerPrefs::GetInt(S("resolution")))
	{
		PlayerPrefs::SetInt(S("resolution"), Screen::get_currentResolution().width);
		ScreenControler::setWindowedResolution(Screen::get_currentResolution().width);
		ScreenControler::setWindowedResolution((int)ScreenControler::allowedResolutions[ScreenControler::allowedResolutions.Length() - 1].x);
		ScreenControler::setFullScreenResolution();
		CurtainController::fixCameraRect();
		Invoke(S("needFix"), 0.5f);
	}
	Invoke(S("checkResolution"), 1.0f);
}

void LocationManager::needFix()
{
	ScreenControler::setWindowedResolution((int)ScreenControler::allowedResolutions[ScreenControler::allowedResolutions.Length() - 1].x);
	ScreenControler::setFullScreenResolution();
	CurtainController::fixCameraRect();
}

void LocationManager::blinkMaybe()
{
	JournalTexts::pickTexts(GameDataController::gd->getCurrentDay());
}

void LocationManager::Update()
{
	if (showInventory)
	{
		if (Input::GetKeyDown(KeyCode::Space) || Input::GetKeyDown(KeyCode::I))
		{
			MonoBehaviour::print(S("SPACJA "));
			if (InventoryButtonController::ibc->gameObject->GetComponent<BoxCollider2D>()->get_enabled())
			{
				InventoryButtonController::ibc->fakeMouseClick(true);
			}
		}
		if (Input::GetKeyDown(KeyCode::J) && GameObject::Find(S("journal")) != nullptr && GameDataController::gd->getObjective(S("tent_distance_checked")))
		{
			GameObject::Find(S("journal"))->GetComponent<JournalButtonController>()->fakeClick();
		}
	}
	if (Input::GetKey(KeyCode::LeftAlt) || Input::GetKey(KeyCode::RightAlt) || Input::GetKey(KeyCode::LeftShift) || Input::GetKey(KeyCode::RightShift))
	{
		highlightItems(true);
	}
	else if (itemsHighlighted)
	{
		highlightItems(false);
	}
	if (esc != nullptr && Input::GetKeyDown(KeyCode::Escape) && !PlayerController::wc->busy)
	{
		esc->fakeClick();
		esc = nullptr;
	}
	if (escButton != nullptr && Input::GetKeyDown(KeyCode::Escape) && !PlayerController::wc->busy)
	{
		escButton->onClick();
		escButton = nullptr;
	}
	if (escButton2 != nullptr && Input::GetKeyDown(KeyCode::Escape) && escButton2->buttonEnabled)
	{
		escButton2->onClick();
		escButton2 = nullptr;
	}
	if (MainCamera == nullptr)
	{
		MainCamera = GameObject::Find(S("Main Camera"));
	}
	if (needShake > 0.0f)
	{
		needShake -= Time::get_deltaTime();
		if (aaa <= 0.0f)
		{
			aaa = 0.03f;
			if (MainCamera == nullptr)
			{
				MainCamera = GameObject::Find(S("Main Camera"));
			}
			if (MainCamera->transform->get_position().y != 0.0f)
			{
				MainCamera->transform->set_position(Vector3(0.0f, 0.0f, -20.0f));
				return;
			}
			MainCamera->transform->set_position(cameraMoved);
			TextFieldController::cameraShiftY = cameraMoved.y * 1.0f;
		}
		else
		{
			aaa -= Time::get_deltaTime();
		}
	}
	else
	{
		MainCamera->transform->set_position(Vector3(0.0f, 0.0f, -20.0f));
	}
}

void LocationManager::highlightItems(bool show)
{
	Array<P<GroundItemController>> array = Object::FindObjectsOfType<GroundItemController>();
	itemsHighlighted = show;
	for (int i = 0; i < array.Length(); i++)
	{
		array[i]->frontView->set_enabled(show);
	}
}

void LocationManager::initNodes()
{
	if (nodes != nullptr)
	{
		for (int i = 0; i < nodesH; i++)
		{
			for (int j = 0; j < nodesW; j++)
			{
				if (nodes[j * nodesH + i]->gameObject != nullptr) Object::Destroy(nodes[j * nodesH + i]->gameObject);
			}
		}
	}
	nodes = Array<P<Node>>::New(nodesW * nodesH);
	for (int k = 0; k < nodesH; k++)
	{
		for (int l = 0; l < nodesW; l++)
		{
			bool clear = true;
			nodes[l * nodesH + k] = New<Node>(Vector2((float)l, (float)k), Vector2((float)(l * pixelsW / nodesW), (float)(k * pixelsH / nodesH)), clear);
			if (DEBUG)   // Vita port: debug marker only when it can be seen (see Node::Node)
			{
				nodes[l * nodesH + k]->gameObject = New<GameObject>();
				nodes[l * nodesH + k]->gameObject->AddComponent<SpriteRenderer>();
				nodes[l * nodesH + k]->gameObject->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 0.5f));
			}
			if (!(bool)Physics2D::Linecast(Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(nodes[l * nodesH + k]->get_GameLocation())), Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(nodes[l * nodesH + k]->get_GameLocation())), pathLayer) || (bool)Physics2D::Linecast(Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(nodes[l * nodesH + k]->get_GameLocation())), Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(nodes[l * nodesH + k]->get_GameLocation())), blockingLayer))
			{
				clear = false;
				if (DEBUG)
				{
					nodes[l * nodesH + k]->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Misc/node_0")));
				}
				nodes[l * nodesH + k]->set_IsWalkable(false);
			}
			else
			{
				clear = true;
				if (DEBUG)
				{
					nodes[l * nodesH + k]->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Misc/node_1")));
				}
				nodes[l * nodesH + k]->set_IsWalkable(true);
			}
			if (nodes[l * nodesH + k]->gameObject != nullptr)
			{
				Vector2 vector = ScreenControler::gameToScreen(Vector2(nodes[l * nodesH + k]->get_GameLocation().x, nodes[l * nodesH + k]->get_GameLocation().y));
				Vector3 vector2 = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
				nodes[l * nodesH + k]->gameObject->transform->set_position(Vector3(vector2.x, vector2.y, -5.0f));
			}
		}
	}
}

void LocationManager::OnMouseOver()
{
}

float LocationManager::dist(Vector2 a, Vector2 b)
{
	return Mathf::Sqrt(Mathf::Pow(a.x - b.x, 2.0f) + Mathf::Pow(a.y - b.y, 2.0f));
}

bool LocationManager::Search(P<Node> currentNode)
{
	currentNode->set_State(NodeState::Closed);
	List<P<Node>> adjacentWalkableNodes = GetAdjacentWalkableNodes(currentNode);
	adjacentWalkableNodes.Sort([](const P<Node>& node1, const P<Node>& node2) { return (node1->get_F() < node2->get_F()) ? -1 : ((node1->get_F() > node2->get_F()) ? 1 : 0); });
	for (P<Node> item : adjacentWalkableNodes)
	{
		if (item->get_Location() == endNode->get_Location())
		{
			MonoBehaviour::print(S("ZNALEZIONO CEL "));
			return true;
		}
		if (Search(item))
		{
			return true;
		}
	}
	return false;
}

void LocationManager::resetShadow()
{
	PlayerController::wc->shadow->clearLastFrame();
}

Vector2 LocationManager::getNodeLocation(Vector2 sourceLocation)
{
	Vector2 result;
	result.x = Mathf::Floor(sourceLocation.x * (float)nodesW / (float)pixelsW);
	result.y = Mathf::Floor(sourceLocation.y * (float)nodesH / (float)pixelsH);
	if (result.x <= 0.0f)
	{
		result.x = 0.0f;
	}
	if (result.y <= 0.0f)
	{
		result.y = 0.0f;
	}
	if (result.x >= (float)nodesW)
	{
		result.x = (float)(nodesW - 1);
	}
	if (result.y >= (float)nodesH)
	{
		result.y = (float)(nodesH - 1);
	}
	return result;
}

void LocationManager::setPathStart(Vector2 start)
{
	startNode = nodes[(int)start.x * nodesH + (int)start.y];
}

void LocationManager::setPathEnd(Vector2 end)
{
	endNode = nodes[(int)end.x * nodesH + (int)end.y];
	if (DEBUG)
	{
		endNode->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Misc/node_2")));
	}
}

Vector2 LocationManager::findNearestClearNode(Vector2 source)
{
	int i = 0;
	P<Node> node = nullptr;
	if (!walkable)
	{
		return source;
	}
	// Vita port: whole-number squares instead of Mathf::Pow (the same values) and no reference counting per cell.
	// This runs for every click on a spot the player cannot stand on and took 16-39 ms on the Vita.
	// Same scan order, so the same node is chosen.
	int sx = (int)source.x, sy = (int)source.y;
	Node* found = nullptr;
	for (; found == nullptr || i > 200; i++)
	{
		int ii = i * i;
		for (int j = -i; j <= i; j++)
		{
			int x = sx + j;
			if (!(x > 0 && x < nodesW)) continue;
			for (int k = -i; k <= i; k++)
			{
				int y = sy + k;
				if (y > 0 && y < nodesH && j * j + k * k <= ii)
				{
					Node* n = nodes[x * nodesH + y].get();
					if (n->get_IsWalkable()) found = n;
				}
			}
		}
	}
	node = P<Node>(found);
	return node->get_Location();
}

List<Vector2> LocationManager::GetAdjacentLocations(Vector2 location)
{
	List<Vector2> list = List<Vector2>::New();
	list.Add(Vector2(location.x - 1.0f, location.y));
	list.Add(Vector2(location.x + 1.0f, location.y));
	list.Add(Vector2(location.x, location.y + 1.0f));
	list.Add(Vector2(location.x, location.y - 1.0f));
	list.Add(Vector2(location.x + 1.0f, location.y + 1.0f));
	list.Add(Vector2(location.x - 1.0f, location.y + 1.0f));
	list.Add(Vector2(location.x + 1.0f, location.y - 1.0f));
	list.Add(Vector2(location.x - 1.0f, location.y - 1.0f));
	return list;
}

List<P<Node>> LocationManager::GetAdjacentWalkableNodes(P<Node> fromNode)
{
	List<P<Node>> list = List<P<Node>>::New();
	List<Vector2> adjacentLocations = GetAdjacentLocations(fromNode->get_Location());
	int num = 0;
	for (Vector2 item : adjacentLocations)
	{
		num++;
		int num2 = (int)item.x;
		int num3 = (int)item.y;
		if (num2 < 0 || num2 >= nodesW || num3 < 0 || num3 >= nodesH)
		{
			continue;
		}
		P<Node> node = nodes[num2 * nodesH + num3];
		if (!node->get_IsWalkable() || node->get_State() == NodeState::Closed)
		{
			continue;
		}
		if (node->get_State() == NodeState::Open)
		{
			float traversalCost = Node::GetTraversalCost(node->get_Location(), fromNode->get_Location());
			float num4 = fromNode->get_G() + traversalCost;
			if (num4 < node->get_G())
			{
				node->ParentNode = fromNode;
				list.Add(node);
			}
		}
		else
		{
			node->ParentNode = fromNode;
			node->set_State(NodeState::Open);
			node->set_H(dist(node->get_Location(), endNode->get_Location()));
			node->set_G(dist(startNode->get_Location(), node->get_Location()));
			list.Add(node);
		}
	}
	return list;
}

List<Vector2> LocationManager::FindPath(Vector2 start, Vector2 finish)
{
	setPathStart(start);
	setPathEnd(finish);
	MonoBehaviour::print(String::Concat(S("SEARCHING FOR PATH FROM "), start.ToString(), S(" TO "), finish.ToString()));
	for (int i = 0; i < nodesH; i++)
	{
		for (int j = 0; j < nodesW; j++)
		{
			nodes[j * nodesH + i]->set_State(NodeState::Untested);
			nodes[j * nodesH + i]->ParentNode = nullptr;
		}
	}
	List<Vector2> list = List<Vector2>::New();
	bool flag = Search(startNode);
	MonoBehaviour::print(S("sukces = ") + flag);
	if (flag)
	{
		P<Node> parentNode = endNode;
		while (parentNode->ParentNode != nullptr)
		{
			list.Add(parentNode->get_Location());
			parentNode->set_State(NodeState::Untested);
			P<Node> node = parentNode;
			parentNode = parentNode->ParentNode;
			node->ParentNode = nullptr;
		}
		list.Reverse();
	}
	if (list != nullptr)
	{
		for (int k = 0; k < list.Count(); k++)
		{
			if (DEBUG)
			{
				nodes[(int)list[k].x * nodesH + (int)list[k].y]->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Misc/node_2")));
			}
			Vector2 location = nodes[(int)list[k].x * nodesH + (int)list[k].y]->get_Location();
			list[k] = Vector2(location.x * (float)pixelsW / (float)nodesW, location.y * (float)pixelsH / (float)nodesH);
		}
	}
	return list;
}

List<Vector2> LocationManager::Search2(Vector2 start, Vector2 finish)
{
	setPathStart(start);
	setPathEnd(finish);
	if (!walkable)
	{
		return nullptr;
	}
	for (int i = 0; i < nodesH; i++)
	{
		for (int j = 0; j < nodesW; j++)
		{
			if (DEBUG)
			{
				if (nodes[j * nodesH + i]->get_IsWalkable())
				{
					nodes[j * nodesH + i]->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Misc/node_1")));
				}
				else
				{
					nodes[j * nodesH + i]->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Misc/node_0")));
				}
			}
			nodes[j * nodesH + i]->ParentNode = nullptr;
		}
	}
	std::vector<Node*> list; list.reserve((size_t)(nodesW * nodesH) + 8);
	list.push_back(startNode.get());
	startNode->ParentNode = nullptr;
	Node* endRaw = endNode.get(); Node* startRaw = startNode.get();
	// Vita port: the queue is read with a moving index instead of RemoveAt(0), which shifted the whole list on every
	// step (20-70 ms per click on the Vita), and neighbours come from a fixed table in GetAdjacentLocations' order.
	// Same visiting order, so the same path.
	static const float adjX[8] = { -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, -1.0f }, adjY[8] = { 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f };
	for (size_t head = 0; head < list.size(); head++)
	{
		Node* node = list[head];
		if (node == endRaw)
		{
			List<Vector2> list2 = List<Vector2>::New();
			while (node != startRaw)
			{
				list2.Add(node->get_Location());
				node = node->ParentNode.get();
			}
			for (int k = 0; k < list2.Count(); k++)
			{
				if (DEBUG)
				{
					nodes[(int)list2[k].x * nodesH + (int)list2[k].y]->gameObject->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Misc/node_2")));
				}
				Vector2 location = nodes[(int)list2[k].x * nodesH + (int)list2[k].y]->get_Location();
				list2[k] = Vector2(location.x * (float)pixelsW / (float)nodesW, location.y * (float)pixelsH / (float)nodesH);
			}
			list2.Reverse();
			return list2;
		}
		Vector2 loc = node->get_Location();
		for (int d = 0; d < 8; d++)
		{
			Vector2 item = Vector2(adjX[d] == 0.0f ? loc.x : (adjX[d] > 0.0f ? loc.x + 1.0f : loc.x - 1.0f), adjY[d] == 0.0f ? loc.y : (adjY[d] > 0.0f ? loc.y + 1.0f : loc.y - 1.0f));
			int num = (int)item.x;
			int num2 = (int)item.y;
			if (num >= 0 && num < nodesW && num2 >= 0 && num2 < nodesH)
			{
				Node* node2 = nodes[num * nodesH + num2].get();
				if (node2->get_IsWalkable() && node2->ParentNode.get() == nullptr)
				{
					node2->ParentNode = P<Node>(node);
					list.push_back(node2);
				}
			}
		}
	}
	return nullptr;
}
