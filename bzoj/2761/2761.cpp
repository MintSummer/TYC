#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<set>
using namespace std;

namespace TYC
{
    set<int> s;

    inline int read()
    {
        int x=0,f=0;
        char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    void work()
    {
        int T=read();
        while(T--)
        {
			s.clear();
			int n=read();
			int x=read();
			s.insert(x);
			printf("%d",x);
			for(int i=2;i<=n;i++)
			{
				x=read();
				if(!s.count(x)) 
					printf(" %d",x),s.insert(x);//行末无空格
			}
			puts("");
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}
