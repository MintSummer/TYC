#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=5e4+10;
	const int inf=0x3f3f3f3f;

	int n,m,top,block,blocknumber,Block,BlockNumber;
	int Head[N],val[N],dep[N],fa[N],belong[N],sta[N],Belong[N],End[N],Mex[N],Cnt[N],Visit[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	inline void write(int x)
	{
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

	struct Ques
	{
		int u,v,id,c;
		bool operator < (const Ques &t) const
		{
			if(belong[u]!=belong[t.u]) return belong[u]<belong[t.u];
			else if(v!=t.v) return v<t.v;
			else return c<t.c;
		}
	}q[N];

	struct Modify
	{
		int x,val,id;
	}c[N];

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
	
	namespace RMQ
	{
		int tot,st[N<<1][18],Log[N<<1],fir[N];

		inline int Min(int x,int y)
		{
			return dep[x]<dep[y]?x:y;
		}

		void Init()
		{
			for(int i=0;i<=17;i++)
				for(int j=(1<<i);j<min(tot+1,(1<<(i+1)));j++) Log[j]=i;
			for(int i=1;i<=17;i++)
				for(int j=1;j+(1<<i)-1<=tot;j++)
					st[j][i]=Min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
		}

		inline int LCA(int u,int v)
		{
			int l=fir[u],r=fir[v];
			if(l>r) swap(l,r);
			int k=Log[r-l+1];
			return Min(st[l][k],st[r-(1<<k)+1][k]);
		}
	}
	
	using namespace RMQ;

	void dfs(int u,int f)
	{
		int bottom=top;
		fa[u]=f;
		dep[u]=dep[f]+1;
		st[++tot][0]=u;
		fir[u]=tot;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==f) continue;
			dfs(v,u);
			st[++tot][0]=u;
			if(top-bottom>=block)
			{
				++blocknumber;
				while(top>bottom)
					belong[sta[top--]]=blocknumber;
			}
		}
		sta[++top]=u;
	}

	void init()
	{
		block=pow(n,0.66667);
		dfs(1,0);
		if(top>0)
		{
			++blocknumber;
			while(top) 
				belong[sta[top--]]=blocknumber;
		}
		Init();
		Block=sqrt(n);
		for(int i=0;i<=n;i++)
			Belong[i]=i/Block+1;
		BlockNumber=Belong[n];
		End[0]=-1;
		for(int i=1;i<=BlockNumber;i++)
		{
			End[i]=End[i-1]+Block;
			Mex[i]=End[i-1]+1;
		}
		End[BlockNumber]=n;
	}

	inline void change(int x)
	{
		if(val[x]<=n)
		{
			int b=Belong[val[x]];
			if(!Visit[x])
			{
				Cnt[val[x]]++;
				if(val[x]==Mex[b])
				{
					int mn=inf;
					for(int i=End[b-1]+1;i<=End[b];i++)
						if(!Cnt[i]) {mn=i;break;}
					Mex[b]=mn;
				}
			}
			else
			{
				Cnt[val[x]]--;
				if(!Cnt[val[x]]&&Mex[b]>val[x])
					Mex[b]=val[x];
			}
		}		
		Visit[x]^=1;
	}

	void solve(int u,int v)
	{
		while(u!=v)
		{
			if(dep[u]<dep[v]) swap(u,v);
			change(u),u=fa[u];
		}
	}

	inline void modify(int id)
	{
		int x=c[id].x;
		if(Visit[x])
		{
			if(val[x]<=n)
			{
				Cnt[val[x]]--;
				int b=Belong[val[x]];
				if(!Cnt[val[x]]&&Mex[b]>val[x])
					Mex[b]=val[x];
			}
			int now=c[id].val;
			if(now<=n)
			{
				Cnt[now]++;
				int b=Belong[now];
				if(Mex[b]==now)
				{
					int mn=inf;
					for(int i=End[b-1]+1;i<=End[b];i++)
						if(!Cnt[i]) {mn=i;break;}
					Mex[b]=mn;
				}
			}
		}
		swap(c[id].val,val[x]);
	}

	inline int query()
	{
		for(int i=1;i<=BlockNumber;i++)
			if(Mex[i]!=inf) return Mex[i];
		return n+1;
	}

	void work()
	{
		n=read(),m=read();
		for(int i=1;i<=n;i++) val[i]=read();
		for(int i=1;i<n;i++)
		{
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		init();
		int totq=0,totc=0;
		for(int i=1;i<=m;i++)
		{
			int opt=read(),x=read(),y=read();
			if(opt==0) totc++,c[totc]=(Modify){x,y,totc};
			else
			{	
				if(belong[x]>belong[y]) swap(x,y);
				totq++,q[totq]=(Ques){x,y,totq,totc};
			}
		}
		static int ans[N];
		sort(q+1,q+1+totq);
		int l=1,r=1,ch=0;
		for(int i=1;i<=totq;i++)
		{
			solve(l,q[i].u),l=q[i].u;
			solve(r,q[i].v),r=q[i].v;
			while(ch<q[i].c) modify(++ch);
			while(ch>q[i].c) modify(ch--);
			change(LCA(q[i].u,q[i].v));
			ans[q[i].id]=query();
			change(LCA(q[i].u,q[i].v));
		}
		for(int i=1;i<=totq;i++) write(ans[i]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
