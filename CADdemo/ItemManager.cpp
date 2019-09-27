#include "ItemManager.h"
namespace geometry
{
	void ItemManager::travelOutput() const
	{
		int i = 0;
		for (auto p : _solid) p->travelOutput(i++);
		std::cout << "=======================================" << std::endl;

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
		
		/*
		lp->mev(_vertex[0], _vertex[1]);
		lp->mev(_vertex[1], _vertex[2]);
		lp->mev(_vertex[2], _vertex[3]);
		lp->mef(_vertex[3], _vertex[0]);

		lp->mev(_vertex[0], _vertex[4]);
		lp->mev(_vertex[1], _vertex[5]);
		lp->mev(_vertex[2], _vertex[6]);
		lp->mev(_vertex[3], _vertex[7]);

		lp->mef(_vertex[4], _vertex[5]);
		lp->mef(_vertex[5], _vertex[6]);
		lp->mef(_vertex[6], _vertex[7]);
		lp->mef(_vertex[7], _vertex[4]);
		*/

		lp->mev(_vertex[0], _vertex[1]);
		lp->mev(_vertex[1], _vertex[2]);
		lp->mev(_vertex[2], _vertex[3]);
		lp->mef(_vertex[3], _vertex[0]);

		lp->mev(_vertex[0], _vertex[4]);
		lp->mev(_vertex[4], _vertex[5]);
		lp->mev(_vertex[5], _vertex[6]);
		lp->mev(_vertex[6], _vertex[7]);
		lp->mef(_vertex[4], _vertex[7]);

		lp->kemr(_vertex[4], _vertex[0]);

		/*
		lp->mev(_vertex[0], _vertex[1]);
		lp->mev(_vertex[1], _vertex[2]);
		lp->mev(_vertex[2], _vertex[3]);
		lp->mev(_vertex[3], _vertex[4]);
		lp->mev(_vertex[3], _vertex[5]);
		lp->mev(_vertex[2], _vertex[6]);
		lp->mev(_vertex[6], _vertex[7]);
		lp->mev(_vertex[6], _vertex[8]);
		lp->mev(_vertex[8], _vertex[9]);
		lp->mev(_vertex[8], _vertex[10]);
		lp->mev(_vertex[0], _vertex[11]);
		lp->mef(_vertex[3], _vertex[8]);
		*/
		
		
		this->travelOutput();
	}

	Solid* ItemManager::kvfs(Vertex* v)
	{
		_solid.push_back(new Solid(v));
		return _solid.back();
	}
}
