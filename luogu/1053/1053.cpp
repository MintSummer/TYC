#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=50010;
    int n,a[N],b[N],l[N],r[N];

    inline int read()
    {
        int x=0,f=0;char ch=getchar();
        while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return f?-x:x;
    }

    void work()
    {
        n=read();
        for(int i=1;i<=n;i++) 
            a[i]=read(),b[i]=read();
        for(int i=1;i<=n;i++)
            l[i]=i-1,r[i]=i+1;
        l[1]=n,r[n]=1;
        for(int i=1;i<=n;i++)
    }
}

int main()
{
    TYC::work();
    return 0;
}