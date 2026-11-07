#include "../game_all.h"

void FusePiece::Start()
{
	dkvs = GameStrings::objects;
	objectName = S("fuse_piece");
	sr = gameObject->GetComponent<SpriteRenderer>();
	pg = gameObject->GetComponent<ParticleGenerator>();
	sprites = Resources::LoadAll<Sprite>(S("Bitmaps/Locations/Outpost/fusebox/buttons"));
	energized = false;
	checkedNow = false;
	updateNESW();
	updateView();
	updateEnergy();
}

void FusePiece::Update()
{
}

void FusePiece::updateNESW()
{
	n_now = N;
	e_now = E;
	w_now = W;
	s_now = S_;
	for (int i = 0; i < GameDataController::gd->getObjectiveDetail(S("outpost_fuse_") + coords_X + coords_Y); i++)
	{
		bool flag = n_now;
		n_now = w_now;
		w_now = s_now;
		s_now = e_now;
		e_now = flag;
	}
}

void FusePiece::updateView(bool slow)
{
	if (!slow)
	{
		updateView();
		return;
	}
	for (int i = 0; i < allPieces.Count(); i++)
	{
		if (allPieces[i] == P<FusePiece>(this))
		{
			Invoke(S("updateView"), 0.075f * (float)i);
			Invoke(S("pykSound"), 0.075f * (float)i);
		}
	}
}

void FusePiece::pykSound()
{
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->hose);
}

void FusePiece::updateView()
{
	String text = String::Empty;
	if (n_now)
	{
		text += S("N");
	}
	if (e_now)
	{
		text += S("E");
	}
	if (s_now)
	{
		text += S("S");
	}
	if (w_now)
	{
		text += S("W");
	}
	if (energized)
	{
		text += S("_L");
	}
	for (int i = 0; i < sprites.Length(); i++)
	{
		if (sprites[i]->get_name() == S("fuse_") + text)
		{
			sr->set_sprite(sprites[i]);
			break;
		}
	}
}

void FusePiece::updateEnergy(bool slow)
{
	for (int i = 0; i < allPieces.Count(); i++)
	{
		allPieces[i]->energized = false;
		allPieces[i]->checkedNow = false;
		allPieces[i]->updateView(slow);
	}
	if (first->w_now)
	{
		first->energizeThis();
	}
	if (!broken && doorish->energized)
	{
		GameDataController::gd->setObjective(S("outpost_door_powered"), true);
		updateAll();
	}
	else if (!doorish->energized)
	{
		GameDataController::gd->setObjective(S("outpost_door_powered"), false);
		updateAll();
	}
	if (!broken && last->energized && (GameDataController::gd->getObjectiveDetail(S("outpost_fuse_55")) == 2 || GameDataController::gd->getObjectiveDetail(S("outpost_fuse_55")) == 3))
	{
		GameDataController::gd->setObjective(S("outpost_elevator_powered"), true);
		updateAll();
	}
	else if (!last->energized)
	{
		GameDataController::gd->setObjective(S("outpost_elevator_powered"), false);
		updateAll();
	}
}

void FusePiece::energizeThis()
{
	energized = true;
	updateView();
	if (checkedNow || broken)
	{
		return;
	}
	checkedNow = true;
	if (breakers.Length() > 0)
	{
		for (int i = 0; i < breakers.Length(); i++)
		{
			if (n_now && (float)int_Parse(coords_X) == breakers[i].x && (float)(int_Parse(coords_Y) - 1) == breakers[i].y)
			{
				breakBoom(i);
			}
			else if (e_now && (float)(int_Parse(coords_X) + 1) == breakers[i].x && (float)int_Parse(coords_Y) == breakers[i].y)
			{
				breakBoom(i);
			}
			else if (s_now && (float)int_Parse(coords_X) == breakers[i].x && (float)(int_Parse(coords_Y) + 1) == breakers[i].y)
			{
				breakBoom(i);
			}
			else if (w_now && (float)(int_Parse(coords_X) - 1) == breakers[i].x && (float)int_Parse(coords_Y) == breakers[i].y)
			{
				breakBoom(i);
			}
		}
	}
	if (n_now && (bool)neighbour_n && neighbour_n->s_now)
	{
		neighbour_n->energizeThis();
	}
	if (e_now && (bool)neighbour_e && neighbour_e->w_now)
	{
		neighbour_e->energizeThis();
	}
	if (s_now && (bool)neighbour_s && neighbour_s->n_now)
	{
		neighbour_s->energizeThis();
	}
	if (w_now && (bool)neighbour_w && neighbour_w->e_now)
	{
		neighbour_w->energizeThis();
	}
	if (!broken)
	{
	}
}

void FusePiece::door()
{
}

void FusePiece::win()
{
}

void FusePiece::breakBoom(int whichone)
{
	PlayerController::pc->setBusy(true);
	breakersParts[whichone]->started = true;
	Invoke(S("stopZapBreak"), 1.2f);
	PlayerController::pc->aS->PlayOneShot(SoundsManagerController::sm->electric);
	Invoke(S("stopBreak"), 1.5f);
	Debug::LogWarning(S("BOOM"));
	broken = true;
	int num = 0;
	for (int i = 0; i < allPieces.Count(); i++)
	{
		if (allPieces[i]->energized)
		{
			num++;
		}
	}
	for (int j = 0; j < allPieces.Count(); j++)
	{
		Debug::LogWarning(S("BOOM ") + j);
		if (allPieces[j]->coords_Y == S("1"))
		{
			if (allPieces[j]->coords_X == S("1"))
			{
				GameDataController::gd->setObjectiveDetail(S("outpost_fuse_") + allPieces[j]->coords_X + allPieces[j]->coords_Y, 1);
			}
			else
			{
				GameDataController::gd->setObjectiveDetail(S("outpost_fuse_") + allPieces[j]->coords_X + allPieces[j]->coords_Y, Random::Range(0, 4));
			}
		}
		else
		{
			GameDataController::gd->setObjectiveDetail(S("outpost_fuse_") + allPieces[j]->coords_X + allPieces[j]->coords_Y, Random::Range(0, 4));
		}
		if (allPieces[j]->energized)
		{
			allPieces[j]->zap((float)(num - j) * 0.1f);
		}
	}
}

void FusePiece::stopZapBreak()
{
	for (int i = 0; i < breakersParts.Length(); i++)
	{
		breakersParts[i]->started = false;
		int num;
		for (num = 0; num < breakersParts[i]->particles.Count(); num++)
		{
			if (breakersParts[i]->particles[num] == nullptr)
			{
				breakersParts[i]->particles.RemoveAt(num);
				num--;
			}
			else
			{
				P<GameObject> obj = breakersParts[i]->particles[num]->get_gameObject();
				breakersParts[i]->particles.RemoveAt(num);
				Object::Destroy(obj);
				num--;
			}
		}
	}
}

void FusePiece::zap(float delay)
{
	Invoke(S("zapzap"), delay);
}

void FusePiece::zapzap()
{
	pg->started = true;
	Invoke(S("endZap"), 1.0f);
}

void FusePiece::stopBreak()
{
	broken = false;
	for (int i = 0; i < allPieces.Count(); i++)
	{
		allPieces[i]->energized = false;
		allPieces[i]->updateView();
	}
	for (int j = 0; j < allPieces.Count(); j++)
	{
		allPieces[j]->updateNESW();
	}
	updateEnergy(true);
	PlayerController::pc->say(GameStrings::getString(GameStrings::actions, S("fuse_short_circuit") + GameDataController::gd->getObjectiveDetail(S("outpost_fuse_short_circuit"))));
	if (GameDataController::gd->getObjectiveDetail(S("outpost_fuse_short_circuit")) < 3)
	{
		GameDataController::gd->setObjectiveDetail(S("outpost_fuse_short_circuit"), GameDataController::gd->getObjectiveDetail(S("outpost_fuse_short_circuit")) + 1);
	}
	else
	{
		GameDataController::gd->setObjectiveDetail(S("outpost_fuse_short_circuit"), 0);
	}
}

void FusePiece::endZap()
{
	pg->started = false;
	int num;
	for (num = 0; num < pg->particles.Count(); num++)
	{
		if (pg->particles[num] == nullptr)
		{
			pg->particles.RemoveAt(num);
			num--;
		}
		else
		{
			P<GameObject> obj = pg->particles[num]->get_gameObject();
			pg->particles.RemoveAt(num);
			Object::Destroy(obj);
			num--;
		}
	}
}

void FusePiece::updateState()
{
}

void FusePiece::clickAction0()
{
}

void FusePiece::rotate()
{
	pykSound();
	int objectiveDetail = GameDataController::gd->getObjectiveDetail(S("outpost_fuse_") + coords_X + coords_Y);
	objectiveDetail++;
	if (objectiveDetail >= 4)
	{
		objectiveDetail = 0;
	}
	GameDataController::gd->setObjectiveDetail(S("outpost_fuse_") + coords_X + coords_Y, objectiveDetail);
}

void FusePiece::clickAction()
{
	rotate();
	updateNESW();
	updateEnergy();
}

void FusePiece::clickAction2()
{
}
