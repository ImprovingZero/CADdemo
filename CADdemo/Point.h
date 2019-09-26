#pragma once
#include"vec3.h"
class Point
{
private:
	vec3 _pos;
public:
	Point(vec3 pos) :_pos(pos) {};
	const vec3 getPos() const { return _pos; };
	const vec3 setPos(const vec3 pos) { _pos = pos; return pos; }
};

