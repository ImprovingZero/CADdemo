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
		Solid* _solid;
		Edge* _prev;
		Edge* _next;
		Vertex* _v1;
		Vertex* _v2;

	public:
		Edge(Solid* s, Halfedge* he1, Halfedge* he2);
		~Edge();

		Edge* insertListAfter(Edge* a, Edge* b = nullptr); //this->e1->...->e2->next
		Edge* insertListBefore(Edge* a, Edge* b = nullptr); //prev->e1->...->e2->this
		Edge* linkAfter(Edge* a); //set: this->e
		void delSelf();

		void printCheck() const;
		Halfedge* getFirst() const { return _he1; }
		Halfedge* getSecond() const { return _he2; }
		Edge* getNext() const { return _next; }
		Edge* getPrev() const { return _prev; }
		void setNext(Edge* e) { _next = e; }
		void setPrev(Edge* e) { _prev = e; }
		Solid* getSolid() const { return _solid; }
		//Edge(Vertex* v1, Vertex* v2);

		void draw();
	};
}


