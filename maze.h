#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"point.h"

#define N 20		//迷宫区域大小, 最外层是保护区，实际大小 (N-2)*(N-2), 1~N-2
#define WALL 0		//表示该位置是墙 wall
#define ROUTE 1		//表示该位置是路 route


void InitMaze(int(*maze)[N]);					//初始化迷宫
void CreatMaze(int(*maze)[N], int x, int y);	// 挖迷宫
void LockMaze(int(*maze)[N]);					// 迷宫外围设置障碍
void PrintMaze(int(*maze)[N]);					//打印迷宫
void CreatInAndOut(int(*maze)[N], Point* in, Point* out);	//随机生成迷宫的入口与出口,将结果赋予两个指针参数
void CopyMaze(int(*maze)[N], int(*MazeCopyer)[N]);		// 拷贝迷宫




//初始化迷宫
void InitMaze(int(*maze)[N]) {
	//生成墙体
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			*(*(maze + i) + j) = WALL;
		}
	}

	//迷宫外围保护，防止挖穿
	for (int i = 0; i < N; ++i) {
		*(*(maze)+i) = ROUTE;
		*(*(maze + N - 1) + i) = ROUTE;
		*(*(maze + i)) = ROUTE;
		*(*(maze + i) + N - 1) = ROUTE;
	}
	srand((int)time(NULL));
}

// 迷宫外围设置障碍
void LockMaze(int(*maze)[N]) {

	for (int i = 0; i < N; ++i) {
		*(*(maze)+i) = WALL;
		*(*(maze + N - 1) + i) = WALL;
		*(*(maze + i)) = WALL;
		*(*(maze + i) + N - 1) = WALL;
	}
}

// 挖迷宫
void CreatMaze(int(*maze)[N], int x, int y) {

	int isWall = maze[x][y] == WALL; //如果该处是墙体，则开始挖通道
	//简单来说就是判断上下左右是否有两个以上的格子为ROUTE，是的话说明挖穿当前格子会造成环的出现。
	int notLoop = maze[x + 1][y] + maze[x - 1][y] + maze[x][y + 1] + maze[x][y - 1] <= ROUTE;

	//int probability = rand() % N;
	
	if (isWall && notLoop ) {
		*(*(maze + x) + y) = ROUTE;//调用成功，将该位置设置为:路
		
		int direction[4] = { 0, 1, 2, 3 };
		for (int i = 4; i > 0; --i) {//四个方向都要尝试
			int ret = rand() % i;//随机生成 0 -- i-1 中的数  (0,1,2,3)

			//交换，防止重复
			int tmp = direction[ret];
			direction[ret] = direction[i - 1];
			direction[i - 1] = tmp;


			//由于每次循环i都会变化，故不会出现重复的下标
			switch (direction[i - 1]) {
			case 0:CreatMaze(maze, x - 1, y); break;//数组标记上移一位
			case 1:CreatMaze(maze, x + 1, y); break;//数组标记下移一位
			case 2:CreatMaze(maze, x, y - 1); break;//数组标记左移一位
			case 3:CreatMaze(maze, x, y + 1); break;//数组标记右移一位
			default: {printf("CreatMaze函数出错!"); return; }
			}
		}

	}
}

//打印迷宫
void PrintMaze(int(*maze)[N]) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (*(*(maze + i) + j) == ROUTE) {
				printf("  ");
			}
			else printf("回");
		}
		printf("\n");
	}
	printf("\n");
}

//随机生成迷宫的入口与出口,将结果赋予两个指针参数
void CreatInAndOut(int(*maze)[N], Point* in, Point* out) {
	in->y = 1;
	out->y = N-2;
	int flag_a = 1;
	int flag_b = 1;

	while (flag_a) {
		//产生下标与迷宫最外层相符的随机数,可以排除下标为1和N-2的位置
		in->x = 2 + rand() % (N - 4);//随机产生 2 -- N-3 之间的数
		//由于传入的是指针，故无需返回值
		if (*(*(maze + in->x) + 2) == ROUTE) {//若条件成立，则使指针in指向入口下标
			*(*(maze + in->x) + 1) = ROUTE;
			flag_a = 0;
		}
	}

	// 设置出口同理
	while (flag_b) {
		out->x = 2 + rand() % (N - 4);
		if (*(*(maze + out->x) + N - 3) == ROUTE) {//若条件成立，则使指针out指向入口下标	
			*(*(maze + out->x) + N - 2) = ROUTE;
			flag_b = 0;
		}
	}
}

inline void CopyMaze(int(*maze)[N], int(*mazeCopyer)[N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			mazeCopyer[i][j] = maze[i][j];
		}
	}
}
