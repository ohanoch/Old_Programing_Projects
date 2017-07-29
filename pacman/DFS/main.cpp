#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

class World{
public:
    int rows, cols;
    vector<string> data;
	stack <pair <int,int>> route;
	pair <int,int> start, goal;

    World(istream &in){
        string line;
        // Read rows and cols
        in >> rows >> cols;
        // Throw away remaining \n
        getline(in, line);

        for(int r = 0; r < rows; r++){
            // Read the line
            getline(in, line);
            data.push_back(line);

            // Check for the start
            auto tmp = line.find('1');
            if(tmp != line.npos){
                start.first  = r;
                start.second = tmp;
            }
            // Check for the goal
            tmp = line.find('0');
            if(tmp != line.npos){
                goal.first  = r;
                goal.second = tmp;
            }
        }
		route.push(make_pair(start.second,start.first));
    }

    void print(){
        for(const string &line : data){
            cout << line << endl;
        }
    }

	void DFS()
	{
/*for (int i=0; i<rows; i++)
{
	cout << data[i] << endl;
}*/
//		cout << route.top().first << "\t"<< route.top().second <<endl << data[14] << endl;
		while (!route.empty() && !((route.top()).first==goal.second && (route.top()).second==goal.first))
		{
			//go down
			if ((route.top()).second<rows-1 && (data[(route.top()).second+1][(route.top()).first]!='x' && data[(route.top()).second+1][(route.top()).first]!='*' && data[(route.top()).second+1][(route.top()).first]!='1' && data[(route.top()).second+1][(route.top()).first]!='B'))
			{

//cout << "down\t"<< route.top().first << "\t"<< route.top().second  << "\t"<< route.size() << "\t" << data[0]<< "a" <<endl;
//throw runtime_error("down");
				data[(route.top()).second+1][(route.top()).first]='*';
				route.push(make_pair((route.top()).first,(route.top()).second+1));

				continue;
			}
			//go left
			else if ((route.top()).first>0 && (data[(route.top()).second][(route.top()).first-1]!='x' &&data[(route.top()).second][(route.top()).first-1]!='*' && data[(route.top()).second][(route.top()).first-1]!='1' && data[(route.top()).second][(route.top()).first-1]!='B'))
			{
//throw runtime_error("left");
//cout << "left\t"<< route.top().first << "\t"<< route.top().second  << "\t"<< route.size()<<endl;
				data[(route.top()).second][(route.top()).first-1]='*';
				route.push(make_pair((route.top()).first-1,(route.top()).second));
				continue;
			}
			//go up
			else if ((route.top()).second>0 && (data[(route.top()).second-1][(route.top()).first]!='x' && data[(route.top()).second-1][(route.top()).first]!='*' && data[(route.top()).second-1][(route.top()).first]!='1' && data[(route.top()).second-1][(route.top()).first]!='B'))
			{
//throw runtime_error("up");
//cout << "up\t"<< route.top().first << "\t"<< route.top().second  << "\t"<< route.size()<<endl;
				data[(route.top()).second-1][(route.top()).first]='*';
				route.push(make_pair((route.top()).first,(route.top()).second-1));
				continue;
			}
			// go right
			else if ((route.top()).first<cols-1 && (data[(route.top()).second][(route.top()).first+1]!='x' && data[(route.top()).second][(route.top()).first+1]!='*' && data[(route.top()).second][(route.top()).first+1]!='1' && data[(route.top()).second][(route.top()).first+1]!='B'))
			{
//throw runtime_error("right");
//cout << "right\t"<< route.top().first << "\t"<< route.top().second  << "\t"<< route.size()<<endl;
				data[(route.top()).second][(route.top()).first+1]='*';
				route.push(make_pair((route.top()).first+1,(route.top()).second));
				continue;
			}
//throw runtime_error("end");
//cout << "end\t" << route.top().first << "\t"<< route.top().second  << "\t"<< route.size()<<endl;
			pair <int,int> temp=route.top();
			data[temp.second][temp.first]='B';
			route.pop();
		}

		for (int i=0; i<rows; i++)
		{
			for (int j=0; j<cols; j++)
			{
				if(data[i][j]=='B')
				{
					data[i][j]=' ';
				}
				if (i==goal.first && j==goal.second)
				{
					data[i][j]='0';
				}
			}
		}
		if (route.empty()==true)
		{
			cout<<"No Path";
		}
		else
		{
			for (int i=0; i<rows; i++)
			{
				cout << data[i] << endl;
			}
		
		}
	}
    
    // This reads in the world and creates a vector of strings.
    // Imagine that a string is just a vector of characters.
    // You can still go data[r][c] 
    // You do not have to use this code.
    //
    // Remember that the C++ stack from the standard library doesn't
    //  return the value when popping, so you need to look at the top
    //  value first.
    // http://www.cplusplus.com/reference/stack/stack/
};

int main()
{
    //fstream f("maze4.txt");
    //World w(f);
    World w(cin);
    w.DFS();
    return 0;
}

