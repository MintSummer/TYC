#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef pair<int,int> pa;
	const int N=810;
	int n,m,k,a[N],b[N],c[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(ll x)
	{
		if(x<0) putchar('-'),x=-x;
		if(!x) putchar('0');
		else
		{
			int len=0;
			static int bask[50];
			while(x) bask[++len]=x%10,x/=10;
			for(;len;len--) putchar('0'+bask[len]);
		}
		putchar(' ');
	}

	struct cmp
	{
		bool operator () (const pa &x, const pa &y)
		{
			return a[x.first]+b[x.second]>a[y.first]+b[y.second];
		}
	};

	void solve(int A,int B)
	{
		static bool vis[N][N];
		memset(vis,false,sizeof(vis));
		memcpy(a,c,sizeof(int[A+1]));
		sort(a+1,a+1+A);
		sort(b+1,b+1+B);	
		priority_queue<pa,vector<pa>,cmp> q;
		q.push(pa(1,1));
		for(int i=1;i<=k;i++)
		{
			int x=q.top().first,y=q.top().second;
			c[i]=a[x]+b[y];q.pop();
			if(x<A&&!vis[x+1][y]) 
				q.push(pa(x+1,y)),vis[x+1][y]=true;
			if(y<B&&!vis[x][y+1]) 
				q.push(pa(x,y+1)),vis[x][y+1]=true;
		}
	}

	void work()
	{
		n=read(),m=read(),k=read();
		for(int i=1;i<=m;i++) c[i]=read();
		for(int i=1;i<=m;i++) b[i]=read();
		solve(m,m);
		for(int i=3;i<=n;i++)
		{
			for(int j=1;j<=m;j++) b[j]=read();
			solve(k,m);
		}
		for(int i=1;i<=k;i++) write(c[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
