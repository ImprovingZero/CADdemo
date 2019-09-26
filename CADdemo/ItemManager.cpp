#include "ItemManager.h"
namespace geometry
{
	void ItemManager::travelOutput() const
	{
		int i = 0;
		for (auto p : _solid) p->travelOutput(i++);

	}

	const bool ItemManager::addVertex(vec3 pos)
	{
		for (auto p : _vertex)
		{
			if (p->getPos() == pos) return false;
		}
		_vertex.push_back(new Vertex(pos));
		return true;
	}

	void ItemManager::tempRoutine()
	{
		auto* sld = this->kvfs(_vertex[0]);
		auto* fac = sld->getFirstFace();
		auto* lp = fac->getFirstLoop();
		lp->mev(_vertex[0], _vertex[1]);
		lp->mev(_vertex[1], _vertex[2]);
		lp->mev(_vertex[1], _vertex[3]);
		this->travelOutput();
	}

	Solid* ItemManager::kvfs(Vertex* v)
	{
		_solid.push_back(new Solid(v));
		return _solid.back();
	}
}
