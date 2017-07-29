#ifndef SNAKE
#define SNAKE

#include <iostream>
#include <vector>
#include <string>

using namespace std;

extern int ROWS;
extern int COLS;
extern int fruitAmount;

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
                void operator^(link& l); //^ is =
	private:
		int xLink;
		int yLink;
};


class snake
{
	public:
		snake();
		snake(int x, int y);
		link getHead();
		int getLength();
		bool isAlive();
		void move(dir direction);
		void grow();
                bool existsOn(int x, int y);
		link getTail();
		void setBody(vector <link> b);
		void setLength(int l);
		void setTail (link t);
		vector <link> getBody();

                string autoMove();
		void actualMove();
		void operator^(snake& s);
	private:
		vector <link> body;
		int length;
		link tail;
};

class fruit
{
        public:
                fruit();
                fruit(int score);
                void eaten(int x, int y);
//                bool fruitExists();
        private:
                link banana;
                int value;
};

#endif
