#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

namespace TYC
{
    const int MAXN=10010,inf=0x3f3f3f3f;
    int n,k,cnt,ans,root,tot,sum,Head[MAXN];
    int size[MAXN];//子树大小(包括自己)
    int f[MAXN];//以i为根的最大的子树大小
    bool vis[MAXN];//标记处理过的
    int dis[MAXN];//到u的距离
    int len[MAXN];//记录当前处理的路径的长
    
    struct edge
    {
		int to,next,w;
    }E[MAXN*2];

    void add(int u,int v,int w)
    {
		cnt++;
		E[cnt].to=v;
		E[cnt].next=Head[u];
		E[cnt].w=w;
		Head[u]=cnt;
    }

    void insert(int u,int v,int w)
    {
		add(u,v,w),add(v,u,w);
    }

    void find_root(int u,int fa)//找重心(树的重心:所有子树大小均<总点数/2)
    {
		size[u]=1;
		f[u]=0;
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa||vis[v]) continue;
			find_root(v,u);
			size[u]+=size[v];
			f[u]=max(f[u],size[v]);
		}
		f[u]=max(f[u],sum-size[u]);//除了自己子树的,还要算上它父亲子树除了它的点数
		//因为我们要是u变成根,fa也变成了u的儿子
		if(f[u]<f[root]) root=u;
    }

    void dfs(int u,int fa)
    {
		len[++tot]=dis[u];
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(v==fa||vis[v]) continue;
			dis[v]=dis[u]+E[i].w;
			dfs(v,u);
		}
    }

    int cal(int u,int c)//给以u为根的路径都加上一个c的合法路径数
    {
		dis[u]=c;
		tot=0;//数这个子树上的点数
		dfs(u,0);
		sort(len+1,len+1+tot);//使路径长有序
		int tmp=0;
		for(int lt=1,rt=tot;lt<rt;)
		{
			if(len[lt]+len[rt]<=k) tmp+=rt-lt,lt++;
			//若成立,则lt到rt的所有路径长度均<=k,都算上,不包含lt共有(rt-lt)个
			else rt--;
		}
		return tmp;
    }
    
    void solve(int u)
    {
		ans+=cal(u,0);//先算上以u为根所有的<=k的边数
		vis[u]=1;//访问了u,标记
		for(int i=Head[u];i;i=E[i].next)
		{
			int v=E[i].to;
			if(vis[v]) continue;
			ans-=cal(v,E[i].w);//去掉不成立的路径的个数
			sum=size[v];//sum为当前要处理的的总点数
			root=0;
			find_root(v,root);//重新找重心作为根
			solve(root);
		}
    }
    
    void init()
    {
    	cnt=ans=0;
    	memset(Head,0,sizeof(Head));
    	memset(vis,0,sizeof(vis));
    }
   
    void work()
    {
		while(1)
		{
			scanf("%d%d",&n,&k);
			if(n==0) break;
			init();
			int u,v,w;
			for(int i=1;i<n;i++)
			{
				scanf("%d%d%d",&u,&v,&w);
				insert(u,v,w);
			}
			f[0]=inf;
			sum=n;
			root=0;
			find_root(1,0);
			solve(root);
			printf("%d\n",ans);
		}
    }	
}

int main()
{
    TYC::work();
    return 0;
}
