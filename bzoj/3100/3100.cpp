#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1000010,inf=0x3f3f3f3f;
	int n,a[N],vis[N];
	ll sum[N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	inline int calc(int len)
	{
		return (len+1)*len/2;
	}
	
	void work()
	{
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		for(int i=1;i<=n;i++) sum[i]=a[i]+sum[i-1];
		int tim=0,ans=0;
		for(int i=1;i<=n;i++) if(a[i]==1)
		{
			tim++;
			for(int j=i;j<=n;j++)
			{
				if(vis[a[j]]==tim) break;
				vis[a[j]]=tim;
				if(sum[j]-sum[i-1]==calc(j-i+1))
					ans=max(ans,j-i+1);
			}
		}
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
} 
