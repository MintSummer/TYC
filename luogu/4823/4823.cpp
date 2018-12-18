#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=2010;
	int n,height,ans,a[N],b[N],list[N],f[N];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	bool cmp(const int &x,const int &y)
	{
		return a[x]+b[x]<a[y]+b[y];
	}
	
	void work()
	{
		n=read();
		int sum=0,ans=0;
		for(int i=1;i<=n;i++) 	
		{
			a[i]=read(),b[i]=read();
			list[i]=i;
			sum+=a[i];
		}
		height=read();
		sort(list+1,list+1+n,cmp);
		memset(f,-1,sizeof(f));
		f[0]=sum;
		for(int i=1;i<=n;i++)
		{
			int now=list[i];
			for(int j=ans;j>=0;j--)
			{
				if(f[j]+b[now]>=height) 
					f[j+1]=max(f[j+1],f[j]-a[now]);
				if(f[ans+1]>=0) ans++;
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
