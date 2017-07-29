#include "snake3.h"
#include <cstdlib> 
#include <ctime> 

fruit::fruit()
{
        srand((unsigned)time(0)); 
        banana.move(rand()%ROWS+1,rand()%COLS+1);
        value=100;
        fruitAmount++;
}

fruit::fruit(int score)
{
        srand((unsigned)time(0)); 
        banana.move(rand()%ROWS+1,rand()%COLS+1);
        value=score;
        fruitAmount++;
}

/*bool fruit::fruitExists()
{
        if (amount==0)
        {
                return true;
        }

        return false;
}*/
