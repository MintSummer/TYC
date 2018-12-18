#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int dx[5]={0,0,0,-1,1},dy[5]={0,-1,1,0,0};
	const int N=15*15*2+10,inf=0x3f3f3f3f;
	int n,m,cnt=1,tot,s,t,Head[N],num[20][20],dis[N],vis[N],pre[N];

	struct edge
	{
		int to,next,w,c;
	}E[N*N*4];

	void insert(int u,int v,int w,int c)
	{
		E[++cnt]=(edge){v,Head[u],w,c};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],0,-c};
		Head[v]=cnt;
	}

	bool spfa()
	{
		memset(pre,0,sizeof(pre));
		memset(dis,inf,sizeof(dis));
		queue<int> q;
		q.push(s);
		dis[s]=0,vis[s]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			vis[u]=0;
			for(int i=Head[u];i;i=E[i].next)
			{
				int v=E[i].to;
				if(E[i].w&&dis[v]>dis[u]+E[i].c)
				{
					dis[v]=dis[u]+E[i].c;
					pre[v]=i;
					if(!vis[v]) vis[v]=1,q.push(v);
				}
			}
		}
		return dis[t]!=inf;
	}

	int mcmf()
	{
		int ans=0;
		while(spfa())
		{
			int mn=inf;
			for(int i=pre[t];i;i=pre[E[i^1].to])
				mn=min(E[i].w,mn);
			for(int i=pre[t];i;i=pre[E[i^1].to])
				E[i].w-=mn,E[i^1].w+=mn;
			ans+=dis[t]*mn;
		}
		return ans;
	}

	void work()
	{
		scanf("%d%d",&n,&m);
		s=n*m*2+1,t=s+1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				num[i][j]=++tot;
				insert(s,tot,1,0);
				insert(tot+n*m,t,1,0);
			}
		char ch[20];
		for(int i=1;i<=n;i++)
		{
			scanf("%s",ch);
			for(int j=1;j<=m;j++)
			{
				int id;
				switch(ch[j-1])
				{
					case 'L': id=1;break;
					case 'R': id=2;break;
					case 'U': id=3;break;
					case 'D': id=4;break;
				}
				for(int k=1;k<=4;k++)
				{
					int x=i+dx[k],y=j+dy[k];
					if(x==0) x=n;
					else if(x==n+1) x=1;
					if(y==0) y=m;
					else if(y==m+1) y=1;
					if(id==k) insert(num[i][j],num[x][y]+n*m,1,0);
					else insert(num[i][j],num[x][y]+n*m,1,1);
				}
			}
		}
		printf("%d\n",mcmf());
	}
}

int main()
{
	TYC::work();
	return 0;
}
