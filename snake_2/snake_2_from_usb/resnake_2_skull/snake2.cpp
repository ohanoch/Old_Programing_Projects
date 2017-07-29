#include "snake2.h"
#include <stdlib.h>

//extern int ROWS;
//extern int COLS;
extern bool freeOnBoard(int x, int y);
extern void drawBoard();
extern vector <snake> players;


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
	cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa     " << count << "\t" << direction <<endl;
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
	for (int i=0; i<=b.size()-1; i++)
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

	players.push_back(*this);

cout << "QQQQQQQQQQQQQQQQQQQQQQQQqqqqQQqqqQQQQQQQQQQQQQQQQQQQQQqqqq" << endl;

	static bool display=true;
	static int times=0;
	times ++;
	static int groupTime=0;

	if (times>2 && times%2==0)
       	{
       	         this->grow();
       	}

	if (this->isAlive()==false)
	{
cout << "DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD DEAD"<<endl;
		players.pop_back();
		return 0;
	}

	if (display==false && (times>=50|| groupTime>=15))
	{
cout << "TIMEOUT TIMEOUT TIMEOUT TIMEOUT TIMEOUT TIMEOUT TIMEOUT TIMEOUT TIMEOUT TIMEOUT TIMEOUT"<<endl;
		players.pop_back();
		return 1;
	}

	snake s1;
	s1^*this;
	snake s2;
cout << "asdasd" << endl;
	s2^*this;
	snake s3;
	s3^*this;
	snake s4;
	s4^*this;

	cout <<(this->getHead()).getX() << "\t" << (this->getHead()).getY() <<endl<<(s1.getHead()).getX() << "\t" << (s1.getHead()).getY() <<endl<< (s2.getHead()).getX() << "\t" << (s2.getHead()).getY() <<endl<< (s3.getHead()).getX() << "\t" << (s3.getHead()).getY() <<endl<< (s4.getHead()).getX() << "\t" << (s4.getHead()).getY() <<endl;

	cout << "--------------------------------------------------------------------------------------------------------" << endl;
	s1.move(UP);
	s2.move(DOWN);
	s3.move(LEFT);
	s4.move(RIGHT);

	if (times>2 && times%2==0)
       	{
		s1.grow();
		s2.grow();
		s3.grow();
   	        s4.grow();
       	}

	cout <<(this->getHead()).getX() << "\t" << (this->getHead()).getY() <<endl<<(s1.getHead()).getX() << "\t" << (s1.getHead()).getY() <<endl<< (s2.getHead()).getX() << "\t" << (s2.getHead()).getY() <<endl<< (s3.getHead()).getX() << "\t" << (s3.getHead()).getY() <<endl<< (s4.getHead()).getX() << "\t" << (s4.getHead()).getY() <<endl;

	int count1=0;
	int count2=0;
	int count3=0;
	int count4=0;

	if(s1.isAlive()==false && s2.isAlive()==false && s3.isAlive()==false && s4.isAlive()==false)
	{
cout << "vvvvVVVvvvvvvvvvvvvvvvvVVVvvvvvvvVVVVvvvvvVVVVVvvvvvvVVV\t" << this->getLength() << endl;
		players.pop_back();
		return 1;
	}
	for (int i=7; i<=length; i++)
	{
		//head is RIGHT of other part
		if ((body[0].getX()>=body[i].getX()-1 && body[0].getX()<=body[i].getX()+1) && (body[0].getY()>=body[i].getY()-1 && body[0].getY()<=body[i].getY()+1))
		{
cout << "CCCCCCCCCCCCCccccccccccccccCCcCCCCCCcccccccCCCCCCCCCcccccCCCCCCCCCCccccc" << endl;
			bool tempbool=true;
			if (display==false)
			{
				tempbool=false;
				groupTime++	;
			}
			else
			{
				groupTime=0;
			}
			display=false;
			if(times%2==0){times=0;}else{times==1;}
if (tempbool==true){cout << "111111111111111111111111111111111111111\t" << groupTime << "\t" << times << endl;}
else{cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\t" << groupTime << "\t" << times << endl;}
			count1 = s1.autoMove();
if (tempbool==true){cout << "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\t" << groupTime << "\t" << times << endl;}
else{cout << "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\t" << groupTime << "\t" << times << endl;}
			if(times%2==0){times=0;}else{times==1;}
			if(tempbool==false)
			{
				groupTime++	;
			}
			else
			{
				groupTime=0;
			}
if (tempbool==true){cout << "222222222222222222222222222222222222222\t" << groupTime << "\t" << times << endl;}
else{cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\t" << groupTime << "\t" << times << endl;}
			count2 = s2.autoMove();
if (tempbool==true){cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\t" << groupTime << "\t" << times << endl;}
else{cout << "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\t" << groupTime << "\t" << times << endl;}
			if(times%2==0){times=0;}else{times==1;}
			if (tempbool==false)
			{
				groupTime++	;
			}
			else
			{
				groupTime=0;
			}
if (tempbool==true){cout << "333333333333333333333333333333333333333\t" << groupTime << "\t" << times << endl;}
else{cout << "######################################################\t" << groupTime << "\t" << times << endl;}
			count3 = s3.autoMove();
if (tempbool==true){cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\t" << groupTime << "\t" << times << endl;}
else{cout << "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\t" << groupTime << "\t" << times << endl;}
			if(times%2==0){times=0;}else{times==1;}
			if (tempbool==false)
			{
				groupTime++	;
			}
			else
			{
				groupTime=0;
			}
if (tempbool==true){cout << "444444444444444444444444444444444444444\t" << groupTime << "\t" << times << endl;}
else{cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\t" << groupTime << "\t" << times << endl;}
			count4 = s4.autoMove();
if (tempbool==true){cout << "RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR\t" << groupTime << "\t" << times << endl;}
else{cout << "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\t" << groupTime << "\t" << times << endl;}
			cout << "111111\t" << count1<< "\t2222222\t" << count2<< "\t33333333\t" << count3<< "\t44444444\t" << count4;
			if (tempbool==true)
			{
				display=true;
			}
			cout << "\tdisplay is: " << display <<endl;
			break;
		}
	}


cout << "RRRRRrrRRRRrrrrrrRRRRRRRRRRRRRRRRRRRrrrRRrrrRRrrRRRrrRRrrRRrrRRRRrrRRrrrRRRRRRRrR" << endl;

	if(display==true)
	{
		system("clear");
        	drawBoard();
        	cin.get();

cout << "ooooooo" << "111111\t" << count1<< "\t2222222\t" << count2<< "\t33333333\t" << count3<< "\t44444444\t" << count4 << "\t555555555555\t"<<maxCount(count1,count2,count3,count4)	<<endl;
		if (maxCount(count1,count2,count3,count4)==count1 && count1!=0)
		{
			this->move(UP);
			players.pop_back();
			return 1+this->autoMove();
		}
		if (maxCount(count1,count2,count3,count4)==count2 && count2!=0)
		{
			this->move(DOWN);
			players.pop_back();
			return 1+this->autoMove();
		}
		if (maxCount(count1,count2,count3,count4)==count3 && count3!=0)
		{
			this->move(LEFT);
			players.pop_back();
			return 1+this->autoMove();
		}
		if (maxCount(count1,count2,count3,count4)==count4 && count4!=0)
		{
			this->move(RIGHT);
			players.pop_back();
			return 1+this->autoMove();
		}
	}
	else
	{
cout << "pppppppppp" << "111111\t" << count1<< "\t2222222\t" << count2<< "\t33333333\t" << count3<< "\t44444444\t" << count4 << "\t555555555555\t"<<maxCount(count1,count2,count3,count4)	<<endl;
		if (maxCount(count1,count2,count3,count4)==count1 && count1!=0)
		{
			this->move(UP);
			players.pop_back();
			return 1+count1;
		}
		if (maxCount(count1,count2,count3,count4)==count2 && count2!=0)
		{
			this->move(DOWN);
			players.pop_back();
			return 1+count2;
		}
		if (maxCount(count1,count2,count3,count4)==count3 && count3!=0)
		{
			this->move(LEFT);
			players.pop_back();
			return 1+count3;
		}
		if (maxCount(count1,count2,count3,count4)==count4 && count4!=0)
		{
			this->move(RIGHT);
			players.pop_back();
			return 1+count4;
		}
	}

cout << "EEEEEEEEEEEEEEEEEEEEEEEEEEeeeeeeeeeeeeeeeeeeEEEEEEeeeeeEEeeeEEeeEEeeEEEEEEEeeeeEEEE"<<endl;

        if (fruitAmount==0)
        {
                //snake is in BOTTOM MIDDLE side of board
                if (body[0].getX()==COLS/2 && body[0].getY()<ROWS/2)
                {
cout<<"11"<<endl;
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
         	        	this->move(UP);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
         	        	this->move(RIGHT);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			this->move(DOWN);
			players.pop_back();
			return 1+this->autoMove();
                }
                //snake is in TOP MIDDLE side of board
                if (body[0].getX()==COLS/2 && body[0].getY()>ROWS/2)
                {
cout<<"22"<<endl;
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
                        	this->move(DOWN);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			this->move(UP);
			players.pop_back();
			return 1+this->autoMove();
                }
                //snake is in MIDDLE LEFT side of board
                if (body[0].getX()<COLS/2 && body[0].getY()==ROWS/2)
                {
cout<<"33"<<endl;
                        if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
                        	this->move(DOWN);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                        	this->move(UP);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			this->move(LEFT);
			players.pop_back();
			return 1+this->autoMove();
                }
                //snake is in MIDDLE RIGHT side of board
                if (body[0].getX()>COLS/2 && body[0].getY()==ROWS/2)
                {
cout<<"44"<<endl;
                        if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
                        	this->move(DOWN);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                        	this->move(UP);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			this->move(RIGHT);
			players.pop_back();
			return 1+this->autoMove();
                }
                //snake is in BOTTOM LEFT side of board
                if (body[0].getX()<COLS/2 && body[0].getY()<ROWS/2)
                {
cout<<"55"<<endl;
                        //snake is closer to the LEFT then to the BOTTOM
                        if(body[0].getX()-0<body[0].getY()-0)
                        {
                                if(freeOnBoard(body[0].getX()+1, body[0].getY()))
				{
                        		this->move(RIGHT);
					players.pop_back();
                      		  	return 1+this->autoMove();
				}
			}
                        if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                       	 	this->move(UP);
				players.pop_back();
                       	 	return 1+this->autoMove();
			}
			//RIGHT should be taken before DOWN or LEFT if it isn't closer to the LEFT border then the BOTTOM
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
				players.pop_back();
                      	  	return 1+this->autoMove();
			}
			if(body[0].getX()-0<body[0].getY()-0)
                        {
                                if(freeOnBoard(body[0].getX(), body[0].getY()-1))
				{
                        		this->move(DOWN);
					players.pop_back();
                      		  	return 1+this->autoMove();
				}
			}
                       	this->move(LEFT);
			players.pop_back();
                       	return 1+this->autoMove();
                }
                //snake is in BOTTOM RIGHT side of board
                if (body[0].getX()>COLS/2 && body[0].getY()<ROWS/2)
                {
cout<<"66"<<endl;
                        //snake is closer to the RIGHT then to the BOTTOM
                        if(COLS-body[0].getX()<body[0].getY()-0)
                        {
				if(freeOnBoard(body[0].getX()-1, body[0].getY()))
				{
         	        		this->move(LEFT);
					players.pop_back();
                        		return 1+this->autoMove();
				}
                        }
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                       	 	this->move(UP);
				players.pop_back();
                       	 	return 1+this->autoMove();
			}
			//LEFT should be taken before DOWN or RIGHT if it isn't closer to the RIGHT border then the BOTTOM
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
                        	this->move(LEFT);
				players.pop_back();
                      	  	return 1+this->autoMove();
			}
			if(COLS-body[0].getX()<body[0].getY()-0)
                        {
				if(freeOnBoard(body[0].getX(), body[0].getY()-1))
				{
         	        		this->move(DOWN);
					players.pop_back();
                        		return 1+this->autoMove();
				}
                        }
			this->move(RIGHT);
			players.pop_back();
			return 1+this->autoMove();
                        
                }
                //snake is in TOP LEFT side of board
                if (body[0].getX()<COLS/2 && body[0].getY()>ROWS/2)
                {
cout << "77" << endl;
                        //snake is closer to the LEFT then to the TOP
                        if(body[0].getX()-0<ROWS-body[0].getY())
                        {
				if(freeOnBoard(body[0].getX()+1, body[0].getY()))
				{
                        		this->move(RIGHT);
					players.pop_back();
                      		  	return 1+this->autoMove();
				}
                        }
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
         	        	this->move(DOWN);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			//RIGHT should be taken before UP or LEFT if it isn't closer to the LEFT border then the TOP
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
				players.pop_back();
                      	  	return 1+this->autoMove();
			}
			if(body[0].getX()-0<ROWS-body[0].getY())
                        {
				if(freeOnBoard(body[0].getX(), body[0].getY()+1))
				{
                        		this->move(UP);
					players.pop_back();
                      		  	return 1+this->autoMove();
				}
                        }
			this->move(LEFT);
			players.pop_back();
			return 1+this->autoMove();
                }
                //snake is in TOP RIGHT side of board
                if (body[0].getX()>COLS/2 && body[0].getY()>ROWS/2)
                {
cout<<"88"<<endl;
                        //snake is closer to the RIGHT then to the TOP
                        if(COLS-body[0].getX()<ROWS-body[0].getY())
                        {
				if(freeOnBoard(body[0].getX()-1, body[0].getY()))
				{
         	        		this->move(LEFT);
					players.pop_back();
                        		return 1+this->autoMove();
				}
                        }

                        if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
         	        	this->move(DOWN);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			//LEFT should be taken before UP or RIGHT if it isn't closer to the RIGHT border then the BOTTOM
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
                        	this->move(LEFT);
				players.pop_back();
                      	  	return 1+this->autoMove();
			}
			if(COLS-body[0].getX()<ROWS-body[0].getY())
                        {
				if(freeOnBoard(body[0].getX(), body[0].getY()+1))
				{
                        		this->move(UP);
					players.pop_back();
                      		  	return 1+this->autoMove();
				}
                        }
			this->move(RIGHT);
			players.pop_back();
			return 1+this->autoMove();
                }
                //snake is in MIDDLE of board
                if (body[0].getX()==COLS/2 && body[0].getY()==ROWS/2)
                {
cout<<"99"<<endl;
                        if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
         	        	this->move(UP);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
         	        	this->move(RIGHT);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
				players.pop_back();
                        	return 1+this->autoMove();
			}
			this->move(DOWN);
			players.pop_back();
			return 1+this->autoMove();
                }
        }

	players.pop_back();
	return 1+this->autoMove();
}










