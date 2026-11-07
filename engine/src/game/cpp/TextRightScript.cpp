#include "../game_all.h"

TextRightScript::TextRightScript()
{
	textToType = GameStrings::getString(GameStrings::journal, S("entry_intro"));
}

void TextRightScript::Start()
{
	rewinded = false;
	textToType = JournalTexts::pickTexts(GameDataController::gd->getCurrentDay(), true);
	tLEFT = gameObject->GetComponent<TextFieldController>();
	tRIGHT = GameObject::Find(S("TextRight"))->get_gameObject()->GetComponent<TextFieldController>();
	prevBtn = GameObject::Find(S("InfoPrev"));
	nextBtn = GameObject::Find(S("InfoNext"));
	pages = List<String>::New();
	pages.Add(String::Empty);
	tLEFT->directionY = 1.0f;
	tRIGHT->directionY = 1.0f;
	currentPage = 0;
	tLEFT->maxLines = 13;
	tRIGHT->maxLines = 13;
	viewText(tLEFT, textToType);
	if (tLEFT->remains.Length() == 0)
	{
		tLEFT->remains = S(" ");
	}
	GameDataController::gd->setJournalDetail(S("journal_changed"), 0);
}

void TextRightScript::gotoNextPage()
{
	currentPage += 2;
	MonoBehaviour::print(S("current page: ") + currentPage);
	if (pages.Count() <= currentPage)
	{
		currentPage -= 2;
	}
	else
	{
		if (pages.Count() > currentPage)
		{
			viewText(tLEFT, pages[currentPage]);
		}
		if (pages.Count() > currentPage + 1)
		{
			viewText(tRIGHT, pages[currentPage + 1]);
		}
		else
		{
			viewText(tRIGHT, S(" "));
		}
	}
	GameDataController::gd->setObjectiveDetail(S("journal_page"), currentPage);
}

void TextRightScript::gotoPrevPage()
{
	currentPage -= 2;
	if (currentPage < 0)
	{
		currentPage = 0;
	}
	else
	{
		if (pages.Count() > currentPage)
		{
			viewText(tLEFT, pages[currentPage]);
		}
		if (pages.Count() > currentPage + 1)
		{
			viewText(tRIGHT, pages[currentPage + 1]);
		}
	}
	MonoBehaviour::print(S("current page: ") + currentPage);
	GameDataController::gd->setObjectiveDetail(S("journal_page"), currentPage);
}

void TextRightScript::Update()
{
	if (tLEFT->remains.Length() > 0)
	{
		pages[pages.Count() - 1] = tLEFT->get_TypedText();
		pages.Add(tLEFT->remains);
		viewText(tRIGHT, tLEFT->remains);
		tLEFT->remains = String::Empty;
	}
	else if (tRIGHT->remains.Length() > 0)
	{
		pages[pages.Count() - 1] = tRIGHT->get_TypedText();
		pages.Add(tRIGHT->remains);
		viewText(tLEFT, tRIGHT->remains);
		tRIGHT->remains = String::Empty;
	}
	else if (!rewinded)
	{
		rewinded = true;
		for (currentPage = GameDataController::gd->getObjectiveDetail(S("journal_page")); currentPage > pages.Count() - 1; currentPage -= 2)
		{
		}
		GameDataController::gd->setObjectiveDetail(S("journal_page"), currentPage);
		if (currentPage < 0)
		{
			currentPage = 0;
		}
		while (pages.Count() < currentPage)
		{
			currentPage -= 2;
		}
		if (pages.Count() > currentPage)
		{
			viewText(tLEFT, pages[currentPage]);
		}
		if (pages.Count() > currentPage + 1)
		{
			viewText(tRIGHT, pages[currentPage + 1]);
		}
		else
		{
			viewText(tRIGHT, S(" "));
		}
	}
	if (pages.Count() <= currentPage + 2)
	{
		nextBtn->GetComponent<SpriteRenderer>()->set_enabled(false);
		nextBtn->GetComponent<PolygonCollider2D>()->set_enabled(false);
	}
	else
	{
		nextBtn->GetComponent<SpriteRenderer>()->set_enabled(true);
		nextBtn->GetComponent<PolygonCollider2D>()->set_enabled(true);
	}
	if (currentPage <= 0)
	{
		prevBtn->GetComponent<SpriteRenderer>()->set_enabled(false);
		prevBtn->GetComponent<PolygonCollider2D>()->set_enabled(false);
	}
	else
	{
		prevBtn->GetComponent<SpriteRenderer>()->set_enabled(true);
		prevBtn->GetComponent<PolygonCollider2D>()->set_enabled(true);
	}
}

void TextRightScript::viewText(P<TextFieldController> tf, String text)
{
	MonoBehaviour::print(S("No dobra, to ja teraz musze napisac... [") + text + S("]"));
	Vector2 vector = ScreenControler::gameToScreen(Vector2(120.0f, 65.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	tf->transform->set_position(position);
	tf->viewText(text, false, true, true, 102, 0.34f, 0.29f, 0.28f, 0.0f, 0.0f, 0.0f, 0.0f);
	tf->black->SetActive(false);
	tf->keepAlive = true;
}
