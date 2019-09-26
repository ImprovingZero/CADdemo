#pragma once
#include"item.h"
#include"geometry.h"
//#include"Halfedge.h"
namespace geometry
{
	class Vertex:public item
	{
	private:
		//int _id;
		vec3 _pos;
		//Point* _point;
		//Halfedge* _halfedge;
		//Vertex* _next;
		//Vertex* _prev;
	public:
		Vertex(vec3 p) :_pos(p) {};

		virtual void travelOutput(int x) const;
		virtual const GeoType getType() const { return VERTEX; }
		inline const float operator[](int i) const
		{
			if (i < 0 || i>2) { std::cout << "VERTEX ERROR::INDEX OUTRANGE" << std::endl; return 0; }
			else return _pos[i];
		}
		const vec3 setPos(vec3 pos) { _pos = pos; return pos; }
		const vec3 getPos() const { return _pos; }
		/*
		Vertex* getNext() const { return _next; }
		Vertex* getPrev() const { return _prev; }
		*/
	};
}

