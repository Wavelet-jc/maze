
#include<stdio.h>
#include<math.h>
#include"maze.h"
//#include"ant.h"
#include"stack.h"

#define M 20 // ÿһ�������ϵĸ���


int main() {

	int maze[N][N];//��ӵ��±��ʾ�Թ��߽�ǽ��
	Point in, out;

	InitMaze(maze);		// ��ʼ���Թ�
	CreatMaze(maze, N / 2, 2);	//��maze[N/2][2]��λ�ÿ�ʼ�����Թ�
	CreatInAndOut(maze, &in, &out);		// �����Թ������
	LockMaze(maze);
	printf("��ʼ���Թ�: ���:(%d,%d), ����:(%d,%d)\n",in.x,in.y,out.x,out.y);
	PrintMaze(maze);


	int maze_col = N;	// �Թ����� 1~N-2
	int maze_row = N;	// �Թ����� 1~N-2

	//const int M = 20;				// ÿһ�������ϵĸ���
	const int RcMax = 20;			// ��������
	const double IN = 0.2;			// ��Ϣ�صĳ�ʼ��

	double alpha = 0.4;	// alpha��Ϣ�ص�Ӱ������
	double beta = 0.4;	// beta·�߾����Ӱ������
	double rout = 0.2;	//  rout��Ϣ�صı��ֶ�
	double Q = 1.0;		// Q���ڼ���ÿֻ��������·�����µ���Ϣ������
	double E = 1.0;		// ��Ӣ���ϲ��Ե�eֵ

	double add[N][N];				// ÿһ�ε���Ϣ����������
	double best_ant_add[N][N];		// ��Ӣ���ϵĶ�����Ϣ����������
	double phe[N][N];				// ÿһ��·���ϵ���Ϣ��
	int bestSolution = INT_MAX;		// ��̾���
	Stack Beststackpath;			// ����·��
	int BestAnt;					// ��Ӣ����

	// ��ʼ����Ϣ������
	for (int i = 0; i < N; i++) 
	{
		for (int j = 0; j < N; j++)
		{
			phe[i][j] = IN;
			//printf("%1.1f ", phe[i][j]);
		}
	}


	Point offset[4] = { {0,1} ,{1,0},{0,-1},{-1,0} }; 	// ���ڷ���ѡ���ƫ��������   ����˳ʱ��ķ��� {��������}
	Stack stackpath[M];			// ÿ��Mֻ���ϣ�ÿһ�ֽ�����Ž���ȫ����Ϣ�ظ���
	int Ini_map[M][N][N];		// �����ϰ���ͼ
	Point Allposition[M];		// ��¼ÿһֻ���ϵĵ�ǰλ��


	for (int s = 0; s < RcMax; s++) 	// һ��RcMax�� !!!!!!!!!!!!!
	{
		printf("-----��%d��ѭ��-----\n", s);

		// ÿ��Mֻ����, �ȳ�ʼ������
		for (int i = 0; i < M; i++) 
		{
			InitStack(&stackpath[i]); 		// �����ÿһֻ���ϵ�·�ߴ洢ջ
			CopyMaze(maze, Ini_map[i]);		// �����ϰ���ͼ
			//PrintMaze(Ini_map[i]);
			
			Ini_map[i][in.x][in.y] = WALL;	// ������ʼ��Ϊ�ϰ���
			Push(&stackpath[i], in);		// �����ջ
			CopyPoint(&in, &Allposition[i]);// ��ʼ��ÿһֻ���ϵĵ�ǰλ��
		}
		
		// ����Mֻ����ѭ��
		for (int j = 0; j < M; j++) 
		{
			
			int map_round[N][N][4];			// ��ͼ����,��ʼ��Ϊδ����
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

				// ѡ����һ��,�������̶�
				double psum = 0;
				for (int op = 0; op < 4; op++)
				{
					// ������һ�����ܵ�����
					int x = Allposition[j].x + offset[op].x;
					int y = Allposition[j].y + offset[op].y;

					if ((Ini_map[j][x][y] != WALL) && (map_round[Allposition[j].x][Allposition[j].y][op]==0))	// �����һ�����겻��ǽ,���һ�δ���ʹ�
					{
						psum += pow(phe[x][y], alpha) * pow((1.0 / StackLength(&stackpath[j])), beta);
					}
				}

				// ����ҵ�����һ������ѡ��
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
						//������һ�����ܵ�����
						x = Allposition[j].x + offset[re].x;
						y = Allposition[j].y + offset[re].y;
						if ((Ini_map[j][x][y] != WALL) && (map_round[Allposition[j].x][Allposition[j].y][re] == 0))	// �����һ�����겻��ǽ,���һ�δ���ʹ�
						{
							//printf("(%d,%d)",x,y);
							//printf("phe=%lf,a=%lf,Dij=%d,b=%lf,psum = %lf", phe[x][y], alpha, StackLength(&stackpath[j]), beta, psum);
							pro += (pow(phe[x][y], alpha) * pow((1.0 / StackLength(&stackpath[j])), beta)) / psum;
							
							if (pro >= drand)
								break;
						}
					}

					// ���õ�ǰλ��
					Allposition[j].x = x;
					Allposition[j].y = y;

					Push(&stackpath[j], Allposition[j]);   // ��ջ
					//printf("��ջ:(%d,%d) ", GetTop(&stackpath[j]).x, GetTop(&stackpath[j]).y);

					//�����ϰ�
					Ini_map[j][Allposition[j].x][Allposition[j].y] = WALL;
					//PrintMaze(Ini_map[j]);
				}
				else // û�ҵ�����һ��
				{
					//printf("��ջ: (%d,%d) ", GetTop(&stackpath[j]).x, GetTop(&stackpath[j]).y);
					Pop(&stackpath[j]);	// �����һ������ջ
					

					//������ջʱ���õ��ϰ�
					Ini_map[j][Allposition[j].x][Allposition[j].y] = ROUTE;
					if (EmptyStack(&stackpath[j]))
					{
						printf("�޽⣬����");
						getchar();
						return 0; // ���� ��������������
					}

					//���û��ݺ��Allposition					 
					if (Allposition[j].x == GetTop(&stackpath[j]).x)
					{
						if (Allposition[j].y - GetTop(&stackpath[j]).y == 1)	//����
						{
							map_round[GetTop(&stackpath[j]).x][GetTop(&stackpath[j]).y][0] = 1;	//��Ǹ÷����ѷ���
						}
						if (Allposition[j].y - GetTop(&stackpath[j]).y == -1)	//����
						{
							map_round[GetTop(&stackpath[j]).x][GetTop(&stackpath[j]).y][2] = 1;	//��Ǹ÷����ѷ���
						}
					}


					if (Allposition[j].y == GetTop(&stackpath[j]).y)
					{

						if ((Allposition[j].x - GetTop(&stackpath[j]).x) == 1)//����
						{
							(map_round[GetTop(&stackpath[j]).x][GetTop(&stackpath[j]).y])[1] = 1;//��Ǹ÷����ѷ���
						}
						if ((Allposition[j].x - GetTop(&stackpath[j]).x) == -1)//����
						{
							(map_round[GetTop(&stackpath[j]).x][GetTop(&stackpath[j]).y])[3] = 1;//��Ǹ÷����ѷ���
						}
					}
					Allposition[j].x = GetTop(&stackpath[j]).x;
					Allposition[j].y = GetTop(&stackpath[j]).y;
				}
				
			}
			printf("��%dֻ���� ����%d��\n", j, step);
		}


		// ��������·��
		int solution = 0;
		for (int i = 0; i < M; i++)
		{
			solution = StackLength(&stackpath[i]);
			//printf("��%dֻ�����߹�·�����ȣ�%d\n",i, solution);
			if (solution < bestSolution)
			{
				Beststackpath = stackpath[i];
				bestSolution = solution;
				BestAnt = i;
			}
		}


		//����ÿһֻ��������ÿһ��·�������µ���Ϣ������
		//��ʼ����Ϣ����������
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
			// �����ÿֻ���ϵ�·�ߵ��ܾ���solu
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

		//������Ϣ��
		for (int i = 0; i < maze_row; i++)
		{

			for (int j = 0; j < maze_col; j++)
			{
				phe[i][j] = phe[i][j] * rout + add[i][j] + best_ant_add[i][j];		// ����Ǿ�Ӣ����,��Ӷ�����Ϣ��;

				//Ϊ��Ϣ������һ������ֵ������ֵ
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


	//�ҵ�·���������stackpath
	printf("�ҵ�����·����\n");
	printf("���·�����ȣ�%d \n", StackLength(&Beststackpath));
	printf("��ӡ���·����\n");

	PrintStack(&Beststackpath);
	int maze_bestpath[N][N];
	InitMaze(maze_bestpath);
	
	while (!EmptyStack(&Beststackpath))
	{
		// printf("<%d,%d> ", GetTop(&Beststackpath).x, GetTop(&Beststackpath).y); // ����
		maze_bestpath[GetTop(&Beststackpath).x][GetTop(&Beststackpath).y] = ROUTE;
		Pop(&Beststackpath);

	}

	
	printf("\n");
	LockMaze(maze_bestpath);
	PrintMaze(maze_bestpath);

	getchar();
	return 0;
}
