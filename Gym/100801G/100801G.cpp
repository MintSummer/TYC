#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=1e5+10;

	int n,m,k,Head[N],deg[N];

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
	}

	struct edge
	{
		int to,next;
	}E[N<<1];

	struct Edge
	{
		int u,v;
	}e[N];

	inline void add(int u,int v)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt; 
	}

	void toposort()
	{
		static priority_queue<int> q2;
		static priority_queue<int,vector<int>,greater<int> > q1;
		static int list[N];
		for(int i=1;i<=n;i++)
			if(!deg[i]) q1.push(i);
		int now=0;
		for(int num=1;num<=n;num++)		
		{
			while(k&&!q1.empty())
			{
				int x=q1.top();
				if(q1.size()==1&&(+q2.empty()||x>q2.top())) break;
				q2.push(x),q1.pop(),k--;
			}
			int u;
			if(!q1.empty())
				u=q1.top(),q1.pop();
			else
			{
				u=q2.top(),q2.pop();
				e[++now]=(Edge){list[num-1],u};
			}
			list[num]=u;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				deg[v]--;
				if(!deg[v]) q1.push(v);
			}
		}
		for(int i=1;i<=n;i++)
			write(list[i]),putchar(' ');
		putchar('\n');
		write(now),putchar('\n');
		for(int i=1;i<=now;i++)
		{
			write(e[i].u),putchar(' ');
			write(e[i].v),putchar('\n');
		}
	}

	void work()
	{
		n=read(),m=read(),k=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			add(u,v),deg[v]++;
		}
		toposort();
	}
}

int main()
{
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	TYC::work();
	return 0;
}
