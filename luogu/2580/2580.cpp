#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	int n,m;
	string str;
	map<string,int> appear,tim;
	
	void work()
	{
		ios::sync_with_stdio(false);
		cin.tie(0);
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>str;
			appear[str]=1;
		}
		cin>>m;
		for(int i=1;i<=m;i++)
		{
			cin>>str;
			if(!appear.count(str)) cout<<"WRONG\n";
			else
			{
				if(!tim.count(str)) cout<<"OK\n";
				else cout<<"REPEAT\n";
				tim[str]++;
			}
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
