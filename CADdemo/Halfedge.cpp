#include "Halfedge.h"

namespace geometry
{
	Halfedge::Halfedge(Loop* lp, Vertex* v)
		:_vertex(v), _next(nullptr), _prev(nullptr), _loop(lp)
	{
	}

	Halfedge* Halfedge::insertListAfter(Halfedge* he1, Halfedge* he2)
	{
		if (he2 == nullptr) he2 = he1;
		auto* q = this->_next;
		this->_next = he1;
		he1->_prev = this;
		he2->_next = q;
		q->_prev = he2;
		return he2;
	}

	Halfedge* Halfedge::insertListBefore(Halfedge* he1, Halfedge* he2)
	{
		if (he2 == nullptr) he2 = he1;
		auto* q = this->_prev;
		this->_prev = he2;
		he2->_next = this;
		he1->_prev = q;
		q->_next = he1;
		return he1;
	}

	Halfedge* Halfedge::setCircleWith(Halfedge* he)
	{
		this->_next = he;
		this->_prev = he;
		he->_next = this;
		he->_prev = this;
		return this;
	}

	Halfedge* Halfedge::linkAfter(Halfedge* he)
	{
		auto* p = this->_next;
		this->_next = he;
		he->_prev = this;
		return p;
	}

	Halfedge* Halfedge::findForward(Vertex* aim)
	{
		if (this->_vertex == aim) return this;
		for (auto* p = this->_next; p != this; p = p->_next)
		{
			if (p->_vertex == aim) return p;
		}
		return nullptr;
	}

	Halfedge* Halfedge::findBackward(Vertex* aim)
	{
		if (this->_vertex == aim) return this;
		for (auto* p = this->_prev; p != this; p = p->_prev)
		{
			if (p->_vertex == aim) return p;
		}
		return nullptr;
	}

	const bool Halfedge::existLoop(Vertex* aim) const
	{
		for (auto* p = this->_next; p->_vertex != aim; p = p->_next)
		{
			if (p->_vertex == _vertex) return true;
		}
		return false;
	}

	void Halfedge::printCheck() const
	{
		_vertex->travelOutput(0);
		std::cout << " -> ";
		this->getNext()->getVertex()->travelOutput(0);
		std::cout << std::endl;
	}

	void Halfedge::travelOutput(int x) const
	{
		//std::cout << "  |--Face " << x << ':' << std::endl;
		//std::cout << "  |    |--Loop " << x << ':' << std::endl;
		std::cout << "  |    |    |--Halfedge " << x << ": ";
		_vertex->travelOutput(0);
		if (_next != nullptr && _next!=this)
		{
			std::cout << " -> ";
			_next->_vertex->travelOutput(0);
		}
		std::cout << std::endl;
	}


}
