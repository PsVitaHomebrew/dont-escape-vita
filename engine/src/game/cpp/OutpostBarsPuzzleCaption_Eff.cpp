#include "../game_all.h"

void OutpostBarsPuzzleCaption_Eff::Start()
{
	t->keepAlive = true;
}

void OutpostBarsPuzzleCaption_Eff::aktualizuj()
{
	score = 0;
	score += GameDataController::gd->getObjectiveDetail(S("outpost_score_a"));
	score += GameDataController::gd->getObjectiveDetail(S("outpost_score_b"));
	score += GameDataController::gd->getObjectiveDetail(S("outpost_score_c"));
	score += GameDataController::gd->getObjectiveDetail(S("outpost_score_d"));
	score += GameDataController::gd->getObjectiveDetail(S("outpost_score_e"));
	if (score == 0)
	{
		t->viewText(GameStrings::getString(GameStrings::world_labels, S("bars_puzzle_q0")), false, true, true, 200, 127.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (score < 2)
	{
		t->viewText(GameStrings::getString(GameStrings::world_labels, S("bars_puzzle_q1")), false, true, true, 200, 124.0f / 255.0f, 31.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (score < 4)
	{
		t->viewText(GameStrings::getString(GameStrings::world_labels, S("bars_puzzle_q2")), false, true, true, 200, 124.0f / 255.0f, 52.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (score < 6)
	{
		t->viewText(GameStrings::getString(GameStrings::world_labels, S("bars_puzzle_q3")), false, true, true, 200, 124.0f / 255.0f, 72.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (score < 8)
	{
		t->viewText(GameStrings::getString(GameStrings::world_labels, S("bars_puzzle_q4")), false, true, true, 200, 127.0f / 255.0f, 106.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (score < 9)
	{
		t->viewText(GameStrings::getString(GameStrings::world_labels, S("bars_puzzle_q5")), false, true, true, 200, 114.0f / 255.0f, 124.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (score < 10)
	{
		t->viewText(GameStrings::getString(GameStrings::world_labels, S("bars_puzzle_q6")), false, true, true, 200, 72.0f / 255.0f, 124.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (score == 10)
	{
		t->viewText(GameStrings::getString(GameStrings::world_labels, S("bars_puzzle_q7")), false, true, true, 200, 0.0f, 124.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	}
}

void OutpostBarsPuzzleCaption_Eff::Update()
{
}
