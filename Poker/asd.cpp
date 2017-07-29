#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
	int rank[13];
	
//1,4,5,6,7 - seems good but isn't ----- 0,2,5,9,14 works but is inefficiant
	rank[0]=-2;
	rank[1]=-1;
	rank[2]=0;
	rank[3]=1;
	rank[4]=3;
//	rank[5]=9;

	for (int i=0; i<15; i++)
	{
		if (i>=5)
		{
	//		rank[i]=i;
	//	}
	//	else
	//	{
			rank[i]=rank[i-1]+rank[i-2]+rank[i-3]+rank[i-4]+rank[i-5]+1 - rank[3]-rank[2]-rank[1]-rank[0];
		}
		cout << i+2 << " - " << rank[i] << endl;
	}
	return 0;
}


//	rank[i-1]+rank[i-2]+rank[i-3]+rank[i-4]+rank[i-5]+1 = rank[i]+rank[0]+rank[1]+rank[2]+rank[3]
