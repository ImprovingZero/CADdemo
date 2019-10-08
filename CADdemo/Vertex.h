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
		
		Vertex(vec3 p) :_pos(p) 
		{ 
			_glpos[0] = _pos[0]; 
			_glpos[1] = _pos[1];
			_glpos[2] = _pos[2];
		};
		~Vertex() {  };

		double _glpos[3];

		virtual void travelOutput(int x) const;
		virtual const GeoType getType() const { return VERTEX; }
		inline const float operator[](int i) const
		{
			if (i < 0 || i>2) { std::cout << "VERTEX ERROR::INDEX OUTRANGE" << std::endl; return 0; }
			else return _pos[i];
		}
		inline const float x() const { return _pos[0]; }
		inline const float y() const { return _pos[1]; }
		inline const float z() const { return _pos[2]; }
		const vec3 setPos(vec3 pos) { _pos = pos; return pos; }
		const vec3 getPos() const { return _pos; }
		//double* getGLPos() const { return (double*)_glpos; }
		
		/*
		Vertex* getNext() const { return _next; }
		Vertex* getPrev() const { return _prev; }
		*/
	};
}

