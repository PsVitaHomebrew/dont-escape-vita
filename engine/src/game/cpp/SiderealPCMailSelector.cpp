#include "../game_all.h"

void SiderealPCMailSelector::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("stop");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("sidereal_mail");
	range = 8000.0f;
	teleport = true;
	updateState();
}

void SiderealPCMailSelector::Update()
{
}

void SiderealPCMailSelector::whatOnClick()
{
}

void SiderealPCMailSelector::clickAction()
{
	PlayerController::pc->setBusy(true);
	beeper->beep();
	Invoke(S("makeItSo"), Random::Range(0.25f, 1.0f));
}

void SiderealPCMailSelector::makeItSo()
{
	PlayerController::pc->setBusy(false);
	GameDataController::gd->setObjectiveDetail(S("sidereal_email_displayed"), mailNumber);
	GameDataController::gd->setObjectiveDetail(S("sidereal_email_page"), 1);
	if (mailNumber == 10)
	{
		caption->b = 111.0f;
		caption->r = 111.0f;
		caption->g = 111.0f;
		GameDataController::gd->setObjective(S("sidereal_read_last_mail"), true);
	}
	updateAll();
}

void SiderealPCMailSelector::updateState()
{
	if (!GameDataController::gd->getObjective(S("sidereal_email_displayed")))
	{
		MonoBehaviour::print(S("IM HIDING MAIL: ") + mailNumber);
		setCollider(-1);
		email->set_enabled(false);
		MHR->set_enabled(false);
		caption->hide();
		return;
	}
	MonoBehaviour::print(S("IM SHOWING MAIL: ") + mailNumber);
	email->set_enabled(true);
	MHR->set_enabled(true);
	if (mailNumber == GameDataController::gd->getObjectiveDetail(S("sidereal_email_displayed")))
	{
		setCollider(-1);
		caption->r = 255.0f;
		caption->g = 255.0f;
		caption->b = 255.0f;
		MHR->set_sprite(mailHighlight);
	}
	else
	{
		setCollider(0);
		if (mailNumber == 10 && !GameDataController::gd->getObjective(S("sidereal_read_last_mail")))
		{
			caption->b = 0.0f;
			caption->r = 0.0f;
			caption->g = 0.0f;
		}
		else
		{
			caption->r = 111.0f;
			caption->g = 111.0f;
			caption->b = 111.0f;
		}
	}
	caption->manualUpdate();
	email->nameToDisplay = S("sidereal_pc_email_") + GameDataController::gd->getObjectiveDetail(S("sidereal_email_displayed")) + S("_b_") + GameDataController::gd->getObjectiveDetail(S("sidereal_email_page"));
	email->manualUpdate();
}

void SiderealPCMailSelector::clickAction2()
{
}

void SiderealPCMailSelector::clickAction0()
{
}
