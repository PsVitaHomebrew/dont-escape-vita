#include "../game_all.h"

void SiderealPCInternet::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_internet_app");
	range = 8000.0f;
	teleport = true;
	updateState();
}

void SiderealPCInternet::Update()
{
}

void SiderealPCInternet::whatOnClick()
{
}

void SiderealPCInternet::clickAction()
{
	beeper->beep();
	if (!GameDataController::gd->getObjective(S("sidereal_internet_displayed")))
	{
		PlayerController::pc->setBusy(true);
		Invoke(S("makeItSo"), Random::Range(0.25f, 1.0f));
	}
	else
	{
		Invoke(S("makeItSo2"), Random::Range(0.15f, 0.25f));
	}
}

void SiderealPCInternet::makeItSo2()
{
	GameDataController::gd->setObjective(S("sidereal_internet_displayed"), false);
	PlayerController::pc->setBusy(false);
	updateAll();
}

void SiderealPCInternet::makeItSo()
{
	PlayerController::pc->setBusy(false);
	GameDataController::gd->setObjective(S("sidereal_internet_displayed"), true);
	updateAll();
}

void SiderealPCInternet::updateState()
{
	if (GameDataController::gd->getObjective(S("sidereal_email_displayed")))
	{
		caption->hide();
		spriter->set_sprite(icon);
		setCollider(-1);
		txt->hide();
		iconCaption->manualUpdate();
	}
	else if (!GameDataController::gd->getObjective(S("sidereal_internet_displayed")))
	{
		caption->hide();
		spriter->set_sprite(icon);
		setCollider(1);
		txt->hide();
		iconCaption->manualUpdate();
		objectName = S("sidereal_internet_app");
	}
	else
	{
		caption->manualUpdate();
		spriter->set_sprite(window);
		setCollider(0);
		txt->manualUpdate();
		objectName = S("sidereal_x_app");
		iconCaption->manualUpdate();
	}
}

void SiderealPCInternet::clickAction2()
{
}

void SiderealPCInternet::clickAction0()
{
}
