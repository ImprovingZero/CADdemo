#pragma once
#include"item.h"
#include"Halfedge.h"
namespace geometry
{
	class Vertex:public item
	{
	private:
		int _id;
		vec3 _pos;
		HegInd _halfedge;
	public:
		Vertex();  //default (0,0,0);
		Vertex(float x, float y, float z, int id = -1, HegInd hal = -1);
		Vertex(vec3 pos, int id = -1, HegInd hal = NULL);

		virtual const GeoType getType() const { return VERTEX; }
		inline const float operator[](int i) const
		{
			if (i < 0 || i>2) { std::cout << "VERTEX ERROR::INDEX OUTRANGE" << std::endl; return 0; }
			else return _pos[i];
		}
	};
}

