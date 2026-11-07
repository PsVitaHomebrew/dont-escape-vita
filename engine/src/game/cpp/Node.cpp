#include "../game_all.h"

Node::Node()
{
}

Node::Node(Vector2 pos, Vector2 pos2, bool clear)
{
	set_Location(pos);
	set_GameLocation(pos2);
	set_IsWalkable(clear);
	// Vita port: the node's debug marker object is made by LocationManager::initNodes only when DEBUG is on
	// (it never is in the shipped scenes); 1296 invisible objects per area were costly to create and to skip.
	set_State(NodeState::Untested);
}

Vector2 Node::get_Location()
{
	return _Location_k;
}

void Node::set_Location(Vector2 value)
{
	_Location_k = value;
}

Vector2 Node::get_GameLocation()
{
	return _GameLocation_k;
}

void Node::set_GameLocation(Vector2 value)
{
	_GameLocation_k = value;
}

bool Node::get_IsWalkable()
{
	return _IsWalkable_k;
}

void Node::set_IsWalkable(bool value)
{
	_IsWalkable_k = value;
}

float Node::get_G()
{
	return _G_k;
}

void Node::set_G(float value)
{
	_G_k = value;
}

float Node::get_H()
{
	return _H_k;
}

void Node::set_H(float value)
{
	_H_k = value;
}

float Node::get_F()
{
	return get_G() + get_H();
}

NodeState Node::get_State()
{
	return _State_k;
}

void Node::set_State(NodeState value)
{
	_State_k = value;
}

float Node::GetTraversalCost(Vector2 p1, Vector2 p2)
{
	return LocationManager::dist(p1, p2);
}
