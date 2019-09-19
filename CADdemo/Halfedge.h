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
		Halfedge(vec3& pos, Loop* loop);
		~Halfedge();
		//Halfedge(Vertex& pos);

		virtual const GeoType getType() const { return HALFEDGE; }
		Loop* getLoop() const { return _loop; }
		Halfedge* getNext() const { return _next; }
		Halfedge* getPrev() const { return _prev; }
		Vertex* getFirstVertex() const { return _vertex; }
	};
}

