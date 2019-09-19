#include "Vertex.h"
namespace geometry
{
	Vertex::Vertex(vec3 p, Halfedge* halfedge)
		:_halfedge(halfedge), _pos(p), _next(nullptr), _prev(nullptr) 
	{

	}

	Vertex::~Vertex()
	{

	}
}