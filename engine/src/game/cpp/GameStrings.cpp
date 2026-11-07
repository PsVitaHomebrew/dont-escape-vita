#include "../game_all.h"

// Vita port: every area load re-parsed the 11 text files (about 150 ms on the Vita). They are parsed once per
// language; later calls get copies of the parsed tables (copies, so changing an entry still changes only that copy).
static Array<KeyValueString> vitaCopyTable(const Array<KeyValueString>& a)
{
	if (a.isNull()) return a;
	Array<KeyValueString> c = Array<KeyValueString>::New(a.Length());
	for (int i = 0; i < a.Length(); i++) c[i] = a[i];
	return c;
}
void GameStrings::readStrings(String lang)
{
	static String parsedLang = nullptr;
	static Array<KeyValueString> pGui, pLanguages, pItems, pObjects, pJournal, pWarnings, pActions, pWorldLabels, pMap, pResults, pDialogues;
	if (!parsedLang.isNull() && parsedLang == lang)
	{
		gui = vitaCopyTable(pGui); languages = vitaCopyTable(pLanguages); items = vitaCopyTable(pItems); objects = vitaCopyTable(pObjects);
		journal = vitaCopyTable(pJournal); warnings = vitaCopyTable(pWarnings); actions = vitaCopyTable(pActions); world_labels = vitaCopyTable(pWorldLabels);
		map = vitaCopyTable(pMap); results = vitaCopyTable(pResults); dialogues = vitaCopyTable(pDialogues);
		return;
	}
	P<TextAsset> toParse = Resources::Load<TextAsset>(S("Txt/") + lang.ToString().ToLower() + S("/gui"));
	gui = parse(toParse);
	languages = parse(Resources::Load<TextAsset>(S("Txt/languages")));
	items = parse(Resources::Load<TextAsset>(S("Txt/") + lang.ToString().ToLower() + S("/items")));
	objects = parse(Resources::Load<TextAsset>(S("Txt/") + lang.ToString().ToLower() + S("/objects")));
	journal = parse(Resources::Load<TextAsset>(S("Txt/") + lang.ToString().ToLower() + S("/journal")));
	warnings = parse(Resources::Load<TextAsset>(S("Txt/") + lang.ToString().ToLower() + S("/warnings")));
	actions = parse(Resources::Load<TextAsset>(S("Txt/") + lang.ToString().ToLower() + S("/actions")));
	world_labels = parse(Resources::Load<TextAsset>(S("Txt/") + lang.ToString().ToLower() + S("/world_labels")));
	map = parse(Resources::Load<TextAsset>(S("Txt/") + lang.ToString().ToLower() + S("/map")));
	results = parse(Resources::Load<TextAsset>(S("Txt/") + lang.ToString().ToLower() + S("/results")));
	dialogues = parse(Resources::Load<TextAsset>(S("Txt/") + lang.ToString().ToLower() + S("/dialogues")));
	pGui = vitaCopyTable(gui); pLanguages = vitaCopyTable(languages); pItems = vitaCopyTable(items); pObjects = vitaCopyTable(objects);
	pJournal = vitaCopyTable(journal); pWarnings = vitaCopyTable(warnings); pActions = vitaCopyTable(actions); pWorldLabels = vitaCopyTable(world_labels);
	pMap = vitaCopyTable(map); pResults = vitaCopyTable(results); pDialogues = vitaCopyTable(dialogues);
	parsedLang = lang;
}

Array<KeyValueString> GameStrings::parse(P<TextAsset> toParse)
{
	Array<String> array = toParse->get_text().Split(u'@');
	Array<KeyValueString> array2 = Array<KeyValueString>::New(array.Length());
	for (int i = 0; i < array.Length(); i++)
	{
		if (array[i].IndexOf(u'=') != -1)
		{
			array2[i].key = array[i].Substring(0, array[i].IndexOf(u'='));
			array2[i].value = array[i].Substring(array[i].IndexOf(u'=') + 1);
			array2[i].value = array2[i].value.Replace(S("\r"), String::Empty).Replace(S("\n"), String::Empty);
		}
	}
	return array2;
}

String GameStrings::getPrefixedShort(Array<KeyValueString> lib, String what, bool capital)
{
	String text = getString(lib, what + S("_prefix"));
	String text2 = getString(lib, what + S("_short"));
	if (capital)
	{
		Array<char16_t> array = text.ToCharArray();
		if (array.Length() > 0)
		{
			array[0] = str(array[0]).ToUpper().ToCharArray()[0];
		}
		text = String::Empty;
		for (int i = 0; i < array.Length(); i++)
		{
			text += str(array[i]);
		}
	}
	if (text.Length() == 0)
	{
		Array<char16_t> array2 = text2.ToCharArray();
		if (capital)
		{
			array2[0] = str(array2[0]).ToUpper().ToCharArray()[0];
		}
		String text3 = text2;
		text2 = array2[0] + text3.Substring(1);
	}
	if (text.Length() > 0)
	{
		return text + S(" ") + text2;
	}
	return text2;
}

String GameStrings::getWrongInteractionText()
{
	Random::set_seed((int)DateTime::Now().get_Ticks());
	int num = Random::Range(1, 7);
	return getString(actions, S("default") + num);
}

String GameStrings::capitalise(String src)
{
	Array<char16_t> array = src.ToCharArray();
	array[0] = str(array[0]).ToUpper().ToCharArray()[0];
	String text = src;
	src = array[0] + text.Substring(1);
	return src;
}

String GameStrings::getString(Array<KeyValueString> lib, String key)
{
	if (lib != nullptr)
	{
		for (int i = 0; i < lib.Length(); i++)
		{
			if (lib[i].key == key)
			{
				return lib[i].value;
			}
		}
	}
	return key + S("_STRING_MISSING");
}
