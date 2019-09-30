#include "Loop.h"
namespace geometry
{
	Loop::Loop(Face* face, Vertex* v)
		:_face(face),_next(nullptr),_prev(nullptr)
	{
		_halfedge = new Halfedge(this, v);
	}

	Loop::Loop(Face* face, Halfedge* he)
		:_face(face),_halfedge(he),_next(nullptr),_prev(nullptr)
	{
	}

	Loop::~Loop()
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
		if (_face->getFirstLoop() == this)
			_face->setLoop(_next);

		if (_halfedge != nullptr) _halfedge->getPrev()->setNext(nullptr);
		while (_halfedge != nullptr)
		{
			auto* he = _halfedge;
			_halfedge = _halfedge->getNext();
			delete he;
		}
	}

	Loop* Loop::extrude(vec3 dir)
	{
		auto* he = _halfedge;
		auto* end = he->getVertex();
		auto* firstV = new Vertex(he->getVertex()->getPos() + dir);
		auto* next = he->getNext();
		mev(he->getVertex(), firstV);
		he = next;
		auto* prevV = firstV;

		bool first = 1;
		while (he->getVertex() != end)
		{
			auto* newV = new Vertex(he->getVertex()->getPos() + dir);
			next = he->getNext();
			mev(he->getVertex(), newV);
			mef(newV, prevV)->travelOutput(0);
			prevV = newV;
			he = next;
		}
		mef(firstV,prevV)->travelOutput(0);
		
		return this;
	}

	Loop* Loop::mev(Vertex* v, Vertex* nv)
	{
		auto he1 = new Halfedge(this, v);
		auto he2 = new Halfedge(this, nv);
		he1->insertListAfter(he2);
		//he1->setCircleWith(he2);
		
		if (_halfedge->getNext() == nullptr ||_halfedge->getNext()==_halfedge)
		{
			delete _halfedge;
			_halfedge = he1;
			return this;
		}
		
		bool f = 0;
		int find = 0;
		Halfedge* p = _halfedge;
		for (; p != nullptr && (f == 0 || p != _halfedge); p = p->getNext())
		{
			f = 1;
			if (p->getNext()->getVertex() == v) break;
		}
		p->insertListAfter(he1, he2);
		return this;
	}

	void Loop::moveLoop(Halfedge* p, Halfedge* q, Halfedge* s, Halfedge* t)
	{
		auto* l = s->getPrev();
		auto* r = t;
		t = t->getPrev();
		l->linkAfter(r);
		auto* f = q->findForward(s->getVertex());
		f->getPrev()->insertListAfter(s, t);
	}

	Loop* Loop::splitLoop(Halfedge* l, Halfedge* r) //new loop direction: r -> l
	{
		auto* lend = r->getPrev();
		auto* rend = l->getPrev();
		rend->linkAfter(r);
		lend->linkAfter(l);
		rend->insertListAfter(new Halfedge(this, l->getVertex()));
		lend->insertListAfter(new Halfedge(this, r->getVertex()));
		_halfedge = r;
		Loop* lp = new Loop(_face, l);
		for (auto* p = lp->getFirstHalfedge(); p->getLoop() != lp; p = p->getNext())
		{
			p->setLoop(lp);
		}
		return lp;
	}

	Face* Loop::mef(Vertex* v1, Vertex* v2) 
		//new face direction: v1 -> v2
		//exist face direction: v2 -> v1
	{
		std::swap(v1, v2);
		Halfedge* p = _halfedge->findForward(v1);
		//nessesary to clean circle on v1 side:
		while (p->existLoop(v2)) p = p->getNext()->findForward(v1);
		Halfedge* q = p->findForward(v2);


		std::unordered_set<Vertex*> S(0);
		for (auto* i = p; i != q;)
		{
			auto* Next = i->getNext();
			if (S.find(i->getVertex()) != S.end())
			{
				auto* s = p->findForward(i->getVertex());
				auto* t = q->findBackward(i->getVertex());
				Next = t->getNext();
				if (s!=q->findForward(i->getVertex())) moveLoop(p, q, s, t);
			}
			else S.insert(i->getVertex());
			i = Next;
		}
		Loop* lp = splitLoop(p, q);
		Face* ret = new Face(_face->getSolid(), lp);
		ret->getFirstLoop()->setFace(ret);
		
		_face->insertListAfter(ret);
		
		return ret;
	}

	Loop* Loop::kemr(Vertex* v1, Vertex* v2)
	{
		auto* he1 = _halfedge->findForward(v1);
		while (he1->getNext()->getVertex() != v2) he1 = he1->getNext()->findForward(v1);
		auto* he2 = _halfedge->findForward(v2);
		while (he2->getNext()->getVertex() != v1) he2 = he2->getNext()->findForward(v2);

		Loop* lp = splitLoop(he1, he2);
		
		insertListAfter(lp);
		auto* temp = he1->getPrev();
		
		lp->eraseList(temp, he1);
		temp = he2->getPrev();
		this->eraseList(temp, he2);
		return lp;
	}

	Loop* Loop::insertListAfter(Loop* a, Loop* b)
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

	Loop* Loop::insertListBefore(Loop* a, Loop* b)
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
	Loop* Loop::setCircleWith(Loop* a)
	{
		this->_next = a;
		this->_prev = a;
		a->_next = this;
		a->_prev = this;
		return this;
	}
	*/

	Loop* Loop::linkAfter(Loop* a)
	{
		auto* p = this->_next;
		this->_next = a;
		a->_prev = this;
		return p;
	}

	void Loop::extractSelf()
	{
		this->_prev->_next = this->_next;
		this->_next->_prev = this->_prev;
	}

	void Loop::eraseList(Halfedge* a, Halfedge* b)
	{
		if (b == nullptr) b = a;
		if (a->getLoop() != this || b->getLoop() != this)
		{
			std::cout << "ERROR::LOOP::REASELIST::NOT_THIS_LOOP" << std::endl;
			return;
		}
		auto* l = a->getPrev();
		auto* r = b->getNext();

		l->linkAfter(r);
		a->getLoop()->setFirstHalfedge(l);
		
		auto* p = a;
		while (p != b)
		{
			auto* temp = p->getNext();
			delete p;
			p = temp;
		}
		delete p;
		
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

	Halfedge* Loop::operator[](int i) const
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
