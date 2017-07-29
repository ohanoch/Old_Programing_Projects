#include "snake3.h"
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

unsigned int maxCount(unsigned int num1, unsigned int num2, unsigned int num3, unsigned int num4)
{
	unsigned int max=num1;
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

string snake::autoMove()
{
cout <<"asdasd";
	globalTempSnake^*this;

	static bool display=true;
	static int times=0;
	times ++;
	static int groupTime=0;

	if ((times>2 || length>2) && times%2==0)
       	{
       	         this->grow();
       	}

	if (this->isAlive()==false)
	{
//cout << "DEAD DEAD"<<endl;
		return "";
	}

	if (display==false && (times>1|| groupTime>=1))
	{
//cout << "TIMEOUT TIMEOUT"<<endl;
		return "!";
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

	if ((times>0 || length>2) && times%2==1)
       	{
		s1.grow();
		s2.grow();
		s3.grow();
   	        s4.grow();
       	}

	string* count1= new string;
	*count1="";
	string* count2= new string;
	*count2="";
	string* count3= new string;
	*count3="";
	string* count4= new string;
	*count4="";

	if(s1.isAlive()==false && s2.isAlive()==false && s3.isAlive()==false && s4.isAlive()==false)
	{
//cout << "VVVVVVVVVVVV"<<endl;
		return "!";
	}

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
			display=false;
			if(tempTimes%2==0){times=0;}else{times=1;}
//cout << "11111"<<endl;
			*count1 = s1.autoMove();
			if(tempTimes%2==0){times=0;}else{times=1;}
			if(tempbool==false)
			{
				groupTime++;
			}
			else
			{
				groupTime=0;
			}
			*count2 = s2.autoMove();
			if(tempTimes%2==0){times=0;}else{times=1;}
			if (tempbool==false)
			{
				groupTime++;
			}
			else
			{
				groupTime=0;
			}
			*count3 = s3.autoMove();
			if(tempTimes%2==0){times=0;}else{times=1;}
			if (tempbool==false)
			{
				groupTime++;
			}
			else
			{
				groupTime=0;
			}
			*count4 = s4.autoMove();

			if(tempTimes%2==0){times=0;}else{times=1;}
			if (tempbool==true)
			{
				display=true;

			cout << "count1\t"<< *count1<< "\tcount2\t"<< *count2<< "\tcount3\t"<< *count3<< "\tcount4\t"<< *count4 <<endl;

			}



		if (maxCount((*count1).length(),(*count2).length(),(*count3).length(),(*count4).length())==(*count1).length() && (*count1).length()!=0)
		{
			delete count2;
			delete count3;
			delete count4;
			this->move(UP);
			return "U"+(*count1);
		}
		if (maxCount((*count1).length(),(*count2).length(),(*count3).length(),(*count4).length())==(*count2).length() && (*count2).length()!=0)
		{
			delete count1;
			delete count3;
			delete count4;
			this->move(DOWN);
			return "D"+(*count2);
		}
		if (maxCount((*count1).length(),(*count2).length(),(*count3).length(),(*count4).length())==(*count3).length() && (*count3).length()!=0)
		{
			delete count1;
			delete count2;
			delete count4;
			this->move(LEFT);
			return "L"+(*count3);
		}
		if (maxCount((*count1).length(),(*count2).length(),(*count3).length(),(*count4).length())==(*count4).length() && (*count4).length()!=0)
		{
			delete count1;
			delete count2;
			delete count3;
			this->move(RIGHT);
			return "R"+(*count4);
		}
	
	return "";
}

void snake::actualMove()
{
//start:
	string s=this->autoMove();
	cout <<"\n\n" << s << endl;
	for (unsigned int i=0; i<s.length()-1; i++)
	{
		//if (fruitExists)
		//{
			//go to fruit
		//	goto start;
		//}
		if (s[i]=='U')
		{
			this->move(UP);
			system("clear");
        		drawBoard();
        		cin.get();
		}
		else if (s[i]=='D')
		{
cout << "asdasd" << endl;
			this->move(DOWN);
			system("clear");
        		drawBoard();
        		cin.get();
		}
		else if (s[i]=='L')
		{
			this->move(LEFT);
			system("clear");
        		drawBoard();
        		cin.get();
		}
		else if (s[i]=='R')
		{
			this->move(RIGHT);
			system("clear");
        		drawBoard();
        		cin.get();
		}
	}
}







