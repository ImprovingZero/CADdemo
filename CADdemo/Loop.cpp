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

	Loop* Loop::mev(Vertex* v, Vertex* nv)
	{
		auto he1 = new Halfedge(this, v);
		auto he2 = new Halfedge(this, nv);
		he1->setCircleWith(he2);
		
		if (_halfedge->getNext() == nullptr ||_halfedge->getNext()==_halfedge)
		{
			//std::cout << "enter here!!" << std::endl;
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

	Loop* Loop::splitLoop(Halfedge* l, Halfedge* r)
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
	{
		Halfedge* p = _halfedge->findForward(v1);
		//nessesary to clean circle on v1 side:
		while (p->existLoop(v2)) p = p->getNext()->findForward(v1);
		Halfedge* q = p->findForward(v2);


		std::unordered_set<Vertex*> s(0);
		for (auto* i = p; i != q;)
		{
			auto* Next = i->getNext();
			if (s.find(i->getVertex()) != s.end())
			{
				auto* s = p->findForward(i->getVertex());
				auto* t = q->findBackward(i->getVertex());
				Next = t->getNext();
				if (s!=q->findForward(i->getVertex())) moveLoop(p, q, s, t);
			}
			else s.insert(i->getVertex());
			i = Next;
		}
		Loop* lp = splitLoop(p, q);
		Face* ret = new Face(_face->getSolid(), lp);
		
		if (_face->getNext() == nullptr)
		{
			_face->setCircleWith(ret);
		}
		else _face->insertListAfter(ret);
		

		return ret;
	}

	Loop* Loop::kemr(Vertex* v1, Vertex* v2)
	{
		auto* he1 = _halfedge->findForward(v1);
		while (he1->getNext()->getVertex() != v2) he1 = he1->getNext()->findForward(v1);
		auto* he2 = _halfedge->findForward(v2);
		while (he2->getNext()->getVertex() != v1) he2 = he2->getNext()->findForward(v2);

		Loop* lp = splitLoop(he1, he2);
		
		if (_next == nullptr)
		{
			setCircleWith(lp);
		}
		else insertListAfter(lp);
		auto* temp = he1->getPrev();
		he1->printCheck();
		temp->printCheck();
		lp->eraseList(temp, he1);
		temp = he2->getPrev();
		this->eraseList(temp, he2);
		return lp;
	}

	Loop* Loop::insertListAfter(Loop* a, Loop* b)
	{
		if (b == nullptr) b = a;
		auto* q = this->_next;
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
		this->_prev = b;
		b->_next = this;
		a->_prev = q;
		q->_next = a;
		return a;
	}

	Loop* Loop::setCircleWith(Loop* a)
	{
		this->_next = a;
		this->_prev = a;
		a->_next = this;
		a->_prev = this;
		return this;
	}

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
		l->printCheck();
		r->printCheck();
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
