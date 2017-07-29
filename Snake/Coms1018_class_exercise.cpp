#include <iostream>
#include <cmath>
#include <unistd.h>
//#include <thread>
//#include <boost/thread.hpp>
//#include <cstdlib>x
//#include <unistd.h>
//#include <process.h>
//#include <windows.h>
#include <ncurses.h>
#include <string>

using namespace std;


/*
void waiting()
//void *PrintWaiting(void *id)
//void myThread( void* number)
{
	sleep(100);	
	while (v<=vdim && h<=hdim && h>0 && v>0)
	{
		if (change=='u')
		{
			h=h-1;
		}
		if (change=='d')
		{
			h=h+1;
		}
		if (change=='r')
		{
			v=v+1;
		}
		if (change=='l')
		{
			v=v-1;
		}
		for (int i=1; i<=hdim ; i++)
		{
			for (int j=1; j<=vdim; j++)
			{
				if(i==h && j==v)
				{
					cout << "0";
				}
				else
				{
					cout << "x";
				}
			}
		cout << endl;
		}

		sleep(100);
	}
//	_endthread();
//	pthread_exit(NULL);
}
*/

int main(void)
{
	int v=0;
	int h=0;
	char change='w';
	int vdim=0;
	int hdim=0;
	int temp;

	cout << "enter verticle dimension of playing field\n";
	cin >> vdim;
	cout << "enter horizontle dimension of playing field\n";
	cin >> hdim;
	cout << "enter verticle position of starting on playing field (from left to right)\n";
	cin >> v;
	cout << "enter horizontle position of starting on playing field (from top to bottom)\n";
	cin >> h;
	
	initscr();
	raw();
	nodelay(stdscr, TRUE);
//	cbreak();
//	temp=getch();
//	cout<< temp << endl;

//	pthread_t thread;
//	pthread_create(&thread, NULL, PrintWaiting, NULL);
//	pthread_cancel(thread);

//	_beginthread( myThread, 0, NULL);

//	thread thread1 = thread(waiting);
//	thread1.join();
//	thread first(waiting,v,h);	
	while (v<=vdim && h<=hdim && h>0 && v>0)
	{
		cout << endl << endl;
		sleep(1);
		for (int i=1; i<=hdim ; i++)
		{
			for (int j=1; j<=vdim; j++)
			{
				if(i==h && j==v)
				{
					cout << "0 ";
				}
				else
				{
					cout << "x ";
				}
			}
		cout << endl;
		}
		cout << "choose where to go (w=up, s=down, a=left, d=right\n";
		temp= getch();
		cout << temp << endl;
		if (temp!=ERR)
		{
			change=temp;
		}
		cout << change << endl;
//		temp=cin.peek();
//		if (temp!=' ')
//		{
//			cin >> change;
//
//		}

		if (change=='w')
		{
			h=h-1;
		}
		if (change=='s')
		{
			h=h+1;
		}
		if (change=='a')
		{
			v=v+1;
		}
		if (change=='d')
		{
			v=v-1;
		}

/*		if (change=='w')
		{
			h=h-1;
		}
		if (change=='s')
		{
			h=h+1;
		}
		if (change=='a')
		{
			v=v+1;
		}
		if (change=='d')
		{
			v=v-1;
		}
*/
	}
	cout << "GAME OVER\n";
	endwin();
//	pthread_exit(NULL);
	return (0);
}
	
	
