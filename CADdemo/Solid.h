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
	public:
		Solid(vec3 &pos);
		~Solid();
		//Solid(Vertex& v);

		virtual const GeoType getType() const { return SOLID; }
		//Solid* getFace() const { return _solid; }
		Solid* getNext() const { return _next; }
		Solid* getPrev() const { return _prev; }
		Face* getFirstVertex() const { return _face; }
	};

}

