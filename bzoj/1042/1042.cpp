#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

namespace TYC
{
	typedef long long ll;
	int q,s,a[8],d[8],t[8];
	ll dp[100010];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	void work()
	{
		a[1]=read(),a[2]=read(),a[3]=read(),a[4]=read();
		dp[0]=1;
		for(int i=1;i<=4;i++)
			for(int j=1;j<=100000;j++)
				dp[j]+=(j>=a[i]?dp[j-a[i]]:0);
		q=read();
		while(q--)
		{
			d[1]=read(),d[2]=read(),d[3]=read(),d[4]=read();
			s=read();
			ll sum=0;
			for(int i=1;i<=4;i++) 
				t[i]=a[i]*(d[i]+1),sum+=t[i];
			ll ans=dp[s];
			for(int i=1;i<=4;i++)
				if(s>=t[i]) ans-=dp[s-t[i]];
			for(int i=1;i<=3;i++)
				for(int j=i+1;j<=4;j++)
					if(s>=t[i]+t[j]) ans+=dp[s-t[i]-t[j]];
			for(int i=1;i<=4;i++)
				if(s>=sum-t[i]) ans-=dp[s-(sum-t[i])];
			if(s>=sum) ans+=dp[s-sum];
			printf("%lld\n",ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}
