#include "snake.h"
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

int count=0;

bool freeOnBoard(int x, int y)
{
	for (unsigned int k=0; k<players.size(); k++)
        {
	        if (players[k].existsOn(x,y)==true && !(((players[k].getTail()).getX()==x) && (players[k].getTail()).getY()==y))
	        {
		        return false;
	        }
	}
	return true;
}

void drawBoard()
{
        bool snakeOn=false;
        for (int i=ROWS; i>=0; i--)
        {
                for (int j=0; j<=COLS; j++)
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
                cout << endl;
        }
        cout << count << endl << players[0].getLength() << endl << (players[0].getTail()).getX() << endl << (players[0].getTail()).getY() << endl<< (players[0].getHead()).getX()<< endl << (players[0].getHead()).getY() <<endl <<endl << ROWS << "\t" << COLS << endl;
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
        
        while (players[0].isAlive()==true)
        {
                system("clear");
                players[0].autoMove();
                if (count>2 && count%2==0)
                {
                        players[0].grow();
                }
                drawBoard();
                cin.get();
                count++;
        }
	return 0;
}
