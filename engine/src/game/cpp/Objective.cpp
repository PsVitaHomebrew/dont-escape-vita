#include "../game_all.h"

Objective::Objective()
{
}

Objective::Objective(String _id, bool _state, int _detail)
{
	id = _id;
	state = _state;
	detail = _detail;
}
