#include<bits/stdc++.h>
using namespace std;

namespace TYC
{
    const int N=60,inf=0x3f3f3f3f;
    int n,s,t,cnt,Head[N],dep[N];
    char ch[N][N];

    struct edge
    {
		int to,next,w;
    }E[N*N*4];

    void add(int u,int v,int w)
    {
		E[++cnt]=(edge){v,Head[u],w};
		Head[u]=cnt;
    }

    void insert(int u,int v,int w)
    {
		add(u,v,w),add(v,u,0);
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

    int Dinic()
    {
		int ans=0;
		while(bfs()) ans+=dfs(s,inf);
		return ans;
    }
    
    int solve(int a1,int a2,int an,int b1,int b2,int bn)
    {
    	cnt=1;
		memset(Head,0,sizeof(Head));
    	insert(s,a1,2*an),insert(s,b1,2*bn);
		insert(a2,t,2*an),insert(b2,t,2*bn);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				if(ch[i][j-1]=='O') insert(i,j,2);
				else if(ch[i][j-1]=='N') insert(i,j,inf);
		}
		return Dinic();
    }
    
    void work()
    {
		while(~scanf("%d",&n))
		{
			s=n+1,t=n+2;
			int a1,a2,an,b1,b2,bn,ans1,ans2;
			scanf("%d%d%d%d%d%d",&a1,&a2,&an,&b1,&b2,&bn);
			a1++,a2++,b1++,b2++;
			for(int i=1;i<=n;i++) scanf("%s",ch[i]);
			ans1=solve(a1,a2,an,b1,b2,bn);//判断是否可以完成
			ans2=solve(a1,a2,an,b2,b1,bn);//判断上一步的流是否为a1->b2,b1->a2
			if(ans1!=2*(an+bn)||ans2!=2*(an+bn)) puts("No");
			else puts("Yes");
		}
    }
}

int main()
{
    TYC::work();
    return 0;
}
