#include "../game_all.h"

ScreenControler::ScreenControler()
{
}

void ScreenControler::_cctor()
{
	allowedResolutions = Array<Vector2>::Of({
		Vector2(1920.0f, 1080.0f),
		Vector2(1680.0f, 945.0f),
		Vector2(1600.0f, 900.0f),
		Vector2(1440.0f, 810.0f),
		Vector2(1366.0f, 768.0f),
		Vector2(1280.0f, 720.0f),
		Vector2(1200.0f, 675.0f),
		Vector2(1152.0f, 648.0f),
		Vector2(1024.0f, 576.0f),
		Vector2(960.0f, 540.0f),
		Vector2(480.0f, 270.0f)
	});
}

Vector2 ScreenControler::getResolution()
{
	Vector2 result = Vector2(0.0f, 0.0f);
	Resolution currentResolution = Screen::get_currentResolution();
	result.x = (float)currentResolution.get_width();
	result.y = (float)currentResolution.get_height();
	return result;
}

Array<Resolution> ScreenControler::getResolutions()
{
	resolutions = Screen::get_resolutions();
	return resolutions;
}

Vector2 ScreenControler::getHighestResolution()
{
	getResolutions();
	return Vector2((float)resolutions[resolutions.Length() - 1].get_width(), (float)resolutions[resolutions.Length() - 1].get_height());
}

Vector2 ScreenControler::getHighestWindowResolution()
{
	getResolutions();
	int width = Screen::get_currentResolution().get_width();
	for (int i = 0; i < allowedResolutions.Length(); i++)
	{
		if ((float)width > allowedResolutions[i].x)
		{
			return Vector2(allowedResolutions[i].x, allowedResolutions[i].y);
		}
	}
	return Vector2(-1.0f, -1.0f);
}

void ScreenControler::setFullScreenResolution()
{
	Vector2 highestResolution = getHighestResolution();
	PlayerPrefs::SetInt(S("fullscreen"), 1);
	PlayerPrefs::SetInt(S("resolution"), (int)highestResolution.x);
	PlayerPrefs::Save();
	Screen::SetResolution((int)highestResolution.x, (int)highestResolution.y, true);
}

void ScreenControler::setWindowedResolution(int width)
{
	getResolutions();
	for (int i = 0; i < allowedResolutions.Length(); i++)
	{
		if ((float)width == allowedResolutions[i].x)
		{
			PlayerPrefs::SetInt(S("fullscreen"), 0);
			PlayerPrefs::SetInt(S("resolution"), (int)allowedResolutions[i].x);
			PlayerPrefs::Save();
			Screen::SetResolution((int)allowedResolutions[i].x, (int)allowedResolutions[i].y, false);
		}
	}
}

void ScreenControler::setSavedResolution()
{
	Vector2 highestResolution = getHighestResolution();
	if (PlayerPrefs::HasKey(S("fullscreen")))
	{
		if (PlayerPrefs::GetInt(S("fullscreen")) == 1)
		{
			setFullScreenResolution();
		}
		else
		{
			setWindowedResolution(PlayerPrefs::GetInt(S("resolution")));
		}
	}
	else
	{
		PlayerPrefs::SetInt(S("resolution"), 1920);
		PlayerPrefs::SetInt(S("fullscreen"), 1);
		setFullScreenResolution();
	}
}

float ScreenControler::distance(Vector2 a, Vector2 b)
{
	return Mathf::Sqrt(Mathf::Pow(a.x - b.x, 2.0f) + Mathf::Pow(a.y - b.y, 2.0f));
}

Vector2 ScreenControler::getScale()
{
	// Vita port: memoized. Dust particles call this four times each per frame; same inputs give the same result.
	static bool known = false; static int kw, kh, ksw, ksh; static float krw, krh; static Vector2 last;
	int w = Screen::get_width(), h = Screen::get_height();
	if (known && w == kw && h == kh && sourceWidth == ksw && sourceHeight == ksh && ratioWidth == krw && ratioHeight == krh) return last;
	Vector2 vector;
	vector.x = Mathf::Floor((float)sourceWidth * ((float)w * ratioWidth / (float)sourceWidth));
	vector.y = Mathf::Floor((float)sourceHeight * ((float)h * ratioHeight / (float)sourceHeight));
	last = Vector2((float)w * ratioWidth / vector.x * ((float)w * ratioWidth / (float)sourceWidth), (float)h * ratioHeight / vector.y * ((float)h * ratioHeight / (float)sourceHeight));
	known = true; kw = w; kh = h; ksw = sourceWidth; ksh = sourceHeight; krw = ratioWidth; krh = ratioHeight;
	return last;
}

Vector2 ScreenControler::gameToScreen(Vector2 vectorToChange)
{
	Vector2 result;
	result.x = Mathf::Floor(vectorToChange.x) * getScale().x + shiftRatioX;
	result.y = Mathf::Floor(vectorToChange.y) * getScale().y + shiftRatioY;
	return result;
}

Vector2 ScreenControler::gameToScreen2(Vector2 vectorToChange)
{
	Vector2 result;
	result.x = Mathf::Round(vectorToChange.x) * getScale().x + shiftRatioX;
	result.y = Mathf::Floor(vectorToChange.y) * getScale().y + shiftRatioY;
	return result;
}

Vector2 ScreenControler::screenToGame(Vector2 vectorToChange)
{
	Vector2 result;
	result.x = (vectorToChange.x - shiftRatioX) / getScale().x;
	result.y = (vectorToChange.y - shiftRatioY) / getScale().y;
	return result;
}

Vector2 ScreenControler::screenToGame2(Vector2 vectorToChange)
{
	Vector2 result;
	result.x = vectorToChange.x / getScale().x - shiftX;
	result.y = vectorToChange.y / getScale().y - shiftY;
	return result;
}

Vector3 ScreenControler::roundToNearestFullPixelOld(Vector3 vectorToChange)
{
	Vector3 result;
	result.x = vectorToChange.x;
	result.y = vectorToChange.y;
	result.z = vectorToChange.z;
	float x = getScale().x;
	float x2 = getScale().x;
	result.x = Mathf::Round(result.x / x) * x;
	result.y = Mathf::Round(result.y / x2) * x2;
	return result;
}

Vector3 ScreenControler::roundToNearestFullPixel(Vector3 vectorToChange)
{
	Vector3 result = screenToGame(Camera::get_main()->WorldToScreenPoint(vectorToChange));
	result.z = vectorToChange.z;
	result.x = Mathf::Floor(result.x);
	result.y = Mathf::Floor(result.y);
	return result;
}

Vector3 ScreenControler::roundToNearestFullPixel2(Vector3 vectorToChange)
{
	vectorToChange = Camera::get_main()->WorldToScreenPoint(vectorToChange);
	Vector2 tmp;
	tmp.x = vectorToChange.x;
	tmp.y = vectorToChange.y;
	Vector2 vector = gameToScreen(screenToGame(tmp));
	Vector3 position;
	position.x = vector.x;
	position.y = vector.y;
	position.z = vectorToChange.z;
	return Camera::get_main()->ScreenToWorldPoint(position);
}

Vector3 ScreenControler::roundToNearestFullPixel3(Vector3 vectorToChange)
{
	vectorToChange = Camera::get_main()->WorldToScreenPoint(vectorToChange);
	Vector2 tmp;
	tmp.x = vectorToChange.x;
	tmp.y = vectorToChange.y;
	Vector2 vector = gameToScreen2(screenToGame(tmp));
	Vector3 position;
	position.x = vector.x;
	position.y = vector.y;
	position.z = vectorToChange.z;
	return Camera::get_main()->ScreenToWorldPoint(position);
}
