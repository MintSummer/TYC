#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=500010;
	typedef long long ll;
	int n;
	ll c,ans,a[N],b[N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}	
	
	struct node
	{
		int id;
		ll val;
		bool operator <(const node &t) const
		{
			return val<t.val;
		}
	}x[N];
	
	void work()
	{
		n=read(),c=read();
		for(int i=1;i<=n;i++)
			a[i]=read(),ans+=a[i];
		for(int i=1;i<=n;i++) b[i]=read();
		for(int i=1;i<=n;i++)
			x[i]=(node){i,b[i]-a[i]+(n-i)*c};
		sort(x+1,x+1+n);
		ll sum=ans;
		for(int i=1;i<=n;i++)
		{
			sum+=x[i].val;
			sum-=(i-1)*c;
			ans=min(ans,sum);
		}
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
