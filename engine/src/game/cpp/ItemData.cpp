#include "../game_all.h"

ItemData::ItemData()
{
}

ItemData::ItemData(String _id, String _droppedLocation, int _locX, int _locY)
{
	id = _id;
	droppedLocation = _droppedLocation;
	locX = _locX;
	locY = _locY;
}
