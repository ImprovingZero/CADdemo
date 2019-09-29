// CADdemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "ItemManager.h"

int main()
{
    std::cout << "Hello World!\n";
	using namespace geometry;
	ItemManager model;
	/*
	float x[16] = { 0.f,4.f,4.f,0.f,0.f,4.f,4.f,0.f,1.f,2.f,2.f,1.f,1.f,2.f,2.f,1.f };
	float y[16] = { 0.f,0.f,4.f,4.f,0.f,0.f,4.f,4.f,1.f,1.f,2.f,2.f,1.f,1.f,2.f,2.f };
	float z[16] = { 0.f,0.f,0.f,0.f,4.f,4.f,4.f,4.f,0.f,0.f,0.f,0.f,4.f,4.f,4.f,4.f };
	
	for (int i = 0; i < 16; i++)
	{
		model.addVertex(vec3(x[i], y[i], z[i]));
	}
	model.makeWithoutSweeping();
	*/

	float x[8] = { 0.f,4.f,4.f,0.f,1.f,2.f,2.f,1.f };
	float y[8] = { 0.f,0.f,4.f,4.f,1.f,1.f,2.f,2.f };
	float z[8] = { 0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };

	for (int i = 0; i < 8; i++)
	{
		model.addVertex(vec3(x[i], y[i], z[i]));
	}
	model.makeWithSweeping();
	
	/*
	for (int i = 0; i < 20; i++)
	{
		model.addVertex(vec3(float(i), 0.f, 0.f));
		//model.addVertex(vec3(x[i], y[i], z[i]));
	}
	*/
	
	


	//TODO:
	//[v] 析构函数：逆操作中删得只剩一个元素的双向链表next和pre指针需要处理
	//[ ] 加入空间位置信息后kemr操作需要增加checkReverse操作
	//[ ] mef操作中的优化 O(n^2)->O(n)
	//[ ] 在mef构成几何形体的最后一步没办法拓扑区分新面与旧面
	//[v] setCircleWith函数可删除
	//[ ] 加入空间位置信息
	//[ ] sweeping操作
	//[ ] 可视化展示
}
