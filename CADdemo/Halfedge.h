#pragma once
#include "item.h"
#include"geometry.h"
#include"set"
//#include"Vertex.h"

namespace geometry
{
	//class Halfedge;
	//using HegIt = std::list<Halfedge>::iterator;

	class Halfedge :public item
	{
	private:
		Halfedge* _next;
		Halfedge* _prev;
		Loop* _loop;
		Vertex* _vertex;
		Edge* _edge;
	public:
		Halfedge(Loop* lp, Vertex* v);
		
		Halfedge* insertListAfter(Halfedge* he1, Halfedge* he2 = nullptr); //this->he1->...->he2->next
		Halfedge* insertListBefore(Halfedge* he1, Halfedge* he2 = nullptr); //prev->he1->...->he2->this
		//Halfedge* setCircleWith(Halfedge* he); //set: this->he->this
		Halfedge* linkAfter(Halfedge* he); //set: this->he

		Halfedge* extractSelf();

		Halfedge* findForward(Vertex* aim);
		Halfedge* findBackward(Vertex* aim);
		const bool existLoop(Vertex* aim) const;

		void printCheck() const;
		virtual void travelOutput(int x) const;
		virtual const GeoType getType() const { return HALFEDGE; }
		Loop* getLoop() const { return _loop; }
		Halfedge* getNext() const { return _next; }
		Halfedge* getPrev() const { return _prev; }
		Vertex* getVertex() const { return _vertex; }
		Edge* getEdge() const { return _edge; }
		Halfedge* getTwin() const;
		void setLoop(Loop* lp) { _loop = lp; }
		void setNext(Halfedge* he) { _next = he; }
		void setEdge(Edge* e) { _edge = e; }
	};
}

