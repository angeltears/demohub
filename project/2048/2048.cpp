#include"2048.h"
#include <stdlib.h>  
#include <time.h>    
#include <conio.h>  
Game::Game()
{
	int i, j , n;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			a[i][j] = 0;
	srand(time(0));
	n = rand() % 4 + 2;
	for (int k = 0; k < n; k++)
	{ 
		i = rand() % 4;
		j = rand() % 4;
		a[i][j] = 2;
	}
	empty = 16 - n;
	score = 0;
	best = 0;
	game_over = false;
}

void Game::draw(void)
{
	int i, j;
	printf("\n\n\n\n");
	printf("                GAME: 2048     SCORE: %06d    STEP: %06d\n  ", score, best);
	printf("             --------------------------------------------------\n\n");
	printf("                        ┌──┬──┬──┬──┐\n");
	for (int i = 0; i < 4; i++)
	{
		printf("                        │");
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] != 0)
			{
				if (a[i][j] < 10)
				{
					printf("  %d │", a[i][j]);
				}
				else if (a[i][j] < 100)
				{
					printf(" %d │", a[i][j]);
				}
				else if (a[i][j] < 1000)
				{
					printf(" %d│", a[i][j]);
				}
				else if (a[i][j] < 10000)
				{
					printf("%4d│", a[i][j]);
				}
				else
				{
					int n = a[i][j];
					for (int k = 1; k < 20; k++)
					{
						n >>= 1;
						if (n == 1)
						{
							printf("2^%02d│", k); /* 超过四位的数字用2的幂形式表示，如2^13形式 */
							break;
						}
					}
				}
			}
			else printf("    │");
		}

		if (i < 3)
		{
			printf("\n                        ├──┼──┼──┼──┤\n");
		}
		else
		{
			printf("\n                        └──┴──┴──┴──┘\n");
		}
	}

	printf("\n");
	printf("             --------------------------------------------------\n");
	printf("                            W↑  A←  →D  ↓S");

}


void Game::play(void)
{
	char ch;
	ch = _getch();
	switch (ch) 
	{
		case 'w':    // 向上移动 
		case 'W':
		{
			to_up();
			system("cls");
			add_number();
			getempty();
			draw();
			gameover();
			break;
		}
		case 's':    // 向下移动 
		case 'S':
		{
			to_down();
			system("cls");
			add_number();
			getempty();
			draw();
			gameover();
			break;
		}
		case 'a':    // 向左移动 
		case 'A':
		{
			to_left();
			system("cls");
			add_number();
			getempty();
			draw();
			gameover();
			break;
		}
		case 'd':     // 向右移动 
		case 'D':
		{
			to_right();
			system("cls");
			add_number();
			getempty();
			draw();
			gameover();
			break;
		}
		case 'q':   // 退出游戏 
		case 'Q':
			exit(0);
			break;
		default:
		{
			system("cls");
			printf("\r\n\n\n\n\n\n");
			cout << "                  --------------------------------------------------" << endl;
			cout << "                  |                  wrong type!!!                 |" << endl;
			cout << "                  |                  please type :                 |" << endl;
			cout << "                  |               w/s/a/d or W/S/A/D               |" << endl;
			cout << "                  |            press q or Q quit game!             |" << endl;
			cout << "                  --------------------------------------------------" << endl;
			cout << "                           Press any key to continue...			 " << endl;
			char r = _getch();
			system("cls");
			draw();
			break;
		}
	}
}


void Game::to_up(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1, k = 0; j < 4; j++)
		{
			if (a[i][j] != 0)
			{
				if (a[k][i] == a[j][i])
				{
					a[k][i] = 2 * a[k][i];
					score += a[k][i];
					a[j][i] = 0;
					k = k + 1;
				}
				else if (a[k][i] == 0)
				{
					a[k][i] = a[j][i];
					a[j][i] = 0;
				}
				else if (k + 1 == j && a[k+1][i] != 0)
				{
					k = k + 1;
				}
				else
				{
					a[k+1][i] = a[j][i];
					if (k + 1 != j)
					{
						a[j][i] = 0;
					}
					k++;
				}
			}
		}
	}
	best = best + 1;
}

void Game::to_down(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2, k = 3; j >= 0; j--)
		{
			if (a[i][j] != 0)
			{
				if (a[k][i] == a[j][i])
				{
					a[k][i] = 2 * a[k][i];
					score += a[k][i];
					a[j][i] = 0;
					k = k - 1;
				}
				else if (a[k][i] == 0)
				{
					a[k][i] = a[j][i];
					a[j][i] = 0;
				}
				else if (k - 1 == j && a[k - 1][i] != 0)
				{
					k = k - 1;
				}
				else
				{
					a[k - 1][i] = a[j][i];
					if (k - 1 != j)
					{
						a[j][i] = 0;
					}
					k--;
				}
			}
		}
	}
	best = best + 1;
}

void Game::to_left(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 1, k = 0; j < 4; j++)
		{
			if (a[i][j] != 0)
			{
				if (a[i][k] == a[i][j])
				{
					a[i][k] = 2 * a[i][k];
					score += a[k][i];
					a[i][j] = 0;
					k = k + 1;
				}
				else if (a[i][k] == 0)
				{
					a[i][k] = a[i][j];
					a[i][j] = 0;
				}
				else if (k + 1 == j && a[i][k+1] != 0)
				{
					k = k + 1;
				}
				else
				{
					a[i][k + 1] = a[i][j];
					if (k + 1 != j)
					{
						a[i][j] = 0;
					}
					k++;
				}
			}
		}
	}
	best = best + 1;
}

void Game::to_right(void)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 2, k = 3; j >= 0; j--)
		{
			if (a[i][j] != 0)
			{
				if (a[i][k] == a[i][j])
				{
					a[i][k] = 2 * a[i][k];
					score += a[k][i];
					a[i][j] = 0;
					k = k - 1;
				}
				else if (a[i][k] == 0)
				{
					a[i][k] = a[i][j];
					a[i][j] = 0;
				}
				else if (k - 1 == j && a[i][k - 1] != 0)
				{
					k = k - 1;
				}
				else
				{
					a[i][k - 1] = a[i][j];
					if (k - 1 != j)
					{
						a[i][j] = 0;
					}
					k--;
				}
			}
		}
	}
	best = best + 1;
}

void Game::add_number(void)
{
	int num;
	int i, j, k;
	int n;
	srand(time(0));
	n = rand() % 2 + 1;
	for (k = 0; k < n; k++)
	{
		if (empty > 0)
		{
			do
			{
				i = rand() % 4;
				j = rand() % 4;
			} while (a[i][j] != 0);
			num = rand() % 3;
			if (num == 1 || num == 2)
			{
				a[i][j] = 2;
			}
			else
				a[i][j] = 4;
			empty = empty - 1;
		}
	}
}

void Game::check_over(void)
{	
	int flag = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (a[i][j] == a[i][j + 1])
			{
				flag = 1;
			}
			if (a[i + 1][j] == a[i][j])
			{
				flag = 1;
			}
		}
	}
	if(flag == 0)
		game_over = true;
	else 
		game_over = false;
}

void Game::gameover(void)
{
	if (empty == 0)
	{
		check_over();
		if (game_over) /* 判断是否输掉游戏 */
		{
			printf("\r                    GAME OVER! TRY THE GAME AGAIN? [Y/N]");
			while (1)
			{
				char ch;
				ch = _getch();
				if (ch == 'y' || ch == 'Y')
				{
					int i, j, n;
					for (i = 0; i < 4; i++)
						for (j = 0; j < 4; j++)
							a[i][j] = 0;
					srand(time(0));
					n = rand() % 4 + 2;
					for (int k = 0; k < n; k++)
					{
						i = rand() % 4;
						j = rand() % 4;
						a[i][j] = 2;
					}
					empty = 16 - n;
					score = 0;
					best = 0;
					game_over = false;
					system("cls");
					draw();
					break;
				}
				if (ch == 'n' || ch == 'N')
					exit(0);
				else
					cout << "\r                    Please input again !   ";
			}
		}
	}
}

void Game::getempty()
{
	int n = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			a[i][j] == 0 ? ++n : 1;
	empty = n;
}