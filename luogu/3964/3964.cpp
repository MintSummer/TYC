#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=100010;
	int n;
	ll x[N],y[N],sx[N],sy[N];

	struct node
	{
		ll x,y;
	}a[N];

	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			ll xx=read(),yy=read();
			x[i]=xx+yy,y[i]=xx-yy;
			a[i]=(node){x[i],y[i]};
		}
		sort(x+1,x+1+n);
		sort(y+1,y+1+n);
		for(int i=1;i<=n;i++)
			sx[i]=sx[i-1]+x[i],sy[i]=sy[i-1]+y[i];
		ll ans=1e15;
		for(int i=1;i<=n;i++)
		{
			int numx=lower_bound(x+1,x+1+n,a[i].x)-x;
			int numy=lower_bound(y+1,y+1+n,a[i].y)-y;
			ll sum=(a[i].x*numx-sx[numx])+(sx[n]-sx[numx]-a[i].x*(n-numx));
			sum+=(a[i].y*numy-sy[numy])+(sy[n]-sy[numy]-a[i].y*(n-numy));
			ans=min(ans,sum);
		}
		printf("%lld\n",ans>>1);
	}
}

int main()
{
	TYC::work();
	return 0;
}
