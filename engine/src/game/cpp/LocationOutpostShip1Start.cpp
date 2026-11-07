#include "../game_all.h"

void LocationOutpostShip1Start::Start()
{
	PlayerController::wc->shadow->fadeRateV = 0.0f;
	PlayerController::wc->shadow->fadeRateH = 0.002f;
	PlayerController::wc->shadowOffsetY = -1;
	PlayerController::wc->shadow->skewFactor = 40.0f;
	PlayerController::wc->shadow->skewFactor2 = 0.0f;
	PlayerController::wc->shadow->startAlpha = 0.0f;
	PlayerController::wc->shadow->source = 60.0f;
	PlayerController::ssg->setStepType2(StepSoundGenerator::METAL, AudioReverbPreset::Hangar);
	PlayerController::wc->shadow->scaleFactor = 0.6f;
	PlayerController::wc->shadow->downwards = true;
	PlayerController::wc->speed = PlayerController::wc->MAX_SPEED;
	PlayerController::wc->GetComponent<Animator>()->set_speed(1.0f);
	PlayerController::pc->copySettingsToNPCs();
	clambino = false;
	PlayerController::pc->allowDrop = false;
	if (!GameDataController::gd->getObjective(S("visited_ship1")))
	{
		Vector3 color = GingerActionController::getColor();
		P<TextFieldController> component = GameObject::Find(S("Ginger"))->GetComponent<TextFieldController>();
		List<P<DialogueLine>> list = List<P<DialogueLine>>::New();
		DialogueController::dc->initDialogue(list, S("ship_enter_intro"), PlayerController::pc->textField, Vector3(1.0f, 1.0f, 1.0f), component, color);
		for (int i = 0; i < list.Count() - 1; i++)
		{
			Timeline::t->addDialogue(list[i]);
		}
		Timeline::t->addDialogue(list[list.Count() - 1]);
	}
	GameDataController::gd->setObjective(S("visited_ship1"), true);
	JukeboxMusic::jb->changeMusic(SoundsManagerController::sm->music_explore_6a);
	JukeboxAmbient::jb->changeAmbient(SoundsManagerController::sm->pc_noise, 1.0f);
}

void LocationOutpostShip1Start::Update()
{
	float num = modX;
	num += (120.0f - PlayerController::wc->currentXY.x) * 0.005f;
	if (clambino)
	{
		num = -0.01f;
		modY = 0.0f;
	}
	playerShadow->transform->set_position(PlayerController::pc->transform->get_position());
	playerShadow->transform->set_position(Vector3(PlayerController::pc->transform->get_position().x + num, PlayerController::pc->transform->get_position().y + modY, -0.8f));
	playerShadow->transform->set_position(ScreenControler::roundToNearestFullPixel2(playerShadow->transform->get_position()));
	playerShadow->set_sprite(PlayerController::wc->sr->get_sprite());
	playerShadow->set_flipX(PlayerController::wc->sr->get_flipX());
}
