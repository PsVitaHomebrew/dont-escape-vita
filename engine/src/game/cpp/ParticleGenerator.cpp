#include "../game_all.h"
#include <map>

namespace engine { int sceneLoadCount(); }
// Vita port: finished particles are hidden and kept here per generator, then reused instead of building a new
// one from the prefab (Instantiate) every spawn. Entries of destroyed objects are dropped on each scene load.
static std::vector<P<GameObject>>& vitaParticlePool(int generatorId, bool glow) {
	static std::map<long long, std::vector<P<GameObject>>> pools; static int loads = -1;
	if (loads != engine::sceneLoadCount()) {
		for (auto it = pools.begin(); it != pools.end();) {
			auto& v = it->second; v.erase(std::remove_if(v.begin(), v.end(), [](const P<GameObject>& o) { return o == nullptr; }), v.end());
			it = v.empty() ? pools.erase(it) : std::next(it);
		}
		loads = engine::sceneLoadCount();
	}
	return pools[(long long)generatorId * 2 + (glow ? 1 : 0)];
}

void ParticleGenerator::Start()
{
	gameObject->transform->set_position(ScreenControler::roundToNearestFullPixel2(gameObject->transform->get_position()));
	index = 0;
}

void ParticleGenerator::Update()
{
	if (!started)
	{
		return;
	}
	if (currentDelay >= (float)delay)
	{
		delay = Random::Range(minDelayBetweeenParticles, maxDelayBetweeenParticles);
		currentDelay = 0.0f;
		int num = maxParticles;
		num = (int)Mathf::Round((float)maxParticles * 1.0f);
		if (particles.Count() < num)
		{
			P<GameObject> gameObject;
			bool reused = false;
			{
				auto& freeList = vitaParticlePool(_id, glow);
				while (!freeList.empty()) {
					P<GameObject> f = freeList.back(); freeList.pop_back();
					if (f != nullptr && !f->_pendingDestroy && f->transform->get_parent() == this->gameObject->transform) { gameObject = f; reused = true; break; }
				}
			}
			if (reused)
			{
				gameObject->transform->set_position(this->gameObject->transform->get_position());
			}
			else
			{
				gameObject = (glow ? (Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/ParticleGlow")), this->gameObject->transform->get_position(), Quaternion()).as<GameObject>()) : (Object::Instantiate(Resources::Load<GameObject>(S("Prefabs/Particle")), this->gameObject->transform->get_position(), Quaternion()).as<GameObject>()));
				gameObject->transform->set_parent(this->gameObject->transform);
			}
			P<ParticleController> component = gameObject->GetComponent<ParticleController>();
			component->speedXMax = speedXMax;
			component->speedYMax = speedYMax;
			component->speedXMin = speedXMin;
			component->speedYMin = speedYMin;
			component->fadeInStep = fadeInStep;
			component->fadeOutStep = fadeOutStep;
			component->minAlpha = minAlpha;
			component->maxAlpha = maxAlpha;
			component->globalized = useGlobalWind;
			Vector3 position = Vector3(gameObject->transform->get_position().x, gameObject->transform->get_position().y, gameObject->transform->get_position().z);
			position = Camera::get_main()->WorldToScreenPoint(position);
			component->currentXY = ScreenControler::screenToGame(Vector2(position.x, position.y));
			component->currentXY.x += xStart;
			component->currentXY.y += yStart;
			Vector3 position2 = Vector3(0.0f, zShift, 0.0f);
			gameObject->transform->Find(S("Z_Marker"))->transform->set_position(position2);
			component->currentXY.x += Random::Range((float)(-xSpread) / 2.0f, (float)xSpread / 2.0f);
			component->currentXY.y += Random::Range((float)(-ySpread) / 2.0f, (float)ySpread / 2.0f);
			component->lifetime = Random::Range(lifetimeMin, lifetimeMax);
			gameObject->GetComponent<SpriteRenderer>()->set_sprite(sprites[Random::Range(0, sprites.Length())]);
			gameObject->GetComponent<SpriteRenderer>()->set_color(Color(1.0f, 1.0f, 1.0f, 0.0f));
			if (reused)
			{
				// the fields a fresh copy of the prefab would have, then what ParticleController::Start does
				P<GameObject> tmpl = Resources::Load<GameObject>(glow ? S("Prefabs/ParticleGlow") : S("Prefabs/Particle"));
				P<ParticleController> d = tmpl != nullptr ? tmpl->GetComponent<ParticleController>() : nullptr;
				component->currentSpeedX = d != nullptr ? d->currentSpeedX : 0;
				component->currentSpeedY = d != nullptr ? d->currentSpeedY : 0;
				component->currentLifetime = d != nullptr ? d->currentLifetime : 0.0f;
				component->takeItEasy = d != nullptr ? d->takeItEasy : 0.0f;
				component->speedDiv = d != nullptr ? d->speedDiv : 10.0f;
				component->die = false;
				component->spriteR = gameObject->GetComponent<SpriteRenderer>();
				component->alpha = 0.0f;
				component->targetAlpha = Random::Range(component->minAlpha, component->maxAlpha);
				gameObject->SetActive(true);
			}
			particles.Add(gameObject);
		}
	}
	else
	{
		currentDelay += Time::get_deltaTime() * 60.0f;
	}
	for (int i = 0; i < particles.Count(); i++)
	{
		if (particles.Count() != 0)
		{
			if (particles[i] == nullptr)
			{
				particles.RemoveAt(i);
				i--;
				index = 0;
			}
			else if (particles[i]->GetComponent<ParticleController>()->die)
			{
				P<GameObject> obj = particles[i]->get_gameObject();
				particles.RemoveAt(i);
				obj->SetActive(false);
				vitaParticlePool(_id, glow).push_back(obj);
				i--;
				index = 0;
			}
		}
	}
}

void ParticleGenerator::removeParticles()
{
	for (int i = 0; i < particles.Count(); i++)
	{
		if (particles.Count() != 0)
		{
			if (particles[i] == nullptr)
			{
				particles.RemoveAt(i);
				i--;
				index = 0;
				continue;
			}
			particles[i]->GetComponent<ParticleController>()->die = true;
			P<GameObject> obj = particles[i]->get_gameObject();
			particles.RemoveAt(i);
			Object::Destroy(obj);
			i--;
			index = 0;
		}
	}
}
