#include "Vertex.h"
namespace geometry
{
	void Vertex::travelOutput(int x) const
	{
		std::cout << '('<<_pos[0] << ',' << _pos[1] << ',' << _pos[2] <<')';
	}
}