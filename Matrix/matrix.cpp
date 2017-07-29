#include <iostream>
#include <cmath>
#include <stdlib.h> //rand
#include <cstdlib> //Turgay rand
#include <ctime>

using namespace std;

int main (void)
{
	const int ROWS=10;
	const int COLS=10;
	int matrix[ROWS][COLS];

	srand(static_cast<unsigned int>(time(0))); // initialize random number generator

	for (int i=0; i<ROWS; i++)
	{
		for (int j=0; j<COLS; j++)
		{
			matrix[i][j]=(-1)^rand();
		}
	}

	
	return 0;
}


