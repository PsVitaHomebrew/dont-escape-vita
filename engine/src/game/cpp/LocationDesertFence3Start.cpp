#include "../game_all.h"

void LocationDesertFence3Start::Start()
{
	alpha = 1.0f;
	PlayerController::wc->shadow->fadeRateV = 0.01f;
	PlayerController::wc->shadow->fadeRateH = 0.0f;
	PlayerController::wc->shadowOffsetY = 2;
	PlayerController::wc->shadow->skewFactor = 0.0f;
	PlayerController::wc->shadow->skewFactor2 = 4.0f;
	PlayerController::wc->shadow->startAlpha = 0.5f;
	PlayerController::wc->shadow->scaleFactor = 0.75f;
	PlayerController::wc->shadow->downwards = false;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::wc->shadow->source = 0.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::DIRT, AudioReverbPreset::Off);
	PlayerController::pc->copySettingsToNPCs();
	JukeboxMusic::jb->changeMusic(nullptr);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->ambient_wind_3, 1.0f);
	hammer = ItemsManager::im->getItem(S("sledgehammer"));
}

void LocationDesertFence3Start::showDropHint(String param)
{
	ExamineSprite::es->textField->shift.x = 10.0f;
	ExamineSprite::es->textField->shift.y = -30.0f;
	ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::gui, S("tutorial_drop_item")) }), 100, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f);
	ExamineSprite::es->show(dropHint);
}

void LocationDesertFence3Start::Update()
{
	Vector3 vector = Vector3(PlayerController::wc->currentXY.x, 0.0f, PlayerController::pc->transform->get_position().z);
	if ((hammer->dataRef->droppedLocation == S("inventory") && PlayerController::wc->currentXY.x >= 135.0f) || (hammer->dataRef->droppedLocation != S("inventory") && hammer->dataRef->locX >= 135))
	{
		hammer->groundSprite = hammerDown2;
	}
	else
	{
		hammer->groundSprite = hammerDown;
	}
	if (GameDataController::gd->getItemData(S("sledgehammer"))->droppedLocation == S("inventory"))
	{
		proc = (vector.x - (float)ScreenControler::sourceWidth * 0.6f) / ((float)ScreenControler::sourceWidth * 0.6f);
		if (PlayerController::wc->currentXY.x > 190.0f)
		{
			PlayerController::wc->currentXY.x = 189.0f;
			PlayerController::wc->fullStop(true);
			P<TimelineAction> timelineAction = New<TimelineAction>(PlayerController::pc->textField);
			timelineAction->text = GameStrings::getString(GameStrings::actions, S("tutorial_quicksands"));
			timelineAction->function = [this](String param) { showDropHint(param); };
			Timeline::t->addAction(timelineAction);
		}
	}
	else
	{
		proc -= 0.015f * Mathf::Abs(previous - PlayerController::wc->currentXY.x);
		if (!GameDataController::gd->getObjective(S("tutorial_tab")))
		{
			GameDataController::gd->setObjective(S("tutorial_tab"), true);
			P<TimelineAction> timelineAction2 = New<TimelineAction>(GameObject::Find(S("BottomText"))->GetComponent<TextFieldController>());
			timelineAction2->text = GameStrings::getString(GameStrings::actions, S("tutorial_tab"));
			timelineAction2->textWidth = 200;
			Timeline::t->addAction(timelineAction2);
		}
	}
	if (vector.x < (float)ScreenControler::sourceWidth * 0.6f || proc < 0.0f)
	{
		vector.x = (float)ScreenControler::sourceWidth * 0.6f;
		PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 1.0f;
		thePiasekB->set_sprite(sand1B);
		thePiasek->set_sprite(sand1);
	}
	else
	{
		vector.y = PlayerController::wc->currentXY.y;
		vector.y += 5.0f + proc * 20.0f;
		if (proc > 0.15f)
		{
			thePiasek->set_sprite(sand4);
		}
		else if (proc > 0.1f)
		{
			thePiasek->set_sprite(sand3);
		}
		else if (proc > 0.05f)
		{
			thePiasek->set_sprite(sand2);
		}
		else
		{
			thePiasek->set_sprite(sand1);
		}
		if (proc > 0.15f)
		{
			thePiasekB->set_sprite(sand4B);
		}
		else if (proc > 0.1f)
		{
			thePiasekB->set_sprite(sand3B);
		}
		else if (proc > 0.05f)
		{
			thePiasekB->set_sprite(sand2B);
		}
		else
		{
			thePiasekB->set_sprite(sand1B);
		}
		if (proc > 0.15f)
		{
			PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.5f;
		}
		else if (proc > 0.1f)
		{
			PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.6f;
		}
		else if (proc > 0.05f)
		{
			PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.75f;
		}
		else if (proc > 0.0f)
		{
			PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 0.9f;
		}
		else
		{
			PlayerController::wc->speed = PlayerController::wc->MAX_SPEED * 1.0f;
		}
	}
	Vector3 position = Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(vector));
	position.z = PlayerController::pc->transform->get_position().z - 0.005f;
	thePiasek->gameObject->transform->set_position(position);
	vector.y += 2.0f;
	position = Camera::get_main()->ScreenToWorldPoint(ScreenControler::gameToScreen(vector));
	position.z = PlayerController::pc->transform->get_position().z + 0.005f;
	thePiasekB->gameObject->transform->set_position(position);
	previous = PlayerController::wc->currentXY.x;
}
