void drawBossLevel(int bowser [], int shot [][2], int level)
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
					if (hole[h]==j)
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
	int bossCoinCount=rand()%20+1;
	char secretMovement=' ';
	bool bossGameOver=false;
	int bowserMove=0;
	int bowserJump=0;
	int shot[level][2];
	int bossHole[level];

	for (int i=0; i<5; i++)
	{
		if (coin[i][2]<=0 && bossCoinCount>0)
		{
			coin[i][0]=rand()%VDIM+1;
			coin[i][1]=rand()%HDIM+1;
			coin[i][2]=1;
			bossCoinCount--;
		}
	}

	for (int i=0; i<level; i++)
	{
		bossHole[i]=rand()%(VDIM-2)+2;
	}

	while(bossGameOver==false)
	{
		//Moving Bowser shot
		for (int i=0; i<level; i++)
		{
			shot[i][0]--;
		}
	
		//Moving Bowser
		bowserMove = rand()%(4+level)+1;
		if (bowserMove==1)
		{
			bowser[0]--;
		}
		if (bowserMove==2)
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
				if (hPlayer[0]!=hPlayer[1])
				{
					hPlayer[0]=hPlayer[1];
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
				coinCount++;
			}
		}
		
		//coin regeneration
		for (int i=0; i<5; i++)
		{
			if (coin[i][2]<=0 && bossCoinCount>0)
			{
				coin[i][0]=rand()%VDIM+1;
				coin[i][1]=rand()%HDIM+1;
				coin[i][2]=1;
				bossCoinCount--;
			}
		}
		
		//returning to normal game
		if (bowser[0]==vPlayer && bowser[1]==hPlayer[0])
		{
			if (hPlayerPrev[0]>hPlayer[0])
			{
				bossGameOver=true;
				vPlayer=1;
				if (hPlayer[0]==hPlayer[1])
				{
					hPlayer[0]=HDIM-2;
					hPlayer[1]=HDIM-2;
				}
				else
				{
					hPlayer[0]=HDIM-3;
					hPlayer[1]=HDIM-2;
				}
				move(0,0);
				printw("WELCOME TO LEVEL: %i",level+1);
				refresh();
				usleep(185000);
				return 1;
			}
			else
			{
				lives--;
				vPlayer=1;
			}
		}

		//dying
		if (lives==0)
		{
			bossGameOver=true;
			gameOver=true;
			return 0;
		}
		//Mario in hole
		for (int i=0; i<level; i++)
		{
			if (bossHole[i]==vPlayer && hPlayer[0]==1)
			{
				bossGameOver=true;
				gameOver=true;				
				return 0;
			}
		}

		if(bossGameOver==false)
		{
			move(0,0);
			drawBossLevel(bowser, shot, level);
			refresh();
			usleep(185000);
		}
		if (score>0)
		{
			score--;
		}

		printw("\n\n score: %i\t lives: %i\t coinCount: %i\t speed: %i\t bossCoinCount: %i\n", score, lives, coinCount, speed, bossCoinCount);
		printw("vPlayer: %i\n",vPlayer);
	}
	return 1;
}
