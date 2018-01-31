#include <iostream>
#include <cstring>
#include <iomanip>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
void init_console();//初始化控制台
void gotoxy(int, int);//坐标
void map();//地图
void gameover();
void dis_conctrl();
bool gameOver = false;

const int bgn_x = 4;
const int bgn_y = 3;

class squre
{
private:
	int LorR, Dow, full, n, cr, _line;

	struct Point { int x, y; }a[4], b[4], nex[4];
	static int squr[7][4];
	static int date[20][10];
	WORD color, color_date[20][10];
	static WORD group_color[2][4];
public:
	squre();


	friend void KeyConctrl(squre &s, int key);
	//生成一种方块保存好坐标
	void Oput_sqr()
	{
		color = group_color[cr][rand() % 4];
		srand((unsigned int)time(NULL));
		n = rand() % 7;
		for (int i = 0; i<4; i++)
		{
			nex[i].x = squr[n][i] / 2;
			nex[i].y = squr[n][i] % 2;
		}
	}

	//移动
	void move()
	{
		for (int i = 0; i<4; i++)
		{
			a[i].x += LorR;
		}
		if (check())
		{
			for (int i = 0; i<4; i++)a[i] = b[i];
		}
		cls();
		dis();
	}
	//下落
	bool down()
	{
		if (check())return true;

		for (int i = 0; i<4; i++)
		{
			a[i].y += Dow;
		}
		if (check())
		{
			for (int i = 0; i<4; i++)
			{
				if (a[i].y < 6) return true;
			}
			for (int i = 0; i<4; i++)
			{
				a[i] = b[i];
				date[(a[i].y - 4)][(a[i].x - 1)] = full;
				color_date[(a[i].y - 4)][(a[i].x - 1)] = color;
			}

			check_line();
			cls_next();
			//把nex的给a[i]
			for (int i = 0; i<4; i++)
			{
				a[i].x = bgn_x + nex[i].x;
				a[i].y = bgn_y + nex[i].y;
				b[i] = a[i];
			}
			//重新生成给 nex
			nexteris();
		}
		else
		{
			cls(); dis();
		}
		return false;
	}
	//旋转系统
	void rotate(bool cw)
	{
		cls();
		Point p = a[2];
		int min_x = a[0].x;
		int max_y = a[0].y;
		for (int i = 1; i<4; i++)
		{
			min_x = min_x <= a[i].x ? min_x : a[i].x;
		}
		for (int i = 1; i<4; i++)
		{
			max_y = max_y >= a[i].y ? max_y : a[i].y;
		}

		for (int i = 0; i<4; i++)
		{
			int x = a[i].x;
			int y = a[i].y;
			if (cw)//逆时针
			{
				a[i].x = (y - p.y) + p.x;
				a[i].y = (p.x - x) + p.y;
			}
			else//顺时针
			{
				a[i].x = (p.x - y) + p.y;
				a[i].y = (p.y + x) - p.x;
			}
		}

		int min_xx = a[0].x;
		int max_yy = a[0].y;
		for (int i = 1; i<4; i++)
		{
			min_xx = min_xx <= a[i].x ? min_xx : a[i].x;
		}
		for (int i = 1; i<4; i++)
		{
			max_yy = max_yy >= a[i].y ? max_yy : a[i].y;
		}

		int x_xx = min_x - min_xx;
		int y_yy = max_y - max_yy;
		for (int i = 0; i<4; i++)
		{
			a[i].x += x_xx;
			a[i].y += y_yy;

		}

		if (!n)
		{
			if (a[0].x == a[1].x)
			{
				for (int i = 0; i<4; i++)
				{
					a[i].x += 2;
				}
			}
			else
			{
				int _x = a[0].x;
				for (int i = 1; i<4; i++)
				{
					_x = _x <= a[i].x ? _x : a[i].x;
				}
				if (_x <= 2)
				{
					for (int i = 0; i<4; i++)
					{
						a[i].x -= _x - 1;
					}
				}
				else
				{
					for (int i = 0; i<4; i++)
					{
						a[i].x -= 2;
					}
				}
			}
		}

		int max_x = a[0].x;
		for (int i = 1; i<4; i++)
		{
			max_x = max_x >= a[i].x ? max_x : a[i].x;
		}

		if (max_x > 10)
		{
			for (int i = 0; i<4; i++)
			{
				a[i].x -= (max_x - 10);
			}
		}

		if (check())
		{
			for (int i = 0; i<4; i++)
			{
				a[i] = b[i];
			}
		}
		dis();
	}

	//碰撞检测
	bool check()
	{
		for (int i = 0; i < 4; i++)
		{
			if (a[i].x < 1 || a[i].x > 10 || a[i].y > 23)return true;
			else if ((a[i].y > 3) && date[(a[i].y - 4)][(a[i].x - 1)]) return true;//
		}
		return false;
	}

	//颜色设置
	void chg_color(WORD col)
	{
		SetConsoleTextAttribute(hOut, col);
	}
	//显示指定方块
	void dis()
	{
		for (int i = 0; i<4; i++)
		{
			b[i] = a[i];
			if (a[i].y > 3)
			{
				gotoxy(a[i].x, a[i].y);
				chg_color(color);
				cout << "■";
			}
		}

	}
	//清除方块
	void cls()
	{
		for (int i = 0; i<4; i++)
		{
			if (b[i].y > 3)
			{
				gotoxy(b[i].x, b[i].y);
				cout << "  ";
			}
		}
	}
	//消行
	void check_line()
	{
		int h = 19; 
		int sum;
		for (int i = 19; i>0; i--)
		{
			sum = 0;
			for (int j = 0; j<10; j++)
			{
				if (date[i][j])
				{
					sum++;
				}

				gotoxy(1 + j, h + 4);
				if (date[i][j])
				{
					chg_color(color_date[i][j]);
					cout << "■";
				}
				else cout << "  ";
				date[h][j] = date[i][j];
				color_date[h][j] = color_date[i][j];

			}
			if (sum < 10) h--;
			else
			{
				_line++;
				dis_score();
			}
		}

	}
	//显示积分
	void dis_score()
	{
		gotoxy(2, 2);
		chg_color(0x05);
		cout << setfill('0') << setw(5) << _line * 1000;
	}

	//.........................//
	//下一方块提示
	void nexteris()
	{
		Oput_sqr();
		for (int i = 0; i<4; i++)
		{
			gotoxy(nex[i].x + 7, nex[i].y + 1);
			chg_color(0x07);
			cout << "■";
		}
	}
	//清除下一方块
	void cls_next()
	{
		for (int j = 0; j<2; j++)
		{
			for (int i = 0; i<4; i++)
			{
				gotoxy(7 + i, 1 + j);
				cout << " ";
			}
		}
	}
};

 squre::squre()
{


	color = 0x01;
	LorR = n = cr = _line = 0;
	Dow = full = 1;
	Oput_sqr();
	for (int i = 0; i<4; i++)
	{
		a[i].x = bgn_x + nex[i].x;
		a[i].y = bgn_y + nex[i].y;
		b[i] = a[i];
	}
	nexteris();
	dis_score();
}


//7种状态方块
int squre::squr[7][4] = {
	1,3,5,7,//I
	2,4,5,7,//Z
	3,5,4,6,//S
	3,5,4,7,//T
	2,3,5,7,//L
	3,5,7,6,//J
	2,3,4,5 //O
};
WORD squre::group_color[2][4] =
{
	0x1,0x3,0x5,0x7,
	0x2,0x4,0x6,0x7
};
int squre::date[20][10] = { 0 };
void KeyConctrl(squre &s, int key)
{
	switch (key)
	{
	case ' ':
		break;
	case '0':
	case 'q':
	case 'Q':
		s.rotate(1);
		break;
	case 'w':
	case 'W':
	case 72:
		s.rotate(0);
		break;
	case 'a':
	case 'A':
	case 75:
		s.LorR = -1, s.move();
		break;
	case 'd':
	case 'D':
	case 77:
		s.LorR = 1; s.move();
		break;
	case 's':
	case 'S':
	case 80:
		s.down();
		break;
	case '+':
		s.cr = s.cr == 0 ? 1 : 0;
		break;
	default: break;
	}
}

int main()
{
	init_console();
	map();
	dis_conctrl();
	squre sqr;
	clock_t t1, t2;
	t1 = clock();
	while (!gameOver)
	{
		if (_kbhit())
		{
			KeyConctrl(sqr, _getch());
		}

		t2 = clock();
		if ((t2 - t1) > 0.3 * CLOCKS_PER_SEC)
		{
			t1 = t2;
			gameOver = sqr.down();
		}
	}
	gameover();
	getchar();
	CloseHandle(hOut);
	return 0;
}
void init_console()
{
	CONSOLE_CURSOR_INFO cur = { 1, FALSE };
	SetConsoleCursorInfo(hOut, &cur);
	system("color 0e");
}
void gotoxy(int x, int y)
{
	COORD rc = { (short)(2 * x), (short)y };
	SetConsoleCursorPosition(hOut, rc);
}
void map()
{
	//上边框
	gotoxy(0, 0);
	for (int i = 0; i < 12; i++)
	{
		cout << "□";
	}
	gotoxy(1, 3);
	for (int i = 0; i < 10; i++)
	{
		cout << "□";
	}

	//左右边框
	for (int i = 0; i < 25; i++)
	{
		gotoxy(0, i);
		cout << "□";
		gotoxy(11, i);
		cout << "□";
	}
	//中隔线
	for (int i = 1; i < 3; i++)
	{
		gotoxy(6, i);
		cout << "□";
	}
	//下边框
	gotoxy(0, 24);
	for (int i = 0; i < 12; i++)
	{
		cout << "□";
	}
	//score
	SetConsoleTextAttribute(hOut, 0x0f);
	gotoxy(2, 1); cout << "score:";
}
void gameover()
{
	SetConsoleTextAttribute(hOut, 0xf0);
	gotoxy(3, 14); cout << " GAME OVER! ";
}
//控制说明
void dis_conctrl()
{
	SetConsoleTextAttribute(hOut, 0xB);
	gotoxy(13, 3);
	cout << "■操作说明：";
	gotoxy(15, 5);
	cout << "□向左移动：← A";
	gotoxy(15, 6);
	cout << "□向右移动：→ D";
	gotoxy(15, 7);
	cout << "□快速下落：↓ S";
	gotoxy(15, 8);
	cout << "□顺时针转：↑ W";
	gotoxy(15, 9);
	cout << "□逆时针转：0  Q";
	gotoxy(15, 10);
	cout << "□变换颜色：+";
	gotoxy(13, 13);
	cout << "●预置有两组颜色：";
	gotoxy(14, 15);
	cout << "◆蓝、浅绿、紫、白";
	gotoxy(14, 16);
	cout << "◆绿、红色、黄、白";
	gotoxy(13, 19);
	cout << "■By:flowind 18.01.15";

}