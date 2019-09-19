#include "Halfedge.h"

namespace geometry
{
	Halfedge::Halfedge(vec3& pos, Loop* loop)
		:_vertex(new Vertex(pos,this)), _next(nullptr), _prev(nullptr), _loop(loop)
	{
	}

	Halfedge::~Halfedge()
	{
		delete _vertex;
	}

}
