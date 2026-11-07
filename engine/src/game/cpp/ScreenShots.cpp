#include "../game_all.h"

String ScreenShots::ScreenShotName(int width, int height)
{
	return Application::get_persistentDataPath() + S("/screen.png");
}

void ScreenShots::Awake()
{
	if (ss == nullptr)
	{
		Object::DontDestroyOnLoad(gameObject);
		ss = this;
	}
	else if (ss != P<ScreenShots>(this))
	{
		Object::Destroy(gameObject);
	}
}

void ScreenShots::Start()
{
}

P<Sprite> ScreenShots::getSprite(String name, bool big)
{
	String text = Application::get_persistentDataPath() + S("/") + name;
	if (camera == nullptr)
	{
		camera = GameObject::Find(S("Main Camera"))->GetComponent<Camera>();
	}
	int num;
	int num2;
	if (big)
	{
		num = bigHeight;
		num2 = bigWidth;
		text += S("_b.png");
	}
	else
	{
		num = smallHeight;
		num2 = smallWidth;
		text += S("_s.png");
	}
	Array<uint8_t> array;
	try
	{
		array = File::ReadAllBytes(text);
	}
	catch (...)
	{
		array = nullptr;
	}
	if (array != nullptr)
	{
		P<Texture2D> texture2D = P<Texture2D>(new Texture2D(73, 73));
		ImageConversion::LoadImage(texture2D, array);
		texture2D->set_filterMode(FilterMode::Point);
		return Sprite::Create(texture2D, Rect(0.0f, 0.0f, (float)num2, (float)num), Vector2(0.0f, 1.0f), 108.0f);
	}
	if (big)
	{
		return Resources::Load<Sprite>(S("Bitmaps/Misc/save_b"));
	}
	return Resources::Load<Sprite>(S("Bitmaps/Misc/save_s"));
}

void ScreenShots::shot()
{
	takeShot = true;
	takeShotNOW = String::Empty;
}

void ScreenShots::shotAndSave(String path)
{
	takeShot = true;
	takeShotNOW = path;
}

void ScreenShots::saveShots(String name)
{
	String path = Application::get_persistentDataPath() + S("/") + name + S("_s.png");
	File::WriteAllBytes(path, small);
	path = Application::get_persistentDataPath() + S("/") + name + S("_b.png");
	File::WriteAllBytes(path, big);
}

void ScreenShots::LateUpdate()
{
	takeShot |= Input::GetKeyDown(KeyCode::K);
	if (takeShot)
	{
		if (camera == nullptr)
		{
			camera = GameObject::Find(S("Main Camera"))->GetComponent<Camera>();
		}
		int cullingMask = camera->get_cullingMask();
		CurtainController::cc->gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
		int num = (int)((float)bigHeight * (1.0f / camera->get_rect().height));
		int num2 = (int)((float)bigWidth * (1.0f / camera->get_rect().width));
		P<RenderTexture> renderTexture = P<RenderTexture>(new RenderTexture(num2, num, 24));
		camera->set_targetTexture(renderTexture);
		P<Texture2D> texture2D = P<Texture2D>(new Texture2D(bigWidth, bigHeight, TextureFormat::RGB24, false));
		camera->Render();
		RenderTexture::set_active(renderTexture);
		MonoBehaviour::print(S("CAMERA RECT") + ENGINE_TODO_V("camera.rect.ToString()", String::Empty));
		float num3 = (float)num2;
		float num4 = (float)num;
		num3 *= camera->get_rect().x * 1.0f;
		num4 *= camera->get_rect().y * 1.0f;
		num3 = Mathf::Round(num3);
		num4 = Mathf::Round(num4);
		MonoBehaviour::print(S("xshift ") + num3 + S(" ,  yshift ") + num4);
		texture2D->ReadPixels(Rect((float)(int)num3, (float)(int)num4, (float)num2, (float)num), 0, 0);
		camera->set_targetTexture(nullptr);
		RenderTexture::set_active(nullptr);
		Object::Destroy(renderTexture);
		big = ImageConversion::EncodeToPNG(texture2D);
		num = (int)((float)smallHeight * (1.0f / camera->get_rect().height));
		num2 = (int)((float)smallWidth * (1.0f / camera->get_rect().width));
		num3 = (float)num2;
		num4 = (float)num;
		num3 *= camera->get_rect().x * 1.0f;
		num4 *= camera->get_rect().y * 1.0f;
		num3 = Mathf::Round(num3);
		num4 = Mathf::Round(num4);
		renderTexture = P<RenderTexture>(new RenderTexture(num2, num, 24));
		camera->set_targetTexture(renderTexture);
		texture2D = P<Texture2D>(new Texture2D(smallWidth, smallHeight, TextureFormat::RGB24, false));
		camera->Render();
		RenderTexture::set_active(renderTexture);
		texture2D->ReadPixels(Rect((float)(int)num3, (float)(int)num4, (float)num2, (float)num), 0, 0);
		camera->set_targetTexture(nullptr);
		RenderTexture::set_active(nullptr);
		Object::Destroy(renderTexture);
		small = ImageConversion::EncodeToPNG(texture2D);
		camera->set_cullingMask(cullingMask);
		CurtainController::cc->gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		takeShot = false;
		if (takeShotNOW != String::Empty)
		{
			saveShots(takeShotNOW);
			takeShotNOW = String::Empty;
		}
	}
}
