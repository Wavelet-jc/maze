#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 20		//�Թ������С, ������Ǳ�������ʵ�ʴ�С (N-2)*(N-2)
#define WALL 0		//��ʾ��λ����ǽ wall
#define ROUTE 1		//��ʾ��λ����· route

void InitMaze(int(*maze)[N]);
void CreatMaze(int(*maze)[N], int x, int y);
void print(int(*maze)[N]);
void CreatInAndOut(int(*maze)[N], int* in, int* out);


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

}
//�����Թ�������洢�ڶ�ά����maze[N][N]��(��ע:�Թ��������㷨�ǲο�CSDN��ĳλ���е�,�Ұ����ӷ����� https://blog.csdn.net/jjwwwww/article/details/106586256)
void CreatMaze(int(*maze)[N], int x, int y) {

	if (*(*(maze + x) + y) == WALL) {//����ô���ǽ�壬��ʼ��ͨ��
		//����˵�����ж����������Ƿ����������ϵĸ���ΪROUTE���ǵĻ�˵���ڴ���ǰ���ӻ���ɻ��ĳ��֡�
		if (*(*(maze + x + 1) + y) + *(*(maze + x - 1) + y) + *(*(maze + x) + y + 1) + *(*(maze + x) + y - 1) <= ROUTE) {

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
}

//��ӡ�Թ�
void print(int(*maze)[N]) {
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
void CreatInAndOut(int(*maze)[N], int* in, int* out) {
	int a, b;
	int flag_a = 1;
	int flag_b = 1;

	while (flag_a) {
		//�����±����Թ����������������,�����ų��±�Ϊ1��N-2��λ��
		a = 2 + rand() % (N - 4);//������� 2 -- N-3 ֮�����
		//���ڴ������ָ�룬�����践��ֵ
		if (*(*(maze + a) + 2) == ROUTE) {//��������������ʹָ��inָ������±�a
			*in = a;
			*(*(maze + a) + 1) = ROUTE;
			flag_a = 0;
		}
	}

	// ���ó���ͬ��
	while (flag_b) {
		b = 2 + rand() % (N - 4);
		if (*(*(maze + b) + N - 3) == ROUTE) {//��������������ʹָ��outָ������±�b
			*out = b;
			*(*(maze + b) + N - 2) = ROUTE;
			flag_b = 0;
		}
	}
}


int main() {
	int maze[N][N];//��ӵ��±��ʾ�Թ��߽�ǽ��
	int in = 0;
	int out = 0;
	srand(time(NULL));

	InitMaze(maze);

	CreatMaze(maze, 2, 2);//��maze[1][1]��λ�ÿ�ʼ�����Թ�
	CreatInAndOut(maze, &in, &out);


	print(maze);
	return 0;
}