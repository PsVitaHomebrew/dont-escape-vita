#include "../game_all.h"

void ColliderManager::setTarget(P<GameObject> target, bool addNew)
{
	gameObject = target;
	if (addNew)
	{
		gameObject->AddComponent<PolygonCollider2D>();
	}
	currentColider = gameObject->GetComponent<PolygonCollider2D>();
	currentColider->set_isTrigger(true);
	setCollider(0);
}

void ColliderManager::setCollider(int number)
{
	if (currentColider != nullptr)
	{
		currentColider->set_pathCount(0);
	}
	for (int i = 0; i < colliders.Count(); i++)
	{
		if (colliders[i] != nullptr)
		{
			colliders[i]->set_enabled(false);
		}
	}
	if (number >= 0 && colliders[number] != nullptr)
	{
		colliders[number]->set_enabled(true);
		if (currentColider != nullptr)
		{
			currentColider->SetPath(0, colliders[number]->GetPath(0));
		}
	}
}
