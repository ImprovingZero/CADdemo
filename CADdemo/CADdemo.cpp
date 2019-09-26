// CADdemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "ItemManager.h"

int main()
{
    std::cout << "Hello World!\n";
	using namespace geometry;
	ItemManager model;
	float x[8] = { 0.f,4.f,4.f,0.f,0.f,4.f,4.f,0.f };
	float y[8] = { 0.f,0.f,4.f,4.f,0.f,0.f,4.f,4.f };
	float z[8] = { 0.f,0.f,0.f,0.f,4.f,4.f,4.f,4.f };
	for (int i = 0; i < 8; i++)
	{
		model.addVertex(vec3(x[i], y[i], z[i]));
	}
	

	model.tempRoutine();


	//TODO:
	//逆操作中删得只剩一个元素的双向链表next和pre指针需要处理
}
