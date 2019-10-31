#pragma once
#include"geometry.h"

namespace geometry
{
	class ItemManager
	{
	private:
		std::vector<Solid*> _solid;
		std::vector<Vertex*> _vertex;
	public:
		ItemManager() { _solid.clear(); }
		void travelOutput() const;

		const bool addVertex(vec3 pos);
		Vertex* v(int i) const { return _vertex[i]; }
		//Solid* operator[](int i) { return _solid[i]; }
		Solid* kvfs(Vertex* v);
		inline const int getVtxNum() const { return _vertex.size(); }
		inline const int getSldNum() const { return _solid.size(); }

		void drawFrame();
		void drawFace();

		void makeWithoutSweeping();
		void makeWithSweeping();
		void multiHandle();

		void addPlaneShape(std::vector<int> id);
		void addHole(int i, std::vector<int> id);
		void sweepPlaneShape(int i, vec3 dir);
		
	};
}


