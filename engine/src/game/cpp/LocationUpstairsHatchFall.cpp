#include "../game_all.h"

void LocationUpstairsHatchFall::Start()
{
}

void LocationUpstairsHatchFall::Update()
{
}

void LocationUpstairsHatchFall::endFall()
{
	GameDataController::gd->setObjective(S("day_2_hatch_fallen"), true);
	GameObject::Find(S("Ladder"))->transform->Find(S("faller"))->GetComponent<Animator>()->Play(S("klapa_0"));
	GetComponent<SpriteRenderer>()->set_enabled(false);
	if (GameDataController::gd->getObjectiveDetail(S("day1_complete")) < 0)
	{
		GameObject::Find(S("Ladder"))->GetComponent<LocationBaseUpstairsLadder>()->updateState();
	}
	else
	{
		GameObject::Find(S("Ladder"))->GetComponent<LocationBaseUpstairsLadder>()->updateAll();
	}
}

void LocationUpstairsHatchFall::jebs()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->double_bang);
	GameDataController::gd->setObjective(S("day_2_hatch_fallen"), true);
}
