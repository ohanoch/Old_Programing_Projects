#include "snake2.h"
#include <stdlib.h>

//extern int ROWS;
//extern int COLS;
extern bool freeOnBoard(int x, int y);
extern void drawBoard();
extern snake globalTempSnake;

snake::snake()
{
	link l;
	tail^l;
//        tail.move(l.getX(),l.getY());
	body.push_back(l);
	length=0;
}

snake::snake(int x, int y)
{
	link l(x,y);
	tail^l;
//        tail.move(l.getX(),l.getY());
	body.push_back(l);
	length=0;
}

link snake::getHead()
{
	return body[0];
}

bool snake::isAlive()
{
	bool alive=true;
	if (body[0].getX()>COLS || body[0].getX()<0 || body[0].getY()>ROWS || body[0].getY()<0)
	{
		alive=false;
	}

	for (int i=1; i<=length; i++)
	{
		
		if (body[0]==body[i])
		{
			alive=false;
		}
	}

	return alive;
}

int snake::getLength()
{
	return length;
}

link snake::getTail()
{
	return tail;
}

void snake::move(dir direction)
{
	tail^body[length];
	static int count=0;
	count++;
//        tail.move(body[length].getX(),body[length].getY());
	switch (direction)
	{
		case UP: {body[length].move(body[0].getX(), body[0].getY()+1); body.insert(body.begin(),body[length]);body.pop_back();} break;
		case DOWN: {body[length].move(body[0].getX(), body[0].getY()-1); body.insert(body.begin(),body[length]); body.pop_back();} break;
		case RIGHT: {body[length].move(body[0].getX()+1, body[0].getY()); body.insert(body.begin(),body[length]); body.pop_back();} break;
		case LEFT: {body[length].move(body[0].getX()-1, body[0].getY()); body.insert(body.begin(),body[length]); body.pop_back();} break;
	}
}

void snake::grow()
{
	body.push_back(tail);
        length++;
}

bool snake::existsOn(int x, int y)
{
        for (int k=0; k<=length; k++)
        {
                if(body[k].getX()==x && body[k].getY()==y)
                {
                        return true;
                }
        }       
        return false;
}

/*##############################################################################
###############################################################################*/

vector <link> snake:: getBody()
{
	return body;
}

void snake::setBody(vector <link> b)
{
	body.clear();
	for (unsigned int i=0; i<=b.size()-1; i++)
	{
		body.push_back(b[i]);
	}
}
void snake::setLength(int l)
{
	length=l;
}
void snake::setTail (link t)
{
	tail^t;
}

void snake::operator^(snake& s)
{
	this->setBody(s.getBody());
	this->setLength(s.getLength());
	this->setTail(s.getTail());
}

int maxCount(int num1, int num2, int num3, int num4)
{
	int max=num1;
	if (num2>max)
	{
		max=num2;
	}
	if (num3>max)
	{
		max=num3;
	}
	if (num4>max)
	{
		max=num4;
	}
	return max;
}

int snake::autoMove()
{
	globalTempSnake^*this;
	const int tol=13;
	static bool display=true;
	static int times=0;
	times ++;
	static int groupTime=0;

	if (times%2==0)
       	{
       	         this->grow();
       	}

	if (this->isAlive()==false)
	{
//cout << "DEAD DEAD"<<endl;
		return 1;
	}

	if (display==false && (/*times>4||*/ groupTime>=tol))
	{
//cout << "TIMEOUT TIMEOUT"<<endl;
		return 1;
	}

	snake s1;
	s1^*this;
	snake s2;
	s2^*this;
	snake s3;
	s3^*this;
	snake s4;
	s4^*this;

	s1.move(UP);
	s2.move(DOWN);
	s3.move(LEFT);
	s4.move(RIGHT);

	if (times%2==1)
       	{
		s1.grow();
		s2.grow();
		s3.grow();
   	        s4.grow();
       	}

	int count1=0;
	int count2=0;
	int count3=0;
	int count4=0;

/*	if(s1.isAlive()==false && s2.isAlive()==false && s3.isAlive()==false && s4.isAlive()==false)
	{
cout << "VVVVVVVVVVVV"<<endl;
		return 1;
	}*/

			int tempTimes=times;
			bool tempbool=true;
			if (display==false)
			{
				tempbool=false;
				groupTime++;
			}
			else
			{
				groupTime=0;
			}
			int tempGroupTime=groupTime;
			display=false;
			if(tempTimes%2==0){times=0;}else{times=1;}
//if(tempbool==true){cout << "111111\t"<< endl;}else{cout << "!!!!!!"<<endl;}
			count4 = s4.autoMove();
			groupTime=tempGroupTime;
/*			if(tempbool==false)
			{
//				groupTime++;
				groupTime=tempGroupTime;
			}
			else
			{
				groupTime=0;
			}*/
			if(tempTimes%2==0){times=0;}else{times=1;}
//if(tempbool==true){cout << "222222\t"<< endl;}else{cout << "@@@@@@@"<<endl;}
			if (!(count4>tol-1)){count3 = s3.autoMove();}
			groupTime=tempGroupTime;
/*			if (tempbool==false)
			{
//				groupTime++;
			}
			else
			{
				groupTime=0;
			}*/
			if(tempTimes%2==0){times=0;}else{times=1;}
//if(tempbool==true){cout << "333333\t"<< endl;}else{cout << "######"<<endl;}
			if (!(count4>tol-1) && !(count3>tol-1)){count2 = s2.autoMove();}
			groupTime=tempGroupTime;
/*			if (tempbool==false)
			{
//				groupTime++;
			}
			else
			{
				groupTime=0;
			}*/
			if(tempTimes%2==0){times=0;}else{times=1;}
//if(tempbool==true){cout << "44444\t"<< endl;}else{cout << "$$$$$$"<<endl;}
			if (!(count4>tol-1) && !(count3>tol-1) && !(count2>tol-1)){count1 = s1.autoMove();}

//			if(tempTimes%2==0){times=0;}else{times=1;}
			times=tempTimes;
			groupTime=tempGroupTime;
			if (tempbool==true)
			{
				display=true;

			cout << "count1\t"<< count1<< "\tcount2\t"<< count2<< "\tcount3\t"<< count3<< "\tcount4\t"<< count4<<endl;

			}

	if(display==true)
	{
		system("clear");
        	drawBoard();
        	cin.get();

		if (maxCount(count1,count2,count3,count4)==count1 && count1!=0)
		{
			this->move(UP);
			return 1+this->autoMove();
		}
		if (maxCount(count1,count2,count3,count4)==count2 && count2!=0)
		{
			this->move(DOWN);
			return 1+this->autoMove();
		}
		if (maxCount(count1,count2,count3,count4)==count3 && count3!=0)
		{
			this->move(LEFT);
			return 1+this->autoMove();
		}
		if (maxCount(count1,count2,count3,count4)==count4 && count4!=0)
		{
			this->move(RIGHT);
			return 1+this->autoMove();
		}
	}
	else
	{
		if (maxCount(count1,count2,count3,count4)==count1 && count1!=0)
		{
			this->move(UP);
			return 1+count1;
		}
		if (maxCount(count1,count2,count3,count4)==count2 && count2!=0)
		{
			this->move(DOWN);
			return 1+count2;
		}
		if (maxCount(count1,count2,count3,count4)==count3 && count3!=0)
		{
			this->move(LEFT);
			return 1+count3;
		}
		if (maxCount(count1,count2,count3,count4)==count4 && count4!=0)
		{
			this->move(RIGHT);
			return 1+count4;
		}
	}

        if (fruitAmount==0)
        {
                //snake is in BOTTOM MIDDLE side of board
                if (body[0].getX()==COLS/2 && body[0].getY()<ROWS/2)
                {
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
         	        	this->move(UP);
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
         	        	this->move(RIGHT);
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
                        	return 1+this->autoMove();
			}
			this->move(DOWN);
			return 1+this->autoMove();
                }
                //snake is in TOP MIDDLE side of board
                if (body[0].getX()==COLS/2 && body[0].getY()>ROWS/2)
                {
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
                        	this->move(DOWN);
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
                        	return 1+this->autoMove();
			}
			this->move(UP);
			return 1+this->autoMove();
                }
                //snake is in MIDDLE LEFT side of board
                if (body[0].getX()<COLS/2 && body[0].getY()==ROWS/2)
                {
                        if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
                        	this->move(DOWN);
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                        	this->move(UP);
                        	return 1+this->autoMove();
			}
			this->move(LEFT);
			return 1+this->autoMove();
                }
                //snake is in MIDDLE RIGHT side of board
                if (body[0].getX()>COLS/2 && body[0].getY()==ROWS/2)
                {
                        if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
                        	this->move(DOWN);
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                        	this->move(UP);
                        	return 1+this->autoMove();
			}
			this->move(RIGHT);
			return 1+this->autoMove();
                }
                //snake is in BOTTOM LEFT side of board
                if (body[0].getX()<COLS/2 && body[0].getY()<ROWS/2)
                {
                        //snake is closer to the LEFT then to the BOTTOM
                        if(body[0].getX()-0<body[0].getY()-0)
                        {
                                if(freeOnBoard(body[0].getX()+1, body[0].getY()))
				{
                        		this->move(RIGHT);
                      		  	return 1+this->autoMove();
				}
			}
                        if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                       	 	this->move(UP);
                       	 	return 1+this->autoMove();
			}
			//RIGHT should be taken before DOWN or LEFT if it isn't closer to the LEFT border then the BOTTOM
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
                      	  	return 1+this->autoMove();
			}
			if(body[0].getX()-0<body[0].getY()-0)
                        {
                                if(freeOnBoard(body[0].getX(), body[0].getY()-1))
				{
                        		this->move(DOWN);
                      		  	return 1+this->autoMove();
				}
			}
                       	this->move(LEFT);
                       	return 1+this->autoMove();
                }
                //snake is in BOTTOM RIGHT side of board
                if (body[0].getX()>COLS/2 && body[0].getY()<ROWS/2)
                {
                        //snake is closer to the RIGHT then to the BOTTOM
                        if(COLS-body[0].getX()<body[0].getY()-0)
                        {
				if(freeOnBoard(body[0].getX()-1, body[0].getY()))
				{
         	        		this->move(LEFT);
                        		return 1+this->autoMove();
				}
                        }
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                       	 	this->move(UP);
                       	 	return 1+this->autoMove();
			}
			//LEFT should be taken before DOWN or RIGHT if it isn't closer to the RIGHT border then the BOTTOM
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
                        	this->move(LEFT);
                      	  	return 1+this->autoMove();
			}
			if(COLS-body[0].getX()<body[0].getY()-0)
                        {
				if(freeOnBoard(body[0].getX(), body[0].getY()-1))
				{
         	        		this->move(DOWN);
                        		return 1+this->autoMove();
				}
                        }
			this->move(RIGHT);
			return 1+this->autoMove();
                        
                }
                //snake is in TOP LEFT side of board
                if (body[0].getX()<COLS/2 && body[0].getY()>ROWS/2)
                {
                        //snake is closer to the LEFT then to the TOP
                        if(body[0].getX()-0<ROWS-body[0].getY())
                        {
				if(freeOnBoard(body[0].getX()+1, body[0].getY()))
				{
                        		this->move(RIGHT);
                      		  	return 1+this->autoMove();
				}
                        }
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
         	        	this->move(DOWN);
                        	return 1+this->autoMove();
			}
			//RIGHT should be taken before UP or LEFT if it isn't closer to the LEFT border then the TOP
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
                      	  	return 1+this->autoMove();
			}
			if(body[0].getX()-0<ROWS-body[0].getY())
                        {
				if(freeOnBoard(body[0].getX(), body[0].getY()+1))
				{
                        		this->move(UP);
                      		  	return 1+this->autoMove();
				}
                        }
			this->move(LEFT);
			return 1+this->autoMove();
                }
                //snake is in TOP RIGHT side of board
                if (body[0].getX()>COLS/2 && body[0].getY()>ROWS/2)
                {
                        //snake is closer to the RIGHT then to the TOP
                        if(COLS-body[0].getX()<ROWS-body[0].getY())
                        {
				if(freeOnBoard(body[0].getX()-1, body[0].getY()))
				{
         	        		this->move(LEFT);
                        		return 1+this->autoMove();
				}
                        }

                        if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
         	        	this->move(DOWN);
                        	return 1+this->autoMove();
			}
			//LEFT should be taken before UP or RIGHT if it isn't closer to the RIGHT border then the BOTTOM
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
                        	this->move(LEFT);
                      	  	return 1+this->autoMove();
			}
			if(COLS-body[0].getX()<ROWS-body[0].getY())
                        {
				if(freeOnBoard(body[0].getX(), body[0].getY()+1))
				{
                        		this->move(UP);
                      		  	return 1+this->autoMove();
				}
                        }
			this->move(RIGHT);
			return 1+this->autoMove();
                }
                //snake is in MIDDLE of board
                if (body[0].getX()==COLS/2 && body[0].getY()==ROWS/2)
                {
                        if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
         	        	this->move(UP);
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
         	        	this->move(RIGHT);
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
                        	return 1+this->autoMove();
			}
			this->move(DOWN);
			return 1+this->autoMove();
                }
        }

	return 1+this->autoMove();
}










