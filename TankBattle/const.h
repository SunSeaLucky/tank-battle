#pragma once
enum DIRECTION { UP, DOWN, RIGHT, LEFT ,STOP};

const int graphWidth = 850;
const int graphHeight = 600;

int score = 0;
int destroyedTank = 0;
int mapType = 1;

int map1[25][35] = {
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,0,1,1,5,-3,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,2},
	{2,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,2},
	{2,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,2,2,0,0,1,1,0,0,1,1,0,0,1,1,0,2},
	{2,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,2,2,0,0,1,1,0,0,1,1,0,0,1,1,0,2},
	{2,0,1,1,0,0,1,1,0,0,0,0,2,2,0,0,0,0,5,-3,0,0,1,1,0,0,1,1,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,0,2},
	{2,2,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,2,2,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,2},
	{2,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,2},
	{2,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,2},
	{2,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,2},
	{2,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,2},
	{2,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,2},
	{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{2,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,2},
	{2,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,2},
	{2,0,1,1,0,0,0,0,4,-3,1,1,3,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,2},
	{2,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},

};


DIRECTION map1_enemy_1_path[200] = {
	DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,RIGHT,RIGHT,RIGHT,RIGHT,RIGHT,DOWN,
	DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,
	DOWN,DOWN,RIGHT,RIGHT,RIGHT,RIGHT,STOP,STOP,STOP,STOP,STOP,STOP,
	STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,
	STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP
};

DIRECTION map1_enemy_2_path[200] = {
	DOWN,DOWN,DOWN,RIGHT,RIGHT,RIGHT,RIGHT,DOWN,DOWN,DOWN,DOWN,DOWN,
	DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,DOWN,LEFT,
	LEFT,LEFT,LEFT,LEFT,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,
	STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP,
	STOP,STOP,STOP,STOP,STOP,STOP,STOP,STOP
};