#include "Face.h"

namespace geometry
{
	Face::Face(Solid* solid, Vertex* v)
		:_loop(new Loop(this,v)), _next(nullptr), _prev(nullptr),_solid(solid)
	{
	}

	Face::Face(Solid* sd, Loop* lp)
		:_loop(lp), _solid(sd), _next(nullptr), _prev(nullptr)
	{
	}

	Face::~Face()
	{
		if (_next == _prev)
		{
			_next->_prev = nullptr;
			_prev->_next = nullptr;
		}
		else
		{
			_next->_prev = _prev;
			_prev->_next = _next;
		}
		if (_solid->getFirstFace() == this)
			_solid->setFace(_next);
		
		if (_loop != nullptr) _loop->getPrev()->setNext(nullptr);
		while (_loop != nullptr)
		{
			auto* lp = _loop;
			_loop = _loop->getNext();
			delete lp;
		}
	}

	Face* Face::kfmrh(Face* cf)
	{
		auto* lp = cf->getFirstLoop();
		if (lp == nullptr)
		{
			std::cout << "ERROR::FACE::KFMRH::cf has no loop" << std::endl;
			return nullptr;
		}
		while (lp!=nullptr && lp->getFace() != this)
		{
			lp->setFace(this);
			lp = lp->getNext();
		}
		lp = cf->getFirstLoop();
		_loop->insertListAfter(lp, lp->getPrev());
		cf->setLoop(nullptr);
		delete cf;
		return this;
	}

	Face* Face::insertListAfter(Face* a, Face* b)
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

	Face* Face::insertListBefore(Face* a, Face* b)
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

	/*
	Face* Face::setCircleWith(Face* a)
	{
		this->_next = a;
		this->_prev = a;
		a->_next = this;
		a->_prev = this;
		return this;
	}
	*/

	Face* Face::linkAfter(Face* a)
	{
		auto* p = this->_next;
		this->_next = a;
		a->_prev = this;
		return p;
	}

	void Face::travelOutput(int x) const
	{
		std::cout << "  |--Face " << x << ':' << this<<std::endl;
		int i = 0;
		auto p = _loop;
		if (p == nullptr) return;
		do
		{
			p->travelOutput(i);
			i++;
			p = p->getNext();
		} while (p != _loop && p!=nullptr);
	}

	Loop* Face::operator[](int i) const
	{
		auto* ret = _loop;
		while (i > 0)
		{
			if (ret == nullptr) return ret;
			ret = ret->getNext();
			i--;
		}
		return ret;
	}
}
