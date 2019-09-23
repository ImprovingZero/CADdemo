#include "Loop.h"
namespace geometry
{
	Loop::Loop(vec3& pos, Face* face)
		:_halfedge(new Halfedge(pos,this)), _next(nullptr), _prev(nullptr), _face(face)
	{
	}

	Loop::~Loop()
	{
		for (auto p = _halfedge; p != nullptr; p=p->getNext())
		{
			auto q = p->getPrev();
			if (q != nullptr) delete q;
		}
	}
	Halfedge* Loop::insertAfter(Halfedge* e, Halfedge* a)
	{
		e->setNext(a->getNext());
		a->setNext(a->getNext());
		e->getNext()->setPrev(e);
		e->setPrev(a);
		return e;
	}
	Halfedge* Loop::insertAfter(Halfedge* e, Vertex* v)
	{
		Halfedge* a = findHalfedge(v);
		insertAfter(e, a);
		return e;
	}
}
