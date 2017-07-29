#include <iostream>
using namespace std;

#include <cmath>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <ncurses.h>

#define _USE_MATH_DEFINES
	
//Declaration of universal variables (some doubles might be able to be converted to int but were kept that way due to changes being made all the time. names of variables should also be changed
double vdim=0; //amount of collumns on the board
double hdim=0; //amount of rows on the board

double vgun=0; //column number of player 1
double hgun=0; //row number of player 1
double vmissle=0.1; //column number of missle for player 1 (starts at 0.1 in order to not be displayed on the screen before shooting)
double hmissle=0.1; //row number of missle for player 1 (starts at 0.1 in order to not be displayed on the screen before shooting)
double speed=0; //speed of missle for player 1
double angle=0; // angle of missle for player 1
double t=0; //time relative to shooting for player 1
bool out_of_bounds=true; //determins if player 1 or its missle have gone out of screen
char temp = ' '; // used to enter changes to player 1
int t_angle=0; //used to change player 1s angle without affecting current shot.
int s_vgun=0; //used to change player 1s location without affecting current shot
int s_hgun=0; //used to change player 1s location without affecting current shot
int t_speed=0; //used to change player 1s shot speed without affecting current shot
bool shoot=false; //used to determin if a command to shoot has been given by player 1

double vbot=0; //column number of player 2
double hbot=0; //row number of player 2
double vBotMissle=0.5; //column number of missle for player 2 (starts at 0.1 in order to not be displayed on the screen before shooting)
double hBotMissle=0.5; //row number of missle for player 2 (starts at 0.1 in order to not be displayed on the screen before shooting)
double botSpeed=0; //speed of missle for player 2
double botAngle=0; // angle of missle for player 2
double botT=0; //time relative to shooting for player 2
//bool botHit=false;
bool bot_out_of_bounds=true; //determins if player 2 or its missle have gone out of screen
int bot_t_angle=0; //used to change player 2s angle without affecting current shot.
int s_vbot=0; //used to change player 2s location without affecting current shot.
int s_hbot=0; //used to change player 2s location without affecting current shot.
int bot_t_speed=0; //used to change player 2s speed without affecting current shot.
bool botShoot=false; //used to determin if a command to shoot has been given by player 2
int tempRandom=9; //used to generate random numbers for single player computer movement and shooting. (value is 9 to render it usless untill summoned)

char multiplayer='s'; //determins if the game is in single or multi player
int level=0; // determins the level of play
bool hit=false; //determins if a player has been hit
char retry='y'; // used to determne when the game has ended. (looks to be redundant and replaced by "hit", need to check)

int count=0; // usefull to help find problems, plus it is nice to see how many times the screen was redrawn.

//drawBoard is the function that draws the grid for the game. it is called from the main() function
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
			}
			else if ((i==hBotMissle && j==vBotMissle) && ((vBotMissle==vbot && hBotMissle==hbot) || (vBotMissle==vgun && hBotMissle==hgun)))
			{
				mvprintw(hdim-i+1, 2*j+1, "X ");
			}		
			else if(i==hgun && j==vgun)
			{
				mvprintw(hdim-i+1, 2*j+1, "& ");
			}
			else if (i==hbot && j==vbot)
			{
				mvprintw(hdim-i+1, 2*j+1, "$ ");
			}
			else if (i==hmissle && j==vmissle)
			{
				mvprintw(hdim-i+1, 2*j+1, "o ");
			}
			else if (i==hBotMissle && j==vBotMissle)
			{
				mvprintw(hdim-i+1, 2*j+1, "0 ");
			}
			else if (i==0 || i==hdim+1)
			{
				mvprintw(hdim-i+1, 2*j+1, "* ");
			}
			else if (j==0 || j==vdim+1)
			{
				mvprintw(hdim-i+1, 2*j+1, "* ");
			}
			else
			{
				mvprintw(hdim-i+1, 2*j+1, "  ");
			}
		}
	}
}

int main(void)
{
//Initial Settings Configuration
	cout << "Multiplayer or single player vs computer? (enter m or s)\n";
	cin >> multiplayer;
	if (multiplayer=='s')
	{
		//The level determins the speed of your rival and the accuracy at which it shoots
		cout << "choose level of dificulty (1 hardest- 10 easiest)\n";
		cin >> level;
	}
	cout << "Enter the amounts of columns in the board: \n";
	cin >> vdim;
	cout << "Enter the amounts of rows in the board: \n";
	cin >> hdim;
	cout << "Enter column starting location for P1: \n";
	cin >> vgun;
	cout << "Enter row starting location for P1: \n";
	cin >> hgun;

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

//Initializing ncurses screen
	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	cbreak();
	keypad(stdscr, TRUE);

//Starting the game
	while (retry=='y')
	{
//Configuring initial settings of player 1 so he/she can start shooting. These settings are reconfigured upon missle exiting the screen "reloading" the gun to enable new shot. (t=0.1 so the missle wont "hit" the player when shooting it). (missle is location not set to (0,0) to avoid bug with initscr)
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
//Configuring initial settings of player 2 so he/she/it can start shooting. These settings are reconfigured upon missle exiting the screen "reloading" the gun to enable new shot. (t=0.1 so the missle wont "hit" the player when shooting it). (missle is location not set to (0,0) to avoid bug with initscr).
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
			//Changing P1 missle position according to player input and physics equation. (We use s_vgun and s_hgun in order for the movement going on while the missle is moving not to effect the missle location)
			if (shoot==true)
			{
				t=t+0.01;
				vmissle=int(s_vgun+speed*cos(angle*((M_PI)/180))*(t));
				hmissle=int(s_hgun+speed*sin(angle*((M_PI)/180))*(t)-4.9*pow(t,2));
			}
			//Changing P1 missle position according to player input and physics equation.  (We use s_vbot and s_hbot in order for the movement going on while the missle is moving not to effect the missle location)
			if (botShoot==true)
			{
				botT=botT+0.01;
				vBotMissle=int(s_vbot+botSpeed*cos(botAngle*((M_PI)/180))*(botT));
				hBotMissle=int(s_hbot+botSpeed*sin(botAngle*((M_PI)/180))*(botT)-4.9*pow(botT,2));
			}
			//Drawing Board.
			drawBoard();
			refresh();
			usleep (90000);

			//Determining if one of the missles has exited the screen or if the missles hit each other.
			if (hdim+1<=hmissle || vdim+1<=vmissle || vmissle<=0 || hmissle<=0)
			{
				out_of_bounds=true;
			}
			if (hdim+1<=hBotMissle || vdim+1<=vBotMissle || vBotMissle<=0 || hBotMissle<=0)
			{
				bot_out_of_bounds=true;
			}
			if (vBotMissle==vmissle && hBotMissle==hmissle)
			{
				out_of_bounds=true;
				bot_out_of_bounds=true;
			}
			//Determining if a player has been hit or if the players have collided
			if(((vmissle==vbot && hmissle==hbot) || (vBotMissle==vbot && hBotMissle==hbot))&&((vmissle==vgun && hmissle==hgun) || (vBotMissle==vgun && hBotMissle==hgun)))
			{
				hit=true;
				endwin();
				cout << "Both players hit each other at the same time! DRAW! Have two cookies!\n";
			}
			if ((vmissle==vbot && hmissle==hbot) || (vBotMissle==vbot && hBotMissle==hbot))
			{
				hit=true;
				endwin();
				cout << "Player 1 Win, have a cookie!\n";
			}
			if ((vmissle==vgun && hmissle==hgun) || (vBotMissle==vgun && hBotMissle==hgun))
			{
				hit=true;
				endwin();

				cout << "Player 2 Win, have a cookie!\n";
			}
			if(vgun==vbot && hgun == hbot)
			{
				hit=true;
				endwin();

				cout << "Collision - DRAW, no cookies for you!\n";
			}

			//Changing P1 Movment
			temp=getch();
			mvprintw(5,vdim+5, "%d", temp);
				
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
			//Changing P1 shot angle and speed. (We use t_angle and t_speed in order to not effect the current shot)
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
			//Changing P2 Settings
			//First if it is multiplayer
			if(multiplayer=='m')
			{
				//Changing P2 multiplayer movement
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
				//Changing P2 multiplayer shot angle and speed (We use bot_t_angle and bot_t_speed in order to not effect the current shot)
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
			//Single Player (P2 auto plays)
			else
			{
				//Changing P2 computer shot angle and speed (We use bot_t_angle and bot_t_speed in order to not effect the current shot)
				tempRandom=pow(-1,rand())*(rand()%level);
				bot_t_angle=180+angle+tempRandom;
				tempRandom=rand()%(level*10)+5;
				bot_t_speed=speed+tempRandom;
				botShoot=true;

				//Changing P2 computer movement
				randomMovement:
				tempRandom=rand()%4;
				//this "if" is intended to avoid the computer player to colide with its missle directly after shooting
				if (vBotMissle==vbot+1 || vBotMissle==vbot-1 || hBotMissle==hbot+1 || hBotMissle==hbot-1)
				{
					tempRandom=9;
				}
				//determining change in location
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
			
			//printing each players angle and speed at the bottom of the screen
			mvprintw(hdim+5,1, "P1: angle: %d speed: %i P2: angle: %d speed: %i\n ??????: %d ???????: %i ???????: %d ????????: %i\n", angle, t_angle, speed, t_speed, botAngle, bot_t_angle, botSpeed, bot_t_speed);

			//Determining if a player has gone out of bounds, and thus lost.
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
			
			//These 2 "if"s are intended to make the first shots have the angle and speed determined, aswell as making new shots start from the current location (as apposed to the location you were at when the last shot went out of bounds)			
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

			//count has been generally usefull for finding problems, plus it's cool to see how many times the loop ran at the end of the game...
			count++;
		}
		
		//exiting the game if a player has been hit and thus there is a winner or a draw
		if (hit==true)
		{
			retry='n';
		}
	}

	//closing initscr and ending the program
	endwin();
	cout << "count is: " << count << endl;
	return(0);
}
