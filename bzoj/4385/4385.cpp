#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=2000010;
	typedef long long ll;
	int n,d,q[N];
	ll p,sum[N];

	inline ll read()
	{
		ll x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}	

	void work()
	{
		n=read(),p=read(),d=read();
		for(int i=1;i<=n;i++) sum[i]=sum[i-1]+read();
		int h=1,t=0,ans=d;
		for(int l=1,r=d;r<=n;r++)
		{
			while(h<=t&&sum[r]-sum[r-d]>sum[q[t]]-sum[q[t]-d]) t--;
			q[++t]=r;
			while(sum[r]-sum[l-1]-(sum[q[h]]-sum[q[h]-d])>p) l++;
			while(h<=t&&q[h]-d+1<l) h++;
			ans=max(ans,r-l+1);
		}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
