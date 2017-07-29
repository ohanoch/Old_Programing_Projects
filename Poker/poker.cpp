#include <iostream>
#include <cmath>

using namespace std;

int rank[13];
/*
int pair_num (int cards[])
{
	for (int i=0; i<4; i++)
	{
		if (cards[i] == cards[i+1])
		{
			return cards[i];
		}
	}
}

int hand_value(int cards [], int hand)
{
	int value=0;
	int sum=0;

	for (int i=0; i<5; i++)
	{	
		sum=sum+rank[cards[i]];
	}
	for (int i=0; i<5; i++)
	{	
		if (hand==0) //high card
		{
			value=value+cards[i];
		}
		if (hand==1) // pair
		{
			int temp=0;
			for (int j=pair_num(cards)-1; j>=2; j--)
			{
				switch (j)
				{
	*///				case 12: {temp=temp+/*rank[j-2]*2*/+rank[11] + rank[10] + rank[9]; break;}
//					case 11: {temp=temp+/*rank[j-2]*2*/+rank[12] + rank[10] + rank[9]; break;}
		//			case 10: {temp=temp+/*rank[j-2]*2*/+rank[12] + rank[11] + rank[9]; break;}
		//			default: temp=temp+/*rank[j-2]*2*/+rank[12] + rank[11] + rank[10];
	/*			}
			}
			if (pair_num(cards)==2)
			{
				temp=0;
			}
			value = non_pair_value(cards) + hand_value([12,11,10,9,7],0)+temp;
		}
		if (hand==2) // two pair
		{
			int pairs[3]=two_pair_num(cards); //pairs[0]<pairs[1] , pairs[3]= lone card
//			int temp=0;
//			for (int j=2; j<=pairs[1]; j++)
//			{
//				for(int k=3; k<=pairs[1]; k++)
//				{			
//					if (k<pairs[0])
//					{
//						temp=temp+13
//					}
//				}
//			}
			value = rank[pairs[3]] + hand_value ([12,12,11,10,9],1)+((pairs[0]-2)*(pairs[1]-2))*rank[12];
		}
		if (hand==3)
		{
			int temp=0;
			
			value= lone_2_cards_values + hand_value([12,12,11,11,10],2)+ temp;
		}
	}
}

*/
int main(void)
{
	for (int i=0; i<=15; i++)
	{
		if (i>=5)
		{
			rank[i]=rank[i-5]+rank[i-4]+rank[i-3]+rank[i-2]+rank[i-1]+1;
		}
		else
		{
			rank[i]=i;
		}
		cout << i+2 << " - " << rank[i] << endl;
	}
	return 0;
}
