#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const ll p=1e9;
	const int N=500000;

	int n,Log[N];
	ll ans,arr[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct RMQ
	{
		int st[21][N];

		inline int minn(int x,int y) {return arr[x]<arr[y]?x:y;}
		inline int maxx(int x,int y) {return arr[x]>arr[y]?x:y;}

		void init(const int type)
		{
			for(int i=1;i<=n;i++) st[0][i]=0;
			for(int i=1;(1<<i)<=n;i++)
				for(int j=1;j+(1<<i)-1<=n;j++)
					if(type) st[i][j]=minn(st[i-1][j],st[i-1][j+(1<<i)]);
					else st[i][j]=maxx(st[i-1][j],st[i-1][j+(1<<i)]);
		}

		inline int query(int l,int r,const int type)
		{
			int k=Log[r-l+1],a=st[k][l],b=st[k][r-(1<<l)+1];
			return type?max(a,b):min(a,b);
		}
	}Min,Max;

	void CDQ(int l,int r,)
	{
		if(l==r) {ans=(ans+(arr[l]*arr[l]%p))%p;return;}
		int mid=(l+r)>>1;
		CDQ(l,mid),CDQ(mid+1,r);
		int t=mid+1,tot=0;
		static int list[N];
		while(t<=r)
		{

		}
		for(int i=l;i<=mid;i++)
		{
			if(Min.query(i,mid,0)<=Max.query(mid+1,r,1))
			{
				
			}
yyy
	}

	void work()
	{
		n=read();
		for(int i=1;i<=n;i++) arr[i]=read();
		for(int i=1;(1<<i)<=n;i++)
			for(int j=(1<<i),t=min(1<<(i+1),n+1);j<t;j++) Log[j]=i;
		Min.init(0),Max.init(1);
		CDQ(1,n);
	}
}

int main()
{
	TYC::work();
	return 0;
}
