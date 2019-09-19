#pragma once
#include"geometry.h"

namespace geometry
{
	class ItemManager
	{
	private:
		std::vector<Solid*> _solid;
	public:
		ItemManager() { _solid.clear(); }

		Solid* kvfs(vec3 pos);
		//const bool mvfs(Vertex* v);


	};
}


