// CADdemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "ItemManager.h"

int main()
{
    std::cout << "Hello World!\n";
	using namespace geometry;
	ItemManager model;
	vec3 p(0.f, 0.f, 0.f);
	model.kvfs(vec3(0.f,0.f,0.f));
}
