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
		Face(vec3& pos, Solid* solid);
		~Face();
		//Face(Vertex &v, Solid* solid);

		virtual const GeoType getType() const { return FACE; }
		Solid* getFace() const { return _solid; }
		Face* getNext() const { return _next; }
		Face* getPrev() const { return _prev; }
		Loop* getFirstVertex() const { return _loop; }
	};

}

