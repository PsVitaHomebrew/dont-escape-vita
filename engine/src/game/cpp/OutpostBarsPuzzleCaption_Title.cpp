#include "../game_all.h"

void OutpostBarsPuzzleCaption_Title::Start()
{
	if (nameToDisplay == S("bars_puzzle_caption_1a"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
		{
			nameToDisplay = S("bars_puzzle_caption_1b");
		}
		else
		{
			nameToDisplay = S("bars_puzzle_caption_1a");
		}
	}
	else if (nameToDisplay == S("bars_puzzle_caption_2a"))
	{
		if (GameDataController::gd->getObjectiveDetail(S("day_4_threat")) == 0)
		{
			nameToDisplay = S("bars_puzzle_caption_2b");
		}
		else
		{
			nameToDisplay = S("bars_puzzle_caption_2a");
		}
	}
	int mwidth = 50;
	if (PlayerPrefs::GetString(S("lang")) == str(GameStrings::Language::DE))
	{
	}
	t = GetComponent<TextFieldController>();
	t->viewText(GameStrings::getString(GameStrings::world_labels, nameToDisplay), false, true, true, mwidth, 35.0f / 255.0f, 1.0f / 3.0f, 115.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	t->keepAlive = true;
}

void OutpostBarsPuzzleCaption_Title::Update()
{
}
