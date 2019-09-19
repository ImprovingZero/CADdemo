#include "ItemManager.h"
namespace geometry
{
	Solid* ItemManager::kvfs(vec3 pos)
	{

		return new Solid(pos);
	}
}
