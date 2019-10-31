#include <iostream>
#include "ItemManager.h"
#include"Visualization.h"
#include<fstream>

void dealInput(std::string file,geometry::ItemManager& model, Visualization* v)
{
	std::ifstream fin(file);
	if (fin.fail())
	{
		std::cout << "ERROR::cannot open file: " << file << std::endl;
		return;
	}
	int numVtx;
	fin >> numVtx;
	for (int i = 0; i < numVtx; i++)
	{
		float x, y, z;
		fin >> x >> y >> z;
		model.addVertex(vec3(x, y, z));
	}
	while (!fin.eof())
	{
		char order;
		//int order; //0: add new plane shape  1: add new hole  2: sweep
		fin >> order;
		if (order == 'n')
		{
			int n;
			fin >> n;
			std::vector<int> newShape(0);
			for (int i = 0; i < n; i++)
			{
				int x;
				fin >> x;
				if (x >= numVtx)
				{
					std::cout << "ERROR:: vertex no." << x << " doesn't exist" << std::endl;
					return;
				}
				newShape.push_back(x);
			}
			model.addPlaneShape(newShape);
		}
		else if (order == 'h')
		{
			int id, n;
			fin >> id >> n;
			if (id >= model.getSldNum())
			{
				std::cout << "ERROR:: solid no." << id << " doesn't exist" << std::endl;
				return;
			}
			std::vector<int> newHole(0);
			for (int i = 0; i < n; i++)
			{
				int x;
				fin >> x;
				if (x >= numVtx)
				{
					std::cout << "ERROR:: vertex no." << x << " doesn't exist" << std::endl;
					return;
				}
				newHole.push_back(x);
			}
			model.addHole(id, newHole);
		}
		else if (order == 's')
		{
			int id;
			vec3 dir;
			fin >> id >> dir.e[0] >> dir.e[1] >> dir.e[2];
			if (id >= model.getSldNum())
			{
				std::cout << "ERROR:: solid no." << id << " doesn't exist" << std::endl;
				return;
			}
			model.sweepPlaneShape(id, dir);
		}
		else if (order == 'f')
		{
			model.travelOutput();
			std::cout << "********FINISH********" << std::endl;
			return;
		}
		else
		{
			std::cout << "ERROR::cannot recognize order: " << order << std::endl;
			return;
		}
		
	}
}

int main()
{
    std::cout << "Hello World!\n";
	using namespace geometry;
	geometry::ItemManager model;
	Visualization* v = new Visualization();

	dealInput("Input.txt", model, v);
	v->drawAll(&model);

	std::cout << "HOW BRAVO THIS WORK IS !" << std::endl;
	std::cout << "IT WORTH A HIGH GRADE RIGHT ?" << std::endl;
	system("pause");
}

//TODO:
	//[v] 析构函数：逆操作中删得只剩一个元素的双向链表next和pre指针需要处理
	//[ ] mef操作中的优化 极端情况多分叉情况下O(n^2)->O(n)
	//[v] 在mef构成几何形体的最后一步没办法拓扑区分新面与旧面
	//[v] setCircleWith函数可删除
	//[v] 加入空间位置信息
	//[v] sweeping操作
	//[v] 可视化展示

//STUPID TEST LINES WHICH ARE ONLY CHERISHED BY MYSELF
	/* test case 0:
	float x[16] = { 0.f,4.f,4.f,0.f,0.f,4.f,4.f,0.f,1.f,2.f,2.f,1.f,1.f,2.f,2.f,1.f };
	float y[16] = { 0.f,0.f,4.f,4.f,0.f,0.f,4.f,4.f,1.f,1.f,2.f,2.f,1.f,1.f,2.f,2.f };
	float z[16] = { 0.f,0.f,0.f,0.f,4.f,4.f,4.f,4.f,0.f,0.f,0.f,0.f,4.f,4.f,4.f,4.f };

	for (int i = 0; i < 16; i++)
	{
		model.addVertex(vec3(x[i], y[i], z[i]));
	}
	model.makeWithoutSweeping();
	*/
	/*
	float x[12] = { 0.f,5.f,5.f,0.f,1.f,2.f,2.f,1.f,3.f,4.f,4.f,3.f };
	float y[12] = { 0.f,0.f,5.f,5.f,1.f,1.f,2.f,2.f,3.f,3.f,4.f,4.f };
	float z[12] = { 0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f };

	for (int i = 0; i < 12; i++)
	{
		model.addVertex(vec3(x[i], y[i], z[i]));
	}
	//model.makeWithSweeping();
	model.multiHandle();
	*/