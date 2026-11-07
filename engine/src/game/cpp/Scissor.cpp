#include "../game_all.h"

void Scissor::SetScissorRect(P<Camera> cam, Rect r)
{
	if (r.x < 0.0f)
	{
		r.width += r.x;
		r.x = 0.0f;
	}
	if (r.y < 0.0f)
	{
		r.height += r.y;
		r.y = 0.0f;
	}
	r.width = Mathf::Min(1.0f - r.x, r.width);
	r.height = Mathf::Min(1.0f - r.y, r.height);
	cam->set_rect(Rect(0.0f, 0.0f, 1.0f, 1.0f));
	cam->ResetProjectionMatrix();
	Matrix4x4 projectionMatrix = cam->get_projectionMatrix();
	cam->set_rect(r);
	Matrix4x4 matrix4x = Matrix4x4::TRS(Vector3(r.x, r.y, 0.0f), Quaternion::get_identity(), Vector3(r.width, r.height, 1.0f));
	Matrix4x4 matrix4x2 = Matrix4x4::TRS(Vector3(1.0f / r.width - 1.0f, 1.0f / r.height - 1.0f, 0.0f), Quaternion::get_identity(), Vector3(1.0f / r.width, 1.0f / r.height, 1.0f));
	Matrix4x4 matrix4x3 = Matrix4x4::TRS(Vector3((0.0f - r.x) * 2.0f / r.width, (0.0f - r.y) * 2.0f / r.height, 0.0f), Quaternion::get_identity(), Vector3::get_one());
	cam->set_projectionMatrix(matrix4x3 * matrix4x2 * projectionMatrix);
}

void Scissor::OnPreRender()
{
	SetScissorRect(GetComponent<Camera>(), scissorRect);
}
