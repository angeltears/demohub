#include<iostream>
using namespace std;
class Game
{
public:
	Game();      // ��ʼ���������ֵ��һ�������ά����Ԫ�� 
	void draw(void);      // ����4 * 4����ͼ 
	void play(void);      // �����ƶ�����
	void to_up(void);     // �����ƶ� 
	void to_down(void);  // �����ƶ� 
	void to_left(void);   // �����ƶ� 
	void to_right(void);  // �����ƶ� 
	void add_number(void);  // ���µ��� 
	void check_over(void);  //�����Ϸ�Ƿ����
	void gameover(void);   //������Ϸ
	void getempty(void);   //��ÿո��ӵ�����
private:
	int a[4][4];
	int empty;
	int score;
	int best;
	bool game_over;
};