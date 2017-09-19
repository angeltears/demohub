#include <iostream>
#include"mazepath.h"

Maze::Maze()
{
    int x = 0;
    int y = 0;
    maze = new point[25];
    
    for (int i = 0; i < 25; i ++)
    {
        maze[i].x = x;
        maze[i].y = y;
        if (i == 6 || i == 8 || i == 11 || i == 13 || i == 16 || i == 18 || i == 21 || i == 23 || i == 24)
        {
            maze[i].block = 1;
        }

        x++;
        if (x == 5)
        {
            x = 0;
            y++;
        }
    }
}
