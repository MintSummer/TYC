#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	typedef long double ld;

	const int N=2e5+10;
	const int inf=0x3f3f3f3f;
	const ld eps=1e-6;

	int n,Head[N],fa[N];
	ll p[N],q[N],lim[N],dp[N],dis[N];

	inline ll read()
	{
		ll x=0,f=0;char ch=getchar();
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
		putchar('\n');
	}

	struct edge
	{
		int to,next;
		ll w;
	}E[N];

	inline void add(int u,int v,ll w)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
	}

	namespace BruteForce // 30pts  
	{
		int id[N];

		void dfs(int u)
		{
			static int tim=0;
			id[++tim]=u;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				dis[v]=dis[u]+E[i].w;
				fa[v]=u;
				dfs(v);
			}
		}

		void work()
		{
			dfs(1);
			for(int i=2;i<=n;i++)
			{
				int now=id[i];
				for(int f=fa[now];f;f=fa[f])
				{
					int len=dis[now]-dis[f];
					if(len>lim[now]) break;
					dp[now]=min(dp[now],dp[f]+(ll)len*p[now]+q[now]);
				}
			}
		}
	}

	namespace NoLimit // 40pts
	{
		typedef pair<int,int> pa;
		int top,sta[N],OperTop;
		pa opt[N*10];

		inline ld K(int a,int b)
		{
			if(dis[b]-dis[a]==0) return 1e20;
			return (ld)(dp[b]-dp[a])/(dis[b]-dis[a]);
		}

		inline ll F(int from,int to)
		{
			return dp[from]+(dis[to]-dis[from])*p[to]+q[to];
		}

		inline void get_ans(int now)
		{
			int l=2,r=top,mid,ans=1;
			while(l<=r)
			{
				mid=(l+r)>>1;
				if(K(sta[mid-1],sta[mid])<=p[now]) ans=mid,l=mid+1;
				else r=mid-1;
			}
			dp[now]=F(sta[ans],now);
		}

		void dfs(int u)
		{
			int bottom=OperTop,last=top;
			if(u!=1)
			{
				get_ans(u);
				while(top>1&&K(sta[top-1],sta[top])>K(sta[top],u)) 
					opt[++OperTop]=pa(top,sta[top]),top--;
				sta[++top]=u;
			}
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				dis[v]=dis[u]+E[i].w;
				dfs(v);
			}
			while(OperTop>bottom)
				sta[opt[OperTop].first]=opt[OperTop].second,OperTop--;
			top=last;
		}
		
		void work()
		{
			sta[++top]=1;
			dfs(1);
		}
	}

	namespace Accpeted
	{
		int rot,tot,top,Size,size[N],mx[N],vis[N],list[N],sta[N];

		void getdis(int u)
		{
			for(int i=Head[u];i;i=E[i].next)
			{
				dis[E[i].to]=dis[u]+E[i].w;
				getdis(E[i].to);
			}
		}

		void get_root(int u)
		{
			size[u]=1;
			mx[u]=0;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(vis[v]) continue;
				get_root(v);
				size[u]+=size[v];
				mx[u]=max(mx[u],size[v]);
			}
			mx[u]=max(mx[u],Size-size[u]);
			if(mx[u]<=mx[rot]) rot=u;
		}

		void dfs(int u)
		{
			list[++tot]=u;
			for(int i=Head[u];i;i=E[i].next) 
				if(!vis[E[i].to]) dfs(E[i].to);
		}

		bool cmp(const int &x,const int &y)
		{
			return dis[x]-lim[x]>dis[y]-lim[y];
		}
		
		inline ld K(int a,int b)
		{
			if(dis[b]-dis[a]==0) return 1e20;
			return (ld)(dp[b]-dp[a])/(dis[b]-dis[a]);
		}

		inline ll F(int from,int to)
		{
			return dp[from]+(dis[to]-dis[from])*p[to]+q[to];
		}

		inline void insert(int u)
		{
			while(top>1&&K(sta[top-1],sta[top])<K(sta[top],u)) top--;
				sta[++top]=u;
		}

		inline void get_ans(int now)
		{
			int l=1,r=top-1,mid,ans=top;
			while(l<=r)
			{
				mid=(l+r)>>1;
				if(K(sta[mid+1],sta[mid])<=p[now]) ans=mid,r=mid-1;
				else l=mid+1;
			}
			dp[now]=min(dp[now],F(sta[ans],now));
		}

		void solve(int now,int sz)
		{
			if(sz==1) return;
			rot=0,Size=sz;
			get_root(now);
			int t=rot;
			for(int i=Head[t];i;i=E[i].next) 
				vis[E[i].to]=1,Size-=size[E[i].to];
			solve(now,Size);
			tot=top=0;
			for(int i=Head[t];i;i=E[i].next) dfs(E[i].to);
			sort(list+1,list+1+tot,cmp);
			for(int i=1,f=t;i<=tot;i++)
			{
				int x=list[i];
				while(f!=fa[now]&&dis[x]-dis[f]<=lim[x]) 
					insert(f),f=fa[f];
				if(top) get_ans(x);
			}
			for(int i=Head[t];i;i=E[i].next) 
				solve(E[i].to,size[E[i].to]);
		}	

		void work()
		{
			getdis(1);
			mx[0]=inf;
			solve(1,n);
		}
	}

	void work()
	{
		n=read();
		int t=read();
		for(int i=2;i<=n;i++)
		{
			fa[i]=read();
			add(fa[i],i,read());
			p[i]=read(),q[i]=read(),lim[i]=read();
			dp[i]=1LL<<61;
		}
		if(n<=2e3) BruteForce::work();
		else if(t<2) NoLimit::work(); 
		else Accpeted::work();
		for(int i=2;i<=n;i++) write(dp[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
