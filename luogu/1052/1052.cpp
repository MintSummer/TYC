#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=1e4+10,inf=0x3f3f3f3f;
    int Length,len,s,t,n,stone[N],dp[N],dis[N],mark[N];

    inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

    void solve_special()
    {
        int ans=0;
        for(int i=1;i<=n;i++) ans+=(!(read()%s));
        printf("%d\n",ans);
    }

    void work()
    {
        Length=read(),s=read(),t=read(),n=read();
        if(s==t) {solve_special();return;}
        for(int i=1;i<=n;i++) stone[i]=read();
        sort(stone+1,stone+1+n);
        dis[n+1]=min(Length-stone[n],100);
        for(int i=1;i<=n;i++)
        {
            dis[i]=min(stone[i]-stone[i-1],90);
            len+=dis[i];
            mark[len]=1;
        }
        len+=dis[n+1];
        memset(dp,inf,sizeof(dp));
		dp[0]=0;
        for(int i=0;i<=len;i++)
            for(int j=s;j<=t;j++)
            {
                int now=min(len,i+j);
                dp[now]=min(dp[now],dp[i]+mark[now]);
            }
        printf("%d\n",dp[len]);
    }
}

int main()
{
    TYC::work();
    return 0;
}
