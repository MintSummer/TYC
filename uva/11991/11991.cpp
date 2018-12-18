#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<map>
using namespace std;
int n,m;
map<int,vector<int> > ma;

int read()
{
	int x=0;char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x;
}

int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		ma.clear();
		int x,k;
		for(int i=1;i<=n;i++) 
		{
			x=read();
			if(!ma.count(x)) ma[x]=vector<int>();
			ma[x].push_back(i);
		}
		while(m--)
		{
			k=read(),x=read();
			if(!ma.count(x)||ma[x].size()<k) printf("0\n");
			else printf("%d\n",ma[x][k-1]);
		}
	}
	return 0;
}
