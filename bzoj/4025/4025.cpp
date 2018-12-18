#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1e5+10;
	int n,m,Time

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{
		n=read(),m=read(),Time=read(); 
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read(),s=read(),t=read();
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
