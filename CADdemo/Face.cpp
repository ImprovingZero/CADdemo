#include "Face.h"

namespace geometry
{
	Face::Face(Solid* solid, Vertex* v)
		:_loop(new Loop(this,v)), _next(nullptr), _prev(nullptr),_solid(solid)
	{
	}
	void Face::travelOutput(int x) const
	{
		std::cout << "  |--Face " << x << ':' << std::endl;
		int i = 0;
		auto p = _loop;
		if (p == nullptr) return;
		do
		{
			p->travelOutput(i);
			i++;
			p = p->getNext();
		} while (p != _loop && p!=nullptr);
	}
	inline Loop* Face::operator[](int i) const
	{
		auto* ret = _loop;
		while (i > 0)
		{
			if (ret == nullptr) return ret;
			ret = ret->getNext();
			i--;
		}
		return ret;
	}
}
