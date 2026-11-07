#include "../game_all.h"

void LoadingScene::Start()
{
	Cursor::set_visible(false);
	pyk = 0.0f;
	doneanddone = false;
	Application::set_targetFrameRate(240);
	if (!PlayerPrefs::HasKey(S("stati")))
	{
		PlayerPrefs::SetInt(S("stati"), 50);
		PlayerPrefs::SetInt(S("music"), 100);
		PlayerPrefs::SetInt(S("sound"), 100);
		PlayerPrefs::SetFloat(S("textSpeed"), 0.0425f);
		PlayerPrefs::SetString(S("lang"), str(GameStrings::Language::EN));
		PlayerPrefs::Save();
	}
	setRes();
	GameStrings::readStrings(PlayerPrefs::GetString(S("lang"), str(GameStrings::Language::EN)));
	loadingTxt = GameStrings::getString(GameStrings::gui, S("loading"));
	dot = 0;
	tfc->viewText(loadingTxt, false, true, true);
}

String LoadingScene::ToHex(Array<uint8_t> bytes)
{
	Array<char16_t> array = Array<char16_t>::New(bytes.Length() * 2);
	int num = 0;
	int num2 = 0;
	while (num < bytes.Length())
	{
		uint8_t b = (uint8_t)(bytes[num] >> 4);
		array[num2] = (char16_t)((b <= 9) ? (b + 48) : (b + 55 + 32));
		b = (uint8_t)(bytes[num] & 0xF);
		array[++num2] = (char16_t)((b <= 9) ? (b + 48) : (b + 55 + 32));
		num++;
		num2++;
	}
	return String::FromChars(array);
}

void LoadingScene::setRes()
{
	ScreenControler::setSavedResolution();
	CurtainController::fixCameraRect();
}

void LoadingScene::Update()
{
	pyk += 0.01f;
	if (pyk >= 0.5f)
	{
		pyk = 0.0f;
		dot++;
		if (dot > 3)
		{
			dot = 0;
		}
	}
	addonTxt1 = String::Empty;
	addonTxt2 = String::Empty;
	for (int i = 0; i < dot; i++)
	{
		addonTxt2 += S(".");
	}
	tfc->viewText(addonTxt1 + loadingTxt + addonTxt2, false, true, true);
	if (!doneanddone && GameObject::Find(S("SoundsManager"))->GetComponent<SoundsManagerController>()->ALL_LOADED)
	{
		doneanddone = true;
		MonoBehaviour::print(S("PlayerPrefs.HasKey(\"font\") ") + PlayerPrefs::HasKey(S("font")));
		if (!PlayerPrefs::HasKey(S("font")))
		{
			PlayerPrefs::SetString(S("font"), S("pixel"));
			SceneManager::LoadScene(S("FontSelector"));
		}
		else
		{
			SceneManager::LoadScene(S("MainMenu"));
		}
	}
}
