#pragma once
#include"item.h"
#include"geometry.h"
namespace geometry
{
	//class Solid;
	//using SldIt = std::list<Solid>::iterator;

	class Solid
	{
	private:
		Solid* _next;
		Solid* _prev;
		Face* _face;
		Edge* _edge;
		Face* _faceDown;
	public:
		Solid(Vertex* v);

		virtual void travelOutput(int i) const;
		void travelFrame() const;
		void addEdge(Edge* e1);

		virtual const GeoType getType() const { return SOLID; }
		//Solid* getFace() const { return _solid; }
		Solid* getNext() const { return _next; }
		Solid* getPrev() const { return _prev; }
		Face* getFirstFace() const { return _face; }
		Edge* getFirstEdge() const { return _edge; }
		Face* operator[](int i) const;
		void setFace(Face* f) { _face = f; }
		void setEdge(Edge* e) { _edge = e; }
		void setFaceDown(Face* f) { _faceDown = f; }
		Face* getFaceDown() { return _faceDown; }

		void drawFace();
		void drawFrame();
	};

}

