#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

namespace TYC
{
    int T,N,M;

    inline int read()
    {
	int x=0,f=0;char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
    }

    void work()
    {
	T=read();
	while(T--)
	{
	    N=read(),M=read();
	}
    }
}

int main()
{
    TYC::work();
    return 0;
}
