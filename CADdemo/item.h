#pragma once
#include"vec3.h"
#include"vec2.h"
#include<list>

namespace geometry
{
	enum GeoType {
		NONE,
		VERTEX,
		HALFEDGE,
		EDGE,
		LOOP,
		FACE,
		SOLID 
	};
	using VtxInd = int;
	using HegInd = int; //Halfedge index
	using EdgInd = int;
	using LopInd = int;
	using FacInd = int;
	using SldInd = int;
	using NmlInd = int;
	using TexInd = int;

	using VtxIt = std::list<Vertex>::iterator;
	using HegIt = std::list<Halfedge>::iterator;
	using LopIt = std::list<Loop>::iterator;
	using FacIt = std::list<Face>::iterator;
	using EdgIt = std::list<Edge>::iterator;
	using SldIt = std::list<Solid>::iterator;
	

	class item
	{
	public:
		virtual const GeoType getType() const = 0;
	};

	class ItemManager
	{
	};
}

