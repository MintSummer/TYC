#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=500010;
	const ll inf=LLONG_MAX;
	
	int n,m,flag[N];
	ll ans,arr[N],bin[70],sum[N];

	inline ll read()
	{
		ll x=0;int f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{
		n=read(),m=read();
		bin[0]=1;
		for(int i=1;i<=60;i++) bin[i]=bin[i-1]<<1;
		for(int i=1;i<=n;i++) 
			arr[i]=read(),sum[i]=sum[i-1]^arr[i]; 
		for(int i=60;i>=0;i--)
		{
			int cnt=0;
			for(int j=1;j<=n;j++)
				if(!flag[j]&&(sum[j]&bin[i])==0) cnt++;
			if((sum[n]&bin[i])!=0||cnt<m) ans+=bin[i];
			else for(int j=1;j<=n;j++) 
				if((sum[j]&bin[i])!=0) flag[j]=1;
		}
		printf("%lld\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
