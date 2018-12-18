#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1e5+10;

	int n,top,sta[N];
	ll dis,sum[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline double K(int a,int b)
	{
		return (double)(sum[a-1]-sum[b-1])/(dis*a-dis*b);
	}

	inline double F(int now,int t,ll start)
	{
		return (double)(sum[now]-sum[t-1])/(dis*(now-t)+start);
	}

	void work()
	{
		n=read(),dis=read();
		double ans=0.0;
		for(int i=1;i<=n;i++)
		{
			ll x=read(),start=read();
			sum[i]=sum[i-1]+x;
			while(top>1&&K(i,sta[top])<=K(sta[top],sta[top-1])) top--;
			sta[++top]=i;
			int l=1,r=top,lmid,rmid;
			while(l<r)
			{
				lmid=(l+l+r)/3;
				rmid=(r+l+r)/3;
				if(lmid==rmid) break;
				if(F(i,lmid,start)>=F(i,rmid,start)) r=rmid-1;
				else l=lmid+1;
			}
			ans+=max(F(i,sta[l],start),F(i,sta[r],start));
		}
		printf("%.0f",ans);
	}
}

int main()
{
	freopen("a.in","r",stdin);
	TYC::work();
	return 0;
}
