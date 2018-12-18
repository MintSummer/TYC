#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef long long ll;
	const int N=50010;

	int n,m,key,top,block,blocknumber,dfstim;
	int Head[N],tim[N],fa[N],dep[N],dfn[N],belong[N],sta[N],real[N],vis[N];
	ll ans,Ans[N<<1];

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
		putchar('\n');
	}

	struct edge
	{
		int to,next;
	}E[N<<1];

	inline void add(int u,int v)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	struct ques
	{
		int u,v,id;
		ques(){}
		ques(int _u,int _v,int _id):u(_u),v(_v),id(_id)
		{
			if(belong[u]>belong[v]) swap(u,v);
		}
		bool operator < (const ques &t)
		{
			return belong[u]==belong[t.u]?dfn[v]<dfn[t.v]:belong[u]<belong[t.u];
		}
	}q[N<<1];

	inline int Mod(int x) {return x>=n?x-n:x;}

	namespace RMQ
	{
		int tot,Log[N<<1],st[18][N<<1],fir[N];
		
		inline int Min(int x,int y)
		{
			return dep[x]<dep[y]?x:y;
		}

		void init()
		{
			for(int i=1;i<=17;i++)
				for(int j=(1<<i);j<min(tot+1,(1<<(i+1)));j++) Log[j]=i;
			for(int i=1;i<=17;i++)
				for(int j=1;j+(1<<i)-1<=tot;j++)
					st[i][j]=Min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
		}

		inline int LCA(int u,int v)
		{
			int l=fir[u],r=fir[v];
			if(l>r) swap(l,r);
			int k=Log[r-l+1];
			return Min(st[k][l],st[k][r-(1<<k)+1]);
		}
	}
	using RMQ::LCA;

	void dfs(int u,int f)
	{
		int bottom=top;
		fa[u]=f;
		dep[u]=dep[f]+1;
		RMQ::st[0][++RMQ::tot]=u;
		RMQ::fir[u]=RMQ::tot;
		dfn[u]=++dfstim;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs(v,u);
			RMQ::st[0][++RMQ::tot]=u;
			if(top-bottom>=block)
			{
				blocknumber++;
				while(top>bottom)
					belong[sta[top--]]=blocknumber;
			}
		}
		sta[++top]=u;
	}

	inline void init()
	{
		sort(real+1,real+1+n);
		int num=unique(real+1,real+1+n)-real-1;
		for(int i=1;i<=n;i++)
			tim[i]=lower_bound(real+1,real+1+num,tim[i])-real;
		
		block=sqrt(n);
		dfs(1,0);
		if(top)
		{
			blocknumber++;
			while(top) 
				belong[sta[top--]]=blocknumber;
		}
		RMQ::init();
	}

	namespace BitTree
	{
		ll num[N],sum[N];

		inline int lowbit(int x) {return x&(-x);}

		inline ll add(int x,int type,int val)
		{
			for(;x<=n;x+=lowbit(x)) 
				num[x]+=type,sum[x]+=val;
		}
		
		inline ll q_sum(int x)
		{
			ll t=0;
			for(;x;x-=lowbit(x)) t+=sum[x];
			return t;
		}

		inline ll q_num(int x)
		{
			ll t=0;
			for(;x;x-=lowbit(x)) t+=num[x];
			return t;
		}
	}
	using namespace BitTree;

	inline void change(int x)
	{
		ll tmp=q_sum(x);
		tmp+=(ll)(q_num(n-x)-q_num(x))*real[tim[x]];
		tmp+=real[tim[x]];
		if(!vis[x]) ans+=tmp,add(tim[x],1,real[tim[x]]);
		else ans-=tmp,add(tim[x],-1,-real[tim[x]]);
		vis[x]^=1;
	}

	void solve(int u,int v)
	{
		while(u!=v)
		{
			if(dep[u]<dep[v]) swap(u,v);
			change(u);
			u=fa[u];
		}
	}

	void work()
	{
		n=read(),m=read(),key=read();
		for(int i=1;i<=n;i++) real[i]=tim[i]=read();
		for(int i=1;i<=n;i++) add(read(),i);
		int water=1,tot=0;
		char ch;
		for(int i=0;i<m;i++)
		{
			do ch=getchar(); while(!isalpha(ch));
			if(ch=='C') water=read();
			else
			{
				int x=read();
				++tot,q[tot]=ques(water,x,tot);
				++tot,q[tot]=ques(water,Mod(x+key)+1,tot);
			}
		}
		init();
		sort(q+1,q+1+tot);
		int l=1,r=1;
		for(int i=1;i<=tot;i++)
		{
			solve(l,q[i].u),l=q[i].u;
			solve(r,q[i].v),r=q[i].v;
			int lca=LCA(q[i].u,q[i].v);
			change(lca);
			Ans[q[i].id]=ans;
			change(lca);
		}
		ll last=0;
		for(int i=1;i<=tot;i+=2)
			if(last&1) write(Ans[i+1]);
			else write(Ans[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
