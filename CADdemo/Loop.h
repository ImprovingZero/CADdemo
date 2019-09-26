#pragma once
#include"item.h"
#include"geometry.h"
#include<unordered_set>
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

		void moveLoop(Halfedge* p, Halfedge* q, Halfedge* s, Halfedge* t);
		Loop* splitLoop(Halfedge* l, Halfedge* r);

	public:
		Loop(Face* face, Vertex* v);
		Loop(Face* face, Halfedge* he);

		Loop* mev(Vertex* v, Vertex* nv);
		Face* mef(Vertex* v1, Vertex* v2);

		virtual void travelOutput(int x) const;
		virtual const GeoType getType() const { return LOOP; }
		Face* getFace() const { return _face; }
		Loop* getNext() const { return _next; }
		Loop* getPrev() const { return _prev; }
		Halfedge* getFirstHalfedge() const { return _halfedge; }
		Halfedge* operator[](int i) const;
	};
}


