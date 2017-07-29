#include "snake.h"
#include <stdlib.h>

int ROWS;
int COLS;
int fruitAmount=0;
        
int count=0;

void drawBoard(vector <snake> players)
{
        bool snakeOn=false;
        for (int i=ROWS; i>=0; i--)
        {
                for (int j=0; j<=COLS; j++)
                {
                        for (unsigned int k=0; k<players.size(); k++)
                        {
                                if (players[k].existsOn(i,j)==true)
                                {
                                        cout << k << " ";
                                        snakeOn=true;
                                }
                        }
                        if (snakeOn==false)
                        {
                                cout << "X ";
                        }
                        snakeOn=false;
                }
                cout << endl;
        }
        cout << count << endl;
}

int main(void)
{
	cout << "enter board dimenssions: ROWS, COLS" << endl;
	cin >> ROWS;
	cin >> COLS;
        ROWS--;
        COLS--;

        vector <snake> players;
        int numOfPlayers;
        cout << "enter amount of players" << endl;
        cin >> numOfPlayers;
        for (int i=0; i<numOfPlayers; i++)
        {
                snake *temp = new snake(2,19);
                players.push_back(*temp);
                delete temp;
        }
        
        while (true)
        {
                system("clear");
                players[0].autoMove();
                if (count>2)
                {
                        players[0].grow();
                }
                drawBoard(players);
                cin.get();
                count++;
        }
	return 0;
}
