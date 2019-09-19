#pragma once
#include "item.h"

namespace geometry
{

	class Halfedge :public item
	{
	private:
		VtxInd _vs; //vertex from
		TexInd _tex;
		NmlInd _nml;
		HegInd _next;
	public:
		virtual const GeoType getType() const { return HALFEDGE; }
	};
}

