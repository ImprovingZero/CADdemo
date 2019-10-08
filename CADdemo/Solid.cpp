#include "Solid.h"

namespace geometry
{
	Solid::Solid(Vertex* v)
		: _face(new Face(this,v)), _next(nullptr), _prev(nullptr),_edge(nullptr)
	{
	}

	void Solid::travelOutput(int x) const
	{
		std::cout << "Solid " << x << ':' << std::endl;
		int i = 0;
		auto p = _face;
		if (p == nullptr) return;
		do
		{
			p->travelOutput(i);
			i++;
			p = p->getNext();
		} while (p != _face && p!=nullptr);
	}

	void Solid::travelFrame() const
	{
		auto* e = _edge->getNext();
		if (_edge!=nullptr) _edge->printCheck();
		while (e != _edge && e!=nullptr)
		{
			e->printCheck();
			e = e->getNext();
		}
		std::cout << "travelFrame Done" << std::endl;
	}

	void Solid::addEdge(Edge* e)
	{
		if (_edge == nullptr)
		{
			_edge = e;
			e->setNext(e);
			e->setPrev(e);
		}
		else
		{
			e->setNext(_edge);
			e->setPrev(_edge->getPrev());
			_edge->getPrev()->setNext(e);
			_edge->setPrev(e);
			_edge = e;
		}
	}

	Face* Solid::operator[](int i) const
	{
		auto* ret = _face;
		while (i > 0)
		{
			if (ret == nullptr) return ret;
			ret = ret->getNext();
			i--;
		}
		return ret;
	}

}
