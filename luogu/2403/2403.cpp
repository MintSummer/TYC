#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	typedef pair<int,int> pa;
	const int dx[9]={0,-1,-1,-1,0,0,1,1,1};
	const int dy[9]={0,-1,0,1,-1,1,-1,0,1};
	const int N=100010;
	map<pa,int> treasure;
	int tot,n,m,cnt,top,scc,dfs_clock;
	int Head[N],dfn[N],st[N],low[N],in[N],belong[N],size[N],h[N],vis[N],deg[N],q[N],dis[N];
	vector<int> node[N];

	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}

	struct Door
	{
		int x,y,opt,id;
	}door[N];

	bool cmprow(const Door &a,const Door &b)
	{
		if(a.x!=b.x) return a.x<b.x;
		if(a.opt==1) return true;
		if(b.opt==1) return false;//将横天门放在前面
		return a.y<b.y;
	}	

	bool cmpline(const Door &a,const Door &b)
	{
		if(a.y!=b.y) return a.y<b.y;
		if(a.opt==2) return true;
		if(b.opt==2) return false;
		return a.x<b.x;
	}

	struct edge
	{
		int to,next;	
	}E[N*50],e[N*50];

	void add(int u,int v)
	{	
		E[++cnt]=(edge){v,Head[u]};
		Head[u]=cnt;
	}

	void add1(int u,int v)
	{
		e[++cnt]=(edge){v,h[u]};
		h[u]=cnt;
	}

	void Tarjan(int u)
	{
		dfn[u]=low[u]=++dfs_clock;
		in[u]=1;
		st[++top]=u;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
			else if(in[v]) low[u]=min(low[u],dfn[v]);
		}
		if(low[u]==dfn[u])
		{
			int x;
			scc++;
			do
			{
				x=st[top--];
				belong[x]=scc;
				size[scc]++;
				in[x]=0;
				node[scc].push_back(x);
			}
			while(x!=u);
		}
	}

	void build()
	{
		cnt=0;
		for(int now=1;now<=scc;now++)
			for(int k=0;k<node[now].size();k++)
			{
				int u=node[now][k];
				for(int i=Head[u];i;i=E[i].next)
				{
					int v=E[i].to;
					if(belong[u]==belong[v]||vis[belong[v]]==now) continue;
				   	vis[belong[v]]=now;
			   		add1(belong[u],belong[v]);   
					deg[belong[v]]++;
				}
			}
	}

	void search()
	{
		int head=1,tail=0;
		for(int i=1;i<=scc;i++) 
			if(!deg[i]) q[++tail]=i,dis[i]=size[i];
		while(head<=tail)
		{
			int u=q[head++];
			for(int i=h[u];i;i=e[i].next)
			{
				int v=e[i].to;
				dis[v]=max(dis[v],dis[u]+size[v]);
				deg[v]--;
				if(!deg[v]) q[++tail]=v;
			}
		}
	}

	void work()
	{
		tot=read(),n=read(),m=read();
		for(int i=1;i<=tot;i++)
		{
			door[i]=(Door){read(),read(),read(),i};
			treasure[pa(door[i].x,door[i].y)]=i;//记下有宝藏的位置,只连有宝藏的地方
		}
		for(int i=1;i<=tot;i++)
			if(door[i].opt==3)
				for(int k=1;k<=8;k++)
				{
					int x=door[i].x+dx[k],y=door[i].y+dy[k];
					if(treasure.count(pa(x,y)))
						add(door[i].id,treasure[pa(x,y)]);
				}//第三种门暴力建边
		sort(door+1,door+1+tot,cmprow);
		int first=1,last=1;//用first和last表示当前这个环的起终点
		for(int i=1;i<=tot;i++)
			if(door[i].x!=door[i+1].x)
			{
				if(first!=last) add(door[last].id,door[first].id);//将环的重点连向起点,构成一个强连通分量(只有一个点的环不连)
				first=last=i+1;//换到下一行后环变了,起终点也要变
			}
			else
			{
				if(door[last].opt==1) add(door[last].id,door[i+1].id);//将这个环连向同行的点
				if(door[i+1].opt==1) last=i+1;//如果i+1也是横向的,就可以扩展环的终点
				if(door[first].opt!=1) first=last=i+1;//如果first都不是横向的,说明这个环不成立,要更新环,指向当前扫到的点
			}
		sort(door+1,door+1+tot,cmpline);
		first=last=1;
		for(int i=1;i<=tot;i++)
			if(door[i].y!=door[i+1].y)
			{
				if(first!=last) add(door[last].id,door[first].id);
				first=last=i+1;
			}
			else
			{
				if(door[last].opt==2) add(door[last].id,door[i+1].id);
				if(door[i+1].opt==2) last=i+1;
				if(door[first].opt!=2) first=last=i+1;
			}
		for(int i=1;i<=tot;i++)
			if(!dfn[i]) Tarjan(i);
		build();
		search();
		int ans=0;
		for(int i=1;i<=scc;i++) 
			ans=max(ans,dis[i]);
		printf("%d\n",ans);
	}
}

int main()
{
	TYC::work();
	return 0;
}
