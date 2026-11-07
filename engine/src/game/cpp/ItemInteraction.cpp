#include "../game_all.h"

ItemInteraction::ItemInteraction()
{
}

ItemInteraction::ItemInteraction(String n, String fail, std::function<void()> act, String anim, int rang)
{
	name = n;
	failText = fail;
	range = rang;
	animation = anim;
	action = act;
}
