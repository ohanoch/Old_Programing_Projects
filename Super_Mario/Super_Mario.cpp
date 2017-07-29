#include <iostream>
#include <cmath>
#include <ncurses.h> //initscrn
#include <stdlib.h> //rand
#include <unistd.h> //usleep
#include <cstdlib> //Turgay rand
#include <ctime>
#include <SFML/Audio.hpp>

using namespace std;

int const VDIM=60;
int const HDIM=30;

int vPlayer=1;
int vPlayerPrev=1;
int hPlayer[2]={1,1};
int hPlayerPrev[2]={1,1};
int goomba1=-1;
int goomba1Dir=-1;
int goomba2=-1;
int goomba2Dir=-1;
int goomba3=-1;
int goomba3Dir=-1;
int coin[5][3]; //5 coins, virticle, height, and if it appears
//int turtle=-1;

int CBox[2][3][5];
int CBoxCoins[5];
int BBox[2][3][5];
int gpipe1[2][2];
int gpipe2[3][2];
int gpipe3[4][2];
int goDownPipe[3];
/*
int CBox1[5]={-1,-1,-1,-1,-1};
int CBox2[5]={-1,-1,-1,-1,-1};
int CBox3[5]={-1,-1,-1,-1,-1};
int CBox4[5]={-1,-1,-1,-1,-1};
int CBox5[5]={-1,-1,-1,-1,-1};
int BBox1[5]={-1,-1,-1,-1,-1};
int BBox2[5]={-1,-1,-1,-1,-1};
int BBox3[5]={-1,-1,-1,-1,-1};
int BBox4[5]={-1,-1,-1,-1,-1};
int BBox5[5]={-1,-1,-1,-1,-1};
int pipe1[4]={-1,-1,-1,-1};
int pipe2[6]={-1,-1,-1,-1,-1,-1};
int pipe3[8]={-1,-1,-1,-1,-1,-1,-1,-1};
*/

int mushroom[2];
int mushroomDir=1;
bool mushroomSurface=false;
int flower[2];
bool isBig=false;

bool gameOver=false;
bool empty=true;
int randomNum=0;
int count1=0;
int tempcount1=0;
char movement=' ';
int jump=0;
int speed=0;
int marioDir[2];
bool surface=true;
int score=0;
bool isCoinPrint=false;
bool isMushroomPrint=false;
int lives=1;
int hole[7];
bool isHole=false;
int coincount1=0;
int level=0;

void drawBoard()
{
	for (int i=HDIM+1; i>=0; i--)
	{
		if (i==0 || i==HDIM+1)
		{
			printw("*");
		}
		else
		{
			printw("|");
		}
		
		for (int j=1; j<=VDIM; j++)
		{
			empty=true;
			
			//drawing top and bottom border with holes
			if (i==0)
			{
				isHole=false;
				for (int h=0; h<7; h++)
				{
					if (hole[h]==j)
					{
						isHole=true;
					}
				}
			}
			if((i==0 && isHole==false)|| i==HDIM+1)
			{
				printw("- ");
				empty=false;
			}
			
			//drawing coin
			for (int k=0; k<5; k++)
			{
				if(coin[k][0]==j && coin[k][1]==i)
				{
					attron(COLOR_PAIR(4));
					printw("$ ");
					attroff(COLOR_PAIR(4));
					empty=false;
					isCoinPrint=true;
				}
			}

			//drawing mushrooms
			if (mushroom[0]==j && mushroom[1]==i)
			{
				printw("M ");
				empty=false;
				isMushroomPrint=true;
			}

			//drawing coin and brick boxes
			for(int a=0; a<2; a++)
			{
				for(int b=0; b<2; b++)
				{
					for(int c=0; c<5; c++)
					{
						if(CBox[a][b][c]==j && CBox[a][2][c]==i && isCoinPrint==false && isMushroomPrint==false)
						{
							attron(COLOR_PAIR(1));
							printw("? ");
							attroff(COLOR_PAIR(1));
							empty=false;
						}
						if(BBox[a][b][c]==j && BBox[a][2][c]==i && isCoinPrint==false && isMushroomPrint==false)
						{
							attron(COLOR_PAIR(2));
							printw("B ");
							attroff(COLOR_PAIR(2));
							empty=false;
						}
					}
				}
			}

			//drawing pipes
			for(int k=0; k<2; k++)
			{
				for(int l=0; l<2; l++)
				{
					if(gpipe1[k][l]==j && k+1==i)
					{
						attron(COLOR_PAIR(3));
						printw("P ");
						attroff(COLOR_PAIR(3));
						empty=false;
					}
				}
			}
			for(int k=0; k<3; k++)
			{
				for(int l=0; l<2; l++)
				{
					if(gpipe2[k][l]==j && k+1==i)
					{
						attron(COLOR_PAIR(3));
						printw("P ");
						attroff(COLOR_PAIR(3));
						empty=false;
					}
				}
			}
			for(int k=0; k<4; k++)
			{
				for(int l=0; l<2; l++)
				{
					if(gpipe3[k][l]==j && k+1==i)
					{
						attron(COLOR_PAIR(3));
						printw("P ");
						attroff(COLOR_PAIR(3));
						empty=false;
					}
				}
			}

			//drawing goombas
			if(i==1 && (goomba1==j) && !(goomba1==mushroom[0] && mushroom[1]==1))
			{
				if(vPlayer==j && (hPlayer[0]==i || hPlayer[1]==i))
				{
					printw("X ");
					empty=false;
				}
				else
				{
					attron(COLOR_PAIR(6));
					printw("G ");
					attroff(COLOR_PAIR(6));
					empty=false;
				}
			}
			if(i==1 && (goomba2==j) && !(goomba2==mushroom[0] && mushroom[1]==1))
			{
				if(vPlayer==j && (hPlayer[0]==i || hPlayer[1]==i))
				{
					printw("X ");
					empty=false;
				}
				else
				{
					attron(COLOR_PAIR(6));
					printw("G ");
					attroff(COLOR_PAIR(6));
					empty=false;
				}
			}
			if(i==1 && (goomba3==j) && !(goomba3==mushroom[0] && mushroom[1]==1))
			{
				if(vPlayer==j && (hPlayer[0]==i || hPlayer[1]==i))
				{
					printw("X ");
					empty=false;
				}
				else
				{
					attron(COLOR_PAIR(6));
					printw("G ");
					attroff(COLOR_PAIR(6));
					empty=false;
				}
			}

			//drawing flowers
			if (flower[0]==j && flower[1]==i)
			{
				attron(COLOR_PAIR(7));
				printw("F ");
				attroff(COLOR_PAIR(7));
				empty=false;
			}

			//drawing Mario
			if (vPlayer==j && (hPlayer[0]==i || hPlayer[1]==i))
			{
				if((i==1 && !(goomba1==j || goomba2==j || goomba3==j))|| i!=1)
				{
					attron(COLOR_PAIR(5));
					printw("@ ");
					attroff(COLOR_PAIR(5));
					empty=false;
				}
			}

			//blank background
			if (empty==true /*&& i!=0 */&& i!=VDIM+1)
			{
				printw("  ");
			}
			isCoinPrint=false;
			isMushroomPrint=false;
		}

		if (i==0 || i==HDIM+1)
		{
			printw("*\n");
		}
		else
		{
			printw("|\n");
		}
	}		
}

void shiftLeft()
{
	//shifting everything to the left
	vPlayerPrev=vPlayer;
	vPlayer=vPlayer-1;
	goomba1=goomba1-1;
	goomba2=goomba2-1;
	goomba3=goomba3-1;
	mushroom[0]=mushroom[0]-1;
	flower[0]=flower[0]-1;

	//shiftin boxes
	for(int a=0; a<2; a++)
	{
		for(int b=0; b<2; b++)
		{
			for(int c=0; c<5; c++)
			{
				CBox[a][b][c]=CBox[a][b][c]-1;
				BBox[a][b][c]=BBox[a][b][c]-1;
			}
		}
	}
	
	//shifting pipes
	for (int p=2; p<=4; p++)
	{
		for(int k=0; k<p; k++)
		{
			for(int l=0; l<2; l++)
			{
				if (p==2)
				{
					gpipe1[k][l]=gpipe1[k][l]-1;
				}
				if (p==3)
				{
					gpipe2[k][l]=gpipe2[k][l]-1;
				}
				if (p==4)
				{
					gpipe3[k][l]=gpipe3[k][l]-1;
				}	
			}
		}
	}

	//shifting coins
	for (int l=0; l<5; l++)
	{
		coin[l][0]=coin[l][0]-1;
	} 

	//shifting holes
	for (int l=0; l<7; l++)
	{
		hole[l]=hole[l]-1;
	}
}

void placeBox(int Box[][3][5], int odds)
{
	randomNum=rand();
	if(randomNum%odds==0)
	{
		randomNum=rand();
		for (int k=0; k<5; k++)
		{
			if(randomNum%5==k)
			{
				tempcount1=0;
				for(int i=0; i<5; i++)
				{
					if(!(BBox[0][1][i]>=VDIM && (BBox[0][2][i]==k+2 || BBox[0][2][i]==k+3 || BBox[0][2][i]==k+4)) && !(CBox[0][1][i]>=VDIM && (CBox[0][2][i]==k+2 || CBox[0][2][i]==k+3 || CBox[0][2][i]==k+4)))
					{
						tempcount1++;
					}
				}
				for(int i=0; i<5; i++)
				{
					if(Box[0][0][i]<=-1 && tempcount1==5 && gpipe1[0][1]<VDIM && gpipe2[0][1]<VDIM && gpipe3[0][1]<VDIM)
					{
						Box[0][0][i]=VDIM;
						Box[1][0][i]=VDIM;
						Box[0][1][i]=VDIM+1;
						Box[1][1][i]=VDIM+1;
						Box[0][2][i]=k+3;
						Box[1][2][i]=k+4;
						CBoxCoins[i]=round(rand()%6)+1;
						break;
					} 
				}
			}
		}
	}
}

void nextColumn()
{
	//getting next new column
	randomNum=rand();
	//placing goombas
	if (randomNum%6==0)
	{
		randomNum=rand();
		if (gpipe1[0][1]!=VDIM &&  gpipe2[0][1]!=VDIM && gpipe3[0][1]!=VDIM)	
		{
			if((goomba1<=-1 || goomba1>=VDIM+5)  && randomNum%3==0)
			{
				goomba1=VDIM;
			}
			if((goomba2<=-1 || goomba2>=VDIM+5) && randomNum%3==1)
			{
				goomba2=VDIM;
			}
			if((goomba3<=-1 || goomba3>=VDIM+5) && randomNum%3==2)
			{
				goomba3=VDIM;
			}
		}
	}	
	//place pipes
	else if (randomNum%7==0)
	{
		tempcount1=0;
		for(int i=0; i<5; i++)
		{
			if(!(BBox[0][1][i]>=VDIM && (BBox[0][2][i]==1 || BBox[0][2][i]==2 || BBox[0][2][i]==3 || BBox[0][2][i]==4 || BBox[0][2][i]==5)) && !(CBox[0][1][i]>=VDIM && (CBox[0][2][i]==1 || CBox[0][2][i]==2 || CBox[0][2][i]==3 || CBox[0][2][i]==4 || CBox[0][2][i]==5)))
			{
				tempcount1++;
			}
		}
		randomNum=rand();
		if (gpipe1[0][0]<=-1 && gpipe2[0][1]!=VDIM && gpipe3[0][1]!=VDIM && randomNum%3==0)
		{
			gpipe1[0][0]=VDIM;
			gpipe1[1][0]=VDIM;
			gpipe1[0][1]=VDIM+1;
			gpipe1[1][1]=VDIM+1;
			if (rand()%3==0)
			{
				goDownPipe[0]=1;
			}
		}
		if (gpipe2[0][0]<=-1 && gpipe1[0][1]!=VDIM && gpipe3[0][1]!=VDIM && randomNum%3==1 && tempcount1==5)
		{
			gpipe2[0][0]=VDIM;
			gpipe2[1][0]=VDIM;
			gpipe2[2][0]=VDIM;
			gpipe2[0][1]=VDIM+1;
			gpipe2[1][1]=VDIM+1;
			gpipe2[2][1]=VDIM+1;
			if (rand()%3==0)
			{
				goDownPipe[1]=1;
			}
		}
		if (gpipe3[0][0]<=-1 && gpipe2[0][1]!=VDIM && gpipe1[0][1]!=VDIM && randomNum%3==2 && tempcount1==5)
		{
			gpipe3[0][0]=VDIM;
			gpipe3[1][0]=VDIM;
			gpipe3[2][0]=VDIM;
			gpipe3[3][0]=VDIM;
			gpipe3[0][1]=VDIM+1;
			gpipe3[1][1]=VDIM+1;
			gpipe3[2][1]=VDIM+1;
			gpipe3[3][1]=VDIM+1;
			if (rand()%3==0)
			{
				goDownPipe[2]=1;
			}
		}
	}
	//creating holes
	else if (randomNum%8==0)
	{
		for (int i=0; i<7; i++)
		{
			if (hole[i]<=0)
			{
				hole[i]=VDIM;
				break;
			}
		}
	}
	placeBox(CBox,5);
	placeBox(BBox,8);
}

void blockHit(int Box[][3][5], char boxType)
{
//case that mario hits brick or coin box
	for (int i=0; i<5; i++)
	{
		for (int j=0; j<2; j++)
		{
			for (int k=0; k<2; k++)
			{
				if (vPlayer==Box[k][j][i] && (hPlayer[0]==Box[k][2][i] || hPlayer[1]==Box[k][2][i]))
				{
printw("GGGGGGGGGGGGGGGGGG\t");
					if(hPlayerPrev[1]==Box[0][2][i]-1) //coming from bellow
					{
printw("HHHHHHHHHHHHHHHHHH\t");
						if (hPlayer[0]!=2)
						{
printw("JJJJJJJJJJJJJJJJJJ\t");
							jump=0;
							hPlayer[0]=hPlayer[0]-2;
							hPlayer[1]=hPlayer[1]-2;
						}
						if (hPlayer[0]==2)
						{
printw("LLLLLLLLLLLLLLLLLLL\t");
							jump=0;
							hPlayer[0]=hPlayer[0]-1;
							hPlayer[1]=hPlayer[1]-1;
						}
						if (boxType=='c' && CBoxCoins[i]!=0)
						{
							if (CBoxCoins[i]==6 && (mushroom[0]<=0 || mushroom[0]>=VDIM+5))
							{
								if (hPlayer[0]==hPlayer[1])
								{
									mushroom[0]=Box[0][0][i];
									mushroom[1]=Box[0][2][i]+2;
									CBoxCoins[i]=0;
								}
								else
								{
									flower[0]=Box[0][0][i];
									flower[1]=Box[0][2][i]+2;
									CBoxCoins[i]=0;
								}
							}
							else
							{
								score=score+100;
								coincount1++;
								CBoxCoins[i]--;
								for (int l=0; l<5; l++)
								{
									if (coin[l][0]<=0 && coin[l][1]<=0)
									{
										coin[l][0]=Box[0][0][i];
										coin[l][1]=Box[0][2][i]+1;
										coin[l][2]=2;
										break;
									}
								} 
							}
						}
						if (boxType=='b' && (hPlayer[0]!=hPlayer[1]))
						{
							Box[0][0][i]=-1;
							Box[1][0][i]=-1;
							Box[0][1][i]=-1;
							Box[1][1][i]=-1;
							Box[0][2][i]=-1;
							Box[-1][2][i]=-1;
							score=score+15;
						}
					}
					else if (vPlayerPrev<vPlayer) //comming from the left
					{
						if(hPlayerPrev[0]>hPlayer[0] && hPlayerPrev[0]>Box[1][2][i]) //comming from left and above
						{
							hPlayer[0]=hPlayerPrev[0];
							hPlayer[1]=hPlayerPrev[1];
printw("AAAAAAAAAAA");

						}
						else //comming from left but not comming from above or bellow
						{
							vPlayer=vPlayerPrev;
							speed=0;
printw("BBBBBBBBBBBBB");
						}
					}
					else if (vPlayerPrev>vPlayer) //comming from the right
					{
						if(hPlayerPrev[0]>hPlayer[0]  && hPlayerPrev[0]>Box[1][2][i]) //comming from right and above
						{
printw("CCCCCCCCCCCCC");
							hPlayer[0]=hPlayerPrev[0];
							hPlayer[1]=hPlayerPrev[1];
//								surface=true;
						}
						else //comming from right but not comming from above or bellow
						{
printw("DDDDDDDDDDDDDDD");
							vPlayer=vPlayerPrev;
							speed=0;
						}
					}
					else //comming from above
					{
printw("EEEEEEEEEEEEEEEEEE");
						hPlayer[0]=hPlayerPrev[0];
						hPlayer[1]=hPlayerPrev[1];
//							surface=true;
					}
				}
			}
		}
	}
}

void hitPipe(int pipe[][2],int height)
{
	//case mario hits pipe
	if (((vPlayer==pipe[0][0] || vPlayer==pipe[0][1])) && (hPlayer[0]>=1 && hPlayer[0]<=height))
	{
printw("ZZZZZZZZZZZZZZZZZZZZZZZ\t");
		if (vPlayerPrev<vPlayer) //comming from the left
		{
printw("XXXXXXXXXXXXXXXXXXXXXXX\t");
			if(hPlayerPrev[0]>hPlayer[0] && hPlayerPrev[0]>height) //comming from left and above
			{
printw("VVVVVVVVVVVVVVVVVVVVVVV\t");
				hPlayer[0]=hPlayerPrev[0];
				hPlayer[1]=hPlayerPrev[1];
//					surface=true;
				/*for(l=0; l<5; l++)
				{
					if ((BBlock[1][0][l]==vPlayerPrev || BBlock[1][1][l]==vPlayerPrev))
					{
						hPlayer[0]=hPlayerPrev[0];
						hPlayer[1]=hPlayerPrev[1];
						break;
					}
				}
				if hPlayerPrev[0]!=hPlayer[0])
				{
					vPlayer=vPlayerPrev;
				}*/
			}
			else //comming from left but not comming from above or bellow
			{
printw("QQQQQQQQQQQQQQQQQQQQQQQQ\t");
				vPlayer=vPlayerPrev;
				speed=0;
			}
		}
		else if (vPlayerPrev>vPlayer) //comming from the right
		{
printw("WWWWWWWWWWWWWWWWWWWWWWWWW\t");
			if(hPlayerPrev[0]>hPlayer[0]  && hPlayerPrev[0]>height) //comming from right and above
			{
printw("EEEEEEEEEEEEEEEEEEEEEEEEE\t");
				hPlayer[0]=hPlayerPrev[0];
				hPlayer[1]=hPlayerPrev[1];
//						surface=true;
			}
			else //comming from right but not comming from above or bellow
			{
printw("RRRRRRRRRRRRRRRRRRRRRRRR\t");
				vPlayer=vPlayerPrev;
				speed=0;
			}
		}
		else //comming from above
		{
printw("TTTTTTTTTTTTTTTTTTTTTTTT\t");
			hPlayer[0]=hPlayerPrev[0];
			hPlayer[1]=hPlayerPrev[1];
//					surface=true;
		}
	}
}

void drawSecretLevel()
{
	for (int i=HDIM+1; i>=0; i--)
	{
		if (i==0 || i==HDIM+1)
		{
			printw("*");
		}
		else
		{
			printw("|");
		}
		
		for (int j=1; j<=VDIM; j++)
		{
			empty=true;
			
			//drawing top and bottom border
			if (i==0 || i==HDIM+1)
			{
				printw("- ");
				empty=false;
			}

			//drawing coins
			for (int k=0; k<5; k++)
			{
				if(coin[k][0]==j && coin[k][1]==i)
				{
					attron(COLOR_PAIR(4));
					printw("$ ");
					attroff(COLOR_PAIR(4));
					empty=false;
				}
			}				
			//drawing Mario
			if (vPlayer==j && (hPlayer[0]==i || hPlayer[1]==i))
			{
				attron(COLOR_PAIR(5));
				printw("@ ");
				attroff(COLOR_PAIR(5));
				empty=false;
			}
			//blank background
			if (empty==true /*&& i!=0 */&& i!=VDIM+1)
			{
				printw("  ");
			}	
		}

		if (i==0 || i==HDIM+1)
		{
			printw("*\n");
		}
		else
		{
			if(i==1 || i==2)
			{
				attron(COLOR_PAIR(3));
				printw("P \n");
				attroff(COLOR_PAIR(3));
			}
			else
			{
				printw("|\n");
			}
		}
	}		
}

void secretLevel(int height)
{
	refresh();
	int secretCoincount1=rand()%20+1;
	char secretMovement=' ';
	bool secretGameOver=false;

	for (int i=0; i<5; i++)
	{
		if (coin[i][2]<=0 && secretCoincount1>0)
		{
			coin[i][0]=rand()%VDIM+1;
			coin[i][1]=rand()%HDIM+1;
			coin[i][2]=1;
			secretCoincount1--;
		}
	}

	while(secretGameOver==false)
	{
		secretMovement=getch();

		//Moving Mario
		if (jump>0)
		{
			hPlayerPrev[0]=hPlayer[0];
			hPlayerPrev[1]=hPlayer[1];
			hPlayer[0]=hPlayer[0]+1;
			hPlayer[1]=hPlayer[1]+1;
			jump--;
		}
		else if (jump==0 && hPlayer[0]!=1)
		{
			hPlayerPrev[0]=hPlayer[0];
			hPlayerPrev[1]=hPlayer[1];
			hPlayer[0]=hPlayer[0]-1;
			hPlayer[1]=hPlayer[1]-1;
		}			
		else if (secretMovement=='w' || secretMovement==KEY_UP)
		{
			jump=3+speed;
			speed=0;
		}
		else if(hPlayer[0]==1)
		{
			hPlayerPrev[0]=hPlayer[0];
			hPlayerPrev[1]=hPlayer[1];
		}
		if (secretMovement=='a' || secretMovement==KEY_LEFT)
		{
			vPlayerPrev=vPlayer;
			vPlayer=vPlayer-1;
			marioDir[0]=marioDir[1];
			marioDir[1]=-1;
		}
		else if (secretMovement=='d' || secretMovement==KEY_RIGHT)
		{
			vPlayerPrev=vPlayer;
			vPlayer=vPlayer+1;
			marioDir[0]=marioDir[1];
			marioDir[1]=1;
		}
		else
		{
			vPlayerPrev=vPlayer;
			marioDir[0]=0;
			marioDir[1]=0;
		}
		if (marioDir[0]==marioDir[1] && (marioDir[0]==1 || marioDir[0]==-1) && hPlayer[0]==1 && vPlayer!=0)
		{
			speed++; //going same direction
		}
		else if ((marioDir[0]==0 && marioDir[1]==0) || vPlayer==0)	
		{
			speed=0; //standing still
		}
		else
		{
			speed=1; //change direction or move from standing still
		}

		//Mario out of borders
		if (vPlayer==0 || (vPlayer==VDIM+1 && hPlayer[1]>2))
		{
			vPlayer=vPlayerPrev;
		}

		//returning to normal game
		else if (vPlayer==VDIM+1 && hPlayer[1]<=2)
		{
			secretGameOver=true;
			for (int i=2; i<=4; i++)
			{
				if (height==i)
				{
					switch (i)
					{
						case 2:	vPlayer=gpipe1[0][0];
						case 3: vPlayer=gpipe2[0][0];
						case 4: vPlayer=gpipe3[0][0];
					}

					if (hPlayer[0]==hPlayer[1])
					{
						hPlayer[0]=i+1;
						hPlayer[1]=i+1;
					}
					else
					{
						hPlayer[0]=i+1;
						hPlayer[1]=i+2;
					}
				}
			}
		}
		
		//collecting coin
		for (int i=0; i<5; i++)
		{
			if (coin[i][0]==vPlayer && (coin[i][1]==hPlayer[0] || coin[i][1]==hPlayer[1]))
			{
				score=score+100;
				coin[i][0]=-1;
				coin[i][1]=-1;
				coin[i][2]=-1;
				coincount1++;
			}
		}
		
		//coin regeneration
		for (int i=0; i<5; i++)
		{
			if (coin[i][2]<=0 && secretCoincount1>0)
			{
				coin[i][0]=rand()%VDIM+1;
				coin[i][1]=rand()%HDIM+1;
				coin[i][2]=1;
				secretCoincount1--;
			}
		}
		
		move(0,0);
		drawSecretLevel();
		refresh();
		usleep(185000);
		if (score>0)
		{
			score--;
		}

		printw("\n\n score: %i\t lives: %i\t coincount1: %i\t speed: %i\t secretCoincount1: %i\n", score, lives, coincount1, speed, secretCoincount1);
		printw("vPlayer: %i\n",vPlayer);
	}
	
}

void drawBossLevel(int bowser [], int shot [][2], int level, int bossHole[])
{
	bool isBossHole=false;
	for (int i=HDIM+1; i>=0; i--)
	{
		if (i==0 || i==HDIM+1)
		{
			printw("*");
		}
		else
		{
			printw("|");
		}
		
		for (int j=1; j<=VDIM; j++)
		{
			empty=true;
			
			//drawing top and bottom border with holes
			if (i==0)
			{
				isBossHole=false;
				for (int h=0; h<7; h++)
				{
					if (bossHole[h]==j)
					{
						isBossHole=true;
					}
				}
			}
			if((i==0 && isBossHole==false)|| i==HDIM+1)
			{
				printw("- ");
				empty=false;
			}

			//drawing coins
			for (int k=0; k<5; k++)
			{
				if(coin[k][0]==j && coin[k][1]==i)
				{
					attron(COLOR_PAIR(4));
					printw("$ ");
					attroff(COLOR_PAIR(4));
					empty=false;
				}
			}				
	
			for (int k=0; k<level; k++)
			{
				//drawing Mario
				if ((vPlayer==j && (hPlayer[0]==i || hPlayer[1]==i))
				 && !(vPlayer==bowser[0] && (hPlayer[0]==bowser[1] || hPlayer[1]==bowser[1]))
				 && !(vPlayer==shot[k][0] && (hPlayer[0]==shot[k][1] || hPlayer[1]==shot[k][1])))
				{
					attron(COLOR_PAIR(5));
					printw("@ ");
					attroff(COLOR_PAIR(5));
					empty=false;
					break;
				}
				//Mario hits Bowser
				else if ((vPlayer==j && (hPlayer[0]==i || hPlayer[1]==i)) && (vPlayer==bowser[0] && (hPlayer[0]==bowser[1] || hPlayer[1]==bowser[1])))
				{
					printw("X ");
					empty=false;
				}
				//Mario hits shot
				else if ((vPlayer==j && (hPlayer[0]==i || hPlayer[1]==i)) && (vPlayer==shot[k][0] && (hPlayer[0]==shot[k][1] || hPlayer[1]==shot[k][1])))
				{
					printw("X ");
					empty=false;
				}

			}
			//drawing Bowser
			if ((bowser[0]==j && bowser[1]==i) && !(vPlayer==bowser[0] && (hPlayer[0]==bowser[1] || hPlayer[1]==bowser[1])))
			{
				attron(COLOR_PAIR(8));
				printw("B ");
				attroff(COLOR_PAIR(8));
				empty=false;
			}
			//drawing shot
			for (int k=0; k<level; k++)
			{
				if((shot[k][0]==j && shot [k][1]==i )&& !(vPlayer==shot[k][0] && (hPlayer[0]==shot[k][1] || hPlayer[1]==shot[k][1])))
				{
					attron(COLOR_PAIR(6));
					printw("< ");
					attroff(COLOR_PAIR(6));
					empty=false;
				}
			}
			//blank background
			if (empty==true /*&& i!=0 */&& i!=VDIM+1)
			{
				printw("  ");
			}	
		}

		if (i==0 || i==HDIM+1)
		{
			printw("*\n");
		}
		else
		{
			if(i==1 || i==2)
			{
				attron(COLOR_PAIR(3));
				printw("P \n");
				attroff(COLOR_PAIR(3));
			}
			else
			{
				printw("|\n");
			}
		}
	}		
}

int bossLevel(int level)
{
	refresh();
	int bowser[2]={VDIM-1,1};
	int bossCoincount1=rand()%20+1;
	char secretMovement=' ';
	bool bossGameOver=false;
	int bowserMove=0;
	int bowserJump=0;
	int shot[level][2];
	int bossHole[level];
	int bosscount1=0;

	//initializing player position
	vPlayerPrev=5;
	vPlayer=5;
	if(hPlayer[0]==hPlayer[1])
	{
		hPlayerPrev[0]=5;
		hPlayerPrev[1]=5;
		hPlayer[0]=5;
		hPlayer[1]=5;
	}
	else
	{
		hPlayerPrev[0]=5;
		hPlayerPrev[1]=6;
		hPlayer[0]=5;
		hPlayer[1]=6;
	}

	//initializing coins
	for (int i=0; i<5; i++)
	{
		if (coin[i][2]<=0 && bossCoincount1>0)
		{
			coin[i][0]=rand()%VDIM+1;
			coin[i][1]=rand()%HDIM+1;
			coin[i][2]=1;
			bossCoincount1--;
		}
	}

	//creating holes
	for (int i=0; i<level; i++)
	{
		bossHole[i]=rand()%(VDIM-4)+4;
	}

	//initializing Bowser shot
	for (int i=0; i<level; i++)
	{
		shot[i][0]=0;
	}

	while(bossGameOver==false)
	{
		bosscount1++;

		//Moving Bowser shot
		for (int i=0; i<level; i++)
		{
			shot[i][0]--;
		}
	
		//Moving Bowser
		if(bosscount1%2==0)
		{
			bowserMove = rand()%(4+level)+1;
			if (bowserMove==1 && bowser[0]>1)
			{
				bowser[0]--;
			}
			if (bowserMove==2 && bowser[0]<VDIM)
			{
				bowser[0]++;
			}
			if (bowserMove==3 && bowser[1]==1)
			{
				bowserJump=2+(rand()%level+1);
				bowser[1]++;
			}
			if (bowserJump>0)
			{
				bowserJump--;
				bowser[1]++;
			}
			if (bowserJump==0 && bowser[1]!=1)
			{
				bowser[1]--;
			}
			//Bowser shooting
			if (bowserMove>=4)
			{			
				for (int i=0; i<level; i++)
				{
					if(shot[i][0]<=0)
					{
						shot[i][0]=bowser[0]-1;
						shot[i][1]=bowser[1];
						break;
					}
				}
			}
		}
		//Moving Mario
		secretMovement=getch();
		if (jump>0)
		{
			hPlayerPrev[0]=hPlayer[0];
			hPlayerPrev[1]=hPlayer[1];
			hPlayer[0]=hPlayer[0]+1;
			hPlayer[1]=hPlayer[1]+1;
			jump--;
		}
		else if (jump==0 && hPlayer[0]!=1)
		{
			hPlayerPrev[0]=hPlayer[0];
			hPlayerPrev[1]=hPlayer[1];
			hPlayer[0]=hPlayer[0]-1;
			hPlayer[1]=hPlayer[1]-1;
		}			
		else if (secretMovement=='w' || secretMovement==KEY_UP)
		{
			jump=3+speed;
			speed=0;
		}
		else if(hPlayer[0]==1)
		{
			hPlayerPrev[0]=hPlayer[0];
			hPlayerPrev[1]=hPlayer[1];
		}
		if (secretMovement=='a' || secretMovement==KEY_LEFT)
		{
			vPlayerPrev=vPlayer;
			vPlayer=vPlayer-1;
			marioDir[0]=marioDir[1];
			marioDir[1]=-1;
		}
		else if (secretMovement=='d' || secretMovement==KEY_RIGHT)
		{
			vPlayerPrev=vPlayer;
			vPlayer=vPlayer+1;
			marioDir[0]=marioDir[1];
			marioDir[1]=1;
		}
		else
		{
			vPlayerPrev=vPlayer;
			marioDir[0]=0;
			marioDir[1]=0;
		}
		if (marioDir[0]==marioDir[1] && (marioDir[0]==1 || marioDir[0]==-1) && hPlayer[0]==1 && vPlayer!=0)
		{
			speed++; //going same direction
		}
		else if ((marioDir[0]==0 && marioDir[1]==0) || vPlayer==0)	
		{
			speed=0; //standing still
		}
		else
		{
			speed=1; //change direction or move from standing still
		}

		//Mario out of borders
		if (vPlayer==0 || (vPlayer==VDIM+1 && hPlayer[1]>2))
		{
			vPlayer=vPlayerPrev;
		}
		
		//getting hit by shot
		for (int i=0; i<level; i++)
		{
			if(vPlayer==shot[i][0] && (hPlayer[0]==shot[i][1] || hPlayer[1]==shot[i][1]))
			{
				lives--;
				shot[i][0]=0;
				shot[i][1]=0;
				hPlayer[1]=hPlayer[0];
			}
		}

		//collecting coin
		for (int i=0; i<5; i++)
		{
			if (coin[i][0]==vPlayer && (coin[i][1]==hPlayer[0] || coin[i][1]==hPlayer[1]))
			{
				score=score+100;
				coin[i][0]=-1;
				coin[i][1]=-1;
				coin[i][2]=-1;
				coincount1++;
			}
		}
		
		//coin regeneration
		for (int i=0; i<5; i++)
		{
			if (coin[i][2]<=0 && bossCoincount1>0)
			{
				coin[i][0]=rand()%VDIM+1;
				coin[i][1]=rand()%HDIM+1;
				coin[i][2]=1;
				bossCoincount1--;
			}
		}
		
		//hitting Bowser
		if (bowser[0]==vPlayer && bowser[1]==hPlayer[0])
		{
			if (hPlayerPrev[0]>hPlayer[0])
			{
				bossGameOver=true;
				vPlayer=5;
				if (hPlayer[0]==hPlayer[1])
				{
					hPlayer[0]=HDIM/2;
					hPlayer[1]=HDIM/2;
				}
				else
				{
					hPlayer[0]=HDIM/3;
					hPlayer[1]=HDIM/2;
				}
				refresh();
				move(VDIM/2,HDIM/2);
				printw("WELCOME TO LEVEL: %i",level+1);
				refresh();
				usleep(1850000);
				return 1;
			}
			else
			{
				lives--;
				vPlayer=1;
				hPlayer[1]=hPlayer[0];
			}
		}

		//dying
		if (lives==0)
		{
			bossGameOver=true;
			gameOver=true;
			return 0;
		}
		//Mario in hole (comment because I dont like to lose)
//		for (int i=0; i<level; i++)
//		{
//			if (bossHole[i]==vPlayer && hPlayer[0]==1)
//			{
//				bossGameOver=true;
//				gameOver=true;				
//				return 0;
//			}
//		}

		if(bossGameOver==false)
		{
			move(0,0);
			drawBossLevel(bowser, shot, level, bossHole);
			refresh();
			usleep(185000);
		}
		if (score>0)
		{
			score--;
		}

		printw("\n\n score: %i\t lives: %i\t coincount1: %i\t speed: %i\t bossCoincount1: %i\t bowserMove: %i\n", score, lives, coincount1, speed, bossCoincount1, bowserMove);
		printw("shot[0][0]: %i\t shot[1][0]: %i\n",shot[0][0], shot[1][0]);		
		printw("vPlayer: %i\n",vPlayer);
	}
	return 1;
}

int main(void)
{
	//initialize music
	sf::Music music;
	if (!music.openFromFile("Theme.ogg"))
	{
		return -1; // error
	}
	music.play();
	
	srand(static_cast<unsigned int>(time(0))); // initialize random number generator

//	cout << "Press any key to start\n";
//	cin.ignore(1);

	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	cbreak();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	init_pair(2, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_GREEN, COLOR_BLACK);

	//creating initial board
	for (int i=1; i<=(VDIM/5)*3; i++)
	{
		shiftLeft();
		nextColumn();
	}
	vPlayer=1;
	hPlayer[0]=1;	
	hPlayer[1]=1;

	//starting game	
	while(gameOver==false)
	{
		count1++;
		printw("count1: %i",count1);
		if (count1%(5-score/500)==0 || vPlayer>=VDIM/2)
		{
			shiftLeft();
			nextColumn();
		}

		//moving Mario
		movement=getch();

		if (jump>0)
		{
			hPlayerPrev[0]=hPlayer[0];
			hPlayerPrev[1]=hPlayer[1];
			hPlayer[0]=hPlayer[0]+1;
			hPlayer[1]=hPlayer[1]+1;
			jump--;
		}
		else if (jump==0 && surface==false)
		{
			hPlayerPrev[0]=hPlayer[0];
			hPlayerPrev[1]=hPlayer[1];
			hPlayer[0]=hPlayer[0]-1;
			hPlayer[1]=hPlayer[1]-1;
//			if (hPlayer[0]==1)
//			{
//				surface=true;
//			}
		}			
		else if (movement=='w' || movement==KEY_UP)
		{
			jump=3+speed;
//			surface=false;
			speed=0;
		}
		else if(surface==true)
		{
			hPlayerPrev[0]=hPlayer[0];
			hPlayerPrev[1]=hPlayer[1];
		}
		if (movement=='s' || movement==KEY_DOWN)
		{
			//case mario goes down a pipe
			if ((vPlayer==gpipe1[0][0] || vPlayer==gpipe1[0][1]) && goDownPipe[0]==1)
			{
				goDownPipe[0]=0;
				secretLevel(2);
			}
			if ((vPlayer==gpipe2[0][0] || vPlayer==gpipe2[0][1]) && goDownPipe[1]==1)
			{
				goDownPipe[1]=0;
				secretLevel(3);
			}
			if ((vPlayer==gpipe3[0][0] || vPlayer==gpipe3[0][1]) && goDownPipe[2]==1)
			{
				goDownPipe[2]=0;
				secretLevel(4);
			}
		}
		if (movement=='a' || movement==KEY_LEFT)
		{
			vPlayerPrev=vPlayer;
			vPlayer=vPlayer-1;
			marioDir[0]=marioDir[1];
			marioDir[1]=-1;
		}
		else if (movement=='d' || movement==KEY_RIGHT)
		{
			vPlayerPrev=vPlayer;
			vPlayer=vPlayer+1;
			marioDir[0]=marioDir[1];
			marioDir[1]=1;
		}
		else
		{
			vPlayerPrev=vPlayer;
			marioDir[0]=0;
			marioDir[1]=0;
		}
		if (marioDir[0]==marioDir[1] && (marioDir[0]==1 || marioDir[0]==-1) && surface==true)
		{
			speed++; //going same direction
		}
		else if (marioDir[0]==0 && marioDir[1]==0)	
		{
			speed=0; //standing still
		}
		else
		{
			speed=1; //change direction or move from standing still
		}
		
		if(count1%2==0)
		{
			//moving goombas
			if (goomba1>0)
			{
				goomba1=goomba1+goomba1Dir;
			}
			if (goomba2>0)
			{
				goomba2=goomba2+goomba2Dir;
			}
			if (goomba3>0)
			{
				goomba3=goomba3+goomba3Dir;
			}
			if (goomba1==gpipe1[0][0] || goomba1==gpipe2[0][0] || goomba1==gpipe3[0][0])
			{
				goomba1=goomba1-2;
				goomba1Dir=goomba1Dir*-1;
			}
			if (goomba1==gpipe1[0][1] || goomba1==gpipe2[0][1] || goomba1==gpipe3[0][1])
			{
				goomba1=goomba1+2;
				goomba1Dir=goomba1Dir*-1;
			}
			if (goomba2==gpipe1[0][0] || goomba2==gpipe2[0][0] || goomba2==gpipe3[0][0])
			{
				goomba2=goomba2-2;
				goomba2Dir=goomba2Dir*-1;
			}
			if (goomba2==gpipe1[0][1] || goomba2==gpipe2[0][1] || goomba2==gpipe3[0][1])
			{
				goomba2=goomba2+2;
				goomba2Dir=goomba2Dir*-1;
			}
			if (goomba3==gpipe1[0][0] || goomba3==gpipe2[0][0] || goomba3==gpipe3[0][0])
			{
				goomba3=goomba3-2;
				goomba3Dir=goomba3Dir*-1;
			}
			if (goomba3==gpipe1[0][1] || goomba3==gpipe2[0][1] || goomba3==gpipe3[0][1])
			{
				goomba3=goomba3+2;
				goomba3Dir=goomba3Dir*-1;
			}
	
			//moving mushroom
			if (mushroom[0]>0 && mushroom[0]<VDIM+5)
			{
				mushroom[0]=mushroom[0]+mushroomDir;
				mushroomSurface=false;
				for (int i=0; i<5; i++)
				{
					if (((mushroom[0]==CBox[0][0][i] || mushroom[0]==CBox[0][1][i]) && mushroom[1]==CBox[1][2][i]+1)
					||  ((mushroom[0]==BBox[0][0][i] || mushroom[0]==BBox[0][1][i]) && mushroom[1]==BBox[1][2][i]+1)
					|| ((mushroom[0]==gpipe1[0][0] || mushroom[0]==gpipe1[0][1]) && mushroom[1]==3)
					|| ((mushroom[0]==gpipe2[0][0] || mushroom[0]==gpipe2[0][1]) && mushroom[1]==4)
					|| ((mushroom[0]==gpipe3[0][0] || mushroom[0]==gpipe3[0][1]) && mushroom[1]==5))
					{
						mushroomSurface=true;		
					}
						
				}
				if (mushroom[1]>1 && mushroomSurface==false)
				{
					mushroom[1]=mushroom[1]-1;
				}
			}
			if (mushroom[0]==gpipe1[0][0] || mushroom[0]==gpipe2[0][0] || mushroom[0]==gpipe3[0][0])
			{
				mushroom[0]=mushroom[0]-2;
				mushroomDir=mushroomDir*-1;
			}
			if (mushroom[0]==gpipe1[0][1] || mushroom[0]==gpipe2[0][1] || mushroom[0]==gpipe3[0][1])
			{
				mushroom[0]=mushroom[0]+2;
				mushroomDir=mushroomDir*-1;
			}
			for (int i=0; i<5; i++)
			{
				for (int j=0; j<2; j++)
				{
					for (int k=0; k<2; k++)
					{
						if ((mushroom[0]==CBox[j][k][i] && mushroom[1]==CBox[j][2][i]) || (mushroom[0]==BBox[j][k][i] && mushroom[1]==BBox[j][2][i]))
						{
							mushroomDir=mushroomDir*-1;
							mushroom[0]=mushroom[0]+2*mushroomDir;
						}
					}
				}
			}
		}
		//Mario hits boxes
		blockHit(BBox, 'b');
		blockHit(CBox, 'c');

		//if Mario hit a coin box, changes coins location
		for (int l=0; l<5; l++)
		{
			if(coin[l][2]==0)
			{
				coin[l][2]--;
				coin[l][0]=-1;
				coin[l][1]=-1;
			}
			if (coin[l][2]>0)
			{
				coin[l][2]--;
				coin[l][1]++;
			}
		} 

		//if Mario hits a pipe
		hitPipe(gpipe1,2);
		hitPipe(gpipe2,3);
		hitPipe(gpipe3,4);
	
		
	
		//case mario hits goomba
		if (vPlayer==goomba1 && hPlayer[0]==1)
		{
			if (hPlayerPrev[0]>1)
			{
				goomba1=-1;
				score=score+75;
			}
			else
			{
				lives--;
				if (hPlayer[0]!=hPlayer[1])
				{
					hPlayer[1]=hPlayer[0];
				}
			}
		}
		if (vPlayer==goomba2 && hPlayer[0]==1)
		{
			if (hPlayerPrev[0]>1)
			{
				goomba2=-1;
				score=score+75;
			}
			else
			{
				lives--;
				if (hPlayer[0]!=hPlayer[1])
				{
					hPlayer[1]=hPlayer[0];
				}
			}
		}
		if (vPlayer==goomba3 && hPlayer[0]==1)
		{
			if (hPlayerPrev[0]>1)
			{
				goomba3=-1;
				score=score+75;
			}
			else
			{
				lives--;
				score=score-30;
				if (hPlayer[0]!=hPlayer[1])
				{
					hPlayer[1]=hPlayer[0];
				}
			}
		}
		//case mario collects mushroom
		if (mushroom[0]==vPlayer && mushroom[1]==hPlayer[0])
		{
			mushroom[0]=-1;
			hPlayer[1]++;
//			isBig=true;
			lives++;
			score=score+150;
		}
		//case mario collects flower
		if (vPlayer==flower[0] && (hPlayer[0]==flower[1] || hPlayer[1]==flower[1]))
		{
			lives++;
			flower[0]=0;
			flower[1]=0;
		}

		//case mario goes out of bounds (commented because I don't like to lose)
//		if (vPlayer <=0)
//		{
//			gameOver=true;
//		}
//		if (vPlayer==VDIM+1)
//		{
//			vPlayer=VDIM;
//		}

		//falling into holes (comments because I don't like to lose)
		for (int h=0; h<7; h++)
		{
			//if(vPlayer==hole[h] && hPlayer[0]==1)
			//{
			//	gameOver=true;
			//	hPlayer[0]--;
			//	hPlayer[1]--;
			//}
			if(goomba1==hole[h])
			{
				goomba1=0;
			}
			if(goomba2==hole[h])
			{
				goomba2=0;
			}
			if(goomba3==hole[h])
			{
				goomba3=0;
			}
		}

		//determining if Mario is on a box or floor rather than in the air
		surface=false;
		for (int i=0; i<5; i++)
		{
			if(((BBox[1][2][i]==hPlayer[0]-1 && (vPlayer==BBox[0][0][i] || vPlayer==BBox[0][1][i]))
			 ||(CBox[1][2][i]==hPlayer[0]-1 && (vPlayer==CBox[0][0][i] || vPlayer==CBox[0][1][i]))
			 || (3==hPlayer[0] && (vPlayer==gpipe1[0][0] || vPlayer==gpipe1[0][1]))
			 || (4==hPlayer[0] && (vPlayer==gpipe2[0][0] || vPlayer==gpipe2[0][1]))
			 || (5==hPlayer[0] && (vPlayer==gpipe3[0][0] || vPlayer==gpipe3[0][1])))
			 ||hPlayer[0]==1)
			{
				surface=true;
				
			}	
		}

		//reseting goDownPipe if pipe disappears
		if (gpipe1[1]==0)
		{
			goDownPipe[0]=0;
		}
		if (gpipe2[1]==0)
		{
			goDownPipe[1]=0;
		}
		if (gpipe3[1]==0)
		{
			goDownPipe[2]=0;
		}

		//adjusting score to go down every cycle
		if (score>0 && count1%2==0)
		{
			score--;
		}
	
		//100 coins=1life
		if (coincount1%100==0 && coincount1!=0)
		{
			lives++;
		}

//		ending game if no lives left (in comment because I don't want to lose :))
//		if (lives==0)
//		{
//			gameOver=true;
//		}

		//entering Boss level
		if (score>1000*(level+1))
		{
			level=level+bossLevel(level+1);
		}

		//drawing the board
		move(0,0);
		drawBoard ();
		refresh();
		usleep(185000);

		printw("\n\n score: %i\t lives: %i\t level: %i\t coincount1: %i\t speed: %i\t", score, lives, level, coincount1, speed);
		printw("vPlayer: %i\n",vPlayer);
//		printw("\n hole1: %i\t hole2: %i\t hole3: %i\t hole4: %i\t hole5: %i\t hole6: %i\t hole7: %i\n", hole[0], hole[1], hole[2], hole[3], hole[4], hole[5], hole[6]);
//		printw("\n hPlayerPrev[0]: %i\t vPlayerPrev: %i\t mushroom[0]: %i\t mushroom[1]: %i\t mushroomDir: %i\t lives: %i\n", hPlayerPrev[0], vPlayerPrev, mushroom[0], mushroom[1], mushroomDir, lives);
//		printw("\nvPlayer: %i\t hPlayer[0]: %i\t hPlayer[1]: %i\t goomba1: %i\t goomba2: %i\t goomba3: %i\n CBox1: %i\t CBox2: %i\t CBox3: %i\t CBox4: %i\t CBox5: %i\n BBox1: %i\t BBox2: %i\t BBox3: %i\t BBox4: %i\t BBox5: %i\n gpipe1: %i\t gpipe2: %i\t gpipe3: %i\n movement: %c\t jump: %i\t speed: %i\t marioDir: %i\n score: %i\t surface: %i\n", vPlayer, hPlayer[0], hPlayer[1], goomba1, goomba2, goomba3, CBox[0][0][0], CBox[0][0][1], CBox[0][0][2], CBox[0][0][3], CBox[0][0][4], BBox[0][0][0], BBox[0][0][1], BBox[0][0][2], BBox[0][0][3], BBox[0][0][4], gpipe1[0][0], gpipe2[0][0], gpipe3[0][0], movement, jump, speed, marioDir, score, surface);
//		printw("hBBox: %i\t hBBox: %i\t hBBox: %i\t hBBox: %i\t hBBox: %i\n", BBox[1][2][0], BBox[1][2][1], BBox[1][2][2], BBox[1][2][3], BBox[1][2][4]);
	}
	endwin();
		
	score = score + level*1000;
	cout << "you lose, your final score is: " << score << endl;
	return 0;
}
