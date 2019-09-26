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
		std::cout << "--------" << std::endl;
		std::cout << v->getPos()[0] << std::endl;
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
		std::cout << "p: ";
		p->printCheck();

		//nessesary to clean circle on v1 side:
		while (p->existLoop(v2)) p = p->getNext()->findForward(v1);
		Halfedge* q = p->findForward(v2);

		std::cout << "q: ";
		q->printCheck();

		std::unordered_set<Vertex*> s(0);
		for (auto* i = p; i != q;)
		{
			auto* Next = i->getNext();
			if (s.find(i->getVertex()) != s.end())
			{
				auto* s = p->findForward(i->getVertex());
				auto* t = q->findBackward(i->getVertex());
				Next = t->getNext();
				moveLoop(p, q, s, t);
			}
			else s.insert(i->getVertex());
			i = Next;
		}
		std::cout << "p: ";
		p->printCheck();
		std::cout << "q: ";
		q->printCheck();
		Loop* lp = splitLoop(p, q);
		Face* ret = new Face(_face->getSolid(), lp);
		
		if (_face->getNext() == nullptr)
		{
			_face->setCircleWith(ret);
		}
		else _face->insertListAfter(ret);
		

		return ret;
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
