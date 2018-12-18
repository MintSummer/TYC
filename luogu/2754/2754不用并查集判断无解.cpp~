//不用并查集判断无解 128ms
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

namespace TYC
{
    const int N=1e6+10,inf=0x3f3f3f3f,s=0,t=N-5;
    int n,m,k,p[100],num[100],step[100][100],fa[100];
    int cnt=1,Head[N],dep[N];

    int find(int a)
    {
		return a==fa[a]?a:fa[a]=find(fa[a]);
    }
    
    void connect(int x,int y)
    {
    	x=find(x),y=find(y);
    	if(x!=y) fa[x]=y;
    }

    struct edge
    {
		int to,next,w;
    }E[N*8];

    void insert(int u,int v,int w)
    {
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
		E[++cnt]=(edge){u,Head[v],0};
		Head[v]=cnt;
    }
    
    bool bfs()
    {
        memset(dep,-1,sizeof(dep));
        queue<int> q;
        q.push(s);
        dep[s]=0;
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            for(int i=Head[u];i;i=E[i].next)
            {
                int v=E[i].to;
                if(E[i].w>0&&dep[v]==-1) 
                    dep[v]=dep[u]+1,q.push(v);
            }
        }
        return dep[t]!=-1;
    }

    int dfs(int u,int mn)
    {
        if(u==t) return mn;
        int w,used=0;
        for(int i=Head[u];i;i=E[i].next)
        {
            int v=E[i].to;
            if(E[i].w>0&&dep[v]==dep[u]+1)
            {
                w=dfs(v,min(E[i].w,mn-used));
                used+=w;
                E[i].w-=w,E[i^1].w+=w;
                if(used==mn) return used;
            }
        }
        if(!used) dep[u]=-1;
        return used;
    }

    void work()
    {
		scanf("%d%d%d",&n,&m,&k);
		//for(int i=1;i<=n+2;i++) fa[i]=i;
		int x,y;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&p[i],&num[i]);
			for(int j=0;j<num[i];j++) 
			{
				scanf("%d",&step[i][j]);
				if(step[i][j]==0) step[i][j]=n+1;
				if(step[i][j]==-1) step[i][j]=n+2;
				//if(j!=1) connect(step[i][j-1],step[i][j]);
			}
		}
		//if(find(n+1)!=find(n+2)) {puts("0");return;}
		int now=0;
		for(int ans=1;ans<=500;ans++)
		{
			insert(s,(ans-1)*(n+1)+n+1,inf);//源点向上一秒的地球连边,容量inf
			for(int i=1;i<=m;i++)//每艘船从上一位置向下一位置连边,容量为船的容量
			{
				x=(ans-1)%num[i],y=ans%num[i];
				if(step[i][x]==n+2) x=t;
				else x=(ans-1)*(n+1)+step[i][x];
				if(step[i][y]==n+2) y=t;
				else y=ans*(n+1)+step[i][y];
				insert(x,y,p[i]);
			}
			
			while(bfs()) now+=dfs(s,inf);
			if(now>=k) {printf("%d\n",ans);return;}
			for(int i=1;i<=n+1;i++) insert((ans-1)*(n+1)+i,ans*(n+1)+i,inf);//不坐车等着的,位置不变,时间+1
		}
		puts("0");
    }
}

int main()
{
    TYC::work();
    return 0;
}
