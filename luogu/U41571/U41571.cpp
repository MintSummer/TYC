#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=1e7+10;
    int n,m,c[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    #define lowbit(x) x&(-x)
    inline void add(int x,int val)
    {
        for(;x<=n;x+=lowbit(x)) c[x]+=val;
    }
    inline int query(int x)
    {
        int sum=0;
        for(;x;x-=lowbit(x)) sum+=c[x];
        return sum;
    }

    void work()
    {
        n=read(),m=read();
        while(m--)
        {
            int opt=read();
            if(!opt)
            {
                int l=read(),r=read();
                add(l,1),add(r+1,-1);
            }
            else printf("%d\n",query(read()));
        }
    }
}

int main()
{
    TYC::work();
    return 0;
}