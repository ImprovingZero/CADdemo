#pragma once
#include"item.h"
#include"geometry.h"
//#include"Halfedge.h"
namespace geometry
{
	//class Vertex;
	//using VtxIt = std::list<Vertex>::iterator;

	class Vertex:public item
	{
	private:
		//int _id;
		vec3 _pos;
		Halfedge* _halfedge;
		Vertex* _next;
		Vertex* _prev;
	public:
		Vertex(vec3 p, Halfedge* halfedge);
		~Vertex();

		virtual const GeoType getType() const { return VERTEX; }
		inline const float operator[](int i) const
		{
			if (i < 0 || i>2) { std::cout << "VERTEX ERROR::INDEX OUTRANGE" << std::endl; return 0; }
			else return _pos[i];
		}
		Halfedge* getHalfedge() const { return _halfedge; }
		Vertex* getNext() const { return _next; }
		Vertex* getPrev() const { return _prev; }
		Vertex* setAfter(Vertex v);
	};
}

