#pragma once
#include"item.h"
#include"geometry.h"
#include<unordered_set>
namespace geometry
{
	//class Loop;
	//using LopIt = std::list<Loop>::iterator;

	class Loop
	{
	private:
		Loop* _next;
		Loop* _prev;
		Face* _face;
		Halfedge* _halfedge;

		void moveLoop(Halfedge* p, Halfedge* q, Halfedge* s, Halfedge* t);
		Loop* splitLoop(Halfedge* l, Halfedge* r);

	public:
		Loop(Face* face, Vertex* v);
		Loop(Face* face, Halfedge* he);
		~Loop();

		Loop* extrude(vec3 dir);

		Loop* mev(Vertex* v, Vertex* nv);
		Face* mef(Vertex* v1, Vertex* v2);
		Loop* kemr(Vertex* v1, Vertex* v2);

		Loop* insertListAfter(Loop* a, Loop* b = nullptr); //this->he1->...->he2->next
		Loop* insertListBefore(Loop* a, Loop* b = nullptr); //prev->he1->...->he2->this
		//Loop* setCircleWith(Loop* a); //set: this->he->this
		Loop* linkAfter(Loop* a); //set: this->he
		void extractSelf(); //erase this
		void eraseList(Halfedge* a, Halfedge* b=nullptr);

		virtual void travelOutput(int x) const;
		virtual const GeoType getType() const { return LOOP; }
		Face* getFace() const { return _face; }
		Loop* getNext() const { return _next; }
		Loop* getPrev() const { return _prev; }
		Halfedge* getFirstHalfedge() const { return _halfedge; }
		void setFace(Face* f) { _face = f; }
		void setFirstHalfedge(Halfedge* a) { _halfedge = a; };
		void setNext(Loop* lp) { _next = lp; }
		
		Halfedge* operator[](int i) const;
	};
}


