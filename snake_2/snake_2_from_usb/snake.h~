#ifndef SNAKE
#define SNAKE

#include <iostream>
#include <vector>

using namespace std;

int DIMX;
int DIMY;
enum dir {UP,DOWN,RIGHT,LEFT};

class link
{
	public:
		link();
		link (int x, int y);
		void move (int x, int y);
		int getX();
		int getY();
		bool operator==(link& l);
	private:
		int xLink;
		int yLink;
};


class snake
{
	public:
		snake();
		link get_head();
		int get_length();
		bool isAlive();
		void move(dir direction);
		void grow();
	private:
		vector <link> body;
		int length;
		link tail;
};

#endif
