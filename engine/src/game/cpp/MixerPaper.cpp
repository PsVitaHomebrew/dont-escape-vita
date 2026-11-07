#include "../game_all.h"

void MixerPaper::Start()
{
	colliderManager->setTarget(gameObject);
	characterAnimationName = S("action_stnd_");
	animationFlip = false;
	useCurrentDirection = true;
	actionMarker = gameObject->transform->Find(S("Action_Marker"))->gameObject;
	dkvs = GameStrings::objects;
	objectName = S("mixer_note");
	range = 8000.0f;
	teleport = false;
	sr = gameObject->GetComponent<SpriteRenderer>();
	interactions = List<P<ItemInteraction>>::New();
	interactions.Add(New<ItemInteraction>(S("mixer_glass"), String::Empty, nullptr, String::Empty));
	interactions.Add(New<ItemInteraction>(S("pill_half"), String::Empty, nullptr, String::Empty));
	updateState();
}

void MixerPaper::Update()
{
}

void MixerPaper::whatOnClick()
{
}

void MixerPaper::clickAction()
{
	ExamineSprite::es->textField->shift.x = -115.0f;
	ExamineSprite::es->textField->shift.y = -23.0f;
	if (InventoryController::ic->isItemInInventory(S("mixer_pills_note")))
	{
		ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("mixer_pills")) }), 122, 62.0f / 255.0f, 58.0f / 255.0f, 28.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		ExamineSprite::es->show(sprite_1);
	}
	else if (InventoryController::ic->isItemInInventory(S("mixer_catalyst_note")))
	{
		ExamineSprite::es->readyText(List<String>::New({ GameStrings::getString(GameStrings::world_labels, S("mixer_catalyst")) }), 122, 62.0f / 255.0f, 58.0f / 255.0f, 28.0f / 255.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		ExamineSprite::es->show(sprite_2);
	}
	ExamineSprite::es->textField->shift.y = -23.0f;
}

void MixerPaper::updateState()
{
	if (InventoryController::ic->isItemInInventory(S("mixer_pills_note")) || InventoryController::ic->isItemInInventory(S("mixer_catalyst_note")))
	{
		sr->set_enabled(true);
		setCollider(0);
	}
	else
	{
		setCollider(-1);
		sr->set_enabled(false);
	}
}

void MixerPaper::clickAction2()
{
}

void MixerPaper::clickAction0()
{
}
