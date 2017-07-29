#include <iostream>
#include <cmath>

using namespace std;

int rank[13];

int testing (int a, int b, int c, int d, int e)
{
	rank[0]=a;
	rank[1]=b;
	rank[2]=c;
	rank[3]=d;
	rank[4]=e;

	for (int i=0; i<15; i++)
	{
		if (i>=5)
		{

			rank[i]=rank[i-1]+rank[i-2]+rank[i-3]+rank[i-4]+rank[i-5]+1 - rank[3]-rank[2]-rank[1]-rank[0];
		}
//		cout << i+2 << " - " << rank[i] << endl;
	}
	return (rank[12]+rank[11]+rank[10]+rank[9]+rank[8]);
}

int main(void)
{
	int r=30;
	for (int a=-r; a<=r; a++)
	{
		for (int b=-r; b<=r; b++)
		{
			for (int c=-r; c<=r; c++)
			{
				for (int d=-r; d<=r; d++)
				{
					for (int e=-r; e<=r; e++)
					{ 
						if (testing(a,b,c,d,e)+a+b+c+d+e==1287 && (e>d && d>c && c>b && b>a) /*&& a+b+c+d+e==1*/ && (a+b!=c+d && a+b!=c+e && a+b!=d+e && a+c!=d+e && a+c!=b+d && a+c!=b+e && a+d!=b+c && a+d!=b+e && a+d!=c+e && a+e!=b+c && a+e!=b+d && a+e!=c+d && b+c!=d+e && b+d!= c+e && b+e!=c+d))
						{
							cout << a << "\n"  << b << "\n" << c << "\n" << d << "\n" <<  e<< "\n ----------------------------\n";
						}
					}
				}
			}
		}
	}

	
	return 0;
}


//	rank[i-1]+rank[i-2]+rank[i-3]+rank[i-4]+rank[i-5]+1 = rank[i]+rank[0]+rank[1]+rank[2]+rank[3]
