#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=2010;
	const int inf=0x3f3f3f3f;

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct node
	{
		int p,val;
		bool operator < (const node &t) const
		{
			return p!=t.p?p>t.p:val>t.val;
		}
	}arr[N];

	void work()
	{
		int n=read();
		for(int i=1;i<=n;i++) 
			arr[i]=(node){read(),read()};
		sort(arr+1,arr+1+n);
		static int dp[N][N];
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n+1;j++) dp[i][j]=-inf;
		dp[0][1]=0;
		for(int i=1;i<=n;i++)
			for(int j=n;j>=0;j--)
				dp[i][j]=max(dp[i-1][j],dp[i-1][max(j-arr[i].p,0)+1]+arr[i].val);
		int ans=0;
		for(int i=0;i<=n;i++) ans=max(ans,dp[n][i]);
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
