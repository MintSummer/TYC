#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=1e5+10;

	int n,dis;
	ll sum[N];
	double f[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{
		n=read(),dis=read();
		double ans=0.0;
		for(int i=1;i<=n;i++)
		{
			sum[i]=read()+sum[i-1];
			int start=read();
			for(int j=1;j<=i;j++)
				f[i]=max(f[i],(double)(sum[i]-sum[j-1])/(dis*(i-j)+start));
			ans+=f[i];
		}
		printf("%.0lf\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
