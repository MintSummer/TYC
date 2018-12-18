#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1e5+10;

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	void work()
	{
		int n=read(),b=read(),ans=0,pos=0;
		static int sum[N],arr[N],L[N<<1],R[N<<1];
		for(int i=1;i<=n;i++) 
		{
			int x=read();
			if(x>b) arr[i]=1;
			else if(x<b) arr[i]=-1;
			else arr[i]=0,pos=i;
		}
		for(int i=pos;i;i--) 
			sum[i]=sum[i+1]+arr[i],L[sum[i]+n]++;
		memset(sum,0,sizeof(int[pos+1]));
		for(int i=pos;i<=n;i++) 
			sum[i]=sum[i-1]+arr[i],R[n-sum[i]]++;
		for(int i=1;i<=n<<1;i++) ans+=L[i]*R[i];
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
