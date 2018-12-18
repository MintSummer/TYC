#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{

	}
}

int main()
{
	TYC::work();
	return 0;
}
