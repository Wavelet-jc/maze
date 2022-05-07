#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"point.h"

#define N 20		//�Թ������С, ������Ǳ�������ʵ�ʴ�С (N-2)*(N-2), 1~N-2
#define WALL 0		//��ʾ��λ����ǽ wall
#define ROUTE 1		//��ʾ��λ����· route


void InitMaze(int(*maze)[N]);					//��ʼ���Թ�
void CreatMaze(int(*maze)[N], int x, int y);	// ���Թ�
void LockMaze(int(*maze)[N]);					// �Թ���Χ�����ϰ�
void PrintMaze(int(*maze)[N]);					//��ӡ�Թ�
void CreatInAndOut(int(*maze)[N], Point* in, Point* out);	//��������Թ�����������,�������������ָ�����
void CopyMaze(int(*maze)[N], int(*MazeCopyer)[N]);		// �����Թ�




//��ʼ���Թ�
void InitMaze(int(*maze)[N]) {
	//����ǽ��
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			*(*(maze + i) + j) = WALL;
		}
	}

	//�Թ���Χ��������ֹ�ڴ�
	for (int i = 0; i < N; ++i) {
		*(*(maze)+i) = ROUTE;
		*(*(maze + N - 1) + i) = ROUTE;
		*(*(maze + i)) = ROUTE;
		*(*(maze + i) + N - 1) = ROUTE;
	}
	srand((int)time(NULL));
}

// �Թ���Χ�����ϰ�
void LockMaze(int(*maze)[N]) {

	for (int i = 0; i < N; ++i) {
		*(*(maze)+i) = WALL;
		*(*(maze + N - 1) + i) = WALL;
		*(*(maze + i)) = WALL;
		*(*(maze + i) + N - 1) = WALL;
	}
}

// ���Թ�
void CreatMaze(int(*maze)[N], int x, int y) {

	int isWall = maze[x][y] == WALL; //����ô���ǽ�壬��ʼ��ͨ��
	//����˵�����ж����������Ƿ����������ϵĸ���ΪROUTE���ǵĻ�˵���ڴ���ǰ���ӻ���ɻ��ĳ��֡�
	int notLoop = maze[x + 1][y] + maze[x - 1][y] + maze[x][y + 1] + maze[x][y - 1] <= ROUTE;

	//int probability = rand() % N;
	
	if (isWall && notLoop ) {
		*(*(maze + x) + y) = ROUTE;//���óɹ�������λ������Ϊ:·
		
		int direction[4] = { 0, 1, 2, 3 };
		for (int i = 4; i > 0; --i) {//�ĸ�����Ҫ����
			int ret = rand() % i;//������� 0 -- i-1 �е���  (0,1,2,3)

			//��������ֹ�ظ�
			int tmp = direction[ret];
			direction[ret] = direction[i - 1];
			direction[i - 1] = tmp;


			//����ÿ��ѭ��i����仯���ʲ�������ظ����±�
			switch (direction[i - 1]) {
			case 0:CreatMaze(maze, x - 1, y); break;//����������һλ
			case 1:CreatMaze(maze, x + 1, y); break;//����������һλ
			case 2:CreatMaze(maze, x, y - 1); break;//����������һλ
			case 3:CreatMaze(maze, x, y + 1); break;//����������һλ
			default: {printf("CreatMaze��������!"); return; }
			}
		}

	}
}

//��ӡ�Թ�
void PrintMaze(int(*maze)[N]) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (*(*(maze + i) + j) == ROUTE) {
				printf("  ");
			}
			else printf("��");
		}
		printf("\n");
	}
	printf("\n");
}

//��������Թ�����������,�������������ָ�����
void CreatInAndOut(int(*maze)[N], Point* in, Point* out) {
	in->y = 1;
	out->y = N-2;
	int flag_a = 1;
	int flag_b = 1;

	while (flag_a) {
		//�����±����Թ����������������,�����ų��±�Ϊ1��N-2��λ��
		in->x = 2 + rand() % (N - 4);//������� 2 -- N-3 ֮�����
		//���ڴ������ָ�룬�����践��ֵ
		if (*(*(maze + in->x) + 2) == ROUTE) {//��������������ʹָ��inָ������±�
			*(*(maze + in->x) + 1) = ROUTE;
			flag_a = 0;
		}
	}

	// ���ó���ͬ��
	while (flag_b) {
		out->x = 2 + rand() % (N - 4);
		if (*(*(maze + out->x) + N - 3) == ROUTE) {//��������������ʹָ��outָ������±�	
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
