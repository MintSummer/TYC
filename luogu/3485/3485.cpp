#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N=410,inf=0x3f3f3f3f;
	int n,m,Head[N],f[N][N],g[N][N][26];
	
	inline int read()
	{
		int x=0,f=0;char ch=getchar();
		while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
		while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
		return f?-x:x;
	}
	
	struct edge
	{
		int to,next,w;
	}E[120010];
	
	inline void add(int u, int v,int c)
	{
		static int cnt=0;
		E[++cnt]=(edge){v,Head[u],c};
		Head[u]=cnt;
	}
	
	struct node
	{
		int x,y,c;
	}lf[N][N],lg[N][N][26];
	vector<node> G[N];
	
	void bfs()
	{
		static queue<node> q;
		for(int i=1;i<=n;i++)
			f[i][i]=0,q.push((node){i,i,-1});
		for(int i=1;i<=n;i++)
			for(int j=Head[i];j;j=E[j].next)
			{
				int k=E[j].to;
				f[i][k]=1;
				lf[i][k]=(node){i,k,E[j].w};
				q.push((node){i,k,-1});
			}
		while(!q.empty())
		{
			node now=q.front();
			q.pop();
			int x=now.x,y=now.y;
			if(now.c==-1)
			{
				for(int i=Head[y];i;i=E[i].next)
				{
					int z=E[i].to,c=E[i].w;
					if(g[x][z][c]>f[x][y]+1)
					{
						g[x][z][c]=f[x][y]+1;
						lg[x][z][c]=(node){y,z,c};
						q.push((node){x,z,c});
					}
				}
			}
			else
			{
				for(int i=0,sz=G[x].size();i<sz;i++)
				{
					int z=G[x][i].y,c=G[x][i].c;
					if(c!=now.c) continue;
					if(f[z][y]>g[x][y][c]+1)
					{
						f[z][y]=g[x][y][c]+1;
						lf[z][y]=(node){x,z,c};
						q.push((node){z,y,-1});
					} 
				}
			}
		}
	}
	
	void print(int s,int t)
	{
		static int ans[N];
		int L=1,R=f[s][t],len=f[s][t],ch=-1,mid=len/2,tag=(len&1);
		while(L<=mid)
		{
			ans[L++]=ans[R--]=ch=lf[s][t].c;
			s=lf[s][t].x;
			t=lg[s][t][ch].x;
		}
		if(tag) ans[L++]=lf[s][t].c;
		for(int i=1;i<=len;i++)
			printf("%c",ans[i]+'a');
		puts("");
	}
	
	void work()
	{
		n=read(),m=read();
		char ch;
		memset(f,inf,sizeof(f));
		memset(g,inf,sizeof(g));
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			do ch=getchar(); while(!isalpha(ch));
			add(u,v,ch-'a');
			G[v].push_back((node){v,u,ch-'a'});
		}
		bfs();
		int d=read(),a=read(),b;
		for(int i=1;i<d;i++)
		{
			b=read();
			if(f[a][b]==inf) puts("-1");
			else 
			{
				printf("%d ",f[a][b]);
				print(a,b);
			}
			swap(a,b);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}

