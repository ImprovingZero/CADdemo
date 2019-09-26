#pragma once
#include "item.h"
#include"geometry.h"
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
	public:
		Halfedge(Loop* lp, Vertex* v);
		//Halfedge(Vertex& pos);

		Halfedge* setAfter(Halfedge* he); //set:  he->this
		Halfedge* setBefore(Halfedge* he); //set: this->he
		Halfedge* setCircleWith(Halfedge* he); //set: this->he->this

		virtual void travelOutput(int x) const;
		virtual const GeoType getType() const { return HALFEDGE; }
		Loop* getLoop() const { return _loop; }
		Halfedge* getNext() const { return _next; }
		Halfedge* getPrev() const { return _prev; }
		Vertex* getVertex() const { return _vertex; }
	};
}

