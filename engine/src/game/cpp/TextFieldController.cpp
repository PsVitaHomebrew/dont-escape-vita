#include "../game_all.h"
#include <unordered_map>

// Vita port: a letter's sprite name depends only on the character, so it is worked out once per character, and a
// font's name list is searched through a map built once per list instead of name by name. Same results; showing a
// line of text (one object per letter) was a visible stutter on the Vita.
namespace {
struct VitaGlyphName { String name; Array<uint8_t> bytes; };
struct VitaNameIndex { int count = -1; String first, last; std::unordered_map<std::u16string, int> map; };
std::unordered_map<char16_t, VitaGlyphName>& vitaGlyphNames() { static std::unordered_map<char16_t, VitaGlyphName> m; return m; }
std::unordered_map<const void*, VitaNameIndex>& vitaNameIndexes() { static std::unordered_map<const void*, VitaNameIndex> m; return m; }
int vitaIndexOfName(List<String>& names, const String& name) {
  int n = names.Count(); if (n == 0) return -1;
  VitaNameIndex& ix = vitaNameIndexes()[(const void*)&names[0]];
  if (ix.count != n || !(ix.first == (String)names[0]) || !(ix.last == (String)names[n - 1])) {
    ix.map.clear(); ix.count = n; ix.first = names[0]; ix.last = names[n - 1];
    for (int i = n - 1; i >= 0; i--) { String s = names[i]; if (!s.isNull()) ix.map[s.u()] = i; }   // first index wins
  }
  if (name.isNull()) return names.IndexOf(name);
  auto it = ix.map.find(name.u()); return it == ix.map.end() ? -1 : it->second;
}
}

String TextFieldController::get_TypedText()
{
	return typed;
}

List<P<GameObject>> TextFieldController::getChars()
{
	return chars;
}

void TextFieldController::createBlack()
{
	black = New<GameObject>(S("black"));
	black->set_layer(LayerMask::NameToLayer(S("text")));
	black->AddComponent<SpriteRenderer>();
	black->GetComponent<SpriteRenderer>()->set_sprite(Resources::Load<Sprite>(S("Bitmaps/Misc/black")));
	black->transform->set_parent(container->transform);
	black->SetActive(false);
}

void TextFieldController::setTime(float t)
{
	waitTillDelete = t;
	keepAlive = false;
}

void TextFieldController::Awake()
{
	BASE_DELAY = PlayerPrefs::GetFloat(S("textSpeed"), 0.05f);
	queued = String::Empty;
	container = New<GameObject>(S("container"));
	container->set_layer(LayerMask::NameToLayer(S("text")));
	force_pixel_font = false;
	force_smooth_font = false;
	createBlack();
	isSmooth = false;
	updateFont();
	initThings();
}

void TextFieldController::initThings()
{
	spritesNames = List<String>::New();
	chars = List<P<GameObject>>::New();
	remains = String::Empty;
	for (int i = 0; i < sprites.Length(); i++)
	{
		spritesNames.Add(sprites[i]->get_name());
	}
}

void TextFieldController::updateFont()
{
	if ((force_pixel_font || PlayerPrefs::GetString(S("font"), S("pixel")) == S("pixel")) && !force_smooth_font)
	{
		smod = 1.0f;
		pmod = 1;
		pmod2 = 1;
		sprites = Resources::LoadAll<Sprite>(S("Bitmaps/Misc/pixelFont"));
	}
	else
	{
		sprites = Resources::LoadAll<Sprite>(S("Bitmaps/Misc/smoothFont"));
		smod = 0.03f;
		pmod = 3;
		pmod2 = 2;
	}
}

void TextFieldController::positionTextfield(int x, int y)
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2((float)x, (float)y));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	position.z = -3.0f;
	gameObject->transform->set_position(position);
}

void TextFieldController::setAlpha(float a)
{
	for (int i = 0; i < chars.Count(); i++)
	{
		chars[i]->GetComponent<SpriteRenderer>()->set_color(Color(red, green, blue, a));
	}
}

void TextFieldController::setTextColor(float r, float g, float b)
{
	for (int i = 0; i < chars.Count(); i++)
	{
		chars[i]->GetComponent<SpriteRenderer>()->set_color(Color(r, g, b, 1.0f));
	}
	red = r;
	green = g;
	blue = b;
}

void TextFieldController::setBGColor(float r, float g, float b, float a)
{
	bgred = r;
	bggreen = g;
	bgblue = b;
	bgalpha = a;
}

void TextFieldController::viewText(String text, bool blockG, bool quick, bool instant, int mwidth, float r, float g, float b, float br, float bg, float bb, float ba, bool constantRefresh, bool mute)
{
	BASE_DELAY = PlayerPrefs::GetFloat(S("textSpeed"), 0.05f);
	if (mwidth == -1)
	{
		mwidth = ((!(PlayerPrefs::GetString(S("lang")) == str(GameStrings::Language::DE))) ? 100 : 130);
	}
	maxWidth = mwidth;
	queued = String::Empty;
	remains = String::Empty;
	dissmiss();
	positionEverytime = constantRefresh;
	setBGColor(br, bg, bb, ba);
	setTextColor(r, g, b);
	keepAlive = false;
	if (blockG)
	{
		blockGame = true;
		GameObject::FindGameObjectWithTag(S("Cursor"))->GetComponent<CursorController>()->showCursor(CursorController::PixelCursor::OK);
		PlayerController::pc->setDialogue(gameObject);
		delay = BASE_DELAY;
		currentDelay = 0.0f;
		perUpdate = 1;
		waitTillDelete = -1.0f;
		pyk = SoundsManagerController::sm->pyk;
	}
	else
	{
		blockGame = false;
		delay = 0.0f;
		if (!quick)
		{
			delay = BASE_DELAY;
		}
		currentDelay = 0.0f;
		perUpdate = 1;
		pyk = nullptr;
	}
	if (mute)
	{
		pyk = nullptr;
	}
	waitTillDelete = 0.5f + (float)text.Length() / 10.0f;
	if (quick)
	{
		waitTillDelete = 0.0f;
		keepAlive = true;
		currentDelay = 1000.0f;
		perUpdate = 2;
		if (instant)
		{
			delay = 0.0f;
			currentDelay = 100.0f;
			perUpdate = 10000;
		}
	}
	currentWait = 0.0f;
	if (black == nullptr)
	{
		createBlack();
	}
	black->transform->set_localScale(Vector3(0.0f, 0.0f, 0.0f));
	black->SetActive(true);
	black->GetComponent<SpriteRenderer>()->set_color(Color(bgred, bggreen, bgblue, bgalpha));
	queued = text;
	Update();
}

Vector3 TextFieldController::coords(Vector2 source)
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2(source.x, source.y));
	Vector3 result = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, 0.0f));
	Vector2 vector2 = ScreenControler::gameToScreen(Vector2(0.0f, 0.0f));
	Vector3 vector3 = Camera::get_main()->ScreenToWorldPoint(Vector3(vector2.x, vector2.y, 0.0f));
	result.x -= vector3.x;
	result.y -= vector3.y;
	return result;
}

void TextFieldController::Update()
{
	currentDelay += Time::get_deltaTime();
	bool flag = false;
	if (queued.Length() < perUpdate)
	{
		perUpdate = queued.Length();
	}
	if (perUpdate == 0)
	{
		perUpdate = 1;
	}
	if (queued.Length() > 0)
	{
		if (currentDelay >= delay)
		{
			currentDelay = 0.0f;
			if ((CurtainController::cc == nullptr || !CurtainController::cc->okToGo()) && delay > 0.0f && blockGame)
			{
				return;
			}
			for (int i = 0; i < perUpdate; i++)
			{
				if (queued.Length() > 0)
				{
					flag = true;
					typed += str(queued[0]);
					container->transform->set_position(Vector3(0.0f, 0.0f, 0.0f));
					addText(str(queued[0]));
					if (queued.Length() > 0)
					{
						queued = queued.Substring(1);
					}
				}
			}
			if (queued.Length() == 0 && blockGame && PlayerController::pc->dialogue == PlayerController::DialogueState::WAIT_TO_SPEED)
			{
				PlayerController::pc->dialogue = PlayerController::DialogueState::WAIT_TO_DISMISS;
				if (pyk != nullptr)
				{
					PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->pyk2, 0.75f);
				}
			}
			if (flag && !positionEverytime)
			{
				arrange();
			}
		}
	}
	else if (blockGame && PlayerController::pc->dialogue == PlayerController::DialogueState::WAIT_TO_SPEED)
	{
		if (keepAlive)
		{
			PlayerController::pc->dialogue = PlayerController::DialogueState::WAIT_TO_DISMISS;
		}
	}
	else if (!blockGame && waitTillDelete >= 0.0f)
	{
		if (!keepAlive)
		{
			currentWait += Time::get_deltaTime();
			if (currentWait >= waitTillDelete)
			{
				waitTillDelete = -1.0f;
				dissmiss();
			}
		}
	}
	else if (PlayerController::pc->dialogue == PlayerController::DialogueState::NONE)
	{
		dissmiss();
	}
	Vector2 source = Vector2(shift.x, shift.y);
	Vector3 vector = coords(source);
	container->transform->set_position(Vector3(gameObject->transform->get_position().x + vector.x, gameObject->transform->get_position().y + vector.y, zzz));
	float num = (float)(longestLine / 2);
	if (center)
	{
		num = 0.0f;
	}
	int num2 = 5;
	Vector2 vector2 = ScreenControler::gameToScreen(Vector2((float)ScreenControler::sourceWidth - Mathf::Floor((float)(longestLine / 2)) - num - (float)num2 - (float)OPTIONAL_MARGIN, currentHeight));
	Vector3 vector3 = Camera::get_main()->ScreenToWorldPoint(Vector3(vector2.x, vector2.y, 0.0f));
	if (container->transform->get_position().x >= vector3.x)
	{
		container->transform->set_position(Vector3(vector3.x, container->transform->get_position().y, container->transform->get_position().z));
	}
	if (container->transform->get_position().y >= 0.0f - vector3.y && blockTop && directionY == -1.0f)
	{
		container->transform->set_position(Vector3(container->transform->get_position().x, 0.0f - vector3.y, container->transform->get_position().z));
	}
	vector2 = ScreenControler::gameToScreen(Vector2(Mathf::Floor((float)(longestLine / 2)) - num + (float)num2 + (float)OPTIONAL_MARGIN, shift.y));
	vector3 = Camera::get_main()->ScreenToWorldPoint(Vector3(vector2.x, vector2.y, 0.0f));
	if (container->transform->get_position().x <= vector3.x)
	{
		container->transform->set_position(Vector3(vector3.x, container->transform->get_position().y, container->transform->get_position().z));
	}
}

void TextFieldController::speedUp()
{
	if (queued.Length() != 0)
	{
		delay = 0.0f;
		perUpdate = 20;
		PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->pyk2, 0.75f);
		pyk = nullptr;
	}
}

void TextFieldController::terminate()
{
	delay = 0.0f;
	perUpdate = 10000;
	queued = String::Empty;
	keepAlive = false;
}

bool TextFieldController::dissmiss(bool hard)
{
	if (hard)
	{
		queued = String::Empty;
	}
	bgalpha = 0.75f;
	bgred = (bggreen = (bgblue = 0.0f));
	blockGame = false;
	if (queued.Length() == 0 && chars != nullptr)
	{
		while (chars.Count() > 0)
		{
			Object::Destroy(chars[0]);
			chars.RemoveAt(0);
		}
		typed = String::Empty;
		queued = String::Empty;
		longestLine = 0;
		if (black != nullptr)
		{
			black->SetActive(false);
		}
		return true;
	}
	return false;
}

void TextFieldController::addText(String text)
{
	for (int i = 0; i < text.Length(); i++)
	{
		P<GameObject> gameObject = New<GameObject>(S("Tf_") + this->gameObject->get_name() + S("_t_") + i);
		gameObject->transform->set_parent(container->transform);
		String text2;
		auto cachedName = vitaGlyphNames().find(text[i]);
		if (cachedName != vitaGlyphNames().end())
		{
			bytes = cachedName->second.bytes;
			text2 = cachedName->second.name;
		}
		else
		{
			if (str(text[i]).Equals(S("^")))
			{
				bytes = Encoding::get_UTF8().GetBytes(S(" "));
			}
			else if (str(text[i]).Equals(S("#")))
			{
				bytes = Encoding::get_UTF8().GetBytes(S("@"));
			}
			else
			{
				bytes = Encoding::get_UTF8().GetBytes(str(text[i]));
			}
			text2 = ((ToHex(bytes).ToString().Length() == 2) ? (S("U+00") + ToHex(bytes)) : ((ToHex(bytes).ToString().Length() != 3) ? (S("U+") + ToHex(bytes)) : (S("U+0") + ToHex(bytes))));
			text2 = text2.ToUpper();
			vitaGlyphNames()[text[i]] = { text2, bytes };
		}
		int num = vitaIndexOfName(spritesNames, text2);
		if (num > -1)
		{
			gameObject->AddComponent<SpriteRenderer>();
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprites[num]);
			gameObject->GetComponent<SpriteRenderer>()->set_color(Color(red, green, blue));
			chars.Add(gameObject);
			if (useSeparateCamera)
			{
				gameObject->set_layer(LayerMask::NameToLayer(S("text")));
			}
			if (pyk != nullptr)
			{
				PlayerController::pc->aS->PlayOneShot(pyk, 0.5f);
			}
		}
	}
	if (positionEverytime)
	{
		arrange();
	}
}

String TextFieldController::ToHex(Array<uint8_t> bytes)
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

void TextFieldController::arrange()
{
	linesBegins = List<int>::New();
	linesBegins.Add(0);
	linesLengths = List<int>::New();
	linesLengths.Add(0);
	int num = 0;
	for (int i = 0; i < chars.Count(); i++)
	{
		int num2 = pmod;
		if (chars[i]->GetComponent<SpriteRenderer>()->get_sprite()->get_rect().width < 30.0f && pmod > 1)
		{
			num2 = pmod2;
		}
		num = linesLengths[linesLengths.Count() - 1] + (int)(chars[i]->GetComponent<SpriteRenderer>()->get_sprite()->get_rect().width * smod) + num2;
		int num3 = 0;
		for (int j = i; j < typed.Length(); j++)
		{
			if (typed[j] == u' ' || j == typed.Length() - 1)
			{
				num -= (int)(chars[i]->GetComponent<SpriteRenderer>()->get_sprite()->get_rect().width * smod) + num2;
				j = typed.Length();
				break;
			}
			num += (int)(chars[j]->GetComponent<SpriteRenderer>()->get_sprite()->get_rect().width * smod) + num2;
			num3++;
		}
		bool flag = true;
		if (num > maxWidth)
		{
			flag = newLine(i);
		}
		if (flag)
		{
			positionCharacter(chars[i], linesLengths[linesLengths.Count() - 1]);
			linesLengths[linesLengths.Count() - 1] += (int)(chars[i]->GetComponent<SpriteRenderer>()->get_sprite()->get_rect().width * smod) + num2;
			if (linesLengths[linesLengths.Count() - 1] > longestLine)
			{
				longestLine = linesLengths[linesLengths.Count() - 1];
			}
		}
		if (typed.Length() > i && typed[i] == u'^')
		{
			flag = newLine(i);
		}
	}
	for (int k = 0; k < linesBegins.Count(); k++)
	{
		int end = chars.Count();
		if (k + 1 < linesBegins.Count())
		{
			end = linesBegins[k + 1];
		}
		int line = linesLengths.Count() - k - 1;
		if (directionY == 1.0f)
		{
			line = k;
		}
		placeAndCenterLine(linesBegins[k], end, linesLengths[k], line);
	}
	if (black == nullptr)
	{
		createBlack();
	}
	float num4 = Mathf::Floor(black->GetComponent<SpriteRenderer>()->get_sprite()->get_rect().width);
	float num5 = Mathf::Floor(black->GetComponent<SpriteRenderer>()->get_sprite()->get_rect().height);
	float num6 = (float)longestLine;
	float num7 = (float)(linesLengths.Count() * lineHeight);
	if (num6 / 2.0f == Mathf::Floor(num6 / 2.0f))
	{
		num6++;
	}
	num6 += 3.0f;
	num7 = (currentHeight = num7 + 2.0f);
	black->transform->set_localScale(Vector3(num6 / num4, num7 / num5, 1.0f));
	float num8 = 1.0f;
	if (center)
	{
		num8 = 0.0f;
	}
	float num9 = 1.0f;
	if (directionY == 1.0f)
	{
		num9 = -1.0f;
	}
	float num10 = 0.0f;
	if (directionY == 1.0f)
	{
		num10 = 10.0f;
	}
	Vector3 vector = coords(Vector2(num8 * (num6 / 2.0f - 2.0f), num9 * num7 / 2.0f - 3.0f + num10));
	black->transform->set_position(Vector3(vector.x, vector.y, black->transform->get_position().z));
	black->GetComponent<SpriteRenderer>()->set_color(Color(bgred, bggreen, bgblue, bgalpha));
}

bool TextFieldController::newLine(int num, int extraChars)
{
	linesBegins.Add(num);
	linesLengths.Add(0);
	if (maxLines > 0 && linesBegins.Count() > maxLines)
	{
		int num2 = 0;
		if (typed.Substring(num, 1).Equals(S("^")))
		{
			num2 = 1;
		}
		remains = typed.Substring(num + num2);
		if (queued.Length() > 1)
		{
			remains += queued.Substring(1);
		}
		while (chars.Count() > num)
		{
			Object::Destroy(chars[chars.Count() - 1]);
			typed = typed.Remove(chars.Count() - 1, 1);
			chars.RemoveAt(chars.Count() - 1);
		}
		queued = String::Empty;
		return false;
	}
	return true;
}

void TextFieldController::positionCharacter(P<GameObject> ch, int lx)
{
	Vector2 vector = ScreenControler::gameToScreen(Vector2((float)lx * 1.0f, 0.0f));
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(Vector3(vector.x, vector.y, -1.0f));
	position.z = -2.0f;
	ch->transform->set_position(position);
}

void TextFieldController::placeAndCenterLine(int start, int end, int lineLength, int line)
{
	float num = 0.0f;
	if (center)
	{
		num = 1.0f;
	}
	Vector2 vectorToChange = Vector2((float)lineLength * 0.5f * num, (float)(-lineHeight * line));
	vectorToChange = ScreenControler::gameToScreen(vectorToChange);
	Vector3 position = Vector3(vectorToChange.x, vectorToChange.y, 0.0f);
	position = Camera::get_main()->ScreenToWorldPoint(position);
	for (int i = start; i < end; i++)
	{
		chars[i]->transform->set_position(Vector3(chars[i]->transform->get_position().x - position.x, -1.0f * directionY * (chars[i]->transform->get_position().y - position.y), -0.1f));
	}
}
