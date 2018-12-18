#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const int N=1e6+10,inf=0x3f3f3f3f;
    const double eps=1e-8;
    int n,x[N],q[N];
    ll dp[N][2];

    inline int read()
    {
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
    }
    
	double y(int a)
	{
		return dp[a][1]+(double)1/2*a*(a-1);
	}
	
	double k(int a,int b)
	{
		return (double)(y(a)-y(b))/(a-b);
	}
	
	ll getans(int i,int x)
	{
		return dp[x][1]+(i-x)*(i-x+1)/2;
	}

    void work()
    {
		n=read();
		for(int i=1;i<=n;i++) x[n-i+1]=read();
		memset(dp,0x3f3f3f3f,sizeof(dp));
		dp[1][1]=x[1];
		int h=1,t=1;
		q[1]=1;
		for(int i=2;i<=n;i++)
		{
		    dp[i][1]=min(dp[i-1][0],dp[i-1][1])+x[i];
			while(h<t&&k(q[h],q[h+1])-i<=eps) h++;
			dp[i][0]=getans(i,q[h]);
			while(h<t&&k(q[t-1],q[t])-k(q[t],i)>=eps) t--;
			q[++t]=i;
		}
		printf("%lld",min(dp[n][0],dp[n][1]));
    }
}

int main()
{
    TYC::work();
    return 0;
}
