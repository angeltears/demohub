#include <iostream>  
#include <vector>  

using namespace std;

typedef struct
{
	int x;
	int y;
}Point;

#define N 5         //�Թ��Ĵ�С  
#define ENTER_X 0    //��ڵ�λ�ã�0��0��  
#define ENTER_Y 0  
#define EXIT_X N-1   //���ڵ�λ��(N-1,N-1)  
#define EXIT_Y N-1   


int Maze[N][N];//����һ���Թ���0��ʾͨ����1��ʾ�����ߣ�ǽ�����ߣ�  
int paths;//·������  
vector<Point> Path;//����һ����ͨ��·��  
vector<Point> BestPath; //������̵�·��  

bool First = true;//��־���ҵ���һ��·��  

																//��ʼ���Թ�  
void InitMaze()
{
	//����������ⶨ��һ���̶���С10*10���Թ�  
	//����һ���Թ���0��ʾͨ����1��ʾǽ(�򲻿���)  
		int mz[N][N] = {
			{0,0,0,0,0}, 
			{0,1,0,1,0}, 
			{1,1,0,0,0},  
			{1,1,0,1,1},  
			{1,1,0,0,0},  
	};

	//���Ƶ��Թ�  
	memcpy(Maze, mz, sizeof(mz));

	paths = 0;
}

//��(x,y)λ�ÿ�ʼ�ߣ���ʼΪ(0,0)  
void MazeTrack(int x, int y)
{
	//��ǰ����뵽·��  
	Point p = {x, y};
	Path.push_back(p);
	Maze[x][y] = 1;        //�߹���·Ҳ����Ϊǽ 

	//����ǰ���ԭ�����Ӧ����ھ��ǳ��ڵ������
	if (x == EXIT_X && y == EXIT_Y)
	{
		cout << "�ҵ�һ����·" << endl;
		paths++;

		//���·��  
		vector<Point>::iterator it;
		for (it = Path.begin(); it != Path.end(); ++it)
		{
			cout << "(" << it->x << "," << it->y << ") ";
		}
		cout << endl;

		//�ж��Ƿ����  
		if (First)//������ҵ��ĵ�һ��·����ֱ�Ӹ��Ƶ�����·��  
		{
			for (it = Path.begin(); it != Path.end(); ++it)
			{
				BestPath.push_back(*it);
			}
			First = false;
		}
		else //���ǵ�һ�������ж��Ƿ����  
		{
			//���̣����Ƶ�����·��  
			if (Path.size()<BestPath.size())
			{
				BestPath.clear();
				for (it = Path.begin(); it != Path.end(); ++it)
				{
					BestPath.push_back(*it);
				}
			}
		}
	}
	//�涨����˳��Ϊ��������

	if ((x - 1) >= 0 && Maze[x - 1][y] == 0)//��(x-1,y)�������ҿ���  
	{
		MazeTrack(x - 1, y);
	}

	if ((x + 1)<N && Maze[x + 1][y] == 0)//��(x+1,y)�������ҿ���  
	{
		MazeTrack(x + 1, y);
	}

	if ((y - 1) >= 0 && Maze[x][y - 1] == 0)//��(x,y-1)�������ҿ���  
	{
		MazeTrack(x, y - 1);
	}

	if ((y + 1)<N && Maze[x][y + 1] == 0)//��(x,y+1)�������ҿ���  
	{
		MazeTrack(x, y + 1);
	}

	//������һ��  
	Path.pop_back();
	Maze[x][y] = 0;         //����Ϊδ��  
}


int main(int argc, char* argv[])
{
	//��ʼ���Թ�  
	InitMaze();

    //��ʾ�Թ�
	for(int i=0;i<N;++i)
	{
		for(int j=0;j<N;++j)
		{ 
			cout<<Maze[i][j]<<"  ";
		}	
		cout<<endl;
	}

	//���ݷ����Թ�  
	MazeTrack(ENTER_X, ENTER_Y);

	//��ʾ���ŵ�·��  
	cout << "����·��������Ϊ" << paths << "������·��Ϊ" << endl;
	vector<Point>::iterator it;
	for (it = BestPath.begin(); it != BestPath.end(); ++it)
	{
		cout << "(" << it->x << "," << it->y << ") ";
	}
	cout << endl;
	system("pause");
	return 0;
}