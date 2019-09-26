#include "Solid.h"

namespace geometry
{
	Solid::Solid(Vertex* v)
		: _face(new Face(this,v)), _next(nullptr), _prev(nullptr)
	{

	}

	void Solid::travelOutput(int x) const
	{
		std::cout << "Solid " << x << ':' << std::endl;
		int i = 0;
		auto p = _face;
		if (p == nullptr) return;
		do
		{
			p->travelOutput(i);
			i++;
			p = p->getNext();
		} while (p != _face && p!=nullptr);
	}

	Face* Solid::operator[](int i) const
	{
		auto* ret = _face;
		while (i > 0)
		{
			if (ret == nullptr) return ret;
			ret = ret->getNext();
			i--;
		}
		return ret;
	}

}
