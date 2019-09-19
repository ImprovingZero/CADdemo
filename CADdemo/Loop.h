#pragma once
#include"item.h"
#include"geometry.h"
namespace geometry
{
	//class Loop;
	//using LopIt = std::list<Loop>::iterator;

	class Loop
	{
	private:
		Loop* _next;
		Loop* _prev;
		Face* _face;
		Halfedge* _halfedge;
	public:
		Loop(vec3& pos, Face* face);
		~Loop();

		virtual const GeoType getType() const { return LOOP; }
		Face* getFace() const { return _face; }
		Loop* getNext() const { return _next; }
		Loop* getPrev() const { return _prev; }
		Halfedge* getFirstVertex() const { return _halfedge; }
	};
}


