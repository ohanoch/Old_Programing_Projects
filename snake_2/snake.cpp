#include "snake.h"

//extern int ROWS;
//extern int COLS;
extern bool freeOnBoard(int x, int y);

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
	if (body[0].getX()>ROWS || body[0].getX()<0 || body[0].getY()>COLS || body[0].getX()<0)
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
		case UP: {body[length].move(body[0].getX(), body[0].getY()+1); body.insert(body.begin(),body[length]); body.pop_back();} break;
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

void snake::autoMove()
{
	static int count=0;
	count ++;
        if (fruitAmount==0)
        {
                //snake is in BOTTOM MIDDLE side of board
                if (body[0].getX()==COLS/2 && body[0].getY()<ROWS/2)
                {
cout<<"11"<<endl;
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
         	        	this->move(UP);
                        	return;
			}
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
         	        	this->move(RIGHT);
                        	return;
			}
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
                        	return;
			}
			this->move(DOWN);
			return;
                }
                //snake is in TOP MIDDLE side of board
                if (body[0].getX()==COLS/2 && body[0].getY()>ROWS/2)
                {
cout<<"22"<<endl;
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
                        	this->move(DOWN);
                        	return;
			}
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
                        	return;
			}
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
                        	return;
			}
			this->move(UP);
			return;
                }
                //snake is in MIDDLE LEFT side of board
                if (body[0].getX()<COLS/2 && body[0].getY()==ROWS/2)
                {
cout<<"33"<<endl;
                        if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
                        	return;
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
                        	this->move(DOWN);
                        	return;
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                        	this->move(UP);
                        	return;
			}
			this->move(LEFT);
			return;
                }
                //snake is in MIDDLE RIGHT side of board
                if (body[0].getX()>COLS/2 && body[0].getY()==ROWS/2)
                {
cout<<"44"<<endl;
                        if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
                        	return;
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
                        	this->move(DOWN);
                        	return;
			}
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                        	this->move(UP);
                        	return;
			}
			this->move(RIGHT);
			return;
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
                      		  	return;
				}
			}
                        if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                       	 	this->move(UP);
                       	 	return;
			}
			//RIGHT should be taken before DOWN or LEFT if it isn't closer to the LEFT border then the BOTTOM
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
                      	  	return;
			}
			if(body[0].getX()-0<body[0].getY()-0)
                        {
                                if(freeOnBoard(body[0].getX(), body[0].getY()-1))
				{
                        		this->move(DOWN);
                      		  	return;
				}
			}
                       	this->move(LEFT);
                       	return;
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
                        		return;
				}
                        }
			if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
                       	 	this->move(UP);
                       	 	return;
			}
			//LEFT should be taken before DOWN or RIGHT if it isn't closer to the RIGHT border then the BOTTOM
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
                        	this->move(LEFT);
                      	  	return;
			}
			if(COLS-body[0].getX()<body[0].getY()-0)
                        {
				if(freeOnBoard(body[0].getX(), body[0].getY()-1))
				{
         	        		this->move(DOWN);
                        		return;
				}
                        }
			this->move(RIGHT);
			return;
                        
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
                      		  	return;
				}
                        }
			if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
         	        	this->move(DOWN);
                        	return;
			}
			//RIGHT should be taken before UP or LEFT if it isn't closer to the LEFT border then the TOP
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
                        	this->move(RIGHT);
                      	  	return;
			}
			if(body[0].getX()-0<ROWS-body[0].getY())
                        {
				if(freeOnBoard(body[0].getX(), body[0].getY()+1))
				{
                        		this->move(UP);
                      		  	return;
				}
                        }
			this->move(LEFT);
			return;
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
                        		return;
				}
                        }

                        if(freeOnBoard(body[0].getX(), body[0].getY()-1))
			{
         	        	this->move(DOWN);
                        	return;
			}
			//LEFT should be taken before UP or RIGHT if it isn't closer to the RIGHT border then the BOTTOM
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
                        	this->move(LEFT);
                      	  	return;
			}
			if(COLS-body[0].getX()<ROWS-body[0].getY())
                        {
				if(freeOnBoard(body[0].getX(), body[0].getY()+1))
				{
                        		this->move(UP);
                      		  	return;
				}
                        }
			this->move(RIGHT);
			return;
                }
                //snake is in MIDDLE of board
                if (body[0].getX()==COLS/2 && body[0].getY()==ROWS/2)
                {
cout<<"99"<<endl;
                        if(freeOnBoard(body[0].getX(), body[0].getY()+1))
			{
         	        	this->move(UP);
                        	return;
			}
			if(freeOnBoard(body[0].getX()+1, body[0].getY()))
			{
         	        	this->move(RIGHT);
                        	return;
			}
			if(freeOnBoard(body[0].getX()-1, body[0].getY()))
			{
         	        	this->move(LEFT);
                        	return;
			}
			this->move(DOWN);
			return;
                }
        }
}










