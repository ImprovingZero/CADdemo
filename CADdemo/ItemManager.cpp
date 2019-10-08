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

	void ItemManager::makeWithoutSweeping()
	{

		//---------make a target solid without sweeping------
		auto* sld = this->kvfs(_vertex[0]);
		auto* fac = sld->getFirstFace();
		auto* lp = fac->getFirstLoop();
		
		//make a cubic
		lp->mev(_vertex[0], _vertex[1]);
		lp->mev(_vertex[1], _vertex[2]);
		lp->mev(_vertex[2], _vertex[3]);
		auto* fdown = lp->mef(_vertex[0], _vertex[3]);
		lp->mev(_vertex[0], _vertex[4]);
		lp->mev(_vertex[1], _vertex[5]);
		lp->mev(_vertex[2], _vertex[6]);
		lp->mev(_vertex[3], _vertex[7]);
		lp->mef(_vertex[5], _vertex[4]);
		lp->mef(_vertex[6], _vertex[5]);
		lp->mef(_vertex[7], _vertex[6]);
		auto* fup = lp->mef(_vertex[7], _vertex[4]);
		
		//make a reverse loop on its buttom
		lp = fdown->getFirstLoop();
		lp->mev(_vertex[0], _vertex[8]);
		lp->mev(_vertex[8], _vertex[9]);
		lp->mev(_vertex[9], _vertex[10]);
		lp->mev(_vertex[10], _vertex[11]);
		fac = lp->mef(_vertex[8], _vertex[11]);
		lp->kemr(_vertex[8], _vertex[0]);
		
		lp = fac->getFirstLoop();
		lp->mev(_vertex[8], _vertex[12]);
		lp->mev(_vertex[11], _vertex[15]);
		lp->mev(_vertex[10], _vertex[14]);
		lp->mev(_vertex[9], _vertex[13]);

		lp->mef(_vertex[12], _vertex[13]);
		lp->mef(_vertex[13], _vertex[14]);
		lp->mef(_vertex[14], _vertex[15]);
		auto* f2 = lp->mef(_vertex[12], _vertex[15]);
		
		fup->kfmrh(f2);
		
		

		/*
		//-------test mef in complex situation-------
		auto* sld = this->kvfs(_vertex[0]);
		auto* fac = sld->getFirstFace();
		auto* lp = fac->getFirstLoop();
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

	void ItemManager::makeWithSweeping()
	{
		auto* sld = this->kvfs(_vertex[0]);
		auto* fac = sld->getFirstFace();
		auto* lp = fac->getFirstLoop();

		lp->mev(_vertex[0], _vertex[1]);
		lp->mev(_vertex[1], _vertex[2]);
		lp->mev(_vertex[2], _vertex[3]);
		auto* fDown = lp->mef(_vertex[0], _vertex[3]);

		lp->mev(_vertex[0], _vertex[4]);
		lp->mev(_vertex[4], _vertex[5]);
		lp->mev(_vertex[5], _vertex[6]);
		lp->mev(_vertex[6], _vertex[7]);
		auto* facDel = lp->mef(_vertex[7], _vertex[4]);
		lp->kemr(_vertex[0], _vertex[4]);
		fDown->kfmrh(facDel);
		//sld->travelFrame();

		lp->getFace()->extrude(vec3(0.f, 0.f, 1.f));

		this->travelOutput();
		sld->travelFrame();
	}

	Solid* ItemManager::kvfs(Vertex* v)
	{
		_solid.push_back(new Solid(v));
		return _solid.back();
	}
	void ItemManager::drawFace()
	{
		for (auto* p : _solid)
			p->drawFace();
	}
	void ItemManager::drawFrame()
	{
		for (auto* p : _solid)
			p->drawFrame();
	}
}
