#include "Halfedge.h"

namespace geometry
{
	Halfedge::Halfedge(Loop* lp, Vertex* v)
		:_vertex(v), _next(nullptr), _prev(nullptr), _loop(lp)
	{
	}

	Halfedge* Halfedge::setAfter(Halfedge* he)
	{
		//set: he->this (->next)
		Halfedge* next = he->_next;
		next->_prev = this;
		this->_next = next;
		this->_prev = he;
		he->_next = this;
		return this;
	}

	Halfedge* Halfedge::setBefore(Halfedge* he)
	{
		//set: (prev->) this->he
		Halfedge* prev = he->_prev;
		prev->_next = this;
		this->_prev = prev;
		this->_next = he;
		he->_prev = this;
		return this;
		
	}

	Halfedge* Halfedge::setCircleWith(Halfedge* he)
	{
		this->_next = he;
		this->_prev = he;
		he->_next = this;
		he->_prev = this;
		return this;
	}

	void Halfedge::travelOutput(int x) const
	{
		//std::cout << "  |--Face " << x << ':' << std::endl;
		//std::cout << "  |    |--Loop " << x << ':' << std::endl;
		std::cout << "  |    |    |--Halfedge " << x << ": ";
		_vertex->travelOutput(0);
		if (_next != nullptr)
		{
			std::cout << " -> ";
			_next->_vertex->travelOutput(0);
		}
		std::cout << std::endl;
	}


}
