#include "Face.h"

namespace geometry
{
	Face::Face(vec3& pos, Solid* solid)
		:_loop(new Loop(pos,this)), _next(nullptr), _prev(nullptr),_solid(solid)
	{
	}

	Face::~Face()
	{
		for (auto p = _loop; p != nullptr; p = p->getNext())
		{
			auto q = p->getPrev();
			if (q != nullptr) delete q;
		}
	}

}
