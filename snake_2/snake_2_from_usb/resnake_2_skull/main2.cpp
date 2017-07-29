#include "snake2.h"
#include <stdlib.h>

int ROWS=19;
int COLS=19;
int fruitAmount=0;
/*cout << "enter board dimenssions: ROWS, COLS" << endl;
cin >> ROWS;
cin >> COLS;
ROWS--;
COLS--;
*/
vector <snake> players;
snake globalTempSnake;

bool freeOnBoard(int x, int y)
{
	for (unsigned int k=0; k<players.size(); k++)
        {
	        if (players[k].existsOn(x,y)==true || globalTempSnake.existsOn(x,y))// && !(((players[k].getTail()).getX()==x) && (players[k].getTail()).getY()==y))
	        {
		        return false;
	        }
	}
	if (x<0 || x>COLS || y<0 || y>ROWS)
	{
		return false;
	}
	return true;
}

void drawBoard()
{
        bool snakeOn=false;
        for (int i=ROWS+1; i>=0; i--)
        {
		if (i!=ROWS+1)
		{
			if (i<10)
			{
				cout << i << " ";
			}
			else
			{
				cout << i;
			}
		}
                for (int j=0; j<=COLS; j++)
                {
			if(i==ROWS+1)
			{
				if (j==0)
				{
					cout << "   " << j << " ";
				}
				else
				{
					cout << j << " ";
				}
			}
			else
			{
	                        for (unsigned int k=0; k<players.size(); k++)
        	                {
        	                        if (players[k].existsOn(j,i)==true)
        	                        {
						if ((players[k].getHead()).getX()==j && (players[k].getHead()).getY()==i)
						{
							cout << "& ";
						}
						else
						{
        	                                	cout << k << " ";
						}
        	                                snakeOn=true;
        	                        }
        	                }
	                        if (snakeOn==false)
        	                {
        	                        cout << "  ";
        	                }
        	                snakeOn=false;
			}
                }
                cout << endl;
        }
        cout << endl << players[0].getLength() << endl << (players[0].getTail()).getX() << endl << (players[0].getTail()).getY() << endl<< (players[0].getHead()).getX()<< endl << (players[0].getHead()).getY() <<endl <<endl << ROWS << "\t" << COLS << endl;
}

int main(void)
{
        int numOfPlayers;
        cout << "enter amount of players" << endl;
        cin >> numOfPlayers;
        for (int i=0; i<numOfPlayers; i++)
        {
                snake *temp = new snake(2,19);
                players.push_back(*temp);
                delete temp;
        }
cout << "TTTTTTTTTTTTTTTTTttTTTttTTttTTttTTttTTTTTTTTTTTTtttt"<< endl;
        players[0].autoMove();

	return 0;
}
