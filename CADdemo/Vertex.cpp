#include "Vertex.h"
geometry::Vertex::Vertex() :_pos(vec3(0.f, 0.f, 0.f)), _id(-1) {}

geometry::Vertex::Vertex(float x, float y, float z, int id, HegInd hal)
	:_pos(vec3(x, y, z)), _id(id), _halfedge(hal)
{

}

geometry::Vertex::Vertex(vec3 pos, int id, HegInd hal)
	: _pos(pos), _id(id), _halfedge(hal)
{

}
