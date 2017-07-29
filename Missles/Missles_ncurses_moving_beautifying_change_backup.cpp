#include <iostream>
using namespace std;

#include <cmath>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <ncurses.h>

#define _USE_MATH_DEFINES	

	double vdim=0;
	double hdim=0;

	double vgun=0;
	double hgun=0;
	double vmissle=0.1;
	double hmissle=0.1;
	double speed=0;
	double angle=0;
	double t=0;
	bool hit=false;
	bool out_of_bounds=true;
	char retry='y';
	char temp = ' ';
	int t_angle=0;
	int s_vgun=0;
	int s_hgun=0;
	int t_speed=0;
	bool shoot=false;

	double vbot=0;
	double hbot=0;
	double vBotMissle=0.5;
	double hBotMissle=0.5;
	double botSpeed=0;
	double botAngle=0;
	double botT=0;
	bool botHit=false;
	bool bot_out_of_bounds=true;
	int bot_t_angle=0;
	int s_vbot=0;
	int s_hbot=0;
	int bot_t_speed=0;
	bool botShoot=false;
	int tempRandom=9;

	char multiplayer='s';
	int level=0;

	int count=0;

void drawBoard(void)
{
	for (double i=hdim+1 ; i>=0 ; i--)
	{
		for (double j=0; j<=vdim+1; j++)
		{
			if ((i==hmissle && j==vmissle) &&(vmissle == vBotMissle && hmissle == hBotMissle))
			{
				mvprintw(hdim-i+1, 2*j+1, "X ");
			}
			else if ((i==hmissle && j==vmissle) && ((vmissle==vbot && hmissle==hbot) || (vmissle==vgun && hmissle==hgun)))
			{
				mvprintw(hdim-i+1, 2*j+1, "X ");
//				cout << "X ";
			}
			else if ((i==hBotMissle && j==vBotMissle) && ((vBotMissle==vbot && hBotMissle==hbot) || (vBotMissle==vgun && hBotMissle==hgun)))
			{
				mvprintw(hdim-i+1, 2*j+1, "X ");
			}		
			else if(i==hgun && j==vgun)
			{
				mvprintw(hdim-i+1, 2*j+1, "& ");
//				cout << "& ";
			}
			else if (i==hbot && j==vbot)
			{
				mvprintw(hdim-i+1, 2*j+1, "$ ");
//				cout << "$ ";
			}
			else if (i==hmissle && j==vmissle/* && !(hmissle==0 && vmissle==0)*/)
			{
				mvprintw(hdim-i+1, 2*j+1, "o ");
//				cout << "o ";
			}
			else if (i==hBotMissle && j==vBotMissle /*&& !(hBotMissle==0 && vBotMissle==0)*/)
			{
				mvprintw(hdim-i+1, 2*j+1, "0 ");
//				cout << "o ";
			}
			else if (i==0 || i==hdim+1)
			{
				mvprintw(hdim-i+1, 2*j+1, "* ");
//				cout << "* ";
			}
			else if (j==0 || j==vdim+1)
			{
				mvprintw(hdim-i+1, 2*j+1, "* ");
//				cout << "* ";
			}
			else
			{
				mvprintw(hdim-i+1, 2*j+1, "  ");
//				cout << "  ";
			}
		}
//		cout << endl;
	}
}

int main(void)
{
	cout << "Multiplayer or single player vs computer? (enter m or s)\n";
	cin >> multiplayer;
	if (multiplayer=='s')
	{
		cout << "choose level of dificulty (0 hardest-3 easiest)\n";
		cin >> level;
	}
	cout << "Enter the amounts of columns in the board: \n";
	cin >> vdim;
//	vdim=vdim/10;
	cout << "Enter the amounts of rows in the board: \n";
	cin >> hdim;
//	vdim=hdim/10;
	cout << "Enter column starting location for P1: \n";
	cin >> vgun;
//	vdim=vgun/10;
	cout << "Enter row starting location for P1: \n";
	cin >> hgun;
//	vdim=hgun/10;

	if(multiplayer=='m')
	{
		cout << "Enter column starting location for P2: \n";
		cin >> vbot;
		cout << "Enter column starting location for P2: \n";
		cin >> hbot;
	}
	else
	{
		vbot = rand()%int(vdim)+1;
		hbot = rand()%int(hdim)+1;
		while (vbot==vdim || hbot==hdim)
		{
		vbot = rand()%int(vdim)+1;
		hbot = rand()%int(hdim)+1;
		}
	}



//	cout << "Enter speed of missle: \n";
//	cin >> speed;
//	cout << "Enter starting shot angle: \n";
//	cin >> angle;
//	t_angle=angle;
//	t_speed=speed;
//	drawBoard();

	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	cbreak();
	keypad(stdscr, TRUE);



	while (retry=='y')
	{
//		printw("Enter speed of missle: \n");
//		halfdelay(100);
//		speed=getch();
//		printw("Enter starting shot angle of missle: \n");
//		halfdelay(100);
//		angle=getch();

		if (out_of_bounds==true)
		{
			out_of_bounds=false;		
			t=0.1;		
			angle=t_angle;
			speed=t_speed;
			s_vgun=vgun;
			s_hgun=hgun;
			shoot=false;
			hmissle=0.1;
			vmissle=0.1;
		}
//		cout << "Enter speed of missle: \n";
//		cin >> speed;
//		cout << "Enter starting shot angle: \n";
//		cin >> angle;
		if (bot_out_of_bounds==true)
		{	
			bot_out_of_bounds=false;		
			botT=0.1;		
			botAngle=bot_t_angle;	
			botSpeed=bot_t_speed;
			s_vbot=vbot;
			s_hbot=hbot;
			botShoot=false;
			hBotMissle=0.5;
			vBotMissle=0.5;
		}

		while (hit==false && (out_of_bounds==false && bot_out_of_bounds==false))
		{
			if (shoot==true)
			{
				t=t+0.01;
				vmissle=int(s_vgun+speed*cos(angle*((M_PI)/180))*(t));
				hmissle=int(s_hgun+speed*sin(angle*((M_PI)/180))*(t)-4.9*pow(t,2));
			}
			if (botShoot==true)
			{
				botT=botT+0.01;
				vBotMissle=int(s_vbot+botSpeed*cos(botAngle*((M_PI)/180))*(botT));
				hBotMissle=int(s_hbot+botSpeed*sin(botAngle*((M_PI)/180))*(botT)-4.9*pow(botT,2));
			}
//			cout << vmissle << endl << hmissle << endl;
			drawBoard();
			refresh();
			usleep (90000);
//			halfdelay(10000);
			if (hdim+1<=hmissle || vdim+1<=vmissle || vmissle<=0 || hmissle<=0)
			{
				out_of_bounds=true;
//				endwin();
			}
			if (hdim+1<=hBotMissle || vdim+1<=vBotMissle || vBotMissle<=0 || hBotMissle<=0)
			{
				bot_out_of_bounds=true;
//				endwin();
			}
			if (vBotMissle==vmissle && hBotMissle==hmissle)
			{
				out_of_bounds=true;
				bot_out_of_bounds=true;
//				endwin();
			}
			if ((vmissle==vbot && hmissle==hbot) || (vBotMissle==vbot && hBotMissle==hbot))
			{
				hit=true;
				endwin();
//				mvprintw(hdim+5,1, "You Win, have a cookie!\n");
				cout << "Player 1 Win, have a cookie!\n";
			}
			if ((vmissle==vgun && hmissle==hgun) || (vBotMissle==vgun && hBotMissle==hgun))
			{
				hit=true;
				endwin();
//				mvprintw(hdim+5,1, "You Win, have a cookie!\n");
				cout << "Player 2 Win, have a cookie!\n";
			}
			if(vgun==vbot && hgun == hbot)
			{
				hit=true;
				endwin();
//				mvprintw(hdim+5,1, "You Win, have a cookie!\n");
				cout << "Collision - DRAW, no cookies for you!\n";
			}
//			halfdelay(50);
			temp=getch();
			mvprintw(5,vdim+5, "%d", temp);
									//P1 Movment
			if (temp=='w' || temp==KEY_UP)
			{
				hgun=hgun+1;
			}
			if (temp=='s' || temp==KEY_DOWN)
			{
				hgun=hgun-1;
			}
			if (temp=='d' || temp==KEY_RIGHT)
			{
				vgun=vgun+1;
			}
			if (temp=='a' || temp==KEY_LEFT)
			{
				vgun=vgun-1;
			}
			if (temp=='l')
			{
				t_angle=t_angle-1;
			}
			if (temp=='j')
			{
				t_angle=t_angle+1;
			}
			if (temp=='i')
			{
				t_speed=t_speed+1;
			}
			if (temp=='k')
			{
				t_speed=t_speed-1;
			}
			if (temp=='c')
			{
				shoot=true;
			}
								//P2 Movment
			if(multiplayer=='m')
			{
				if (temp=='t')
				{
					hbot=hbot+1;
				}
				if (temp=='g')
				{
					hbot=hbot-1;
				}
				if (temp=='h')
				{
					vbot=vbot+1;
				}
				if (temp=='f')
				{
					vbot=vbot-1;
				}
				if (temp=='v')
				{
					bot_t_angle=bot_t_angle-1;
				}
				if (temp=='b')
				{
					bot_t_angle=bot_t_angle+1;
				}
				if (temp=='n')
				{
					bot_t_speed=bot_t_speed+1;
				}
				if (temp=='m')
				{
					bot_t_speed=bot_t_speed-1;
				}
				if (temp=='z')
				{
					botShoot=true;
				}
			}
			else
			{
				tempRandom=pow(-1,rand())*(rand()%level);
				bot_t_angle=180+angle+tempRandom;
				tempRandom=rand()%(level*10)+5;
				bot_t_speed=speed+tempRandom;
				botShoot=true;

				randomMovement:
				tempRandom=rand()%4;
				if (vBotMissle==vbot+1 || vBotMissle==vbot-1 || hBotMissle==hbot+1 || hBotMissle==hbot-1)
				{
					tempRandom=9;
				}
				if (tempRandom==0 && count%(level*2)==0)
				{
					if (hbot+1>hdim)
					{
						goto randomMovement;
					}
					hbot=hbot+1;
				}
				if (tempRandom==1 && count%(level*2)==0)
				{
					if (hbot-1<=0)
					{
						goto randomMovement;
					}
					hbot=hbot-1;
				}
				if (tempRandom==2 && count%(level*2)==0)
				{
					if (vbot+1>vdim)
					{
						goto randomMovement;
					}
					vbot=vbot+1;
				}
				if (tempRandom==3 && count%(level*2)==0)
				{
					if (vbot-1<=0)
					{
						goto randomMovement;
					}
					vbot=vbot-1;
				}
				
			}
			mvprintw(hdim+5,1, "P1: angle: %d speed: %i P2: angle: %d speed: %i\n ??????: %d ???????: %i ???????: %d ????????: %i\n", angle, t_angle, speed, t_speed, botAngle, bot_t_angle, botSpeed, bot_t_speed);

			if (hdim+1<=hgun || vdim+1<=vgun || vgun<=0 || hgun<=0)
			{
				out_of_bounds=true;
				endwin();
				cout << "Player 1 went out of bounds - Player 1 loses\n";
				retry = 'n';
			}
			if (hdim+1<=hbot || vdim+1<=vbot || vbot<=0 || hbot<=0 )
			{
				out_of_bounds=true;
				endwin();
				cout << "Player 2 went out of bounds - Player 2 loses\n";
				retry = 'n';
			}
						
			if(t==0.1)
			{
				s_vgun=vgun;
				s_hgun=hgun;
				angle=t_angle;
				speed=t_speed;
			}
			if(botT==0.1)
			{
				s_vbot=vbot;
				s_hbot=hbot;
				botAngle=bot_t_angle;	
				botSpeed=bot_t_speed;
			}
			count++;
		}
//		endwin();

/*		if (hit==false)
		{
//			mvprintw(hdim+5,1, "You missed, try again?\n");
			cout << "You missed, try again?\n";
			cout << out_of_bounds << endl << hit << endl;
//			halfdelay(50);
//			retry=getch();
			cin >> retry;
		}
		else
		{
			retry='n';
		} */
		if (hit==true)
		{
			retry='n';
		}
	}

	endwin();
	cout << "count is: " << count << endl;
	return(0);
}
