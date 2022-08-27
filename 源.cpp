#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<Windows.h>


#define MAX_GRID 4//number of girds per row
#define GRID_WIDTH 100//Grid width
#define INTERVAL 15//Grid interval
enum Color//different color
{
	zero = RGB(205, 193, 180),//color of 0
	twoTo1 = RGB(238, 228, 218),
	twoTo2 = RGB(237, 224, 200),
	twoTo3 = RGB(242, 177, 121),
	twoTo4 = RGB(245, 149, 99),
	twoTo5 = RGB(246, 124, 95),
	twoTo6 = RGB(246, 94, 59),
	twoTo7 = RGB(242, 177, 121),
	twoTo8 = RGB(237, 204, 97),
	twoTo9 = RGB(255, 0, 128),
	twoTo10 = RGB(145, 0, 72),
	twoTo11 = RGB(242, 17, 158),
	back = RGB(280, 173, 160)//color of back
};
Color arr[13] = { zero,twoTo1,twoTo2,twoTo3,twoTo4,twoTo5,twoTo6,twoTo7,twoTo8,twoTo9,twoTo10,twoTo11,back };
int num[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
int map[MAX_GRID][MAX_GRID];//ALL VARIABLES
POINT pos[MAX_GRID][MAX_GRID];//Save the coordinates of the upper left corner of each grid
bool flag = false;
//define function, return to 2 or 
int twoOrFour()
{
	if (rand() % 10 == 1)
	{
		return 4;
	}
	else
	{
		return 2;
	}
}
//Generate numbers at random positions, then put numbers into an array
void CreateNumber()
{
	while (1)
	{
		int x = rand() % MAX_GRID;
		int y = rand() % MAX_GRID;
		if (map[x][y] == 0)
		{
			map[x][y] = twoOrFour();
			break;
		}

	}
}

void GameInit()
{
	//random number seed
	srand(GetTickCount());
	//Calculate grid coordinates
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			pos[i][k].x = k * GRID_WIDTH + (k + 1)*INTERVAL;
			pos[i][k].y = i * GRID_WIDTH + (i + 1)*INTERVAL;
		}
	}
	//The game starts to randomly generate two numbers
	CreateNumber();
	CreateNumber();


}
void GameDraw()
{
	setbkcolor(back);
	cleardevice();
	for (int i = 0; i < MAX_GRID; i++)
	{
		for (int k = 0; k < MAX_GRID; k++)
		{
			for (int q = 0; q < 12; q++)
			{
				if (map[i][k] == num[q])
				{
					setfillcolor(arr[q]);
					solidrectangle(pos[i][k].x, pos[i][k].y, pos[i][k].x + GRID_WIDTH, pos[i][k].y + GRID_WIDTH);
					if (map[i][k] != 0)
					{
						char number[5] = " ";
						settextcolor(RGB(119, 110, 101));
						setbkmode(TRANSPARENT);
						sprintf_s(number, "%d", map[i][k]);
						//Half the grid minus half the width of the string, to center the numbers
						int tempx = GRID_WIDTH / 2 - textwidth(number) / 2;
						int tempy = GRID_WIDTH / 2 - textheight(number) / 2;
						outtextxy(pos[i][k].x + tempx, pos[i][k].y + tempy, number);

					}
				}
			}
		}
	}
}
//Moving to the up
void moveup()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_GRID; begin++)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
				}
				else
				{
					map[temp + 1][i] = map[begin][i];
					if (temp + 1 != begin)
					{
						map[begin][i] = 0;
					}
				}
				temp++;
				flag = true;
			}
		}
	}
	printf("up\n");
}
//Moving to the down
void movedown()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = MAX_GRID - 1;
		for (int begin = MAX_GRID - 2; begin >= 0; begin--)
		{
			if (map[begin][i] != 0)
			{
				if (map[temp][i] == 0)
				{
					map[temp][i] = map[begin][i];
					map[begin][i] = 0;
				}
				else if (map[temp][i] == map[begin][i])
				{
					map[temp][i] += map[begin][i];
					map[begin][i] = 0;
				}
				else
				{
					map[temp - 1][i] = map[begin][i];
					if (temp - 1 != begin)
					{
						map[begin][i] = 0;
					}
				}
				temp--;
				flag = true;
			}
		}
	}
	printf("down\n");
}
//moving to the left
void moveleft()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = 0;
		for (int begin = 1; begin < MAX_GRID; begin++)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
				}
				else
				{
					map[i][temp + 1] = map[i][begin];
					if (temp + 1 != begin)
					{
						map[i][begin] = 0;
					}
				}
				temp++;
				flag = true;
			}
		}
	}
	printf("left\n");
}
// moving to the right
void moveright()
{
	for (int i = 0; i < MAX_GRID; i++)
	{
		int temp = MAX_GRID - 1;
		for (int begin = 2; begin >= 0; begin--)
		{
			if (map[i][begin] != 0)
			{
				if (map[i][temp] == 0)
				{
					map[i][temp] = map[i][begin];
					map[i][begin] = 0;
				}
				else if (map[i][temp] == map[i][begin])
				{
					map[i][temp] += map[i][begin];
					map[i][begin] = 0;
				}
				else
				{
					map[i][temp - 1] = map[i][begin];
					if (temp - 1 != begin)
					{
						map[i][begin] = 0;
					}
				}
				temp--;
				flag = true;
			}
		}
	}
	printf("right\n");
}
void GameJude()
{
	if (flag)
	{
		CreateNumber();
		flag = false;
	}
}
//keyboard control number movement
void GameControl()
{
	//get keyboard input,——getch();
	char key = _getch();
	switch (key)
	{
	case 'w':
	case 'W':
	case 72:
		moveup();

		break;
	case 's':
	case 'S':
	case 80:
		movedown();

		break;
	case 'a':
	case 'A':
	case 75:
		moveleft();

		break;
	case 'd':
	case 'D':
	case 77:
		moveright();

		break;
	}
}
int main()
{
	//create a window
	initgraph(MAX_GRID*GRID_WIDTH + 5 * INTERVAL, MAX_GRID*GRID_WIDTH + 5 * INTERVAL, 1);
	GameInit();
	while (1)
	{
		GameDraw();
		GameControl();
		GameJude();
	}

	getchar();
	return 0;
}