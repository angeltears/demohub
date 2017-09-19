#pragma once
struct point
{
    int x;
    int y;
    int block;
};

class Maze
{
public:
    Maze();
public:
    point *maze;
};

class Path
{
public:
    Path(){};

public:
    point *pre;
};
