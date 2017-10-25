#include<iostream>
using namespace std;
class Game
{
public:
	Game();      // 初始化数组跟赋值第一个随机二维数组元素 
	void draw(void);      // 绘制4 * 4方格图 
	void play(void);      // 控制移动方向
	void to_up(void);     // 向上移动 
	void to_down(void);  // 像下移动 
	void to_left(void);   // 向左移动 
	void to_right(void);  // 向右移动 
	void add_number(void);  // 加新的数 
	void check_over(void);  //检查游戏是否结束
	void gameover(void);   //结束游戏
	void getempty(void);   //获得空格子的数量
private:
	int a[4][4];
	int empty;
	int score;
	int best;
	bool game_over;
};