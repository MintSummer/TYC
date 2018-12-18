#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=110;
	
	int n,d,arr[N],x[N],y[N];
	bitset<N> G[N],now,ans,s; 

	inline double sqr(double a) {return a*a;}

	inline double dis(int a,int b)
	{
		return sqrt(sqr(x[a]-x[b])+sqr(y[a]-y[b]));
	}

	void work()
	{
		scanf("%d%d",&n,&d);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&x[i],&y[i]);
			arr[i]=i;
		}	
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(dis(i,j)<=d)
					G[i][j]=G[j][i]=1;
		int T=10000;
		while(T--)
		{
			random_shuffle(arr+1,arr+1+n);
			s.set(),now.reset();
			for(int i=1;i<=n;i++)
				if(s[arr[i]]) now[arr[i]]=1,s&=G[arr[i]];
			if(now.count()>ans.count()) ans=now;
		}
		printf("%d\n",(int)ans.count());
		for(int i=1;i<=n;i++)
			if(ans[i]) printf("%d ",i);
	}
}

int main()
{
	TYC::work();
	return 0;
}#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=110;
	
	int n,d,arr[N],x[N],y[N];
	bitset<N> G[N],now,ans,s; 

	inline double sqr(double a) {return a*a;}

	inline double dis(int a,int b)
	{
		return sqrt(sqr(x[a]-x[b])+sqr(y[a]-y[b]));
	}

	void work()
	{
		scanf("%d%d",&n,&d);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&x[i],&y[i]);
			arr[i]=i;
		}	
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				if(dis(i,j)<=d)
					G[i][j]=G[j][i]=1;
		int T=10000;
		while(T--)
		{
			random_shuffle(arr+1,arr+1+n);
			s.set(),now.reset();
			for(int i=1;i<=n;i++)
				if(s[arr[i]]) now[arr[i]]=1,s&=G[arr[i]];
			if(now.count()>ans.count()) ans=now;
		}
		printf("%d\n",(int)ans.count());
		for(int i=1;i<=n;i++)
			if(ans[i]) printf("%d ",i);
	}
}

int main()
{
	TYC::work();
	return 0;
}
