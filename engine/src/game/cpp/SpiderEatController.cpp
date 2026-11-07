#include "../game_all.h"

void SpiderEatController::Start()
{
	colliderManager->setTarget(gameObject);
	animationFlip = false;
	characterAnimationName = S("action_stnd_");
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("nasty_spider");
	updateState();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("hammer"), GameStrings::getString(GameStrings::actions, S("dont_attack_spider")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("rock"), GameStrings::getString(GameStrings::actions, S("dont_attack_spider")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("wrench"), GameStrings::getString(GameStrings::actions, S("dont_attack_spider")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pipe"), GameStrings::getString(GameStrings::actions, S("dont_attack_spider")), nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pest"), GameStrings::getString(GameStrings::actions, S("dont_attack_spider")), nullptr, String::Empty));
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	gameObject->GetComponent<Animator>()->Play(S("eat"));
	setCollider(0);
	updateState();
}

void SpiderEatController::Update()
{
}

void SpiderEatController::clickAction()
{
}

void SpiderEatController::whatOnClick0()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		PlayerController::pc->textField->viewText(GameStrings::getString(GameStrings::actions, S("nasty_spider_eating")), true);
		PlayerController::wc->fullStop(true);
	}
}

void SpiderEatController::updateState()
{
	if (GameDataController::gd->getCurrentDay() == 1 && GameDataController::gd->getObjectiveDetail(S("day_1_threat")) == 2 && !GameDataController::gd->getObjective(S("gasstation_spider_baited")))
	{
		setCollider(0);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(true);
		GameDataController::gd->setObjective(S("gasstation_spider_discovered"), true);
	}
	else
	{
		setCollider(-1);
		gameObject->GetComponent<SpriteRenderer>()->set_enabled(false);
	}
}

void SpiderEatController::clickAction2()
{
}

void SpiderEatController::clickAction0()
{
}
