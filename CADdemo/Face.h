#pragma once
#include"item.h"
#include"geometry.h"
namespace geometry
{
	//class Face;
	//using FacIt = std::list<Face>::iterator;

	class Face
	{
	private:
		Face* _next;
		Face* _prev;
		Solid* _solid;
		Loop* _loop;
	public:
		Face(Solid* sd, Vertex* v);

		virtual void travelOutput(int x) const;
		virtual const GeoType getType() const { return FACE; }
		Solid* getSolid() const { return _solid; }
		Face* getNext() const { return _next; }
		Face* getPrev() const { return _prev; }
		Loop* getFirstLoop() const { return _loop; }
		Loop* operator[](int i) const;
	};

}

