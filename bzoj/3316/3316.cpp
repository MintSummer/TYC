#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=2e5+10;
	const double eps=1e-6;
	
	int n,L,R,arr[N];
	ll down,up,s[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	#define head q[now][h[now]]
	#define tail q[now][t[now]]

	bool check(double mid)
	{
		static double sum[N];
		static int q[2][N];
		for(int i=1;i<=n;i++)
			sum[i]=sum[i-1]+mid-arr[i];
		int h[2]={1,1},t[2]={0,0};
		for(int i=L;i<=n;i++)
		{
			int x=i-L,now=i&1;
			while(h[now]<=t[now]&&sum[tail]<=sum[x]) t[now]--;
			q[now][++t[now]]=x;
			while(h[now]<=t[now]&&i-head>R) h[now]++;
			if(sum[i]-sum[head]<=0)
			{
				up=s[i]-s[head],down=i-head;
				return true;
			}
		}
		return false;
	}

	inline ll gcd(ll x,ll y)
	{
		return !y?x:gcd(y,x%y);
	}

	void work()
	{
		n=read(),L=read(),R=read();
		L+=(L&1),R-=(R&1);
		int mx=0;
		for(int i=1;i<=n;i++)
		{
		   arr[i]=read();
		   mx=max(mx,arr[i]);
		   s[i]=s[i-1]+arr[i];
		}
		n<<=1;
		for(int i=(n>>1)+1;i<=n;i++)	
			arr[i]=arr[i-(n>>1)],s[i]=s[i-1]+arr[i];
		double l=0,r=mx,mid;
		while(r-l>=eps)
		{
			mid=(l+r)/2;
			if(check(mid)) l=mid+eps;
			else r=mid-eps;
		}
		ll g=gcd(up,down);
		if(down==g) printf("%lld\n",up/g);
		else printf("%lld/%lld\n",up/g,down/g);
	}
}

int main()
{
	TYC::work();
	return 0;
}
