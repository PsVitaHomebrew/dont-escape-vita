#include "../game_all.h"

void ObjectZController::Start()
{
}

void ObjectZController::Update()
{
	// Vita port: the original lines with fewer temporary references (this runs on every dust mote every frame)
	Transform* own = gameObject->transform.get();
	if (!own || !own->_parent) throwNull();
	Transform* up = own->_parent;
	if (parentObject.get() != up->gameObject.get()) parentObject = up->gameObject;
	Transform* pt = parentObject->transform.get();
	if (!pt) throwNull();
	Vector3 pp = pt->get_position(), op = own->get_position();
	Vector3 vector2 = Camera::get_main()->WorldToScreenPoint(op);
	Vector2 vectorToChange = ScreenControler::screenToGame(Vector2(vector2.x, vector2.y));
	float z = 1.0f + (0.0f - vectorToChange.y) / (float)ScreenControler::sourceHeight;
	z *= -1.0f;
	aa = vector2.y;
	bb = vectorToChange.y;
	cc = z;
	vec1 = pp;
	vec2 = op;
	vec3 = op + pp;
	pt->set_position(Vector3(pp.x, pp.y, z));
}
