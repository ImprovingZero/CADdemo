#pragma once
#include"geometry.h"

namespace geometry
{
	class ItemManager
	{
	private:
		std::vector<Solid*> _solid;
		//std::vector<Point> _point;
		std::vector<Vertex*> _vertex;
	public:
		ItemManager() { _solid.clear(); }
		void travelOutput() const;

		const bool addVertex(vec3 pos);
		Vertex* v(int i) const { return _vertex[i]; }
		//Solid* operator[](int i) { return _solid[i]; }
		Solid* kvfs(Vertex* v);

		void makeWithoutSweeping();
		void makeWithSweeping();
		
	};
}


