#include "Solid.h"

namespace geometry
{
	Solid::Solid(vec3& pos)
		:_face(new Face(pos,this)),_next(nullptr),_prev(nullptr)
	{
	}

	/*
	Solid::Solid(Vertex& v)
		: _face(new Face(v,this)), _next(nullptr), _prev(nullptr)
	{
	}
	*/

	Solid::~Solid()
	{
		for (auto p = _face; p != nullptr; p = p->getNext())
		{
			auto q = p->getPrev();
			if (q != nullptr) delete q;
		}
	}
}
