#include "Edge.h"

namespace geometry
{
	Edge::Edge(Solid* s, Halfedge* he1, Halfedge* he2)
		:_solid(s), _he1(he1), _he2(he2),
		_prev(nullptr), _next(nullptr)
	{
		_he1->setEdge(this);
		_he2->setEdge(this);
		s->addEdge(this);
		_v1 = he1->getVertex();
		_v2 = he2->getVertex();
		//if(he1->getNext()!=nullptr) printCheck();
	}

	Edge::~Edge()
	{
		//std::cout << "Edge::~Edge" << this << std::endl;
		_prev->setNext(_next);
		_next->setPrev(_prev);
		_he1->setEdge(nullptr);
		_he2->setEdge(nullptr);
		if (_next == nullptr || _next == this)
		{
			//std::cout << "Edge::~Edge::No Edge" << std::endl;
			_solid->setEdge(nullptr);
			return;
		}
		if (_solid->getFirstEdge() == this)
		{
			//std::cout << "Edge::~Edge::Is This" << std::endl;
			_solid->setEdge(_next);
		}
	}

	Edge* Edge::insertListAfter(Edge* a, Edge* b)
	{
		if (b == nullptr) b = a;
		auto* q = this->_next;
		if (q == nullptr) q = this;
		this->_next = a;
		a->_prev = this;
		b->_next = q;
		q->_prev = b;
		return b;
	}

	Edge* Edge::insertListBefore(Edge* a, Edge* b)
	{
		if (b == nullptr) b = a;
		auto* q = this->_prev;
		if (q == nullptr) q = this;
		this->_prev = b;
		b->_next = this;
		a->_prev = q;
		q->_next = a;
		return a;
	}

	Edge* Edge::linkAfter(Edge* a)
	{
		auto* p = this->_next;
		this->_next = a;
		a->_prev = this;
		return p;
	}

	void Edge::delSelf()
	{
		//std::cout << "EDGE::delSelf::";
		//_v1->travelOutput(0);
		//_v2->travelOutput(0);
		//std::cout << std::endl;
		this->~Edge();
	}

	void Edge::printCheck() const
	{
		auto* v1 = _he1->getVertex();
		auto* v2 = _he2->getVertex();
		std::cout << this << ' ';
		//if (v1 != _v1 && v1!= _v2) std::cout << "WARRNING!!!!" << std::endl;
		_v1->travelOutput(0);
		_v2->travelOutput(0);
		std::cout << std::endl;
	}
	void Edge::draw()
	{
		glColor3f(1, 0, 0);
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex3f(_v1->x(), _v1->y(), _v1->z());
		glVertex3f(_v2->x(), _v2->y(), _v2->z());
		glEnd();
	}
}


