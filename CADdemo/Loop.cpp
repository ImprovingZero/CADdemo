#include "Loop.h"
namespace geometry
{

	Loop::Loop(Face* face, Vertex* v)
		:_face(face),_next(nullptr),_prev(nullptr)
	{
		_halfedge = new Halfedge(this, v);
	}

	Loop* Loop::mev(Vertex* v, Vertex* nv)
	{
		auto he1 = new Halfedge(this, v);
		auto he2 = new Halfedge(this, nv);
		if (_halfedge->getNext() == nullptr)
		{
			delete _halfedge;
			_halfedge = he1;
			he1->setCircleWith(he2);
			return this;
		}

		bool f = 0;
		int find = 0;
		auto p = _halfedge;
		for (; f == 1 && p != _halfedge && p != nullptr; p = p->getNext())
		{
			f = 1;
			if (p->getVertex() == v) break;
		}
		auto q = p->getNext();
		he1->setAfter(p);
		he2->setBefore(q);
		return this;
	}

	void Loop::travelOutput(int x) const
	{
		//std::cout << "  |--Face " << x << ':' << std::endl;
		std::cout << "  |    |--Loop " << x << ':' << std::endl;
		int i = 0;
		auto p = _halfedge;
		if (p == nullptr) return;
		do
		{
			p->travelOutput(i);
			i++;
			p = p->getNext();
		} while (p != _halfedge && p != nullptr);
	}

	inline Halfedge* Loop::operator[](int i) const
	{
		auto* ret = _halfedge;
		while (i > 0)
		{
			if (ret == nullptr) return ret;
			ret = ret->getNext();
			i--;
		}
		return ret;
	}


}
