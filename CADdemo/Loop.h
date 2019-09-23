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
		Halfedge* getHalfedge() const { return _halfedge; }

		Loop* mev(Vertex* v1, vec3 pos);

		Halfedge* insertAfter(Halfedge* e, Halfedge* a);
		Halfedge* insertAfter(Halfedge* e, Vertex* v);
		Halfedge* insertBefore(Halfedge* e, Halfedge* b);
		Halfedge* insertBefore(Halfedge* e, Vertex* v);
		Vertex* findVertex(vec3 pos);
		Halfedge* findHalfedge(vec3 pos);
		Halfedge* findHalfedge(Vertex* v);
		void erase(Vertex* v);
		void erase(Halfedge* e);
		Loop* seperate();
		Loop* combine(Loop* lp);
	};
}


