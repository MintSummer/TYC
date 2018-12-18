#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<queue>
#include<string>
#include<cmath>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	typedef long long ll;
	const int N=1614501;
	const ll p=1e9+7;
	
	int Length,Head[N],id[N],pos[32800];

	inline int read()
	{
		int x=0;char f=0,ch=getchar();
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
			static char bask[15];
			while(x) bask[++len]=x%10+'0',x/=10;
			for(;len;len--) putchar(bask[len]);
		}
		putchar('\n');
	}

	struct edge
	{
		int to,next;
	}E[N];

	inline void add(const int &u,const int &v)
	{
		static int tot=0;
		E[++tot]=(edge){v,Head[u]};
		Head[u]=tot;
	}

	namespace AC
	{
		int cnt,son[N][26],val[N];

		void insert(char ch)
		{
			int now=0;
			for(;isalpha(ch);ch=getchar())
			{
				int c=ch-'a';
				if(!son[now][c]) 
					son[now][c]=++cnt,val[cnt]=((ll)val[now]*26+c)%p;
				now=son[now][c];
				id[++Length]=now;
			}
		}

		void get_fail()
		{
			static queue<pa> q;
			for(int i=0;i<26;i++)
				if(son[0][i]) q.push(pa(son[0][i],0));
			while(!q.empty())
			{
				int now=q.front().first,f=q.front().second;
				q.pop();
				add(f,now);
				for(int i=0;i<26;i++)
				{
					int x=son[now][i];
					if(!x) son[now][i]=son[f][i];
					else q.push(pa(x,son[f][i]));
				}
			}
		}
	}

	int h[N],fa[N],lca[N];
	bool vis[N];

	struct query
	{
		int to,nxt,id;
	}q[N+400000];

	int find(const int &x)
	{
		return x==fa[x]?x:fa[x]=find(fa[x]);
	}

	void Tarjan(const int &u)
	{
		fa[u]=u;
		for(int i=Head[u];i;i=E[i].next)
		{
			Tarjan(E[i].to);
			fa[find(E[i].to)]=u;
		}
		vis[u]=1;
		for(int i=h[u];i;i=q[i].nxt)
			if(vis[q[i].to]) lca[q[i].id]=find(q[i].to);
	}
	
	void work()
	{
		int n=read();
		char ch;
		for(int i=1;i<=n;i++)
		{
			do ch=getchar(); while(!isalpha(ch));
			pos[i]=Length;
			AC::insert(ch);
		}
		AC::get_fail();
		int m=read(),t=0;
		for(int kase=1;kase<=m;kase++)
		{
			int a=read(),b=read(),c=read(),d=read();
			int u=id[pos[a]+b],v=id[pos[c]+d];
			q[++t]=(query){v,h[u],kase},h[u]=t;
			q[++t]=(query){u,h[v],kase},h[v]=t;
		}
		Tarjan(0);
		for(int i=1;i<=m;i++) write(AC::val[lca[i]]);
	}
}

int main()
{
	TYC::work();
	return 0;
}
