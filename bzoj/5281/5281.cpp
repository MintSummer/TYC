#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=260;
	const ll inf=1e15;
	int n,m,w[N],t[N];
	ll dp[1010],val[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	bool check(int mid)
	{
		for(int i=1;i<=n;i++) 
			val[i]=t[i]-(ll)w[i]*mid;
		for(int i=1;i<=m;i++) dp[i]=-inf;
		dp[0]=0;
		for(int i=1;i<=n;i++)
			for(int j=m;j>=0;j--) 
			{
				int x=min(j+w[i],m);
				dp[x]=max(dp[x],dp[j]+val[i]);
			}
		return dp[m]>0;
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++)
			w[i]=read(),t[i]=read()*1000;
		int l=0,r=1000000,mid,ans;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
