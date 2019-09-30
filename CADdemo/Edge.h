#pragma once
#include"item.h"
#include"geometry.h"
namespace geometry
{
	//class Edge;
	//using EdgIt = std::list<Edge>::iterator;

	class Edge
	{
	private:
		Halfedge* _he1;
		Halfedge* _he2;
	public:
		Halfedge* getFirst() const { return _he1; }
		Halfedge* getSecond() const { return _he2; }
		//Edge(Vertex* v1, Vertex* v2);
	};
}


