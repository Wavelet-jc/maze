
#include<stdio.h>
#include<math.h>
#include"maze.h"
//#include"ant.h"
#include"stack.h"

#define M 20 // 每一轮中蚂蚁的个数


int main() {

	int maze[N][N];//添加的下标表示迷宫边界墙体
	Point in, out;

	InitMaze(maze);		// 初始化迷宫
	CreatMaze(maze, N / 2, 2);	//从maze[N/2][2]的位置开始创建迷宫
	CreatInAndOut(maze, &in, &out);		// 制造迷宫出入口
	LockMaze(maze);
	printf("初始化迷宫: 入口:(%d,%d), 出口:(%d,%d)\n",in.x,in.y,out.x,out.y);
	PrintMaze(maze);


	int maze_col = N;	// 迷宫列数 1~N-2
	int maze_row = N;	// 迷宫行数 1~N-2

	//const int M = 20;				// 每一轮中蚂蚁的个数
	const int RcMax = 20;			// 迭代次数
	const double IN = 0.2;			// 信息素的初始量

	double alpha = 0.4;	// alpha信息素的影响因子
	double beta = 0.4;	// beta路线距离的影响因子
	double rout = 0.2;	//  rout信息素的保持度
	double Q = 1.0;		// Q用于计算每只蚂蚁在其路迹留下的信息素增量
	double E = 1.0;		// 精英蚂蚁策略的e值

	double add[N][N];				// 每一段的信息素增量数组
	double best_ant_add[N][N];		// 精英蚂蚁的额外信息素增量数组
	double phe[N][N];				// 每一段路径上的信息素
	int bestSolution = INT_MAX;		// 最短距离
	Stack Beststackpath;			// 最优路线
	int BestAnt;					// 精英蚂蚁

	// 初始化信息素数组
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
		{
			phe[i][j] = IN;
			//printf("%1.1f ", phe[i][j]);
		}
	}


	Point offset[4] = { {0,1} ,{1,0},{0,-1},{-1,0} }; 	// 用于方向选择的偏移量数组   按照顺时针的方向 {右下左上}
	Stack stackpath[M];			// 每轮M只蚂蚁，每一轮结束后才进行全局信息素更新
	int Ini_map[M][N][N];		// 拷贝障碍地图
	Point Allposition[M];		// 记录每一只蚂蚁的当前位置


	for (int s = 0; s < RcMax; s++) 	// 一共RcMax轮 !!!!!!!!!!!!!
	{
		printf("-----第%d轮循环-----\n", s);

		// 每轮M只蚂蚁, 先初始化数据
		for (int i = 0; i < M; i++) 
		{
			InitStack(&stackpath[i]); 		// 先清空每一只蚂蚁的路线存储栈
			CopyMaze(maze, Ini_map[i]);		// 拷贝障碍地图
			//PrintMaze(Ini_map[i]);
			
			Ini_map[i][in.x][in.y] = WALL;	// 将起点初始化为障碍点
			Push(&stackpath[i], in);		// 起点入栈
			CopyPoint(&in, &Allposition[i]);// 初始化每一只蚂蚁的当前位置
		}
		
		// 开启M只蚂蚁循环
		for (int j = 0; j < M; j++) 
		{
			
			int map_round[N][N][4];			// 地图四周,初始花为未访问
			for (int mr = 0; mr < N; mr++) {
				for (int mc = 0; mc < N; mc++) {
					for (int mf = 0; mf < 4; mf++) {
						map_round[mr][mc][mf] = 0;
					}
				}
			}
			int step = 1;
			while ((Allposition[j].x != out.x) || (Allposition[j].y != out.y))
			{
				step++;
				//printf("current:(%d,%d)", Allposition[j].x, Allposition[j].y);

				// 选择下一步,进行轮盘赌
				double psum = 0;
				for (int op = 0; op < 4; op++)
				{
					// 计算下一个可能的坐标
					int x = Allposition[j].x + offset[op].x;
					int y = Allposition[j].y + offset[op].y;

					if ((Ini_map[j][x][y] != WALL) && (map_round[Allposition[j].x][Allposition[j].y][op]==0))	// 如果下一个坐标不是墙,并且还未访问过
					{
						psum += pow(phe[x][y], alpha) * pow((1.0 / StackLength(&stackpath[j])), beta);
					}
				}

				// 如果找到了下一步，有选择
				//printf("\npsum=%.6lf  ", psum);
				if (fabs(psum)>1e-15)
				{
					//printf("rand=%d, randmax=%d, drand=%lf   ", rand(),RAND_MAX,rand()/(RAND_MAX+1.0

					double drand = (double)(rand() / (RAND_MAX + 1.0));
					double pro = 0;
					int re;
					int x, y;
					//printf(" drand=%lf ", drand);
					for (re = 0; re < 4; re++)
					{
						//计算下一个可能的坐标
						x = Allposition[j].x + offset[re].x;
						y = Allposition[j].y + offset[re].y;
						if ((Ini_map[j][x][y] != WALL) && (map_round[Allposition[j].x][Allposition[j].y][re] == 0))	// 如果下一个坐标不是墙,并且还未访问过
						{
							//printf("(%d,%d)",x,y);
							//printf("phe=%lf,a=%lf,Dij=%d,b=%lf,psum = %lf", phe[x][y], alpha, StackLength(&stackpath[j]), beta, psum);
							pro += (pow(phe[x][y], alpha) * pow((1.0 / StackLength(&stackpath[j])), beta)) / psum;
							
							if (pro >= drand)
								break;
						}
					}

					// 设置当前位置
					Allposition[j].x = x;
					Allposition[j].y = y;

					Push(&stackpath[j], Allposition[j]);   // 入栈
					//printf("入栈:(%d,%d) ", GetTop(&stackpath[j]).x, GetTop(&stackpath[j]).y);

					//设置障碍
					Ini_map[j][Allposition[j].x][Allposition[j].y] = WALL;
					//PrintMaze(Ini_map[j]);
				}
				else // 没找到了下一点
				{
					//printf("出栈: (%d,%d) ", GetTop(&stackpath[j]).x, GetTop(&stackpath[j]).y);
					Pop(&stackpath[j]);	// 向后退一步，出栈
					

					//消除入栈时设置的障碍
					Ini_map[j][Allposition[j].x][Allposition[j].y] = ROUTE;
					if (EmptyStack(&stackpath[j]))
					{
						printf("无解，结束");
						getchar();
						return 0; // 结束 ！！！！！！！
					}

					//设置回溯后的Allposition					 
					if (Allposition[j].x == GetTop(&stackpath[j]).x)
					{
						if (Allposition[j].y - GetTop(&stackpath[j]).y == 1)	//向右
						{
							map_round[GetTop(&stackpath[j]).x][GetTop(&stackpath[j]).y][0] = 1;	//标记该方向已访问
						}
						if (Allposition[j].y - GetTop(&stackpath[j]).y == -1)	//向左
						{
							map_round[GetTop(&stackpath[j]).x][GetTop(&stackpath[j]).y][2] = 1;	//标记该方向已访问
						}
					}


					if (Allposition[j].y == GetTop(&stackpath[j]).y)
					{

						if ((Allposition[j].x - GetTop(&stackpath[j]).x) == 1)//向下
						{
							(map_round[GetTop(&stackpath[j]).x][GetTop(&stackpath[j]).y])[1] = 1;//标记该方向已访问
						}
						if ((Allposition[j].x - GetTop(&stackpath[j]).x) == -1)//向上
						{
							(map_round[GetTop(&stackpath[j]).x][GetTop(&stackpath[j]).y])[3] = 1;//标记该方向已访问
						}
					}
					Allposition[j].x = GetTop(&stackpath[j]).x;
					Allposition[j].y = GetTop(&stackpath[j]).y;
				}
				
			}
			printf("第%d只蚂蚁 走了%d步\n", j, step);
		}


		// 保存最优路径
		int solution = 0;
		for (int i = 0; i < M; i++)
		{
			solution = StackLength(&stackpath[i]);
			//printf("第%d只蚂蚁走过路径长度：%d\n",i, solution);
			if (solution < bestSolution)
			{
				Beststackpath = stackpath[i];
				bestSolution = solution;
				BestAnt = i;
			}
		}


		//计算每一只蚂蚁在其每一段路径上留下的信息素增量
		//初始化信息素增量数组
		for (int i = 0; i < maze_row; i++)
		{
			for (int j = 0; j < maze_col; j++)
			{
				add[i][j] = 0;
				best_ant_add[i][j] = 0;
			}
		}


		for (int i = 0; i < M; i++)
		{
			// 先算出每只蚂蚁的路线的总距离solu
			double solu = 0;
			solu = StackLength(&stackpath[i]);
			double d = Q / solu;
			double e = 0;
			if (i == BestAnt) {
				e = E / solu;
				//printf("e=%lf", e);
			}
			while (!EmptyStack(&stackpath[i]))
			{
				add[GetTop(&stackpath[i]).x][GetTop(&stackpath[i]).y] += d;
				best_ant_add[GetTop(&stackpath[i]).x][GetTop(&stackpath[i]).y] += e;
				Pop(&stackpath[i]);
			}
		}

		//更新信息素
		for (int i = 0; i < maze_row; i++)
		{

			for (int j = 0; j < maze_col; j++)
			{
				phe[i][j] = phe[i][j] * rout + add[i][j] + best_ant_add[i][j];		// 如果是精英蚂蚁,添加额外信息素;

				//为信息素设置一个下限值和上限值
				if (phe[i][j] < 0.0001)
				{
					phe[i][j] = 0.0001;
				}
				if (phe[i][j] > 20)
				{
					phe[i][j] = 20;
				}
			}
		}
	}


	//找到路径，并输出stackpath
	printf("找到最优路径！\n");
	printf("最短路径长度：%d \n", StackLength(&Beststackpath));
	printf("打印最短路径！\n");

	PrintStack(&Beststackpath);
	int maze_bestpath[N][N];
	InitMaze(maze_bestpath);
	
	while (!EmptyStack(&Beststackpath))
	{
		// printf("<%d,%d> ", GetTop(&Beststackpath).x, GetTop(&Beststackpath).y); // 倒序
		maze_bestpath[GetTop(&Beststackpath).x][GetTop(&Beststackpath).y] = ROUTE;
		Pop(&Beststackpath);

	}

	
	printf("\n");
	LockMaze(maze_bestpath);
	PrintMaze(maze_bestpath);

	getchar();
	return 0;
}
