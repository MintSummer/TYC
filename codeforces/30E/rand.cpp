#include<bits/stdc++.h>
using namespace std;

int main()
{
	srand(time(NULL));
	int n=1e5;
	for(int i=1;i<=n;i++)
	{
		char t=rand()%26+'a';
		cout<<t;
	}
	return 0;
}
